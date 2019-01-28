#ifndef AB_SEXPRPRINTER_HPP_
#define AB_SEXPRPRINTER_HPP_

#include <Ab/Config.hpp>
#include <fmt/core.h>

namespace Ab {

/// An object for printing indentation.
/// Output the indent object to print indentation levels.
/// Use ++indent or --indent to manipulate the depth.
struct Indent {
public:
	Indent(std::size_t depth) : depth_{depth} {}

	auto operator++() -> Indent& {
		++depth_;
		return *this;
	}

	auto operator++(int) -> Indent {
		Indent copy = *this;
		depth_++;
		return copy;
	}

	auto operator--() -> Indent& {
		if (depth_ > 0) {
			--depth_;
		}
		return *this;
	}

	auto operator--(int) -> Indent {
		Indent copy = *this;
		if (depth_ > 0) {
			depth_--;
		}
		return copy;
	}

	auto depth() const -> std::size_t { return depth_; }

	auto depth(std::size_t depth) -> Indent& {
		depth_ = depth;
		return *this;
	}

	auto tostr() const -> std::string {
		std::string result = "";
		for (auto i = 0; i < depth_; ++i) {
			result = result + " ";
		}
		return result;
	}

private:
	static const constexpr std::size_t MAX_DEPTH = 10;

	std::size_t depth_ = 0;
};

}  // namespace Ab

template <>
struct ::fmt::formatter<Ab::Indent> {
	template <typename ParseContext>
	constexpr auto parse(ParseContext& cx) const {
		return cx.begin();
	}

	template <typename FormatContext>
	constexpr auto format(const Indent& indent, FormatContext& cx) const {
		return format_to(ctx.out(), indent.tostring());
	}
};

namespace Ab::Sexpr {

class Formatter {};

/// A formatted printer.
/// Prints S-Expressions, ie (output (style lisp)).
class Formatter {
public:
	Formatter() : stream_{stream}, indent_{0}, fresh_{true}, needsSpacing_{false} {}

	auto stream() const -> std::ostream& { return stream_; }

	auto indent() -> Indent& { return indent_; }

	auto indent() const -> const Indent& { return indent_; }

	auto freshen() -> SexprPrinter& {
		if (!fresh_) {
			fresh_        = true;
			needsSpacing_ = false;
			stream_ << std::endl;
		}
		return *this;
	}

	auto spacing() -> SexprPrinter& {
		if (fresh_) {
			stream_ << indent_;
		} else if (needsSpacing_) {
			stream_ << " ";
		}
		needsSpacing_ = false;
		fresh_        = false;
		return *this;
	}

	auto needsSpacing() const -> bool { return needsSpacing_; }

	auto needsSpacing(bool p) -> SexprPrinter& {
		needsSpacing_ = p;
		return *this;
	}

	auto fresh() const -> bool { return fresh_; }

	auto fresh(bool p) -> SexprPrinter& {
		fresh_ = p;
		return *this;
	}

	auto dirty() -> SexprPrinter& {
		fresh_        = false;
		needsSpacing_ = true;
		return *this;
	}

	SexprPrinter(std::ostream& out);

	/// Obtain the underlying stream object for unformatted output.
	auto stream() const -> std::ostream&;

	/// Obtain the indentation state.
	/// To increase the indentation, try:
	/// printer.indent()++;
	auto indent() -> Indent&;

	auto indent() const -> const Indent&;

	/// Prints a newline, if the current line is dirty.
	auto freshen() -> SexprPrinter&;

	/// Prints spacing between elements, or indentation if the line is fresh.
	auto spacing() -> SexprPrinter&;

	/// True if the line is dirty
	auto needsSpacing() const -> bool;

	/// Manually set the needs spacing flag.
	auto needsSpacing(bool p) -> SexprPrinter&;

	/// True if output is currently at the beginning of a line.
	auto fresh() const -> bool;

	/// Manually set the freshness, if you've been doing raw output.
	auto fresh(bool p) -> SexprPrinter&;

