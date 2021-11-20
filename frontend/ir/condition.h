// SPDX-License-Identifier: MPL-2.0
// Copyright © 2021 yuzu Emulator Project (https://github.com/yuzu-emu/yuzu/)

#pragma once

#include <compare>
#include <string>

#include <fmt/format.h>

#include <common/common_types.h>
#include "flow_test.h"
#include "pred.h"

namespace Shader::IR {

class Condition {
public:
    Condition() noexcept = default;

    explicit Condition(FlowTest flow_test_, Pred pred_, bool pred_negated_ = false) noexcept
        : flow_test{static_cast<u16>(flow_test_)}, pred{static_cast<u8>(pred_)},
          pred_negated{pred_negated_ ? u8{1} : u8{0}} {}

    explicit Condition(Pred pred_, bool pred_negated_ = false) noexcept
        : Condition(FlowTest::T, pred_, pred_negated_) {}

    explicit Condition(bool value) : Condition(Pred::PT, !value) {}

    auto operator<=>(const Condition&) const noexcept = default;

    [[nodiscard]] IR::FlowTest GetFlowTest() const noexcept {
        return static_cast<IR::FlowTest>(flow_test);
    }

    [[nodiscard]] std::pair<IR::Pred, bool> GetPred() const noexcept {
        return {static_cast<IR::Pred>(pred), pred_negated != 0};
    }

private:
    u16 flow_test;
    u8 pred;
    u8 pred_negated;
};

std::string NameOf(Condition condition);

} // namespace Shader::IR

template <>
struct fmt::formatter<Shader::IR::Condition> {
    constexpr auto parse(format_parse_context& ctx) {
        return ctx.begin();
    }
    template <typename FormatContext>
    auto format(const Shader::IR::Condition& cond, FormatContext& ctx) {
        return fmt::format_to(ctx.out(), "{}", Shader::IR::NameOf(cond));
    }
};
