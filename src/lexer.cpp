#include "zc/lex/lexer.h"
#include <cctype>
#include <algorithm>

namespace {
    bool MatchesIdentifier(char ch) {
        return std::isalnum(ch) || ch == '_';
    }

    bool MatchesNumber(char ch) {
        return std::isdigit(ch) || ch == '.';
    }

    bool MatchesOperator(char ch) {
        switch (ch) {
        case '=':
        case '|':
        case '&':
        case '+':
        case '-':
        case '*':
        case '/':
        case '?':
        case ':':
        case '%':
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
        case ',':
        case '.':
        case '<':
        case '>':
        case '!':
        case '"':
        case '\'':
            return true;
        }
        return false;
    }
}

namespace zc::lex {
	Lexer::Lexer(const char* begin, const char* end)
		: current(begin)
		, end(end)
	{
	}

	Token Lexer::Next() {
        if (current == end)
            return Token{ .type = Token::Type::EndOfStream };

        // Store off the start of this token.
        const auto tokenStart = current;

        // Always advance and emit at least one character of a possibly unknown
        // type. This prevents any complete breakdowns of parsing because it
        // cannot get stuck not advancing at all.
        auto type = Token::Type::Unknown;
        ++current;

        if (std::isspace(*tokenStart)) {
            type = Token::Type::Whitespace;
            current = std::find_if_not(current, end, std::isspace);
        }
        else if (MatchesOperator(*tokenStart)) {
            type = Token::Type::Operator;
        }
        else if (MatchesNumber(*tokenStart)) {
            type = Token::Type::Number;
            current = std::find_if_not(current, end, MatchesNumber);
        }
        else if (MatchesIdentifier(*tokenStart)) {
            type = Token::Type::Identifier;
            current = std::find_if_not(current, end, MatchesIdentifier);
        }

        return Token{
            .type = type,
            .str = std::string_view(tokenStart, current),
        };
	}
}