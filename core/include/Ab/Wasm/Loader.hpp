#ifndef AB_WASM_LOADER_HPP_
#define AB_WASM_LOADER_HPP_

#include <Ab/Config.hpp>
#include <Ab/Context.hpp>
#include <Ab/Module.hpp>

#include <memory>

namespace Ab {
namespace Wasm {

enum class LoaderError { UNKNOWN_ERROR };

class Loader {
public:
	/// Load a module from a binary stream
	auto operator()(Context& cx, std::istream& in) -> std::shared_ptr<Module>;

	/// Load a module from a mmap'd input.
	auto operator()(Context& cx, void* start, std::size_t nbytes) ->std::shared_ptr<Module>;

};

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_LOADER_HPP_
