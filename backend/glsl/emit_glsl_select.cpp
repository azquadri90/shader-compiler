// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <string_view>

#include "emit_context.h"
#include "emit_glsl_instructions.h"
#include <shader_compiler/frontend/ir/value.h>

namespace Shader::Backend::GLSL {
void EmitSelectU1(EmitContext& ctx, IR::Inst& inst, std::string_view cond,
                  std::string_view true_value, std::string_view false_value) {
    ctx.AddU1("{}={}?{}:{};", inst, cond, true_value, false_value);
}

void EmitSelectU8([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] std::string_view cond,
                  [[maybe_unused]] std::string_view true_value,
                  [[maybe_unused]] std::string_view false_value) {
    NotImplemented();
}

void EmitSelectU16([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] std::string_view cond,
                   [[maybe_unused]] std::string_view true_value,
                   [[maybe_unused]] std::string_view false_value) {
    NotImplemented();
}

void EmitSelectU32(EmitContext& ctx, IR::Inst& inst, std::string_view cond,
                   std::string_view true_value, std::string_view false_value) {
    ctx.AddU32("{}={}?{}:{};", inst, cond, true_value, false_value);
}

void EmitSelectU64(EmitContext& ctx, IR::Inst& inst, std::string_view cond,
                   std::string_view true_value, std::string_view false_value) {
    ctx.AddU64("{}={}?{}:{};", inst, cond, true_value, false_value);
}

void EmitSelectF16([[maybe_unused]] EmitContext& ctx, [[maybe_unused]] std::string_view cond,
                   [[maybe_unused]] std::string_view true_value,
                   [[maybe_unused]] std::string_view false_value) {
    NotImplemented();
}

void EmitSelectF32(EmitContext& ctx, IR::Inst& inst, std::string_view cond,
                   std::string_view true_value, std::string_view false_value) {
    ctx.AddF32("{}={}?{}:{};", inst, cond, true_value, false_value);
}

void EmitSelectF64(EmitContext& ctx, IR::Inst& inst, std::string_view cond,
                   std::string_view true_value, std::string_view false_value) {
    ctx.AddF64("{}={}?{}:{};", inst, cond, true_value, false_value);
}

} // namespace Shader::Backend::GLSL
