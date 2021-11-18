// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <string_view>

#include "shader_recompiler/backend/glsl/emit_context.h"
#include "shader_recompiler/backend/glsl/emit_glsl_instructions.h"
#include "shader_recompiler/frontend/ir/value.h"

namespace Shader::Backend::GLSL {

void EmitLogicalOr(EmitContext& ctx, IR::Inst& inst, std::string_view a, std::string_view b) {
    ctx.AddU1("{}={}||{};", inst, a, b);
}

void EmitLogicalAnd(EmitContext& ctx, IR::Inst& inst, std::string_view a, std::string_view b) {
    ctx.AddU1("{}={}&&{};", inst, a, b);
}

void EmitLogicalXor(EmitContext& ctx, IR::Inst& inst, std::string_view a, std::string_view b) {
    ctx.AddU1("{}={}^^{};", inst, a, b);
}

void EmitLogicalNot(EmitContext& ctx, IR::Inst& inst, std::string_view value) {
    ctx.AddU1("{}=!{};", inst, value);
}
} // namespace Shader::Backend::GLSL
