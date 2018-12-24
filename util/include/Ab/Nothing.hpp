#ifndef AB_NOTHING_HPP_
#define AB_NOTHING_HPP_

namespace Ab {

/// A special tag indicating no value.
/// Usage:
///   Ab::Nothing::VALUE, Ab::NOTHING, or Ab::nothing
enum class Nothing { VALUE };

namespace {
static constexpr const Nothing NOTHING = Nothing::VALUE;
static constexpr const Nothing nothing = NOTHING;
}  // namespace

}  // namespace Ab

#endif  // AB_NOTHING_HPP_
