/*
 * VxWindowingSystem.cpp
 *
 *  Created on: 2016-8-27
 *      Author: jinping
 */
#include "GraphicsWindowVxWorks.h"
#include "VxWindowingSystem.h"

/*
 * Default constructor
 */
//VxWindowingSystem::VxWindowingSystem()
//{
//	
//}

/*
 * Default destructor
 */
//VxWindowingSystem::~VxWindowingSystem()
//{
//	
//}
VxWindowingSystem::VxWindowingSystem()
{
}

VxWindowingSystem::~VxWindowingSystem()
{
    if (osg::Referenced::getDeleteHandler())
    {
        osg::Referenced::getDeleteHandler()->setNumFramesToRetainObjects(0);
        osg::Referenced::getDeleteHandler()->flushAll();
    }
}

unsigned int VxWindowingSystem::getNumScreens( const osg::GraphicsContext::ScreenIdentifier& si )
{
    return 0;
}

void VxWindowingSystem::getScreenResolution(const osg::GraphicsContext::ScreenIdentifier& si, unsigned int& width, unsigned int& height )
{
	//whatever si,now always return 1024*768
	width = 1280;
	height = 1024;
	return;
}

bool VxWindowingSystem::setScreenResolution( const osg::GraphicsContext::ScreenIdentifier& si, unsigned int width, unsigned int height )
{ 
	return false; 
}

bool VxWindowingSystem::setScreenRefreshRate(const osg::GraphicsContext::ScreenIdentifier& si, double refreshRate)
{
	return false;
}

osg::GraphicsContext* VxWindowingSystem::createGraphicsContext( osg::GraphicsContext::Traits* traits )
{
    osg::ref_ptr<GraphicsWindowVxWorks> window = new GraphicsWindowVxWorks(traits);
    if (window->valid()) 
    	return window.release();
    else
    	return NULL;
}


//static RegisterWindowingSystemInterfaceProxy createWindowingSystemInterfaceProxy;
