// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <shader_compiler/common/bit_field.h>
#include <shader_compiler/common/common_types.h>
#include "impl.h"

namespace Shader::Maxwell {
namespace {
enum class Mode : u64 {
    SINCOS,
    EX2,
};

void RRO(TranslatorVisitor& v, u64 insn, const IR::F32& src) {
    union {
        u64 raw;
        BitField<0, 8, IR::Reg> dest_reg;
        BitField<39, 1, Mode> mode;
        BitField<45, 1, u64> neg;
        BitField<49, 1, u64> abs;
    } const rro{insn};

    v.F(rro.dest_reg, v.ir.FPAbsNeg(src, rro.abs != 0, rro.neg != 0));
}
} // Anonymous namespace

void TranslatorVisitor::RRO_reg(u64 insn) {
    RRO(*this, insn, GetFloatReg20(insn));
}

void TranslatorVisitor::RRO_cbuf(u64 insn) {
    RRO(*this, insn, GetFloatCbuf(insn));
}

void TranslatorVisitor::RRO_imm(u64) {
    throw NotImplementedException("RRO (imm)");
}

} // namespace Shader::Maxwell
