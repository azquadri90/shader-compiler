// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <shader_compiler/common/common_types.h>
#include "impl.h"

namespace Shader::Maxwell {
[[nodiscard]] IR::U1 IntegerCompare(IR::IREmitter& ir, const IR::U32& operand_1,
                                    const IR::U32& operand_2, CompareOp compare_op, bool is_signed);

[[nodiscard]] IR::U1 ExtendedIntegerCompare(IR::IREmitter& ir, const IR::U32& operand_1,
                                            const IR::U32& operand_2, CompareOp compare_op,
                                            bool is_signed);

[[nodiscard]] IR::U1 PredicateCombine(IR::IREmitter& ir, const IR::U1& predicate_1,
                                      const IR::U1& predicate_2, BooleanOp bop);

[[nodiscard]] IR::U1 PredicateOperation(IR::IREmitter& ir, const IR::U32& result, PredicateOp op);

[[nodiscard]] bool IsCompareOpOrdered(FPCompareOp op);

[[nodiscard]] IR::U1 FloatingPointCompare(IR::IREmitter& ir, const IR::F16F32F64& operand_1,
                                          const IR::F16F32F64& operand_2, FPCompareOp compare_op,
                                          IR::FpControl control = {});
} // namespace Shader::Maxwell
