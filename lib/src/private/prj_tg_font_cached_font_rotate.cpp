#include "prj_tg_font_cached_font_rotate.h"
#include <cstring>
#include <limits>
#include "prj_tg_font_cached_font_move_glyph_x.h"
#include "tg_global_log.h"
#include "prj_tg_font_cached_font_size.h"

PrjTgFontCachedFontRotate::PrjTgFontCachedFontRotate(PrjTgFontCachedFontSize *parent, const float rotate)
    : m_rotate(rotate)
    , m_parent(parent)
{
}

PrjTgFontCachedFontRotate::~PrjTgFontCachedFontRotate()
{
    for (PrjTgFontCachedFontMoveGlyphX *f : m_listMoveGlyphX) {
        delete f;
    }
    m_listMoveGlyphX.clear();
}

bool PrjTgFontCachedFontRotate::load(const std::vector<uint32_t> &listCharacters, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    TG_FUNCTION_BEGIN();
    PrjTgFontCachedFontMoveGlyphX *f = getCreateIfNotExists(move_glyph_x);
    TG_FUNCTION_END();
    return f->load(listCharacters, move_glyph_y, quality);
}

bool PrjTgFontCachedFontRotate::isEqual(const float rotate) const
{
    return memcmp(&m_rotate, &rotate, sizeof(rotate)) == 0;
}

PrjTgFontCachedFontMoveGlyphX *PrjTgFontCachedFontRotate::getCreateIfNotExists(const float move_glyph_x)
{
    for (PrjTgFontCachedFontMoveGlyphX *f : m_listMoveGlyphX) {
        if (f->isEqual(move_glyph_x)) {
            return f;
        }
    }
    m_listMoveGlyphX.push_back(new PrjTgFontCachedFontMoveGlyphX(this, move_glyph_x));
    return m_listMoveGlyphX.back();
}

const std::string PrjTgFontCachedFontRotate::getFilename() const
{
    return m_parent->getFilename();
}

float PrjTgFontCachedFontRotate::getFontSize() const
{
    return m_parent->getFontSize();
}

float PrjTgFontCachedFontRotate::getRotate() const
{
    return m_rotate;
}

float PrjTgFontCachedFontRotate::getFontHeight(const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphX *f = get(move_glyph_x);
    if (!f) {
        return 0;
    }
    return f->getFontHeight(move_glyph_y, quality);
}

const PrjTgFontCachedFontMoveGlyphX *PrjTgFontCachedFontRotate::get(const float move_glyph_x) const
{
    for (const PrjTgFontCachedFontMoveGlyphX *f : m_listMoveGlyphX) {
        if (f->isEqual(move_glyph_x)) {
            return f;
        }
    }
    return nullptr;
}

float PrjTgFontCachedFontRotate::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter,
                                          float &advance, float &leftBearing, float &rightBearing, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphX *f = get(move_glyph_x);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing, move_glyph_y, quality);
}

const uint8_t *PrjTgFontCachedFontRotate::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontMoveGlyphX *f = get(move_glyph_x);
    if (!f) {
        return nullptr;
    }
    return f->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, move_glyph_y, quality);
}

bool PrjTgFontCachedFontRotate::clear(const float move_glyph_x, const float move_glyph_y, const int quality)
{
    for (size_t i=0;i<m_listMoveGlyphX.size();i++) {
        if (m_listMoveGlyphX[i]->isEqual(move_glyph_x)) {
            if (m_listMoveGlyphX[i]->clear(move_glyph_y, quality)) {
                delete m_listMoveGlyphX[i];
                m_listMoveGlyphX.erase(m_listMoveGlyphX.begin()+i);
            }
            break;
        }
    }
    return m_listMoveGlyphX.empty();
}
