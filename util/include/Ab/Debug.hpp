#ifndef AB_DEBUG_HPP_
#define AB_DEBUG_HPP_

/// Defines a set of debug-only macros and APIs.
/// The macros in this header are conditionally enabled by the OM_DEBUG define.
/// To enable debug code with cmake, use:
/// `cmake -DOM_DEBUG=On`

#include <Ab/Config.hpp>
#include <Ab/CppUtilities.hpp>
#include <iostream>

namespace Ab {
namespace {

inline auto trace(const char* function) -> void {
	std::cerr << "TRACE!> " << function << std::endl;
}

}  // namespace
}  // namespace Ab

#define AB_TRACE() ::Ab::trace(AB_FUNCTION_STR())

#ifdef AB_DEBUG
#define AB_DEBUG_TRACE() AB_TRACE()
#else
#define AB_DEBUG_TRACE()  // nothing
#endif

/// @macro OM_DBG_ASSERT(assertion)
/// Assert that the assertion is true. Be careful, when OM_DEBUG is disabled,
/// the assertion won't be compiled.)
#ifdef AB_DEBUG
#define AB_DEBUG_ASSERT(x) AB_ASSERT(x)
#else
#define AB_DEBUG_ASSERT(x)  // nothing
#endif

#endif  // AB_DEBUG_HPP_
