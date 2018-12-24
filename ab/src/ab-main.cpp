
#include <fmt/core.h>
#include <span>
#include <string_view>

constexpr const std::size_t NSUBCOMMANDS = 4;

void execBuiltinCommand() {

}

void execExternalCommand() {

}

void execCommand() {

}

void printSubCommands() {
	for (const auto subcommand : SUBCOMMANDS) {
		fmt::print(subcommand, "\n");
	}
}

constexpr const char* const HELP_STRING =
	"ab: web assembly interpreter\n"
	"built-in subcommands:\n"
	"  ab run <wasm>:              Run a WASM module.\n"
	"  ab asm <wast> [<wasm>]:     Assemble a WAST input to a WASM module.\n"
	"  ab disasm <wasm> [<wast>]:  Disassemble a WASM module to WAST.\n"
	"  ab help:                    Print this help message.\n"
	"  ab version:                 Print the version of Ab.\n";

void printHelp() {
	fmt::print(HELP_STRING);
}

int processArgs(std::span<char*> args) {
	if (args.size() == 1) {
		printHelp();
		return 1;
	}

	std::string_view target = args[2];

	if (target == "help") {
		printHelp();
		return 0;
	}

	fmt::print("ab-", target, "\n");
}

extern "C" int main(int argc, char** argv) {
	return processArgs(std::span<char*>(argv, argc));
}
