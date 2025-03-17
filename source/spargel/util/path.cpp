#include <spargel/base/const.h>
#include <spargel/util/path.h>

namespace spargel::util {

    base::string dirname(const base::string& path) {
        if (path.length() == 0) return base::string(".");

        const char* data = path.data();
        const char* cur = path.end() - 1;

        // Skip trailing separators
        while (cur >= path.begin() && *cur == PATH_SPLIT) {
            cur--;
        }

        // Handle case where all characters were separators
        if (cur < path.begin()) {
            if (path.length() > 0 && *path.begin() == PATH_SPLIT) {
                return base::string("/");
            } else {
                return base::string(".");
            }
        }

        // Find last separator
        for (; cur >= path.begin(); cur--) {
            if (*cur == PATH_SPLIT) break;
        }

        // If no separator found, return "."
        if (cur < path.begin()) return base::string(".");

        // If we're at root, return "/"
        if (cur == path.begin() && *cur == PATH_SPLIT) {
            return base::string_from_range(data, cur + 1);
        }

        // Return path up to but not including the separator
        return base::string_from_range(data, cur);
    }

    ParsedPath parsePath(const base::string& path) {
        if (path.length() == 0) return {.absolute = false, .directory = false, .components = {}};

        const char* data = path.data();
        const char *cur = path.begin(), *s;

        bool absolute = data[0] == '/';
        bool directory = false;
        base::vector<base::string> components;

        for (; cur < path.end(); cur++) {
            if (*cur == '/') continue;

            directory = true;

            s = cur;
            for (; cur < path.end(); cur++) {
                directory = false;
                if (*cur == '/') {
                    directory = true;
                    break;
                }
            }

            components.push(base::string_from_range(s, cur));
        }

        return {.absolute = absolute, .directory = directory, .components = components};
    }

}  // namespace spargel::util
