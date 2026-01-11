/*!
 * \file
 * \brief file prj_tg_font_cached_file.cpp
 *
 * main head of PrjTgFontCachedFile
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include "prj_tg_font_cached_file.h"
#include <limits>
#include "tg_global_log.h"

PrjTgFontCachedFile::PrjTgFontCachedFile(const std::string &filename)
    : m_filename(std::move(filename))
{
}

PrjTgFontCachedFile::~PrjTgFontCachedFile()
{
    for (PrjTgFontCachedFontSize *f : m_listCachedByFontSize) {
        delete f;
    }
    m_listCachedByFontSize.clear();
}

/**
 * @brief get font filename
 *
 * @return full path of font filename
 */
const std::string &PrjTgFontCachedFile::getFilename() const
{
    return m_filename;
}

bool PrjTgFontCachedFile::load(const std::vector<uint32_t> &listCharacters, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    TG_FUNCTION_BEGIN();
    PrjTgFontCachedFontSize *f = getCreateIfNotExists(fontSize);
    TG_FUNCTION_END();
    return f->load(listCharacters, rotate, move_glyph_x, move_glyph_y, quality);
}

PrjTgFontCachedFontSize *PrjTgFontCachedFile::getCreateIfNotExists(const float fontSize)
{
    for (PrjTgFontCachedFontSize *f : m_listCachedByFontSize) {
        if (f->isEqual(fontSize)) {
            return f;
        }
    }
    m_listCachedByFontSize.push_back(new PrjTgFontCachedFontSize(this, fontSize));
    return m_listCachedByFontSize[m_listCachedByFontSize.size()-1];
}

const PrjTgFontCachedFontSize *PrjTgFontCachedFile::get(const float fontSize) const
{
    for (const PrjTgFontCachedFontSize *f : m_listCachedByFontSize) {
        if (f->isEqual(fontSize)) {
            return f;
        }
    }
    return nullptr;
}

/**
 * @brief get loaded font height
 *
 * @param fontSize font size
 * @return font height of the font, if font is not loaded before, returns std::numeric_limits<float>::min()
 */
float PrjTgFontCachedFile::getFontHeight(const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontSize *f = get(fontSize);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getFontHeight(rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief Get kerning between characters
 *
 * @param fontSize font size
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
float PrjTgFontCachedFile::getKerning(const float fontSize, const uint32_t leftCharacter, const uint32_t rightCharacter,
                                      float &advance, float &leftBearing, float &rightBearing,
                                      const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontSize *f = get(fontSize);
    if (!f) {
        return std::numeric_limits<float>::min();
    }
    return f->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief get glyph image data
 *
 * @param fontSize font size
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
const uint8_t *PrjTgFontCachedFile::getGlyphImage(const float fontSize, const uint32_t character, int32_t &leftX, int32_t &rightX,
    int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    const PrjTgFontCachedFontSize *f = get(fontSize);
    if (!f) {
        return nullptr;
    }
    return f->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, rotate, move_glyph_x, move_glyph_y, quality);
}

bool PrjTgFontCachedFile::clear(const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    for (size_t i=0;i<m_listCachedByFontSize.size();i++) {
        if (m_listCachedByFontSize[i]->isEqual(fontSize)) {
            if (m_listCachedByFontSize[i]->clear(rotate, move_glyph_x, move_glyph_y, quality)) {
                delete m_listCachedByFontSize[i];
                m_listCachedByFontSize.erase(m_listCachedByFontSize.begin()+i);
            }
            break;
        }
    }
    return m_listCachedByFontSize.empty();
}