#include <spargel/base/logging.h>
#include <spargel/ui/platform.h>
#include <spargel/ui/window.h>

class delegate final : public spargel::ui::WindowDelegate {
public:
    void onKeyboard(spargel::ui::KeyboardEvent& e) override {
        spargel_log_info("key down : %d", e.key);
    }
    void onMouseDown(float x, float y) override {
        spargel_log_info("mouse down : %.3f %.3f", x, y);
    }
};

int main() {
    auto platform = spargel::ui::makePlatform();
    auto window = platform->makeWindow(500, 500);
    window->setTitle("Spargel Demo - Window");
    delegate d;
    window->setDelegate(&d);
    platform->startLoop();
    return 0;
}
