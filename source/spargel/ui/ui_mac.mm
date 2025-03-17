#include <spargel/base/allocator.h>
#include <spargel/base/assert.h>
#include <spargel/base/logging.h>
#include <spargel/base/meta.h>
#include <spargel/base/unique_ptr.h>
#include <spargel/base/vector.h>
#include <spargel/ui/ui_mac.h>

//
#include <math.h>
#include <stddef.h>
#include <string.h>

//
#import <AppKit/AppKit.h>
#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <CoreText/CoreText.h>
#import <QuartzCore/QuartzCore.h>

using namespace spargel;

@implementation SpargelApplicationDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
    return YES;
}
@end

@implementation SpargelMetalView {
    CADisplayLink* _link;
    CAMetalLayer* _layer;
    NSTrackingArea* _tracking;
    ui::WindowAppKit* _bridge;
}
- (instancetype)initWithSpargelUIWindow:(ui::WindowAppKit*)w metalLayer:(CAMetalLayer*)layer {
    [super init];
    _bridge = w;
    _layer = layer;
    _tracking = nil;
    self.layer = _layer;
    self.wantsLayer = YES;  // layer-hosting view
    return self;
}
- (void)recreateTrackingArea {
    if (_tracking != nil) {
        [self removeTrackingArea:_tracking];
        [_tracking release];
    }

    NSTrackingAreaOptions options = NSTrackingActiveAlways | NSTrackingInVisibleRect |
                                    NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved;

    _tracking = [[NSTrackingArea alloc] initWithRect:[self bounds]
                                             options:options
                                               owner:self
                                            userInfo:nil];
    [self addTrackingArea:_tracking];
}
- (void)mouseMoved:(NSEvent*)event {
    spargel_log_info("mouse moved");
}
- (void)mouseDragged:(NSEvent*)event {
    _bridge->_bridgeMouseDragged(event.deltaX, event.deltaY);
}
- (void)mouseDown:(NSEvent*)event {
    auto loc = [event locationInWindow];
    _bridge->_bridgeMouseDown(loc.x, loc.y);
}
- (void)viewDidMoveToWindow {
    [super viewDidMoveToWindow];
    if (self.window == nil) {
        // move off a window
        [_link invalidate];
        _link = nil;
        return;
    }
    [self setupDisplayLink:self.window];
    [_link addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSRunLoopCommonModes];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}
- (void)setupDisplayLink:(NSWindow*)window {
    [_link invalidate];
    _link = [window displayLinkWithTarget:self selector:@selector(render:)];
}
- (void)setAnimating:(bool)animating {
    _link.paused = !animating;
}
- (void)render:(CADisplayLink*)sender {
    // The Application Kit creates an autorelease pool on the main thread at the beginning of every
    // cycle of the event loop, and drains it at the end, thereby releasing any autoreleased objects
    // generated while processing an event.
    //
    _bridge->_bridge_render();
}
- (void)viewDidChangeBackingProperties {
    [super viewDidChangeBackingProperties];
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}
- (void)setFrameSize:(NSSize)size {
    [super setFrameSize:size];
    _bridge->_updateSize(size.width, size.height);
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}
- (void)setBoundsSize:(NSSize)size {
    [super setBoundsSize:size];
    _bridge->_updateSize(size.width, size.height);
    [self resizeDrawable:self.window.screen.backingScaleFactor];
}
- (void)resizeDrawable:(CGFloat)scaleFactor {
    CGSize newSize = self.bounds.size;
    newSize.width *= scaleFactor;
    newSize.height *= scaleFactor;

    if (newSize.width <= 0 || newSize.width <= 0) {
        return;
    }
    if (newSize.width == _layer.drawableSize.width &&
        newSize.height == _layer.drawableSize.height) {
        return;
    }
    _layer.drawableSize = newSize;

    // _bridge->_setDrawableSize((float)newSize.width, (float)newSize.height);
}
- (void)keyDown:(NSEvent*)event {
    auto code = [event keyCode];
    _bridge->_bridge_key_down(code, event.type);
    // [self interpretKeyEvents:@[ event ]];
}
- (BOOL)acceptsFirstResponder {
    return YES;
}

// protocol NSTextInputClient

- (BOOL)hasMarkedText {
    return _bridge->getTextDelegate()->hasMarkedText();
}

- (NSRange)markedRange {
    return _bridge->getTextDelegate()->getMarkedRange();
}

- (NSRange)selectedRange {
    return _bridge->getTextDelegate()->getSelectedRange();
}

