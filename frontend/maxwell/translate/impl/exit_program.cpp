// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <shader_compiler/common/common_types.h>
#include <shader_compiler/exception.h>
#include "impl.h"

namespace Shader::Maxwell {
namespace {
void ExitFragment(TranslatorVisitor& v) {
    const ProgramHeader sph{v.env.SPH()};
    IR::Reg src_reg{IR::Reg::R0};
    for (u32 render_target = 0; render_target < 8; ++render_target) {
        const std::array<bool, 4> mask{sph.ps.EnabledOutputComponents(render_target)};
        for (u32 component = 0; component < 4; ++component) {
            if (!mask[component]) {
                continue;
            }
            v.ir.SetFragColor(render_target, component, v.F(src_reg));
            ++src_reg;
        }
    }
    if (sph.ps.omap.sample_mask != 0) {
        v.ir.SetSampleMask(v.X(src_reg));
    }
    if (sph.ps.omap.depth != 0) {
        v.ir.SetFragDepth(v.F(src_reg + 1));
    }
}
} // Anonymous namespace

void TranslatorVisitor::EXIT() {
    switch (env.ShaderStage()) {
    case Stage::Fragment:
        ExitFragment(*this);
        break;
    default:
        break;
    }
}

} // namespace Shader::Maxwell
