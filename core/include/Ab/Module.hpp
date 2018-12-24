#ifndef AB_MODULE_HPP_
#define AB_MODULE_HPP_

#include <Ab/Config.hpp>
#include <Ab/Context.hpp>

namespace Ab {

/// Derived from the Mozilla WASM API
/// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WebAssembly/Module
/// An internal, decoded module. Fully loaded and linked.
class Module {
public:
	/// Compile and load a module from src
	Module();

	~Module();

	// auto customSections() const -> ???;

	// auto exports() const -> ???;

	// auto imports() const -> ???;

private:

};

}  // namespace Ab

#endif  // AB_MODULE_HPP_
