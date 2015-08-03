/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#import "AppController.h"
#import "AppDelegate.h"

#include <cocos2d.h>
#include "physics/physics.h"
#include "common/assets.h"

using namespace cocos2d;
using namespace pix2d;

@implementation MyWindow
- (void)keyDown:(NSEvent *)theEvent {
    /*
    if ([[theEvent characters] isEqualToString:@" "]) {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCRenderTexture *render = CCRenderTexture::create(size.width, size.height);
        render->setPosition(CCSizeMake(size.width/2, size.height/2));
        ccColor4F color = Physics::getDefaultBackgroundColor();
        render->beginWithClear(color.r,color.g,color.b,color.a);
        CCDirector::sharedDirector()->getRunningScene()->visit();
        render->end();
        render->saveToFile("/Users/lzubiaur/Desktop/screenshot.png");
    }
    */
}
@end

@implementation AppController

	static AppDelegate s_sharedApplication;

	@synthesize window, glView;

	-(void) applicationDidFinishLaunching:(NSNotification *)aNotification
	{
		// create the window
		// note that using NSResizableWindowMask causes the window to be a little
		// smaller and therefore ipad graphics are not loaded
        // Resolution tests
        // NSRect rect = NSMakeRect(200, 200, 480, 320); /// SD
        // NSRect rect = NSMakeRect(200, 200, 1024, 768); /// HD
        // NSRect rect = NSMakeRect(200, 200, 2048, 1536); /// Retina
        // NSRect rect = NSMakeRect(200, 200, 800, 600);
        // NSRect rect = NSMakeRect(200, 200, 1280, 720); /// youtube
        // NSRect rect = NSMakeRect(200, 200, 640, 360); /// 0.5 ratio
        // NSRect rect = NSMakeRect(200, 200, 1920, 1080); /// youtube 1.5 ratio to allow video zooms

        // NSRect rect = NSMakeRect(200, 200, 960, 380);

        /// Get the screen resolution
        NSRect rect = [[NSScreen mainScreen] frame];

		window = [[MyWindow alloc] initWithContentRect:rect
			styleMask:( NSClosableWindowMask | NSTitledWindowMask )
			backing:NSBackingStoreBuffered
			defer:YES];

        NSOpenGLPixelFormatAttribute attributes[] = {
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAStencilSize, 8,
            0
        };
        
        NSOpenGLPixelFormat *pixelFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes:attributes] autorelease];
		
		// allocate our GL view
		// (isn't there already a shared EAGLView?)
		glView = [[EAGLView alloc] initWithFrame:rect pixelFormat:pixelFormat];

		// set window parameters
		[window becomeFirstResponder];
		[window setContentView:glView];
		[window setTitle:@"Yummy Jump"];
		[window makeKeyAndOrderFront:self];
		[window setAcceptsMouseMovedEvents:NO];

        /// Set full screen
		EAGLView* pView = [EAGLView sharedEGLView];
		[pView setFullScreen:!pView.isFullScreen];

		cocos2d::CCApplication::sharedApplication()->run();
	}

	-(BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)theApplication
	{
		return YES;
	}

	-(void) dealloc
	{
		cocos2d::CCDirector::sharedDirector()->end();
		[super dealloc];
	}

#pragma mark -
#pragma mark IB Actions

	-(IBAction) toggleFullScreen:(id)sender
	{
        // TODO setContentScaleFactor not working
		EAGLView* pView = [EAGLView sharedEGLView];
		[pView setFullScreen:!pView.isFullScreen];
	}

	-(IBAction) exitFullScreen:(id)sender
	{
		[[EAGLView sharedEGLView] setFullScreen:NO];
	}

@end
