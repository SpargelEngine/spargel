#include <spargel/config.h>
#include <spargel/ui/platform.h>

namespace spargel::ui {

#if SPARGEL_IS_LINUX && SPARGEL_LINUX_IS_DESKTOP
    base::unique_ptr<Platform> makePlatformXcb();
#elif SPARGEL_IS_MACOS
    base::unique_ptr<Platform> makePlatformAppKit();
#elif SPARGEL_IS_WINDOWS
    base::unique_ptr<Platform> makePlatformWin32();
#endif

    base::unique_ptr<Platform> makePlatformDummy();

    base::unique_ptr<Platform> makePlatform() {
#if SPARGEL_IS_LINUX && SPARGEL_LINUX_IS_DESKTOP
        return makePlatformXcb();
#elif SPARGEL_IS_MACOS
        return makePlatformAppKit();
#elif SPARGEL_IS_WINDOWS
        return makePlatformWin32();
#else
        return makePlatformDummy();
#endif
    }

}  // namespace spargel::ui
