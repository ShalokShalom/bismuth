// SPDX-FileCopyrightText: 2022 Mikhail Zolotukhin <mail@gikari.com>
// SPDX-License-Identifier: MIT

#include "half-split.hpp"

#include "config.hpp"
#include "engine/layout/utils.hpp"
#include "logger.hpp"

namespace Bismuth
{

HalfSplitPiece::HalfSplitPiece(std::unique_ptr<LayoutPiece> &&primary, std::unique_ptr<LayoutPiece> &&secondary)
    : AngleDependentPiece(primary->config())
    , m_primary(std::move(primary))
    , m_secondary(std::move(secondary))
{
}

std::unordered_map<WindowGroup *, QRectF> HalfSplitPiece::apply(const QRectF &area, const std::vector<WindowGroup *> &groups)
{
    qDebug(Bi) << "Half-Split (area" << area << ") part groups";
    for (auto group : groups) {
        qDebug(Bi) << "HSG" << group;
    }

    if (groups.size() <= m_primarySize) {
        // Primary only
        return m_primary->apply(area, groups);
    } else if (m_primarySize == 0) {
        // Secondary only
        return m_secondary->apply(area, groups);
    } else {
        qDebug(Bi) << "Both parts";
        // Both parts
        auto ratio = reversed() ? 1 - m_ratio : m_ratio;
        qDebug(Bi) << "Ratio" << ratio;
        auto [area1, area2] = AreaSplitter(m_config.tileLayoutGap(), orientation()).splitAreaHalfWeighted(area, ratio);

        qDebug(Bi) << "Area1" << area1 << ". Area2" << area2;
        auto result1 = m_primary->apply(reversed() ? area2 : area1, slice(groups, 0, m_primarySize));
        auto result2 = m_secondary->apply(reversed() ? area1 : area2, slice(groups, m_primarySize));
        result1.insert(result2.begin(), result2.end());
        return result1;
    }
}
}
