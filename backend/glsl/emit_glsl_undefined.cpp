// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <string_view>

#include "emit_context.h"
#include "emit_glsl_instructions.h"

namespace Shader::Backend::GLSL {

void EmitUndefU1(EmitContext& ctx, IR::Inst& inst) {
    ctx.AddU1("{}=false;", inst);
}

void EmitUndefU8(EmitContext& ctx, IR::Inst& inst) {
    ctx.AddU32("{}=0u;", inst);
}

void EmitUndefU16(EmitContext& ctx, IR::Inst& inst) {
    ctx.AddU32("{}=0u;", inst);
}

void EmitUndefU32(EmitContext& ctx, IR::Inst& inst) {
    ctx.AddU32("{}=0u;", inst);
}

void EmitUndefU64(EmitContext& ctx, IR::Inst& inst) {
    ctx.AddU64("{}=0u;", inst);
}

} // namespace Shader::Backend::GLSL
