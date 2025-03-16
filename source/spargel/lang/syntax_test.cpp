#include <spargel/base/check.h>
#include <spargel/base/test.h>
#include <spargel/lang/syntax.h>

using spargel::lang::Lexer;
using spargel::lang::TokenKind;
using spargel::lang::Token;
using spargel::lang::KeywordKind;
using spargel::lang::LexStatus;

TEST(Lexer_Basic) {
    Lexer l("def hello()\n  print(\"hello, world\")\n");
    spargel_check(!l.isEnd());
    spargel_check(l.peekByte() == 'd');
    l.advance();
    spargel_check(l.peekByte() == 'e');
    l.advance();
    spargel_check(l.peekByte() == 'f');
    l.advance(2);
    spargel_check(l.peekByte() == 'h');
    spargel_check(l.peekByte(5) == '(');

    l.reset();

    l.eatWhile([](char c) { return c >= 'a' && c <= 'z'; });
    spargel_check(l.peekByte() == ' ');
}

TEST(Lexer_Null) {
    Lexer l("\0hello");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(r == LexStatus::unexpected_null_byte);
}

TEST(Lexer_Newline) {
    Lexer l("\n\r\n\rxyz\n");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(!l.isEnd() && l.peekByte() == 'x');
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::newline);
    spargel_check(tok.length() == 4);
    spargel_check(tok.content == "\n\r\n\r");
}

TEST(Lexer_Whitespace) {
    Lexer l(" \t  xyz\n");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(!l.isEnd() && l.peekByte() == 'x');
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::whitespace);
    spargel_check(tok.length() == 4);
    spargel_check(tok.content == " \t  ");
}

TEST(Lexer_LineComment) {
    Lexer l("// hello\nxyz");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(!l.isEnd() && l.peekByte() == '\n');
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::line_comment);
    spargel_check(tok.length() == 6); // " hello"
    spargel_check(tok.content == " hello");
}

TEST(Lexer_LineComment_EOF) {
    Lexer l("// hello");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(l.isEnd());
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::line_comment);
    spargel_check(tok.length() == 6); // " hello"
    spargel_check(tok.content == " hello");
}

TEST(Lexer_Paren) {
    Lexer l("( )");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::left_paren);
    spargel_check(tok.content == "(");
    l.lex(tok);
    r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::right_paren);
    spargel_check(tok.content == ")");
}

TEST(Lexer_Identifer) {
    Lexer l("hello _world");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::identifier);
    spargel_check(tok.content == "hello");
    spargel_check(!tok.identifier().keyword_like);
    l.lex(tok);
    r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::identifier);
    spargel_check(tok.content == "_world");
}

TEST(Lexer_Keyword) {
    Lexer l("import Builtins\ndefine main() { return }");
    Token tok;
    auto r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::identifier);
    spargel_check(tok.content == "import");
    spargel_check(tok.identifier().keyword_like);
    spargel_check(tok.identifier().keyword_candidate == KeywordKind::import);
    l.lex(tok); l.lex(tok); l.lex(tok);
    r = l.lex(tok);
    spargel_check(r == LexStatus::success);
    spargel_check(tok.kind == TokenKind::identifier);
    spargel_check(tok.content == "define");
    spargel_check(tok.identifier().keyword_like);
    spargel_check(tok.identifier().keyword_candidate == KeywordKind::define);
}