- (void)setMarkedText:(id)string
        selectedRange:(NSRange)selectedRange
     replacementRange:(NSRange)replacementRange {
    _bridge->getTextDelegate()->setMarkedText(string, selectedRange, replacementRange);
}

- (void)unmarkText {
    _bridge->getTextDelegate()->unmarkText();
}

- (NSArray<NSAttributedStringKey>*)validAttributesForMarkedText {
    return _bridge->getTextDelegate()->validAttributesForMarkedText();
}

// - (NSAttributedString *) attributedString {}

- (NSAttributedString*)attributedSubstringForProposedRange:(NSRange)range
                                               actualRange:(NSRangePointer)actualRange {
    return _bridge->getTextDelegate()->attributedSubstringForProposedRange(range, actualRange);
}

- (void)insertText:(id)string replacementRange:(NSRange)replacementRange {
    _bridge->getTextDelegate()->insertText(string, replacementRange);
}

- (NSUInteger)characterIndexForPoint:(NSPoint)point {
    return _bridge->getTextDelegate()->characterIndexForPoint(point);
}

- (NSRect)firstRectForCharacterRange:(NSRange)range actualRange:(NSRangePointer)actualRange {
    return _bridge->getTextDelegate()->firstRectForCharacterRange(range, actualRange);
}

@end

@implementation SpargelWindowDelegate {
    ui::WindowAppKit* _bridge;
}
- (instancetype)initWithSpargelUIWindow:(ui::WindowAppKit*)w {
    [super init];
    _bridge = w;
    return self;
}
@end

namespace {
    ui::PhysicalKey translatePhysicalKey(int code) {
        using enum ui::PhysicalKey;
        switch (code) {
        case kVK_ANSI_A:
            return key_a;
        case kVK_ANSI_B:
            return key_b;
        case kVK_ANSI_C:
            return key_c;
        case kVK_ANSI_D:
            return key_d;
        case kVK_ANSI_E:
            return key_e;
        case kVK_ANSI_F:
            return key_f;
        case kVK_ANSI_G:
            return key_g;
        case kVK_ANSI_H:
            return key_h;
        case kVK_ANSI_I:
            return key_i;
        case kVK_ANSI_J:
            return key_j;
        case kVK_ANSI_K:
            return key_k;
        case kVK_ANSI_L:
            return key_l;
        case kVK_ANSI_M:
            return key_m;
        case kVK_ANSI_N:
            return key_n;
        case kVK_ANSI_O:
            return key_o;
        case kVK_ANSI_P:
            return key_p;
        case kVK_ANSI_Q:
            return key_q;
        case kVK_ANSI_R:
            return key_r;
        case kVK_ANSI_S:
            return key_s;
        case kVK_ANSI_T:
            return key_t;
        case kVK_ANSI_U:
            return key_u;
        case kVK_ANSI_V:
            return key_v;
        case kVK_ANSI_W:
            return key_w;
        case kVK_ANSI_X:
            return key_x;
        case kVK_ANSI_Y:
            return key_y;
        case kVK_ANSI_Z:
            return key_z;
        case kVK_Space:
            return space;
        case kVK_Escape:
            return escape;
        case kVK_Delete:
            return key_delete;
        default:
            return unknown;
        }
    }
}  // namespace

namespace spargel::ui {

    base::unique_ptr<Platform> makePlatformAppKit() { return base::make_unique<PlatformAppKit>(); }

    PlatformAppKit::PlatformAppKit() : Platform(PlatformKind::appkit) {
        _app = [NSApplication sharedApplication];
        [_app setActivationPolicy:NSApplicationActivationPolicyRegular];

        SpargelApplicationDelegate* delegate = [[SpargelApplicationDelegate alloc] init];
        // NSApp.delegate is a weak reference
        _app.delegate = delegate;

        initGlobalMenu();
    }

    PlatformAppKit::~PlatformAppKit() {}

    void PlatformAppKit::startLoop() { [_app run]; }

    base::unique_ptr<Window> PlatformAppKit::makeWindow(u32 width, u32 height) {
        spargel_assert(width > 0 && height > 0);
        return base::make_unique<WindowAppKit>(width, height);
    }
    base::unique_ptr<TextSystem> PlatformAppKit::createTextSystem() {
        return base::make_unique<TextSystemAppKit>();
    }