	/// Manually mark the line as dirty, needsSpacing.
	auto dirty() -> SexprPrinter&;

protected:
	std::ostream& stream_;
	Indent indent_{0};
	bool fresh_        = true;   // line is new
	bool needsSpacing_ = false;  // needs space between elements.
};

/// A debug s-expression printer.
extern SexprPrinter debug_out;

/// Print anything to the s-expression stream.
/// The type T must be streamable to std::ostream.
template <typename T>
inline auto operator<<(SexprPrinter& out, T&& x) -> SexprPrinter&;

/// Forward a manipulator to the underlying ostream.
inline auto operator<<(SexprPrinter& out, std::ostream& (*manipulator)(std::ostream&))
	-> SexprPrinter&;

/// Fresh line manipulator.
struct FreshLine {};

extern const FreshLine freshLine;

/// Begin a fresh line. If the current line is already fresh, do nothing.
inline auto operator<<(SexprPrinter& out, Ab::FreshLine) -> Ab::SexprPrinter& {
	out.freshen();
	return out;
}

/// S-Expression start manipulator.
struct SexprStart {};

extern const SexprStart sexprStart;

/// Begin an s-expression. Prints "(".
inline auto operator<<(SexprPrinter& out, SexprStart) -> SexprPrinter&;

/// S-Expression end manipulator.
struct SexprEnd {};

extern const SexprEnd sexprEnd;

/// End an s-expression. Prints ")".
inline auto operator<<(SexprPrinter& out, SexprEnd) -> SexprPrinter&;

/// Stringify the next thing. A manipulator that will wrap the text of the next object in quotes.
/// This manipulator only affects the one next object. Usage:
///   sexpr << stringify << "abcd";
/// output:
///   "abcd"
/// When you output a Stringify object to an SexprPrinter, the printer becomes a StringifyPrinter.
/// The stringify printer will stream
struct Stringify {};

extern const Stringify stringify;

/// A printer that stringifies one thing, then reverts back to a SexprPrinter.
struct StringifyPrinter {
	SexprPrinter& sexpr;
};

/// Convert the SexprPrinter to a Stringify printer.
inline auto operator<<(SexprPrinter& out, Stringify) -> StringifyPrinter;

/// Print the stringified version of x. Returns the SexprPrinter, so all following operations will
/// operate as normal.
template <typename T>
inline auto operator<<(const StringifyPrinter& out, T&& x) -> SexprPrinter&;

/// A printer that bypasses the SexprPrinter's formatting. To start raw output, stream rawStart to
/// an SexprPrinter. To end raw output, stream rawEnd;
struct RawPrinter {
	SexprPrinter& sexpr;
};

/// Print x without any SexprPrinter-based formatting.
template <typename T>
inline auto operator<<(const RawPrinter& out, T&& x) -> const RawPrinter&;
struct RawStart {};

/// Convert an SexprPrinter to a RawPrinter.
inline auto operator<<(SexprPrinter& out, const RawStart&) -> RawPrinter;

extern const RawStart rawStart;

struct RawEnd {};

extern const RawEnd rawEnd;

/// convert a RawPrinter to a SexprPrinter.
/// The SexprPrinter is dirtied.
inline auto operator<<(const RawPrinter& out, const RawEnd&) -> SexprPrinter&;

}  // namespace Ab::Sexpr

#ifndef AB_SEXPRPRINTER_INL_HPP_
#define AB_SEXPRPRINTER_INL_HPP_

#include <Ab/SexprPrinter.hpp>

namespace Ab {

inline auto operator<<(std::ostream& out, const Indent& indent) -> std::ostream& {
	for (std::size_t i = 0; i < indent.depth(); i++) {
		out << "  ";
	}
	return out;
}

template <typename T>
inline auto operator<<(SexprPrinter& out, T&& x) -> SexprPrinter& {
	out.spacing();
	out.stream() << std::forward<T>(x);
	out.dirty();
	return out;
}

inline auto operator<<(SexprPrinter& out, std::ostream& (*manipulator)(std::ostream&))
	-> SexprPrinter& {
	out.stream() << manipulator;
	return out;
}

inline auto operator<<(SexprPrinter& out, SexprStart) -> SexprPrinter& {
	out.spacing();
	out.stream() << "(";
	out.fresh(false);
	out.needsSpacing(false);
	out.indent()++;
	return out;
}

inline auto operator<<(SexprPrinter& out, SexprEnd) -> SexprPrinter& {
	out.stream() << ")";
	out.stream().flush();
	out.fresh(false);
	out.needsSpacing(true);
	out.indent()--;
	return out;
}

template <typename T>
inline auto operator<<(const StringifyPrinter& out, T&& x) -> SexprPrinter& {
	return out.sexpr << rawStart << "\"" << x << "\"" << rawEnd;
}

inline auto operator<<(SexprPrinter& out, Stringify) -> StringifyPrinter {
	return StringifyPrinter{out};
}

template <typename T>
inline auto operator<<(const RawPrinter& out, T&& x) -> const RawPrinter& {
	out.sexpr.stream() << std::forward<T>(x);
	return out;
}

inline auto operator<<(SexprPrinter& out, const RawStart&) -> RawPrinter {
	out.spacing();
	return RawPrinter{out};
};

inline auto operator<<(const RawPrinter& out, const RawEnd&) -> SexprPrinter& {
	out.sexpr.fresh(false);
	out.sexpr.needsSpacing(true);
	return out.sexpr;
}

}  // namespace Ab

#endif  // AB_SEXPRPRINTER_HPP_
