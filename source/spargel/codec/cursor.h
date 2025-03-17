#pragma once

#include <spargel/base/types.h>

namespace spargel::codec {

    struct Cursor {
        const char* cur;
        const char* end;
    };

    inline bool cursorIsEnd(const Cursor& cursor) { return cursor.cur >= cursor.end; }

    inline u8 cursorPeek(const Cursor& cursor) {
        if (cursorIsEnd(cursor)) return 0;
        return *cursor.cur;
    }

    inline void cursorAdvance(Cursor& cursor, int steps = 1) { cursor.cur += steps; }

    inline u8 cursorGetChar(Cursor& cursor) {
        u8 ch = cursorPeek(cursor);
        cursorAdvance(cursor);
        return ch;
    }

    inline char const* cursorGetPtr(Cursor& cursor) {
        return cursor.cur;
    }

    /*
     * These funtions will move the cursor if succeeds,
     * otherwise the cursor will not move.
     */
    bool cursorTryEatChar(Cursor& cursor, char ch);
    bool cursorTryEatBytes(Cursor& cursor, const u8* bytes, usize count);
    bool cursorTryEatString(Cursor& cursor, const char* str);

}  // namespace spargel::codec