    void PlatformAppKit::initGlobalMenu() {
        NSMenu* menu_bar = [[NSMenu alloc] init];

        NSMenu* app_menu = [[NSMenu alloc] initWithTitle:@"Spargel"];
        [app_menu addItemWithTitle:@"About Spargel" action:nil keyEquivalent:@""];
        [app_menu addItemWithTitle:@"Check for Updates" action:nil keyEquivalent:@""];
        [app_menu addItemWithTitle:@"Quit Spargel" action:@selector(terminate:) keyEquivalent:@"q"];

        NSMenuItem* app_menu_item = [[NSMenuItem alloc] init];
        [app_menu_item setSubmenu:app_menu];
        [menu_bar addItem:app_menu_item];

        // mainMenu is a strong reference
        _app.mainMenu = menu_bar;
    }

    WindowAppKit::WindowAppKit(int width, int height)
        : _width{static_cast<float>(width)}, _height{static_cast<float>(height)} {
        NSScreen* screen = [NSScreen mainScreen];

        NSWindowStyleMask style = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
                                  NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;

        NSRect rect = NSMakeRect(0, 0, width, height);
        // center the window
        rect.origin.x = (screen.frame.size.width - _width) / 2;
        rect.origin.y = (screen.frame.size.height - _height) / 2;

        _bridge = [[SpargelWindowDelegate alloc] initWithSpargelUIWindow:this];

        _window = [[NSWindow alloc] initWithContentRect:rect
                                              styleMask:style
                                                backing:NSBackingStoreBuffered
                                                  defer:NO
                                                 screen:screen];
        // weak reference
        _window.delegate = _bridge;
        _window.releasedWhenClosed = NO;
        // TODO: fix this
        _window.minSize = NSMakeSize(200, 200);

        _layer = [[CAMetalLayer alloc] init];

        _view = [[SpargelMetalView alloc] initWithSpargelUIWindow:this metalLayer:_layer];

        // auto _text_cursor = [[NSTextInsertionIndicator alloc] initWithFrame:NSMakeRect(0, 0, 0,
        // 0)];
        // [_view addSubview:_text_cursor];

        // _text_cursor.displayMode = NSTextInsertionIndicatorDisplayModeAutomatic;

        // strong reference
        _window.contentView = _view;

        [_window makeKeyAndOrderFront:nil];
    }

    void WindowAppKit::_enable_text_cursor() {
        // _text_cursor.displayMode = NSTextInsertionIndicatorDisplayModeAutomatic;
    }

    WindowAppKit::~WindowAppKit() {
        [_window release];
        [_bridge release];
    }

    void WindowAppKit::setTitle(char const* title) {
        _window.title = [NSString stringWithUTF8String:title];
    }

    void WindowAppKit::setAnimating(bool animating) {
        if (_animating != animating) {
            [_view setAnimating:animating];
        }
        _animating = animating;
    }

    void WindowAppKit::requestRedraw() { _bridge_render(); }

    void WindowAppKit::_setDrawableSize(float width, float height) {
        _drawable_width = width;
        _drawable_height = height;
    }

    WindowHandle WindowAppKit::getHandle() {
        WindowHandle handle;
        handle.apple.layer = _layer;
        return handle;
    }

    void WindowAppKit::_bridge_render() {
        if (getDelegate() != nullptr) {
            getDelegate()->onRender();
        }
    }

    void WindowAppKit::_bridge_key_down(int key, NSEventType type) {
        if (getDelegate() != nullptr) {
            KeyboardEvent e;
            e.key = translatePhysicalKey(key);
            if (type == NSEventTypeKeyDown) {
                e.action = KeyboardAction::press;
            } else if (type == NSEventTypeKeyUp) {
                e.action = KeyboardAction::release;
            } else {
                spargel_panic_here();
            }
            getDelegate()->onKeyboard(e);
        }
    }

    // Coordinate of AppKit:
    //
    //   ^ y
    //   |
    //   |
    //   +----> x
    //
    void WindowAppKit::_bridgeMouseDown(float x, float y) {
        if (getDelegate() != nullptr) {
            getDelegate()->onMouseDown(x, _height - y);
        }
    }

    void WindowAppKit::_bridgeMouseDragged(float dx, float dy) {
        if (getDelegate() != nullptr) {
            getDelegate()->onMouseDragged(dx, dy);
        }
    }

    TextSystemAppKit::TextSystemAppKit() {
        // use system language
        // _font = CTFontCreateUIFontForLanguage(kCTFontUIFontSystem, 14, NULL);
        static constexpr char const* font_name = "Times New Roman";
        // static constexpr char const* font_name = "Apple Color Emoji";
        auto name =
            CFStringCreateWithCString(kCFAllocatorDefault, font_name, kCFStringEncodingUTF8);
        _font = CTFontCreateWithName(name, 20, NULL);
        CFRelease(name);
    }

