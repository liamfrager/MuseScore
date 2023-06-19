/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "layoutcontext.h"

#include "style/defaultstyle.h"

#include "libmscore/mscoreview.h"
#include "libmscore/score.h"
#include "libmscore/spanner.h"

#include "tlayout.h"

using namespace mu::engraving;
using namespace mu::engraving::layout::v0;

LayoutContext::LayoutContext(Score* score)
    : m_score(score)
{
    firstSystemIndent = score && score->styleB(Sid::enableIndentationOnFirstSystem);
}

LayoutContext::~LayoutContext()
{
    for (Spanner* s : processedSpanners) {
        TLayout::layoutSystemsDone(s);
    }

    for (MuseScoreView* v : score()->getViewer()) {
        v->layoutChanged();
    }
}

double LayoutContext::spatium() const
{
    IF_ASSERT_FAILED(m_score) {
        return DefaultStyle::defaultStyle().styleD(Sid::spatium);
    }
    return m_score->spatium();
}

const MStyle& LayoutContext::style() const
{
    IF_ASSERT_FAILED(m_score) {
        return DefaultStyle::defaultStyle();
    }

    return m_score->style();
}

IEngravingFontPtr LayoutContext::engravingFont() const
{
    IF_ASSERT_FAILED(m_score) {
        return nullptr;
    }
    return m_score->engravingFont();
}

const Staff* LayoutContext::staff(staff_idx_t idx) const
{
    IF_ASSERT_FAILED(m_score) {
        return nullptr;
    }
    return m_score->staff(idx);
}

void LayoutContext::setLayout(const Fraction& tick1, const Fraction& tick2, staff_idx_t staff1, staff_idx_t staff2, const EngravingItem* e)
{
    IF_ASSERT_FAILED(m_score) {
        return;
    }
    m_score->setLayout(tick1, tick2, staff1, staff2, e);
}
