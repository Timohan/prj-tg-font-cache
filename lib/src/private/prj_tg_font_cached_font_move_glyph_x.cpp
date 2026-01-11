#include "prj_tg_font_cached_font_move_glyph_x.h"
#include <cstring>
#include <limits>
#include "prj_tg_font_cached_font_move_glyph_y.h"
#include "tg_global_log.h"
#include "prj_tg_font_cached_font_rotate.h"

PrjTgFontCachedFontMoveGlyphX::PrjTgFontCachedFontMoveGlyphX(PrjTgFontCachedFontRotate *parent, const float move_glyph_x)
    : m_move_glyph_x(move_glyph_x)
    , m_parent(parent)
{
}

PrjTgFontCachedFontMoveGlyphX::~PrjTgFontCachedFontMoveGlyphX()
{
    for (PrjTgFontCachedFontMoveGlyphY *f : m_listMoveGlyphY) {
        delete f;
    }
    m_listMoveGlyphY.clear();
}

bool PrjTgFontCachedFontMoveGlyphX::load(const std::vector<uint32_t> &listCharacters, const float move_glyph_y, const int quality)
{
    TG_FUNCTION_BEGIN();
    PrjTgFontCachedFontMoveGlyphY *f = getCreateIfNotExists(move_glyph_y);
    TG_FUNCTION_END();
    return f->load(listCharacters, quality);
}

bool PrjTgFontCachedFontMoveGlyphX::isEqual(const float move_glyph_x) const
{
    return memcmp(&m_move_glyph_x, &move_glyph_x, sizeof(move_glyph_x)) == 0;
}

PrjTgFontCachedFontMoveGlyphY *PrjTgFontCachedFontMoveGlyphX::getCreateIfNotExists(const float move_glyph_y)
{
    for (PrjTgFontCachedFontMoveGlyphY *f : m_listMoveGlyphY) {
        if (f->isEqual(move_glyph_y)) {
            return f;
        }
    }
    m_listMoveGlyphY.push_back(new PrjTgFontCachedFontMoveGlyphY(this, move_glyph_y));
    return m_listMoveGlyphY.back();
}

const std::string PrjTgFontCachedFontMoveGlyphX::getFilename() const
{
    return m_parent->getFilename();
}

float PrjTgFontCachedFontMoveGlyphX::getFontSize() const
{
    return m_parent->getFontSize();
}

float PrjTgFontCachedFontMoveGlyphX::getRotate() const
{
    return m_parent->getRotate();
}

float PrjTgFontCachedFontMoveGlyphX::getMoveGlyphX() const
{
    return m_move_glyph_x;
}

const PrjTgFontCachedFontMoveGlyphY *PrjTgFontCachedFontMoveGlyphX::get(const float move_glyph_y) const
{
    for (const PrjTgFontCachedFontMoveGlyphY *f : m_listMoveGlyphY) {
        if (f->isEqual(move_glyph_y)) {
            return f;
        }
    }
    return nullptr;
}

float PrjTgFontCachedFontMoveGlyphX::getFontHeight(const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphY *f = get(move_glyph_y);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getFontHeight(quality);
}

float PrjTgFontCachedFontMoveGlyphX::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter,
                                                float &advance, float &leftBearing, float &rightBearing,
                                                const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphY *f = get(move_glyph_y);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing, quality);
}

const uint8_t *PrjTgFontCachedFontMoveGlyphX::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphY *f = get(move_glyph_y);
    if (!f) {
        return nullptr;
    }
    return f->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, quality);
}

bool PrjTgFontCachedFontMoveGlyphX::clear(const float move_glyph_y, const int quality)
{
    for (size_t i=0;i<m_listMoveGlyphY.size();i++) {
        if (m_listMoveGlyphY[i]->isEqual(move_glyph_y)) {
            if (m_listMoveGlyphY[i]->clear(quality)) {
                delete m_listMoveGlyphY[i];
                m_listMoveGlyphY.erase(m_listMoveGlyphY.begin()+i);
            }
            break;
        }
    }
    return m_listMoveGlyphY.empty();
}
