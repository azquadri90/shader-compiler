// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <array>
#include <string>

#include "abstract_syntax_list.h"
#include "basic_block.h"
#include <shader_compiler/program_header.h>
#include <shader_compiler/shader_info.h>
#include <shader_compiler/stage.h>

namespace Shader::IR {

struct Program {
    AbstractSyntaxList syntax_list;
    BlockList blocks;
    BlockList post_order_blocks;
    Info info;
    Stage stage{};
    std::array<u32, 3> workgroup_size{};
    OutputTopology output_topology{};
    u32 output_vertices{};
    u32 invocations{};
    u32 local_memory_size{};
    u32 shared_memory_size{};
    bool is_geometry_passthrough{};
};

[[nodiscard]] std::string DumpProgram(const Program& program);

} // namespace Shader::IR
