#include "prj_tg_font_cached_font_move_glyph_y.h"
#include <cstring>
#include <limits>
#include "prj_tg_font_cached_font_quality.h"
#include "tg_global_log.h"
#include "prj_tg_font_cached_font_move_glyph_x.h"

PrjTgFontCachedFontMoveGlyphY::PrjTgFontCachedFontMoveGlyphY(PrjTgFontCachedFontMoveGlyphX *parent, const float move_glyph_y)
    : m_move_glyph_y(move_glyph_y)
    , m_parent(parent)
{

}
PrjTgFontCachedFontMoveGlyphY::~PrjTgFontCachedFontMoveGlyphY()
{
    for (PrjTgFontCachedFontQuality *f : m_listQuality) {
        delete f;
    }
    m_listQuality.clear();
}

bool PrjTgFontCachedFontMoveGlyphY::load(const std::vector<uint32_t> &listCharacters, const int quality)
{
    TG_FUNCTION_BEGIN();
    PrjTgFontCachedFontQuality *f = getCreateIfNotExists(quality);
    TG_FUNCTION_END();
    return f->load(listCharacters);
}

bool PrjTgFontCachedFontMoveGlyphY::isEqual(const float move_glyph_y) const
{
    return memcmp(&m_move_glyph_y, &move_glyph_y, sizeof(move_glyph_y)) == 0;
}

PrjTgFontCachedFontQuality *PrjTgFontCachedFontMoveGlyphY::getCreateIfNotExists(const int quality)
{
    for (PrjTgFontCachedFontQuality *f : m_listQuality) {
        if (f->isEqual(quality)) {
            return f;
        }
    }
    m_listQuality.push_back(new PrjTgFontCachedFontQuality(this, quality));
    return m_listQuality.back();
}

const std::string PrjTgFontCachedFontMoveGlyphY::getFilename() const
{
    return m_parent->getFilename();
}

float PrjTgFontCachedFontMoveGlyphY::getFontSize() const
{
    return m_parent->getFontSize();
}

float PrjTgFontCachedFontMoveGlyphY::getRotate() const
{
    return m_parent->getRotate();
}

float PrjTgFontCachedFontMoveGlyphY::getMoveGlyphX() const
{
    return m_parent->getMoveGlyphX();
}

float PrjTgFontCachedFontMoveGlyphY::getMoveGlyphY() const
{
    return m_move_glyph_y;
}

const PrjTgFontCachedFontQuality *PrjTgFontCachedFontMoveGlyphY::get(const int quality) const
{
    for (const PrjTgFontCachedFontQuality *f : m_listQuality) {
        if (f->isEqual(quality)) {
            return f;
        }
    }
    return nullptr;
}

float PrjTgFontCachedFontMoveGlyphY::getFontHeight(const int quality) const
{
    const PrjTgFontCachedFontQuality *f = get(quality);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getFontHeight();
}

float PrjTgFontCachedFontMoveGlyphY::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const int quality) const
{
    const PrjTgFontCachedFontQuality *f = get(quality);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing);
}

const uint8_t *PrjTgFontCachedFontMoveGlyphY::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const int quality) const
{
    const PrjTgFontCachedFontQuality *f = get(quality);
    if (!f) {
        return nullptr;
    }
    return f->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex);
}

bool PrjTgFontCachedFontMoveGlyphY::clear(const int quality)
{
    for (size_t i=0;i<m_listQuality.size();i++) {
        if (m_listQuality[i]->isEqual(quality)) {
            delete m_listQuality[i];
            m_listQuality.erase(m_listQuality.begin()+i);
            break;
        }
    }
    return m_listQuality.empty();
}