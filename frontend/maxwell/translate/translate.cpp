// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#include <shader_compiler/environment.h>
#include <shader_compiler/frontend/ir/basic_block.h>
#include <shader_compiler/frontend/maxwell/decode.h>
#include <shader_compiler/frontend/maxwell/location.h>
#include "impl/impl.h"
#include "translate.h"

namespace Shader::Maxwell {

template <auto method>
static void Invoke(TranslatorVisitor& visitor, Location pc, u64 insn) {
    using MethodType = decltype(method);
    if constexpr (std::is_invocable_r_v<void, MethodType, TranslatorVisitor&, Location, u64>) {
        (visitor.*method)(pc, insn);
    } else if constexpr (std::is_invocable_r_v<void, MethodType, TranslatorVisitor&, u64>) {
        (visitor.*method)(insn);
    } else {
        (visitor.*method)();
    }
}

void Translate(Environment& env, IR::Block* block, u32 location_begin, u32 location_end) {
    if (location_begin == location_end) {
        return;
    }
    TranslatorVisitor visitor{env, *block};
    for (Location pc = location_begin; pc != location_end; ++pc) {
        const u64 insn{env.ReadInstruction(pc.Offset())};
        try {
            const Opcode opcode{Decode(insn)};
            switch (opcode) {
#define INST(name, cute, mask)                                                                     \
    case Opcode::name:                                                                             \
        Invoke<&TranslatorVisitor::name>(visitor, pc, insn);                                       \
        break;
#include <shader_compiler/frontend/maxwell/maxwell.inc>
#undef OPCODE
            default:
                throw LogicError("Invalid opcode {}", opcode);
            }
        } catch (Exception& exception) {
            exception.Prepend(fmt::format("Translate {}: ", Decode(insn)));
            throw;
        }
    }
}

} // namespace Shader::Maxwell
