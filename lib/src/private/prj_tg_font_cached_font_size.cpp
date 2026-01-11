/*!
 * \file
 * \brief file prj_tg_font_cached_font_size.cpp
 *
 * main head of PrjTgFontCachedFontSize
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include "prj_tg_font_cached_font_size.h"
#include <cstring>
#include "tg_global_log.h"
#include "prj_tg_font_cached_file.h"
#include "prj_tg_font_cached_font_rotate.h"
#include <prj-ttf-reader.h>
#include <algorithm>
#include <limits>

PrjTgFontCachedFontSize::PrjTgFontCachedFontSize(PrjTgFontCachedFile *parent, const float fontSize)
    : m_fontSize(fontSize)
    , m_parent(parent)
{
}

PrjTgFontCachedFontSize::~PrjTgFontCachedFontSize()
{
    for (PrjTgFontCachedFontRotate *f : m_listRotate) {
        delete f;
    }
    m_listRotate.clear();
}

bool PrjTgFontCachedFontSize::load(const std::vector<uint32_t> &listCharacters, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    TG_FUNCTION_BEGIN();
    PrjTgFontCachedFontRotate *f = getCreateIfNotExists(rotate);
    TG_FUNCTION_END();
    return f->load(listCharacters, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief checks if font size is equal
 *
 * @param fontSize
 * @return true if fontSize is equal
 */
bool PrjTgFontCachedFontSize::isEqual(const float fontSize) const
{
    return memcmp(&m_fontSize, &fontSize, sizeof(fontSize)) == 0;
}

/**
 * @brief get font filename
 *
 * @return full path of font filename
 */
const std::string PrjTgFontCachedFontSize::getFilename() const
{
    return m_parent->getFilename();
}

float PrjTgFontCachedFontSize::getFontSize() const
{
    return m_fontSize;
}

float PrjTgFontCachedFontSize::getFontHeight(const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontRotate *f = PrjTgFontCachedFontSize::get(rotate);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getFontHeight(move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief Get kerning between characters
 *
 * @param leftCharacter left character index, for example 'a' == 97
 * @param rightCharacter right character index, for example 'b' == 98
 * @param advance [out] value from advance field to calculation
 * advance (how much pixels (x) moves for next character) after the drawing
 * @param leftBearing [out] value from bearing field to calculation of left glyph
 * how many pixel (x) moves to right or left side before the drawing
 * @param rightBearing [out] value from bearing field to calculation of right glyph
 * how many pixel (x) moves to right or left side before the drawing
 * @return kerning, if font is not loaded before, returns std::numeric_limits<float>::min()
 */
float PrjTgFontCachedFontSize::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter,
                                          float &advance, float &leftBearing, float &rightBearing, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontRotate *f = PrjTgFontCachedFontSize::get(rotate);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief get glyph image data
 *
 * @param character character index, for example 'a' == 97
 * @param leftX [out] left pixel x on returned image data, filled only if returns image data
 * @param rightX [out] right pixel x on returned image data, filled only if returns image data
 * @param topY [out] top pixel y on returned image data, filled only if returns image data
 * @param bottomY [out] bottom pixel y on returned image data, filled only if returns image data
 * @param offsetX [out] offset position by pixels when drawing a pixel (x)
 * On rotate == 0.0f, this is (almost) always 0, but
 * on rotate, it will change
 * @param offsetY [out] offset position by pixels when drawing a pixel,
 * for example in A or R, it's 0, but with  characters 'j' or 'y' it can be negative value
 * for example, character minus '-' it is  positive value (pixels to up)
 * for example: if 'j' height is 20px, the offset can be -4 (4px to down)
 * NOTE: using rotate will change offset position
 * @param dataWidth data image width
 * @param dataHeight data image height
 * @param imageIndex data image index
 * @return pointer of image data, if not found, then nullptr and glyph should be loaded with function load()
 */
const uint8_t *PrjTgFontCachedFontSize::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontRotate *f = PrjTgFontCachedFontSize::get(rotate);
    if (!f) {
        return nullptr;
    }
    return f->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, move_glyph_x, move_glyph_y, quality);
}

PrjTgFontCachedFontRotate *PrjTgFontCachedFontSize::getCreateIfNotExists(const float rotate)
{
    for (PrjTgFontCachedFontRotate *f : m_listRotate) {
        if (f->isEqual(rotate)) {
            return f;
        }
    }
    m_listRotate.push_back(new PrjTgFontCachedFontRotate(this, rotate));
    return m_listRotate.back();
}

const PrjTgFontCachedFontRotate *PrjTgFontCachedFontSize::get(const float rotate) const
{
    for (const PrjTgFontCachedFontRotate *f : m_listRotate) {
        if (f->isEqual(rotate)) {
            return f;
        }
    }
    return nullptr;
}

bool PrjTgFontCachedFontSize::clear(const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    for (size_t i=0;i<m_listRotate.size();i++) {
        if (m_listRotate[i]->isEqual(rotate)) {
            if (m_listRotate[i]->clear(move_glyph_x, move_glyph_y, quality)) {
                delete m_listRotate[i];
                m_listRotate.erase(m_listRotate.begin()+i);
            }
            break;
        }
    }
    return m_listRotate.empty();
}
