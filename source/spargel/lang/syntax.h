#pragma once

#include <spargel/base/check.h>
#include <spargel/base/either.h>
#include <spargel/base/optional.h>
#include <spargel/base/string_view.h>
#include <spargel/base/tagged_union.h>

namespace spargel::lang {

    enum class TokenKind {
        //------------------------
        // Newline and Whitespace
        //
        // Definition (cf. UTR #13 and UAX #31)
        //  - NLF (new line function) : any of { CR, LF, CRLF, NEL (U+0085) }, depending on the platform
        //  - LS (line separator) : U+2028
        //  - PS (paragraph separator) : U+2029
        //  - Pattern_White_Space characters :
        //      the set { ??? }
        //
        // The syntax is sensitive to line breaks. So newline is separated from whitespace.
        //
        // Decision:
        //  - Only U+000D (CR) and U+000A (LF) are considered as newline.
        //  - Only U+0020 (space) and U+0009 (horizontal tab) are considered as whitespace.
        //
        // Other choices:
        //  - https://go.dev/ref/spec#Tokens
        //  - https://docs.swift.org/swift-book/documentation/the-swift-programming-language/lexicalstructure/#Whitespace-and-Comments
        //
        newline,
        whitespace,

        line_comment,

        identifier,

        left_paren,
        right_paren,
        left_brace,
        right_brace,

        at,
        comma,
        equal,
    };

    enum class KeywordKind {
        import,
        define,
    };

    struct SourceLocation {
        int line;
        int column;

        void advance(char c) {
            if (c == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
        }
    };

    struct SourceRange {
        SourceLocation start;
        SourceLocation end;
    };

    struct Token {
        TokenKind kind;
        base::string_view content;
        SourceRange range;

        union {
            struct {
                bool doc;
            } line_comment;
            struct {
                bool keyword_like;
                KeywordKind keyword_candidate;
            } identifier;
        } data;

        auto& line_comment() { return data.line_comment; }
        auto& identifier() { return data.identifier; }

        void init(TokenKind k) {
            kind = k;
            switch (kind) {
                case TokenKind::line_comment:
                    line_comment().doc = false;
                    break;
                case TokenKind::identifier:
                    identifier().keyword_like = false;
                    break;
                default:
                    break;
            }
        }

        usize length() const { return content.length(); }

        void setKeywordCandidate(KeywordKind k) {
            spargel_check(kind == TokenKind::identifier);
            identifier().keyword_like = true;
            identifier().keyword_candidate = k;
        }
    };

    enum class LexStatus {
        success,

        // The cursor has reached the end of the buffer. So there is nothing to lex.
        end_of_buffer,

        // Null character is not allowed inside the buffer.
        unexpected_null_byte,

        // Usually some feature not implemented yet.
        internal_error,
    };

    //=============
    // class Lexer
    //
    // A lossless tokenizer.
    //
    class Lexer {
    public:
        struct LexState {
            char const* cur;
            SourceLocation loc;
        };


        Lexer(base::string_view source) : _begin{source.begin()}, _end{source.end()}, _cur{source.begin()}, _loc(1, 1) {}

        // Whether the end of buffer is reached.
        bool isEnd() const { return _cur >= _end; }

        // Advance the cursor by `n`.
        // 
        // Note:
        //  - The cursor stops at the end of the buffer.
        //
        void advance(usize n = 1) {
            if (_cur + n >= _end) {
                _cur = _end;
            } else {
                _cur += n;
            }
        }

        // Get the `n`-th byte from the current position. Return 0 if the `n`-th byte goes out the buffer.
        char peekByte(usize n = 0) const {
            if (_cur + n >= _end) return 0;
            return *(_cur + n);
        }

        LexStatus lex(Token& out);
        LexStatus lexNewline(Token& out);
        LexStatus lexWhitespace(Token& out);
        LexStatus lexLineComment(Token& out);
        LexStatus lexIdentifier(Token& out);
        
        // Keep advancing until the condition on the character is false.
        void eatWhile(auto&& f) {
            while (!isEnd()) {
                if (!f(peekByte())) return;
                advance();
            }
        }

        // Reset state.
        void reset() { _cur = _begin; }

        LexState saveState() const { return LexState(_cur, _loc); }
        void restoreState(LexState s) {
            spargel_check(s.cur >= _begin && s.cur <= _end);
            _cur = s.cur;
            _loc = s.loc;
        }

        void formToken(Token& out, TokenKind kind, LexState start) {
            out.init(kind);
            out.content = base::string_view(start.cur, _cur);
            out.range = SourceRange(start.loc, _loc);
        }

    private:
        char const* _begin;
        char const* _end;
        char const* _cur;
        SourceLocation _loc;
    };

    class ASTNodeBase {
    public:
        SourceRange range() const { return _range; }

    private:
        SourceRange _range;
    };

    enum class DeclarationKind {
        // `import Builtin`
        import,
        // `def pi = 3.14159`
        define,
    };

    class ImportDeclaration : public ASTNodeBase {
    public:
    private:
    };

    class DefineDeclaration : public ASTNodeBase {
    public:
    private:
    };

    using ASTDeclaration = base::TaggedUnion<
        base::Case<DeclarationKind::import, ImportDeclaration>,
        base::Case<DeclarationKind::define, DefineDeclaration>>;

    enum class ParseError {
        internal_error,
    };

    //==============
    // class Parser
    //
    // Parse into the loseless AST.
    //
    class Parser {
    public:
        Parser(base::string_view source) : _lexer(source) {}

        base::Either<ASTDeclaration, ParseError> parseDeclaration();
        base::Either<ImportDeclaration, ParseError> parseImportDeclaration();
        base::Either<DefineDeclaration, ParseError> parseDefineDeclaration();

    private:
        Lexer _lexer;
    };

}
