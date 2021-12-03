#include "zc/lex/token_queue.h"

namespace zc::lex {
	namespace {
		constexpr bool MatchesOptions(const Token& token, const TokenQueue::Options& options) {
			switch (token.type) {
			case Token::Type::Whitespace:
				return !options.skipWhitespace;
			case Token::Type::Comment:
				return !options.skipComments;
			}
			return true;
		}
	}

	TokenQueue::TokenQueue(std::string_view input, Options options)
		: lexer(input.data(), input.data() + input.size())
		, options(options)
	{
		Pop();
	}

	Token TokenQueue::Peek() const {
		return next;
	}

	Token TokenQueue::Pop() {
		auto result = next;
		do {
			next = lexer.Next();
		} while (!MatchesOptions(next, options));
		return result;
	}
}