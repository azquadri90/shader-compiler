// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <common/common_types.h>
#include <exception.h>
#include "common_encoding.h"
#include "common_funcs.h"
#include "impl.h"

namespace Shader::Maxwell {

enum class Merge : u64 {
    H1_H0,
    F32,
    MRG_H0,
    MRG_H1,
};

enum class Swizzle : u64 {
    H1_H0,
    F32,
    H0_H0,
    H1_H1,
};

enum class HalfPrecision : u64 {
    None = 0,
    FTZ = 1,
    FMZ = 2,
};

IR::FmzMode HalfPrecision2FmzMode(HalfPrecision precision);

std::pair<IR::F16F32F64, IR::F16F32F64> Extract(IR::IREmitter& ir, IR::U32 value, Swizzle swizzle);

IR::U32 MergeResult(IR::IREmitter& ir, IR::Reg dest, const IR::F16& lhs, const IR::F16& rhs,
                    Merge merge);

} // namespace Shader::Maxwell
