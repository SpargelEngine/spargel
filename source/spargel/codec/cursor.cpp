#include <spargel/codec/cursor.h>

/* libc */
#include <string.h>

namespace spargel::codec {

    bool cursorTryEatChar(Cursor& cursor, char ch) {
        if (cursor.cur + 1 > cursor.end) return false;
        if (cursorPeek(cursor) != ch) return false;
        cursorAdvance(cursor);
        return true;
    }

    bool cursorTryEatString(Cursor& cursor, const char* str) {
        usize len = (usize)strlen(str);
        return cursorTryEatBytes(cursor, (const u8*)str, len);
    }

    bool cursorTryEatBytes(Cursor& cursor, const u8* bytes, usize len) {
        if (cursor.cur + len > cursor.end) return false;
        if (memcmp(bytes, cursor.cur, len) != 0) return false;
        cursor.cur += len;
        return true;
    }

}  // namespace spargel::codec
