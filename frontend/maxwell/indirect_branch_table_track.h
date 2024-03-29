// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <optional>

#include <shader_compiler/common/bit_field.h>
#include <shader_compiler/common/common_types.h>
#include <shader_compiler/environment.h>
#include <shader_compiler/frontend/ir/reg.h>
#include "location.h"

namespace Shader::Maxwell {

struct IndirectBranchTableInfo {
    u32 cbuf_index{};
    u32 cbuf_offset{};
    u32 num_entries{};
    s32 branch_offset{};
    IR::Reg branch_reg{};
};

std::optional<IndirectBranchTableInfo> TrackIndirectBranchTable(Environment& env, Location brx_pos,
                                                                Location block_begin);

} // namespace Shader::Maxwell
