// Copyright 2021 yuzu Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/bit_field.h"
#include "common/common_types.h"
#include "shader_recompiler/frontend/maxwell/translate/impl/impl.h"

namespace Shader::Maxwell {
namespace {
enum class IntegerWidth : u64 {
    Byte,
    Short,
    Word,
};

[[nodiscard]] IR::U32 WidthSize(IR::IREmitter& ir, IntegerWidth width) {
    switch (width) {
    case IntegerWidth::Byte:
        return ir.Imm32(8);
    case IntegerWidth::Short:
        return ir.Imm32(16);
    case IntegerWidth::Word:
        return ir.Imm32(32);
    default:
        throw NotImplementedException("Invalid width {}", width);
    }
}

[[nodiscard]] IR::U32 ConvertInteger(IR::IREmitter& ir, const IR::U32& src,
                                     IntegerWidth dst_width) {
    const IR::U32 zero{ir.Imm32(0)};
    switch (dst_width) {
    case IntegerWidth::Byte:
        return ir.BitFieldExtract(src, zero, ir.Imm32(8), false);
    case IntegerWidth::Short:
        return ir.BitFieldExtract(src, zero, ir.Imm32(16), false);
    case IntegerWidth::Word:
        return ir.BitFieldExtract(src, zero, ir.Imm32(32), false);
    default:
        throw NotImplementedException("Invalid width {}", dst_width);
    }
}

void I2I(TranslatorVisitor& v, u64 insn, const IR::U32& src_a) {
    union {
        u64 insn;
        BitField<0, 8, IR::Reg> dest_reg;
        BitField<8, 2, IntegerWidth> dst_fmt;
        BitField<12, 1, u64> dst_fmt_sign;
        BitField<10, 2, IntegerWidth> src_fmt;
        BitField<13, 1, u64> src_fmt_sign;
        BitField<41, 3, u64> selector;
        BitField<45, 1, u64> neg;
        BitField<49, 1, u64> abs;
        BitField<50, 1, u64> sat;
    } const i2i{insn};

    if (i2i.sat != 0) {
        throw NotImplementedException("I2I SAT");
    }
    if (i2i.src_fmt == IntegerWidth::Short && (i2i.selector == 1 || i2i.selector == 3)) {
        throw NotImplementedException("16-bit source format incompatible with selector {}",
                                      i2i.selector);
    }
    if (i2i.src_fmt == IntegerWidth::Word && i2i.selector != 0) {
        throw NotImplementedException("32-bit source format incompatible with selector {}",
                                      i2i.selector);
    }

    const s32 selector{static_cast<s32>(i2i.selector)};
    const IR::U32 offset{v.ir.Imm32(selector * 8)};
    const IR::U32 count{WidthSize(v.ir, i2i.src_fmt)};
    IR::U32 src_values{v.ir.BitFieldExtract(src_a, offset, count, i2i.src_fmt_sign != 0)};
    if (i2i.abs) {
        src_values = v.ir.IAbs(src_values);
    }
    if (i2i.neg) {
        src_values = v.ir.INeg(src_values);
    }

    const IR::U32 result{ConvertInteger(v.ir, src_values, i2i.dst_fmt)};
    v.X(i2i.dest_reg, result);
}
} // Anonymous namespace

void TranslatorVisitor::I2I_reg(u64 insn) {
    I2I(*this, insn, GetReg20(insn));
}

void TranslatorVisitor::I2I_cbuf(u64 insn) {
    I2I(*this, insn, GetCbuf(insn));
}

void TranslatorVisitor::I2I_imm(u64 insn) {
    I2I(*this, insn, GetImm20(insn));
}

} // namespace Shader::Maxwell