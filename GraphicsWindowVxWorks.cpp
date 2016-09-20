/*
 * GraphicsWindowVxWorks.cpp
 *
 *  Created on: 2016-8-28
 *      Author: jinping
 */

#include "GraphicsWindowVxWorks.h"

/*
 * Default constructor
 */
GraphicsWindowVxWorks::GraphicsWindowVxWorks(osg::GraphicsContext::Traits* traits)
:_realized(false),
 _valid(false),
_initialized(false)
{
	_traits = traits;
	f_attribs[0]=  EGL_BUFFER_SIZE;
	f_attribs[1]=  32;
	f_attribs[2]= EGL_DEPTH_SIZE;
	f_attribs[3]=  24;
	f_attribs[4]=  EGL_NONE;
	
	 f_dispMode.cardId = DISPLAY_CARD_ID;
	 f_dispMode.outputHead = DISPLAY_SCREEN_HEAD; 
	 f_dispMode.outputType = DISPLAY_OUTPUT_TYPE;
	 f_dispMode.xResolution = DISPLAY_WIDTH;
	 f_dispMode.yResolution = DISPLAY_HEIGHT;
	 f_dispMode.refreshRate = DISPLAY_SCREEN_REFRESH;
	 f_dispMode.colorDepth = DISPLAY_COLOR_DEPTH;
	 f_dispMode.interlaced = FALSE;
	 f_dispMode.extendedCardSpecificInfo = NULL;
	 f_dispMode.extendedGPUSpecificInfo = NULL;
	 
	 init();
	 if (valid())
	 {
		 setState( new osg::State );
		 getState()->setGraphicsContext(this);

		 if (_traits.valid() && _traits->sharedContext)
		 {
			 getState()->setContextID( _traits->sharedContext->getState()->getContextID() );
			 incrementContextIDUsageCount( getState()->getContextID() );   
		 }
		 else
		 {
			 getState()->setContextID( osg::GraphicsContext::createNewContextID() );
		 }
	 }
}

/*
 * Default destructor
 */
GraphicsWindowVxWorks::~GraphicsWindowVxWorks()
{
	
}

void GraphicsWindowVxWorks::init()
 {
	if (_initialized)
		return;
	EGLBoolean errorStatus = EGL_TRUE;

	struct E4690ExtendedDisplayInfo GPUSpecificInfo1;

	CoreAVIDriverInitInfo initInfo;
	struct E4690DriverInitInfo chipInfo;

	memset(&chipInfo, 0x00, sizeof(chipInfo));
	memset(&initInfo, 0x00, sizeof(initInfo));
	chipInfo.gpuClockMHz = 110;
	chipInfo.memClockMHz = 220;
	chipInfo.gpuVoltage = 1000;
	chipInfo.memVoltage = 1500;
	chipInfo.pcieLanes = 2;
	chipInfo.pcieGen = 1;
	chipInfo.fcram.enable = 0;
	chipInfo.selfUpdatingTextureHeapSize = 0;
	chipInfo.gartMiscHeapSize = 0;

	initInfo.cardId = 0;
	initInfo.chipInitInfo = &chipInfo;

	memset(&GPUSpecificInfo1, 0x00, sizeof(GPUSpecificInfo1));
	GPUSpecificInfo1.frameBufHeapSize = 0;
	GPUSpecificInfo1.fcvm.enable = false;
	GPUSpecificInfo1.hSyncPolarity = E4690_SYNC_POLARITY_LOW;
	GPUSpecificInfo1.vSyncPolarity = E4690_SYNC_POLARITY_LOW;
	GPUSpecificInfo1.rotation = 0;
	GPUSpecificInfo1.syncWithOtherHead = false;

	f_dispMode.extendedCardSpecificInfo = (void *) (&GPUSpecificInfo1);
	/* Open Native Display */
	if (COREAVI_ERROR_SUCCESS != CoreAVIInitializeDriver(&initInfo)
			|| COREAVI_ERROR_SUCCESS != CoreAVIOpenDisplay(&f_dispMode,
					&f_disp_id)) {
		errorStatus = EGL_FALSE;
	}

	/* Obtain an EGL Display */
	if (EGL_TRUE == errorStatus) {
		f_dpy = eglGetDisplay(f_disp_id); /* EGL Get Display */

		/* Check if error occurred */
		if (EGL_NO_DISPLAY == f_dpy) {
			errorStatus = EGL_FALSE;
		}
	}

	/* Initialize EGL */
	if (EGL_TRUE == errorStatus) {
		errorStatus = eglInitialize(f_dpy, 0, 0); /* EGL Initialize */
	}

	/* Obtain the first configuration with a buffer size of 32 bits */
	if (EGL_TRUE == errorStatus) {
		errorStatus = eglChooseConfig(f_dpy, f_attribs, &f_config, 1,
				&f_num_configs); /* EGL Choose Config */
	}

	/* Create a Native Window */
	if (EGL_TRUE == errorStatus) {
		errorStatus = CoreAVICreateWindow(f_dpy, 0, 0, 0, DISPLAY_WIDTH,
				DISPLAY_HEIGHT, &f_win); /* EGL Create Window */
		errorStatus = (COREAVI_ERROR_SUCCESS == errorStatus) ? EGL_TRUE
				: EGL_FALSE;
	}

	/* Create an EGL Surface */
	if (EGL_TRUE == errorStatus) {
		f_surface = eglCreateWindowSurface(f_dpy, f_config, f_win, NULL); /* EGL Create Window Surface */

		if (EGL_NO_SURFACE == f_surface) {
			errorStatus = EGL_FALSE;
		}
	}

	/* Map the EGL Surface */
	if (EGL_TRUE == errorStatus) {
		//errorStatus = eglMapWindowCoreAVI(f_dpy, f_surface);
	}

	/* Create an EGL Context */
	if (EGL_TRUE == errorStatus) {
		EGLint f_attribs[3] = {COREAVI_HW_TEXTURE_HEAP_SIZE, 33554432,EGL_NONE }; 
		f_eglContext = eglCreateContext(f_dpy, f_config, EGL_NO_CONTEXT, f_attribs); /* EGL Create Context */

		if (EGL_NO_CONTEXT == f_eglContext) {
			errorStatus = EGL_FALSE;
		}
	}
	
    if (EGL_TRUE == errorStatus)
	{
		errorStatus = eglMakeCurrent(f_dpy, f_surface, f_surface, f_eglContext);        /* EGL Make Current */
		/* Setting swap interval to 0 will rely on hsync */
		eglSwapInterval(f_dpy, 0);
	}
    
	_initialized = true;
    _valid       = _initialized;
	
}

void GraphicsWindowVxWorks::closeImplementation()
{
	
}

bool GraphicsWindowVxWorks::makeCurrentImplementation()
{
	EGLBoolean errorStatus = EGL_TRUE;
     errorStatus = eglMakeCurrent(f_dpy, f_surface, f_surface, f_eglContext);        /* EGL Make Current */
      if (EGL_TRUE == errorStatus) 
    	 return true;
     else
    	 return false;
    	 
}

bool GraphicsWindowVxWorks::releaseContextImplementation()
{
	return false;
}

void GraphicsWindowVxWorks::swapBuffersImplementation()
{
	EGLBoolean errorStatus = EGL_TRUE;
	errorStatus = eglSwapBuffers(f_dpy, f_surface);
}

bool GraphicsWindowVxWorks::setWindowRectangleImplementation(int x, int y, int width, int height)
{
	return false;
}