    TextSystemAppKit::~TextSystemAppKit() { CFRelease(_font); }

    constexpr float scale = 2;

    LineLayout TextSystemAppKit::layoutLine(base::string_view str) {
        auto cfstr = CFStringCreateWithBytes(kCFAllocatorDefault, (u8 const*)str.data(),
                                             str.length(), kCFStringEncodingUTF8, false);

        void const* keys[] = {kCTFontAttributeName, kCTLigatureAttributeName};
        int val = 2;
        auto number = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &val);
        void const* values[] = {_font, number};

        auto dict = CFDictionaryCreate(kCFAllocatorDefault, keys, values, 1, NULL, NULL);
        CFRelease(number);

        auto attr_str = CFAttributedStringCreate(kCFAllocatorDefault, cfstr, dict);

        auto line = CTLineCreateWithAttributedString(attr_str);

        auto glyph_runs = CTLineGetGlyphRuns(line);
        auto run_count = CFArrayGetCount(glyph_runs);

        LineLayout result;
        LayoutRun r;

        base::vector<CGGlyph> glyphs;
        base::vector<CGPoint> points;

        for (CFIndex i = 0; i < run_count; i++) {
            CTRunRef run = (CTRunRef)CFArrayGetValueAtIndex(glyph_runs, i);
            auto count = CTRunGetGlyphCount(run);

            glyphs.reserve(count);
            CTRunGetGlyphs(run, CFRangeMake(0, count), glyphs.data());
            glyphs.set_count(count);

            points.reserve(count);
            CTRunGetPositions(run, CFRangeMake(0, count), points.data());
            points.set_count(count);

            r.glyphs.reserve(count);
            r.glyphs.set_count(count);
            for (usize j = 0; j < count; j++) {
                r.glyphs[j] = glyphs[j];
            }
            r.positions.reserve(count);
            r.positions.set_count(count);
            for (usize j = 0; j < count; j++) {
                r.positions[j].x = points[j].x * scale;
                r.positions[j].y = points[j].y * scale;
            }

            r.width =
                CTRunGetTypographicBounds(run, CFRangeMake(0, count), NULL, NULL, NULL) * scale;

            result.runs.push(base::move(r));
        }

        CFRelease(line);
        CFRelease(attr_str);
        CFRelease(dict);
        CFRelease(cfstr);

        return result;
    }

    RasterResult TextSystemAppKit::rasterizeGlyph(GlyphId id) {
        CGGlyph glyphs[] = {(CGGlyph)id};
        CGRect rect;
        CTFontGetBoundingRectsForGlyphs(_font, kCTFontOrientationDefault, glyphs, &rect, 1);

        u32 width = (u32)ceil(rect.size.width);
        u32 height = (u32)ceil(rect.size.height);

        // scaling
        width *= scale;
        height *= scale;

        // for anti-aliasing
        width += 2;
        height += 2;

        Bitmap bitmap;
        bitmap.width = width;
        bitmap.height = height;
        bitmap.data.reserve(width *
                            height);  // only alpha. 8 bits per channel and 1 bytes per pixel
        bitmap.data.set_count(width * height);
        memset(bitmap.data.data(), 0x3f, width * height);

        auto color_space = CGColorSpaceCreateDeviceGray();
        auto ctx = CGBitmapContextCreate(bitmap.data.data(), width, height,
                                         8,      // bits per channel
                                         width,  // bytes per row
                                         color_space, kCGImageAlphaOnly);
        // for scale = 5, shift = 2
        static constexpr float shift = 1.0;
        CGContextTranslateCTM(ctx, -rect.origin.x * scale + shift, -rect.origin.y * scale + shift);
        // scale does not change the translate part!!!
        CGContextScaleCTM(ctx, scale, scale);

        CGContextSetShouldAntialias(ctx, true);

        // shift for anti-aliasing
        CGPoint point = CGPointMake(0, 0);
        CTFontDrawGlyphs(_font, glyphs, &point, 1, ctx);

        CFRelease(color_space);
        CGContextRelease(ctx);

        RasterResult result;
        result.bitmap = base::move(bitmap);
        result.glyph_width = rect.size.width * scale;
        result.glyph_height = rect.size.height * scale;
        result.descent = rect.origin.y * scale;

        return result;
    }

}  // namespace spargel::ui
