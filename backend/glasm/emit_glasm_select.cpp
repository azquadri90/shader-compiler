
// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include "emit_context.h"
#include "emit_glasm_instructions.h"
#include <shader_compiler/frontend/ir/value.h>

namespace Shader::Backend::GLASM {

void EmitSelectU1(EmitContext& ctx, IR::Inst& inst, ScalarS32 cond, ScalarS32 true_value,
                  ScalarS32 false_value) {
    ctx.Add("CMP.S {},{},{},{};", inst, cond, true_value, false_value);
}

void EmitSelectU8([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] ScalarS32 cond,
                  [[maybe_unused]] ScalarS32 true_value, [[maybe_unused]] ScalarS32 false_value) {
    throw NotImplementedException("GLASM instruction");
}

void EmitSelectU16([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] ScalarS32 cond,
                   [[maybe_unused]] ScalarS32 true_value, [[maybe_unused]] ScalarS32 false_value) {
    throw NotImplementedException("GLASM instruction");
}

void EmitSelectU32(EmitContext& ctx, IR::Inst& inst, ScalarS32 cond, ScalarS32 true_value,
                   ScalarS32 false_value) {
    ctx.Add("CMP.S {},{},{},{};", inst, cond, true_value, false_value);
}

void EmitSelectU64(EmitContext& ctx, IR::Inst& inst, ScalarS32 cond, Register true_value,
                   Register false_value) {
    ctx.reg_alloc.InvalidateConditionCodes();
    const Register ret{ctx.reg_alloc.LongDefine(inst)};
    if (ret == true_value) {
        ctx.Add("MOV.S.CC RC.x,{};"
                "MOV.U64 {}.x(EQ.x),{};",
                cond, ret, false_value);
    } else if (ret == false_value) {
        ctx.Add("MOV.S.CC RC.x,{};"
                "MOV.U64 {}.x(NE.x),{};",
                cond, ret, true_value);
    } else {
        ctx.Add("MOV.S.CC RC.x,{};"
                "MOV.U64 {}.x,{};"
                "MOV.U64 {}.x(NE.x),{};",
                cond, ret, false_value, ret, true_value);
    }
}

void EmitSelectF16([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] ScalarS32 cond,
                   [[maybe_unused]] Register true_value, [[maybe_unused]] Register false_value) {
    throw NotImplementedException("GLASM instruction");
}

void EmitSelectF32(EmitContext& ctx, IR::Inst& inst, ScalarS32 cond, ScalarS32 true_value,
                   ScalarS32 false_value) {
    ctx.Add("CMP.S {},{},{},{};", inst, cond, true_value, false_value);
}

void EmitSelectF64([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] ScalarS32 cond,
                   [[maybe_unused]] Register true_value, [[maybe_unused]] Register false_value) {
    throw NotImplementedException("GLASM instruction");
}

} // namespace Shader::Backend::GLASM
