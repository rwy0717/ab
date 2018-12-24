#include <Ab/Config.hpp>
#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/Ir.hpp>
#include <Ab/Wasm/NoOpVisitor.hpp>
#include <Ab/Wasm/Printing.hpp>
#include <Ab/Wasm/ExprPrinter.hpp>
#include <Ab/Wasm/Reader.hpp>
#include <Ab/Maybe.hpp>
#include <Ab/SexprPrinter.hpp>
#include <Ab/StringSpan.hpp>
#include <fstream>
#include <iostream>

const char* name = "";

const char* const VERSION_STRING = "ab-dump version 0.0.1-danger";

const char* const USAGE =
	"Disassemble a WASM binary module.\n"
	"Usage: ab-dump [-o <output>] [--] <input>\n"
	"   Or: ab-dump --help";

struct Config {
	Ab::Maybe<std::string> in  = Ab::nothing;
	Ab::Maybe<std::string> out = Ab::nothing;
	bool debug                   = false;
	bool verbose                 = false;
};

namespace Ab {
namespace Wasm {

const bool DEBUG = false;

/// A Binary::Visitor that dumps human readable results to an ostream.
class WastPrinter : public NoOpVisitor {
public:
	WastPrinter(const Config& cfg, Ab::SexprPrinter& out) : cfg_{cfg}, out_{out} {
	}

	virtual auto moduleStart() -> void override {
		out_ << Ab::sexprStart << "module";
	}

	virtual auto moduleEnd() -> void override {
		out_ << Ab::sexprEnd;
		out_ << Ab::freshLine;
	}

	virtual auto sectionStart(const Section& section) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine << ";;;;;;;;;;;;;;" << section;
			++(out_.indent());
		}
	}

	virtual auto sectionEnd(const Section& section) -> void override {
		if (cfg_.verbose) {
			--out_.indent();
		}
	}

	virtual auto typeSection(std::size_t count) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine;
			out_ << Ab::rawStart << ";; count: " << count << Ab::rawEnd;
			out_ << Ab::freshLine;
		}
	}

	virtual auto functionType(const FunctionType& type) -> void override {
		out_ << Ab::freshLine << type;
	}

	virtual auto importSection(std::size_t count) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine;
			out_ << Ab::rawStart << ";; count: " << count << Ab::rawEnd;
			out_ << Ab::freshLine;
		}
	}

	virtual auto importEntry(const ImportEntry& entry) -> void override {
		out_ << Ab::freshLine << entry;
	}

	virtual auto functionSection(std::size_t count) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine;
			out_ << Ab::rawStart << ";; count: " << count << Ab::rawEnd;
			out_ << Ab::freshLine;
		}
		types_.reserve(count);
	}

	virtual auto functionEntry(std::size_t i, std::uint32_t type) -> void override {
		if (DEBUG) {
			out_ << Ab::freshLine;
			out_ << ";; " << Ab::sexprStart << "type" << type << Ab::sexprEnd;
		}
		types_.push_back(type);
	}

	virtual auto globalSection(std::size_t count) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine;
			out_ << Ab::rawStart << ";; count: " << count << Ab::rawEnd;
			out_ << Ab::freshLine;
		}
	}

	virtual auto globalEntry(const GlobalType& type, const InitExpr& expr) -> void override {
		out_ << Ab::freshLine;
		out_ << Ab::sexprStart << "global" << type;
		out_ << Ab::sexprStart << expr << Ab::sexprEnd;
		out_ << Ab::sexprEnd;
	}

	virtual auto exportEntry(const ExportEntry& entry) -> void override {
		out_ << Ab::freshLine << entry;
	}

	/// Element Section

	virtual auto elementSection(std::size_t count) -> void override {
	}

	virtual auto elementEntry(const ElementEntry& entry) -> void override {
		out_ << Ab::freshLine;
		out_ << Ab::sexprStart << "elem";
		out_ << Ab::sexprStart << entry.offset << Ab::sexprEnd;
	}

	virtual auto element(const ElementEntry& entry, std::uint32_t index) -> void override {
		out_ << index;
	}

	virtual auto elementEntryEnd(const ElementEntry& entry) -> void override {
		out_ << Ab::sexprEnd;
	}

	/// Code Section

	virtual auto codeSection(std::size_t count) -> void override {
		if (cfg_.verbose) {
			out_ << Ab::freshLine;
			out_.stream() << ";; count:" << count;
			out_.fresh(false);
		}
	}

	virtual auto functionBody(std::size_t index, const FunctionBody& body, ReaderInput& in)
		-> void override {
		out_ << Ab::freshLine;
		out_ << Ab::sexprStart << "func";
		out_ << Ab::sexprStart << "type" << types_[index] << Ab::sexprEnd;
		out_ << Ab::freshLine;
		out_ << body;

		ExprReader read;
		ExprPrinter print(out_);
		read(in, body.size, print);
		// auto& ops = *body.ops;

		out_ << Ab::sexprEnd;
	}

	virtual auto functionBodyEnd(const FunctionBody& entry) -> void override {
	}

	virtual auto dataSegment(const DataSegment& segment) -> void override {
		out_ << Ab::freshLine << segment;
	}

private:
	const Config& cfg_;
	std::vector<std::uint32_t> types_;
	Ab::SexprPrinter out_;
};

}  // namespace Wasm
}  // namespace Ab

auto dump(Config& cfg, std::istream& is, std::ostream& os) -> void {
	Ab::SexprPrinter out{os};
	Ab::Wasm::WastPrinter printer{cfg, out};
	Ab::Wasm::Reader reader{printer, is};

	reader();
}

auto parseArguments(Config& cfg, int argc, const char* const* argv) -> void {
	name  = argv[0];
	int i = 1;

	// Flags and non-positional arguments

	while (i < argc) {
		Ab::StringSpan arg{argv[i]};
		if (arg == "-o" || arg == "--ouput") {
			i++;
			cfg.out = Ab::Maybe<std::string>(argv[i]);
		} else if (arg == "-h" || arg == "--help") {
			std::cout << USAGE << std::endl;
			exit(EXIT_SUCCESS);
		} else if (arg == "--version") {
			std::cout << VERSION_STRING << std::endl;
			exit(EXIT_SUCCESS);
		} else if (arg == "--debug" || arg == "-d") {
			cfg.debug = true;
		} else if (arg == "--verbose" || arg == "-v") {
			cfg.verbose = true;
		} else if (arg == "--") {
			i++;
			break;
		} else {
			break;
		}
		i++;
	}

#if 0
	for (option : OPTION_TABLE) {
		if (option.matches(argv[index])) {
			option.handle(argc, argv, index);
		}
	}
#endif  //

	// Positional arguments

	if (i < argc) {
		cfg.in = Ab::just(std::string{argv[i]});
		i++;
	}
};

extern "C" auto main(int argc, char** argv) -> int {
	Config cfg;

	parseArguments(cfg, argc, argv);

	std::ifstream infile;
	std::streambuf* inbuffer = std::cin.rdbuf();
	if (cfg.in) {
		infile.open(*cfg.in, std::ios::in | std::ios::binary);
		inbuffer = infile.rdbuf();
	}
	std::istream in(inbuffer);

	std::ofstream outfile;
	std::streambuf* outbuffer = std::cout.rdbuf();
	if (cfg.out) {
		outfile.open(*cfg.out, std::ios::out | std::ios::binary);
		outbuffer = outfile.rdbuf();
	}
	std::ostream out(outbuffer);

	dump(cfg, in, out);
	return EXIT_SUCCESS;
}
