// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <shader_compiler/common/bit_field.h>
#include <shader_compiler/common/common_types.h>
#include <shader_compiler/exception.h>
#include "impl.h"

namespace Shader::Maxwell {
namespace {
void Check(u64 insn) {
    union {
        u64 raw;
        BitField<5, 1, u64> cbuf_mode;
        BitField<6, 1, u64> lmt;
    } const encoding{insn};

    if (encoding.cbuf_mode != 0) {
        throw NotImplementedException("Constant buffer mode");
    }
    if (encoding.lmt != 0) {
        throw NotImplementedException("LMT");
    }
}
} // Anonymous namespace

void TranslatorVisitor::BRX(u64 insn) {
    Check(insn);
}

void TranslatorVisitor::JMX(u64 insn) {
    Check(insn);
}

} // namespace Shader::Maxwell
