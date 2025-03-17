#include <spargel/base/string.h>

// libc
#include <string.h>

namespace spargel::base {

    namespace _string {
        string::string(string_view v) {
            _length = v.length();
            if (_length > 0) {
                // _data = (char*)allocate(_length + 1, ALLOCATION_BASE);
                _data = (char*)default_allocator()->allocate(_length + 1);
                memcpy(_data, v.data(), _length);
                _data[_length] = 0;
            }
        }

        string::string(string const& other) {
            _length = other._length;
            if (_length > 0) {
                // _data = (char*)allocate(_length + 1, ALLOCATION_BASE);
                _data = (char*)default_allocator()->allocate(_length + 1);
                memcpy(_data, other._data, _length);
                _data[_length] = 0;
            }
        }

        string::string(const char* cstr) {
            _length = strlen(cstr);
            if (_length > 0) {
                _data = (char*)default_allocator()->allocate(_length + 1);
                memcpy(_data, cstr, _length);
                _data[_length] = 0;
            }
        }

        string::string(char ch) {
            _length = 1;
            _data = (char*)default_allocator()->allocate(2);
            _data[0] = ch;
            _data[1] = '\0';
        }

        string::~string() {
            if (_length > 0) {
                // deallocate(_data, _length + 1, ALLOCATION_BASE);
                default_allocator()->free(_data, _length + 1);
            }
        }

        bool operator==(string const& lhs, string const& rhs) {
            if (lhs._length != rhs._length) return false;
            if (lhs._length == 0) return true;
            return memcmp(lhs._data, rhs._data, lhs._length) == 0;
        }

        string operator+(const string& lhs, const string& rhs) {
            string str;
            str._length = lhs._length + rhs._length;
            if (str._length > 0) {
                // str._data = (char*)allocate(str._length + 1, ALLOCATION_BASE);
                str._data = (char*)default_allocator()->allocate(str._length + 1);
                memcpy(str._data, lhs._data, lhs._length);
                memcpy(str._data + lhs._length, rhs._data, rhs._length);
                str._data[str._length] = '\0';
            }
            return str;
        }

        string operator+(const string& s, char ch) {
            string str;
            str._length = s._length + 1;
            // str._data = (char*)allocate(str._length + 1, ALLOCATION_BASE);
            str._data = (char*)default_allocator()->allocate(str._length + 1);
            memcpy(str._data, s._data, s._length);
            str._data[s._length] = ch;
            str._data[s._length + 1] = '\0';
            return str;
        }

    }  // namespace _string

    string string_from_range(char const* begin, char const* end) {
        string str;
        str._length = end - begin;
        if (str._length > 0) {
            str._data = (char*)default_allocator()->allocate(str._length + 1);
            memcpy(str._data, begin, str._length);
            str._data[str._length] = 0;
        }
        return str;
    }

}  // namespace spargel::base
