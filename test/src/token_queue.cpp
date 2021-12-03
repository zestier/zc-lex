#include <catch2/catch.hpp>
#include "zc/lex/token_queue.h"

using namespace zc::lex;

namespace {
	constexpr bool TokenMatches(const Token& token, Token::Type type, std::string_view str) {
		return token.type == type && token.str == str;
	}
}

TEST_CASE("Parses identifiers") {
	auto tq = TokenQueue("hello");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "hello"));

	tq = TokenQueue("hello world");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "hello"));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Whitespace, " "));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "world"));

	tq = TokenQueue("_id1 __abc 123");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "_id1"));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Whitespace, " "));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "__abc"));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Whitespace, " "));
	REQUIRE(tq.Pop().type != Token::Type::Identifier);
}

TEST_CASE("Parses numbers") {
	auto tq = TokenQueue("123");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Number, "123"));

	tq = TokenQueue("123.456");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Number, "123.456"));
}

TEST_CASE("Peek works immediately") {
	auto tq = TokenQueue("the quick brown fox jumps over the lazy dog");
	REQUIRE(tq.Peek().str == "the");
	REQUIRE(tq.Pop().str == "the");
}

TEST_CASE("Peek always predicts the next Pop") {
	auto tq = TokenQueue("the quick brown fox jumps over the lazy dog");
	for (;;) {
		const auto peeked = tq.Peek();
		const auto popped = tq.Pop();
		REQUIRE(peeked == popped);
		if (popped.type == Token::Type::EndOfStream)
			break;
	}
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::EndOfStream, ""));
}

TEST_CASE("After the end of the stream returns additional EOS") {
	auto tq = TokenQueue("");
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::EndOfStream, ""));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::EndOfStream, ""));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::EndOfStream, ""));
}

TEST_CASE("Skipping whitespace works") {
	auto tq = TokenQueue(" hello world ", TokenQueue::Options{ .skipWhitespace = true });
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "hello"));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::Identifier, "world"));
	REQUIRE(TokenMatches(tq.Pop(), Token::Type::EndOfStream, ""));
}