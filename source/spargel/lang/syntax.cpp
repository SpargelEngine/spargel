#include <spargel/base/check.h>
#include <spargel/lang/syntax.h>

namespace spargel::lang {

    namespace {

        bool isNewline(char c) { return c == '\n' || c == '\r'; }
        bool isWhitespace(char c) { return c == ' ' || c == '\t'; }
        bool isIdentifierBegin(char c) {
            return (c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z')
                || c == '_';
        }
        bool isIdentifierContinuation(char c) {
            return (c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z')
                || (c >= '0' && c <= '9')
                || c == '_';
        }

    }

    LexStatus Lexer::lex(Token& out) {
        if (isEnd()) return LexStatus::end_of_buffer;

        char c = peekByte();

        LexState start = saveState();

        switch (c) {
            
            // null byte
            case 0:
                return LexStatus::unexpected_null_byte;

            // newline
            case '\n':
            case '\r':
                return lexNewline(out);

            // whitespace
            case ' ':
            case '\t':
                return lexWhitespace(out);

            case '/': {
                char next = peekByte(1);
                if (next == '/') {
                    return lexLineComment(out);
                }
                // TODO
                break;
            }

            case '(': { advance(); formToken(out, TokenKind::left_paren,  start); return LexStatus::success; }
            case ')': { advance(); formToken(out, TokenKind::right_paren, start); return LexStatus::success; }
            case '{': { advance(); formToken(out, TokenKind::left_brace,  start); return LexStatus::success; }
            case '}': { advance(); formToken(out, TokenKind::right_brace, start); return LexStatus::success; }
            case '@': { advance(); formToken(out, TokenKind::at,          start); return LexStatus::success; }
            case ',': { advance(); formToken(out, TokenKind::comma,       start); return LexStatus::success; }
            
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
            case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
            case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
            case 'V': case 'W': case 'X': case 'Y': case 'Z':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
            case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
            case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
            case 'v': case 'w': case 'x': case 'y': case 'z':
            case '_':
                return lexIdentifier(out);

            default:
                break;
        }

        return LexStatus::internal_error;
    }

    LexStatus Lexer::lexNewline(Token& out) {
        spargel_check(isNewline(peekByte()));

        LexState start = saveState();

        eatWhile([](char c) {
            return isNewline(c);
        });

        formToken(out, TokenKind::newline, start);
        return LexStatus::success;
    }

    LexStatus Lexer::lexWhitespace(Token& out) {
        spargel_check(isWhitespace(peekByte()));

        LexState start = saveState();

        eatWhile([](char c) {
            return isWhitespace(c);
        });

        formToken(out, TokenKind::whitespace, start);
        return LexStatus::success;
    }

    LexStatus Lexer::lexLineComment(Token& out) {
        spargel_check(peekByte() == '/' && peekByte(1) == '/');
        
        advance(2);

        LexState start = saveState();
        eatWhile([](char c) {
            return !isNewline(c);
        });

        formToken(out, TokenKind::line_comment, start);
        return LexStatus::success;
    }

    LexStatus Lexer::lexIdentifier(Token& out) {
        spargel_check(isIdentifierBegin(peekByte()));

        LexState start = saveState();
        eatWhile([](char c) {
            return isIdentifierContinuation(c);
        });

        formToken(out, TokenKind::identifier, start);

        if (out.content == "import") { out.identifier().keyword_like = true; out.identifier().keyword_candidate = KeywordKind::import; }
        if (out.content == "define") { out.identifier().keyword_like = true; out.identifier().keyword_candidate = KeywordKind::define; }

        return LexStatus::success;
    }

    base::Either<ASTDeclaration, ParseError> Parser::parseDeclaration() {
        return base::Right{ParseError::internal_error};
    }

    base::Either<ImportDeclaration, ParseError> Parser::parseImportDeclaration() {
        return base::Right{ParseError::internal_error};
    }

    base::Either<DefineDeclaration, ParseError> Parser::parseDefineDeclaration() {
        return base::Right{ParseError::internal_error};
    }

}
