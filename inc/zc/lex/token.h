#pragma once

#include <string_view>

namespace zc::lex {
	struct Token {
		enum class Type {
			Invalid,
			Unknown,
			EndOfStream,
			Whitespace,
			Comment,
			Identifier,
			Number,
			Operator,
		};

		Type type = Type::Invalid;
		std::string_view str;

		bool operator!=(const Token& rhs) const = default;
		bool operator==(const Token& rhs) const = default;
	};
}