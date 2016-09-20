/*
 * VxWindowingSystem.h
 *
 *  Created on: 2016-8-27
 *      Author: jinping
 */

/*
 * Description:
 */

#include <osg/graphicscontext>

class VxWindowingSystem : public osg::GraphicsContext::WindowingSystemInterface
{
  public:

	VxWindowingSystem();
    ~VxWindowingSystem();
    
    // Access the VxWorks windowing system through this singleton class.
    static VxWindowingSystem* getInterface()
    {
        static VxWindowingSystem* winInterface = new VxWindowingSystem;
        return winInterface;
    }
    
    // Return the number of screens present in the system
       virtual unsigned int getNumScreens( const osg::GraphicsContext::ScreenIdentifier& si );

       // Return the resolution of specified screen
       // (0,0) is returned if screen is unknown
       virtual void getScreenResolution( const osg::GraphicsContext::ScreenIdentifier& si, unsigned int& width, unsigned int& height );

       // Set the resolution for given screen
       virtual bool setScreenResolution( const osg::GraphicsContext::ScreenIdentifier& si, unsigned int width, unsigned int height );

       // Set the refresh rate for given screen
       virtual bool setScreenRefreshRate( const osg::GraphicsContext::ScreenIdentifier& si, double refreshRate );

    
       virtual osg::GraphicsContext* createGraphicsContext( osg::GraphicsContext::Traits* traits );

  private:
      // No implementation for these
       VxWindowingSystem( const VxWindowingSystem& );
       VxWindowingSystem& operator=( const VxWindowingSystem& );
};

//////////////////////////////////////////////////////////////////////////////
//  Class responsible for registering the Win32 Windowing System interface
//////////////////////////////////////////////////////////////////////////////
#include <osg/DeleteHandler>
struct RegisterWindowingSystemInterfaceProxy
{
    RegisterWindowingSystemInterfaceProxy()
    {
        osg::GraphicsContext::setWindowingSystemInterface(VxWindowingSystem::getInterface());
    }

    ~RegisterWindowingSystemInterfaceProxy()
    {
        if (osg::Referenced::getDeleteHandler())
        {
            osg::Referenced::getDeleteHandler()->setNumFramesToRetainObjects(0);
            osg::Referenced::getDeleteHandler()->flushAll();
        }

        osg::GraphicsContext::setWindowingSystemInterface(0);
    }
};
