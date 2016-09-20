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

//void VxWindowingSystem::getScreenResolution(const osg::GraphicsContext::ScreenIdentifier& si, unsigned int& width, unsigned int& height )
//{
//	//whatever si,now always return 1024*768
//	width = 1280;
//	height = 1024;
//	return;
//}
//
//bool VxWindowingSystem::setScreenResolution( const osg::GraphicsContext::ScreenIdentifier& si, unsigned int width, unsigned int height )
//{ 
//	return false; 
//}
//
//bool VxWindowingSystem::setScreenRefreshRate(const osg::GraphicsContext::ScreenIdentifier& si, double refreshRate)
//{
//	return false;
//}

void VxWindowingSystem::getScreenSettings(const osg::GraphicsContext::ScreenIdentifier& screenIdentifier, osg::GraphicsContext::ScreenSettings & resolution)
{
    resolution.width = 1280;
    resolution.height = 1024;
}

void VxWindowingSystem::enumerateScreenSettings(const osg::GraphicsContext::ScreenIdentifier& screenIdentifier, osg::GraphicsContext::ScreenSettingsList & resolutionList)
{
	osg::GraphicsContext::ScreenSettings  resolution;
	resolution.width = 1280;
	resolution.height = 1024;
	resolutionList.push_back(resolution);
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
