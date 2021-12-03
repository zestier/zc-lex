#pragma once

#include "token.h"

namespace zc::lex {
	class Lexer {
		const char* current;
		const char* end;

	public:
		Lexer(const char* begin, const char* end);

	public:
		Token Next();
	};
}