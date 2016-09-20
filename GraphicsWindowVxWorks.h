/*
 * GraphicsWindowVxWorks.h
 *
 *  Created on: 2016-8-28
 *      Author: jinping
 */

/*
 * Description:
 */
#include <e4690/e4690_display.h>
#include <coreavi_display/coreavi_display.h>
#include <global/coreavi_globals.h>

#include <EGL/egl.h>              /* EGL header file */
             /* GLU header file */
#include <os_helper/os_helper.h>

#include <osgViewer/GraphicsWindow>

#define DISPLAY_WIDTH      1280
#define DISPLAY_HEIGHT     1024
#define DISPLAY_WIDTH2      1024
#define DISPLAY_HEIGHT2     768
#define DISPLAY_COLOR_DEPTH     32
#define DISPLAY_SCREEN_REFRESH  60
#define DISPLAY_SCREEN_HEAD     OUTPUT_HEAD_PRIMARY   //OUTPUT_HEAD_PRIMARY
#define DISPLAY_SCREEN_HEAD2     OUTPUT_HEAD_SECONDARY  //OUTPUT_HEAD_PRIMARY
#define DISPLAY_OUTPUT_TYPE     OUTPUT_TYPE_DVI
#define DISPLAY_OUTPUT_TYPE2     OUTPUT_TYPE_DVI
#define DISPLAY_CARD_ID 0
#define EYESEP 0.02
#define CUBEES 4

#define SYS_CLK_RATE 1000
#define DISP_NUM 2


class GraphicsWindowVxWorks : public osgViewer::GraphicsWindow
{
public:
	/*
	 * Default constructor
	 */
	GraphicsWindowVxWorks(osg::GraphicsContext::Traits* traits);

	/*
	 * Default destructor
	 */
	~GraphicsWindowVxWorks();

	 virtual bool isSameKindAs(const osg::Object* object) const 
	{ 
		 return dynamic_cast<const GraphicsWindowVxWorks*>(object)!=0;
	}
	 
	 virtual const char* className() const { return "GraphicsWindowVxWorks"; }

	 /** Realize the GraphicsContext.*/
	virtual bool realizeImplementation(){ _realized = true; return true;}

	/** Return true if the graphics context has been realized and is ready to use.*/
	virtual bool isRealizedImplementation() const 
	{ 
		return _realized; 
	}

	/** Close the graphics context.*/
	virtual void closeImplementation();

	/** Make this graphics context current.*/
	virtual bool makeCurrentImplementation();

	/** Release the graphics context.*/
	virtual bool releaseContextImplementation();

	/** Swap the front and back buffers.*/
	virtual void swapBuffersImplementation();
	
	/** Set the window's position and size.*/
	virtual bool setWindowRectangleImplementation(int x, int y, int width, int height);

    virtual bool valid() const { return _valid; }
protected:
	void init();
	
private:
	 bool _realized;
	 bool _initialized;
     bool _valid;
	 
	 EGLDisplay      f_dpy;               /* Native display */
	 EGLNativeWindowType    f_win;               /* EGL Window */
	 EGLContext      f_eglContext;        /* EGL Context */
	 EGLConfig       f_config;            /* EGL Config */
	 EGLSurface      f_surface;           /* EGL Surface */
	 EGLNativeDisplayType f_disp_id;
	 EGLint          f_num_configs;       /* EGLConfig */
	 EGLint          f_attribs[5];         /* EGL Config */
	                              


	 CoreAVIDisplayMode  f_dispMode;        /* Display Mode */

};
