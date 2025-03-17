#pragma once

#include <spargel/base/string.h>
#include <spargel/base/vector.h>

namespace spargel::util {

    struct ParsedPath {
        // whether the path starts with '/'
        bool absolute;

        // whether the path ends with '/
        bool directory;

        base::vector<base::string> components;
    };

    base::string dirname(const base::string& path);

    ParsedPath parsePath(const base::string& path);

}  // namespace spargel::util
