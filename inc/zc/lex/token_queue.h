#pragma once

#include "lexer.h"
#include "token.h"
#include <string_view>

namespace zc::lex {
	class TokenQueue {
	public:
		struct Options {
			bool skipWhitespace;
			bool skipComments;
		};

	private:
		Lexer	lexer;
		Token	next;
		Options options;

	public:
		TokenQueue(std::string_view input, Options defaultOptions = Options{});

	public:
		Token Peek() const;
		Token Pop();
	};
}