#ifndef AB_WASM_OPNAME_HPP_
#define AB_WASM_OPNAME_HPP_

#include <Ab/Wasm/OpCode.hpp>

namespace Ab {
namespace Wasm {

template <OpCode op>
constexpr const char* OP_NAME = "UNKNOWN_OP";

template <>
constexpr const char* OP_NAME<OpCode::UNREACHABLE> = "unreachable";

template <>
constexpr const char* OP_NAME<OpCode::NOP> = "nop";

template <>
constexpr const char* OP_NAME<OpCode::BLOCK> = "block";

template <>
constexpr const char* OP_NAME<OpCode::LOOP> = "loop";

template <>
constexpr const char* OP_NAME<OpCode::IF> = "if";

template <>
constexpr const char* OP_NAME<OpCode::ELSE> = "else";

template <>
constexpr const char* OP_NAME<OpCode::END> = "end";

template <>
constexpr const char* OP_NAME<OpCode::BR> = "br";

template <>
constexpr const char* OP_NAME<OpCode::BR_IF> = "br_if";

template <>
constexpr const char* OP_NAME<OpCode::BR_TABLE> = "br_table";

template <>
constexpr const char* OP_NAME<OpCode::RETURN> = "return";

template <>
constexpr const char* OP_NAME<OpCode::CALL> = "call";

template <>
constexpr const char* OP_NAME<OpCode::CALL_INDIRECT> = "call_indirect";

template <>
constexpr const char* OP_NAME<OpCode::DROP> = "drop";

template <>
constexpr const char* OP_NAME<OpCode::SELECT> = "select";

template <>
constexpr const char* OP_NAME<OpCode::GET_LOCAL> = "get_local";

template <>
constexpr const char* OP_NAME<OpCode::SET_LOCAL> = "set_local";

template <>
constexpr const char* OP_NAME<OpCode::TEE_LOCAL> = "tee_local";

template <>
constexpr const char* OP_NAME<OpCode::GET_GLOBAL> = "get_global";

template <>
constexpr const char* OP_NAME<OpCode::SET_GLOBAL> = "set_global";

template <>
constexpr const char* OP_NAME<OpCode::I32_LOAD> = "i32.load";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD> = "i64.load";

template <>
constexpr const char* OP_NAME<OpCode::F32_LOAD> = "f32.load";

template <>
constexpr const char* OP_NAME<OpCode::F64_LOAD> = "f64.load";

template <>
constexpr const char* OP_NAME<OpCode::I32_LOAD8_S> = "i32.load8_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_LOAD8_U> = "i32.load8_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_LOAD16_S> = "i32.load16_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_LOAD16_U> = "i32.load16_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD8_S> = "i64.load8_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD8_U> = "i64.load8_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD16_S> = "i64.load16_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD16_U> = "i64.load16_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD32_S> = "i64.load32_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_LOAD32_U> = "i64.load32_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_STORE> = "i32.store";

template <>
constexpr const char* OP_NAME<OpCode::I64_STORE> = "i64.store";

template <>
constexpr const char* OP_NAME<OpCode::F32_STORE> = "f32.store";

template <>
constexpr const char* OP_NAME<OpCode::F64_STORE> = "f64.store";

template <>
constexpr const char* OP_NAME<OpCode::I32_STORE8> = "i32.store8";

template <>
constexpr const char* OP_NAME<OpCode::I32_STORE16> = "i32.store16";

template <>
constexpr const char* OP_NAME<OpCode::I64_STORE8> = "i64.store8";

template <>
constexpr const char* OP_NAME<OpCode::I64_STORE16> = "i64.store16";

template <>
constexpr const char* OP_NAME<OpCode::I64_STORE32> = "i64.store32";

template <>
constexpr const char* OP_NAME<OpCode::CURRENT_MEMORY> = "current_memory";

template <>
constexpr const char* OP_NAME<OpCode::GROW_MEMORY> = "grow_memory";

template <>
constexpr const char* OP_NAME<OpCode::I32_CONST> = "i32.const";

template <>
constexpr const char* OP_NAME<OpCode::I64_CONST> = "i64.const";

template <>
constexpr const char* OP_NAME<OpCode::F32_CONST> = "f32.const";

template <>
constexpr const char* OP_NAME<OpCode::F64_CONST> = "f64.const";

template <>
constexpr const char* OP_NAME<OpCode::I32_EQZ> = "i32.eqz";

template <>
constexpr const char* OP_NAME<OpCode::I32_EQ> = "i32.eq";

template <>
constexpr const char* OP_NAME<OpCode::I32_NE> = "i32.ne";

template <>
constexpr const char* OP_NAME<OpCode::I32_LT_S> = "i32.lt_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_LT_U> = "i32.lt_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_GT_S> = "i32.gt_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_GT_U> = "i32.gt_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_LE_S> = "i32.le_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_LE_U> = "i32.le_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_GE_S> = "i32.ge_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_GE_U> = "i32.ge_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_EQZ> = "i64.eqz";

template <>
constexpr const char* OP_NAME<OpCode::I64_EQ> = "i64.eq";

template <>
constexpr const char* OP_NAME<OpCode::I64_NE> = "i64.ne";

template <>
constexpr const char* OP_NAME<OpCode::I64_LT_S> = "i64.lt_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_LT_U> = "i64.lt_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_GT_S> = "i64.gt_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_GT_U> = "i64.gt_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_LE_S> = "i64.le_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_LE_U> = "i64.le_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_GE_S> = "i64.ge_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_GE_U> = "i64.ge_u";

template <>
constexpr const char* OP_NAME<OpCode::F32_EQ> = "f32.eq";

template <>
constexpr const char* OP_NAME<OpCode::F32_NE> = "f32.ne";

template <>
constexpr const char* OP_NAME<OpCode::F32_LT> = "f32.lt";

template <>
constexpr const char* OP_NAME<OpCode::F32_GT> = "f32.gt";

template <>
constexpr const char* OP_NAME<OpCode::F32_LE> = "f32.le";

template <>
constexpr const char* OP_NAME<OpCode::F32_GE> = "f32.ge";

template <>
constexpr const char* OP_NAME<OpCode::F64_EQ> = "f64.eq";

template <>
constexpr const char* OP_NAME<OpCode::F64_NE> = "f64.ne";

template <>
constexpr const char* OP_NAME<OpCode::F64_LT> = "f64.lt";

template <>
constexpr const char* OP_NAME<OpCode::F64_GT> = "f64.gt";

template <>
constexpr const char* OP_NAME<OpCode::F64_LE> = "f64.le";

template <>
constexpr const char* OP_NAME<OpCode::F64_GE> = "f64.ge";

template <>
constexpr const char* OP_NAME<OpCode::I32_CLZ> = "i32.clz";

template <>
constexpr const char* OP_NAME<OpCode::I32_CTZ> = "i32.ctz";

template <>
constexpr const char* OP_NAME<OpCode::I32_POPCNT> = "i32.popcnt";

template <>
constexpr const char* OP_NAME<OpCode::I32_ADD> = "i32.add";

template <>
constexpr const char* OP_NAME<OpCode::I32_SUB> = "i32.sub";

template <>
constexpr const char* OP_NAME<OpCode::I32_MUL> = "i32.mul";

template <>
constexpr const char* OP_NAME<OpCode::I32_DIV_S> = "i32.div_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_DIV_U> = "i32.div_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_REM_S> = "i32.rem_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_REM_U> = "i32.rem_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_AND> = "i32.and";

template <>
constexpr const char* OP_NAME<OpCode::I32_OR> = "i32.or";

template <>
constexpr const char* OP_NAME<OpCode::I32_XOR> = "i32.xor";

template <>
constexpr const char* OP_NAME<OpCode::I32_SHL> = "i32.shl";

template <>
constexpr const char* OP_NAME<OpCode::I32_SHR_S> = "i32.shr_s";

template <>
constexpr const char* OP_NAME<OpCode::I32_SHR_U> = "i32.shr_u";

template <>
constexpr const char* OP_NAME<OpCode::I32_ROTL> = "i32.rotl";

template <>
constexpr const char* OP_NAME<OpCode::I32_ROTR> = "i32.rotr";

template <>
constexpr const char* OP_NAME<OpCode::I64_CLZ> = "i64.clz";

template <>
constexpr const char* OP_NAME<OpCode::I64_CTZ> = "i64.ctz";

template <>
constexpr const char* OP_NAME<OpCode::I64_POPCNT> = "i64.popcnt";

template <>
constexpr const char* OP_NAME<OpCode::I64_ADD> = "i64.add";

template <>
constexpr const char* OP_NAME<OpCode::I64_SUB> = "i64.sub";

template <>
constexpr const char* OP_NAME<OpCode::I64_MUL> = "i64.mul";

template <>
constexpr const char* OP_NAME<OpCode::I64_DIV_S> = "i64.div_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_DIV_U> = "i64.div_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_REM_S> = "i64.rem_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_REM_U> = "i64.rem_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_AND> = "i64.and";

template <>
constexpr const char* OP_NAME<OpCode::I64_OR> = "i64.or";

template <>
constexpr const char* OP_NAME<OpCode::I64_XOR> = "i64.xor";

template <>
constexpr const char* OP_NAME<OpCode::I64_SHL> = "i64.shl";

template <>
constexpr const char* OP_NAME<OpCode::I64_SHR_S> = "i64.shr_s";

template <>
constexpr const char* OP_NAME<OpCode::I64_SHR_U> = "i64.shr_u";

template <>
constexpr const char* OP_NAME<OpCode::I64_ROTL> = "i64.rotl";

template <>
constexpr const char* OP_NAME<OpCode::I64_ROTR> = "i64.rotr";

template <>
constexpr const char* OP_NAME<OpCode::F32_ABS> = "f32.abs";

template <>
constexpr const char* OP_NAME<OpCode::F32_NEG> = "f32.neg";

template <>
constexpr const char* OP_NAME<OpCode::F32_CEIL> = "f32.ceil";

template <>
constexpr const char* OP_NAME<OpCode::F32_FLOOR> = "f32.floor";

template <>
constexpr const char* OP_NAME<OpCode::F32_TRUNC> = "f32.trunc";

template <>
constexpr const char* OP_NAME<OpCode::F32_NEAREST> = "f32.nearest";

template <>
constexpr const char* OP_NAME<OpCode::F32_SQRT> = "f32.sqrt";

template <>
constexpr const char* OP_NAME<OpCode::F32_ADD> = "f32.add";

template <>
constexpr const char* OP_NAME<OpCode::F32_SUB> = "f32.sub";

template <>
constexpr const char* OP_NAME<OpCode::F32_MUL> = "f32.mul";

template <>
constexpr const char* OP_NAME<OpCode::F32_DIV> = "f32.div";

template <>
constexpr const char* OP_NAME<OpCode::F32_MIN> = "f32.min";

template <>
constexpr const char* OP_NAME<OpCode::F32_MAX> = "f32.max";

template <>
constexpr const char* OP_NAME<OpCode::F32_COPYSIGN> = "f32.copysign";

template <>
constexpr const char* OP_NAME<OpCode::F64_ABS> = "f64.abs";

template <>
constexpr const char* OP_NAME<OpCode::F64_NEG> = "f64.neg";

template <>
constexpr const char* OP_NAME<OpCode::F64_CEIL> = "f64.ceil";

template <>
constexpr const char* OP_NAME<OpCode::F64_FLOOR> = "f64.floor";

template <>
constexpr const char* OP_NAME<OpCode::F64_TRUNC> = "f64.trunc";

template <>
constexpr const char* OP_NAME<OpCode::F64_NEAREST> = "f64.nearest";

template <>
constexpr const char* OP_NAME<OpCode::F64_SQRT> = "f64.sqrt";

template <>
constexpr const char* OP_NAME<OpCode::F64_ADD> = "f64.add";

template <>
constexpr const char* OP_NAME<OpCode::F64_SUB> = "f64.sub";

template <>
constexpr const char* OP_NAME<OpCode::F64_MUL> = "f64.mul";

template <>
constexpr const char* OP_NAME<OpCode::F64_DIV> = "f64.div";

template <>
constexpr const char* OP_NAME<OpCode::F64_MIN> = "f64.min";

template <>
constexpr const char* OP_NAME<OpCode::F64_MAX> = "f64.max";

template <>
constexpr const char* OP_NAME<OpCode::F64_COPYSIGN> = "f64.copysign";

template <>
constexpr const char* OP_NAME<OpCode::I32_WRAP_I64> = "i32.wrap/i64";

template <>
constexpr const char* OP_NAME<OpCode::I32_TRUNC_S_F32> = "i32.trunc_s/f32";

template <>
constexpr const char* OP_NAME<OpCode::I32_TRUNC_U_F32> = "i32.trunc_u/f32";

template <>
constexpr const char* OP_NAME<OpCode::I32_TRUNC_S_F64> = "i32.trunc_s/f64";

template <>
constexpr const char* OP_NAME<OpCode::I32_TRUNC_U_F64> = "i32.trunc_u/f64";

template <>
constexpr const char* OP_NAME<OpCode::I64_EXTEND_S_I32> = "i64.extend_s/i32";

template <>
constexpr const char* OP_NAME<OpCode::I64_EXTEND_U_I32> = "i64.extend_u/i32";

template <>
constexpr const char* OP_NAME<OpCode::I64_TRUNC_S_F32> = "i64.trunc_s/f32";

template <>
constexpr const char* OP_NAME<OpCode::I64_TRUNC_U_F32> = "i64.trunc_u/f32";

template <>
constexpr const char* OP_NAME<OpCode::I64_TRUNC_S_F64> = "i64.trunc_s/f64";

template <>
constexpr const char* OP_NAME<OpCode::I64_TRUNC_U_F64> = "i64.trunc_u/f64";

template <>
constexpr const char* OP_NAME<OpCode::F32_CONVERT_S_I32> = "f32.convert_s/i32";

template <>
constexpr const char* OP_NAME<OpCode::F32_CONVERT_U_I32> = "f32.convert_u/i32";

template <>
constexpr const char* OP_NAME<OpCode::F32_CONVERT_S_I64> = "f32.convert_s/i64";

template <>
constexpr const char* OP_NAME<OpCode::F32_CONVERT_U_I64> = "f32.convert_u/i64";

template <>
constexpr const char* OP_NAME<OpCode::F32_DEMOTE_F64> = "f32.demote/f64";

template <>
constexpr const char* OP_NAME<OpCode::F64_CONVERT_S_I32> = "f64.convert_s/i32";

template <>
constexpr const char* OP_NAME<OpCode::F64_CONVERT_U_I32> = "f64.convert_u/i32";

template <>
constexpr const char* OP_NAME<OpCode::F64_CONVERT_S_I64> = "f64.convert_s/i64";

template <>
constexpr const char* OP_NAME<OpCode::F64_CONVERT_U_I64> = "f64.convert_u/i64";

template <>
constexpr const char* OP_NAME<OpCode::F64_PROMOTE_F32> = "f64.promote/f32";

template <>
constexpr const char* OP_NAME<OpCode::I32_REINTERPRET_F32> = "i32.reinterpret/f32";

template <>
constexpr const char* OP_NAME<OpCode::I64_REINTERPRET_F64> = "i64.reinterpret/f64";

template <>
constexpr const char* OP_NAME<OpCode::F32_REINTERPRET_I32> = "f32.reinterpret/i32";

template <>
constexpr const char* OP_NAME<OpCode::F64_REINTERPRET_I64> = "f64.reinterpret/i64";

/// Instantiates FunctionTemplate as
///   FunctionTemplate<OpCode>
template <OpCode op>
struct OpName {
	auto operator()() -> const char* {
		return OP_NAME<op>;
	}
};

} // namespace Wasm
} // namespace Ab

#endif // AB_WASM_OPCODENAME_HPP_
