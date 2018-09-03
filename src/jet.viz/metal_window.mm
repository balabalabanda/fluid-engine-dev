// Copyright (c) 2018 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#import <jet.viz/metal_window.h>

#import "metal_view.h"
#import "mtlpp_wrappers.h"

#import <Cocoa/Cocoa.h>
#import <MetalKit/MetalKit.h>

using namespace jet::viz;

// MARK: WindowViewController

@interface WindowViewController : NSViewController<MTKViewDelegate> {
    @public void (*render)(const MetalWindow&);
    @public const MetalWindow* window;
}

@end

@implementation WindowViewController
-(void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
}

-(void)drawInMTKView:(nonnull MTKView *)view {
    (*render)(*window);
}
@end

// MARK: MetalWindow

MetalWindow::MetalWindow(const std::string& title, int width, int height) {
    _renderer = std::make_shared<MetalRenderer>();

    NSRect frame = NSMakeRect(0, 0, width, height);
    NSWindow* window = [[NSWindow alloc] initWithContentRect:frame
#if MTLPP_IS_AVAILABLE_MAC(10_12)
        styleMask:(NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable)
#else
        styleMask:(NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask)
#endif
        backing:NSBackingStoreBuffered
        defer:NO];
    window.title = [[NSProcessInfo processInfo] processName];
    WindowViewController* viewController = [WindowViewController new];
    viewController->render = MetalWindow::render;
    viewController->window = this;

    MTKView* view = [[MTKView alloc] initWithFrame:frame];
    view.device = (__bridge id<MTLDevice>)_renderer->device()->value.GetPtr();
    view.delegate = viewController;
    view.autoresizingMask = NSViewWidthSizable | NSViewHeightSizable;

    [window.contentView addSubview:view];
    [window center];
    [window orderFrontRegardless];

    _view = new MetalView(ns::Handle{ (__bridge void*)view });
}

MetalWindow::~MetalWindow() {
    delete _view;
}

MetalView* MetalWindow::view() const {
    return _view;
}

void MetalWindow::render(const MetalWindow& window) {
    window._renderer->render(&window);
}

