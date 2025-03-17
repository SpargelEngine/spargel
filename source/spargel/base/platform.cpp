#include <spargel/base/const.h>
#include <spargel/base/platform.h>

namespace spargel::base {

    // FIXME
    string get_executable_path() {
        char* buf = (char*)base::default_allocator()->allocate(PATH_MAX);
        usize len = _get_executable_path(buf, PATH_MAX);
        if (len >= PATH_MAX) {
            buf = (char*)base::default_allocator()->resize(buf, PATH_MAX, len + 1);
            _get_executable_path(buf, len + 1);
        }
        buf[len] = '\0';
        string s;
        s._length = len;
        s._data = buf;
        return s;
    }

}  // namespace spargel::base
