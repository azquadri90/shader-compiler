// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <shader_compiler/common/bit_field.h>
#include <shader_compiler/common/common_types.h>
#include <shader_compiler/frontend/ir/flow_test.h>
#include <shader_compiler/frontend/ir/reg.h>

namespace Shader::Maxwell {

struct Predicate {
    Predicate() = default;
    Predicate(unsigned index_, bool negated_ = false) : index{index_}, negated{negated_} {}
    Predicate(bool value) : index{7}, negated{!value} {}
    Predicate(u64 raw) : index{static_cast<unsigned>(raw & 7)}, negated{(raw & 8) != 0} {}

    unsigned index;
    bool negated;
};

inline bool operator==(const Predicate& lhs, const Predicate& rhs) noexcept {
    return lhs.index == rhs.index && lhs.negated == rhs.negated;
}

inline bool operator!=(const Predicate& lhs, const Predicate& rhs) noexcept {
    return !(lhs == rhs);
}

union Instruction {
    Instruction(u64 raw_) : raw{raw_} {}

    u64 raw;

    union {
        BitField<5, 1, u64> is_cbuf;
        BitField<0, 5, IR::FlowTest> flow_test;

        [[nodiscard]] u32 Absolute() const noexcept {
            return static_cast<u32>(absolute);
        }

        [[nodiscard]] s32 Offset() const noexcept {
            return static_cast<s32>(offset);
        }

    private:
        BitField<20, 24, s64> offset;
        BitField<20, 32, u64> absolute;
    } branch;

    [[nodiscard]] Predicate Pred() const noexcept {
        return Predicate{pred};
    }

private:
    BitField<16, 4, u64> pred;
};
static_assert(std::is_trivially_copyable_v<Instruction>);

} // namespace Shader::Maxwell
