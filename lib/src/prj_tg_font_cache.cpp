/*!
 * \file
 * \brief file prj_tg_font_cache.cpp
 *
 * main head of PrjTgFontCache
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include "prj_tg_font_cache.h"
#include "private/prj_tg_font_cache_private.h"

PrjTgFontCache::PrjTgFontCache()
    : m_private(new PrjTgFontCachePrivate())
{
}

PrjTgFontCache::~PrjTgFontCache()
{
    delete m_private;
}

/**
 * loads characters into cache
 *
 * after loading getGlyphImage() and other functions be used
 *
 * @param listCharacters
 * @param fontFilename
 * @param fontSize
 * @param rotate
 * @param move_glyph_x
 * @param move_glyph_y
 * @param quality
 * @return
 */
bool PrjTgFontCache::load(const std::vector<uint32_t> &listCharacters, const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    return m_private->load(listCharacters, fontFilename, fontSize, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * get loaded font height
 *
 * PrjTgFontCache::load() must be used before using this function
 *
 * @param fontFilename full filepath of font
 * @param fontSize font size
 * @param rotate
 * @param move_glyph_x
 * @param move_glyph_y
 * @param quality
 * @return font height if if font is not loaded, then it returns std::numeric_limits<float>::min()
 */
float PrjTgFontCache::getFontHeight(const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    return m_private->getFontHeight(fontFilename, fontSize, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief Get kerning between characters
 *
 * PrjTgFontCache::load() must be used before using this function
 *
 * @param fontFilename full filepath of font
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
float PrjTgFontCache::getKerning(const std::string &fontFilename, const float fontSize, const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing,
                                 const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    return m_private->getKerning(fontFilename, fontSize, leftCharacter, rightCharacter, advance, leftBearing, rightBearing, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * @brief get glyph image data
 *
 * PrjTgFontCache::load() must be used before using this function
 *
 * @param fontFilename full filepath of font
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
 * @param rotate rotate in radians, must be between >= 0 && < M_PI*2
 * @param dataWidth data image width
 * @param dataHeight data image height
 * @param imageIndex data image index
 * @param move_glyph_x glyph drawing move in quality pixels (x), this must be >= 0 && < quality
 * for example, if move_glyph_x is 1 and quality is 5, glyph drawing is 0.2 pixels to right
 * @param move_glyph_y glyph drawing move in quality pixels (y), this must be >= 0 && < quality
 * for example, if move_glyph_y is 1 and quality is 5, glyph drawing is 0.2 pixels to up
 * @param quality quality of the anti-aliasing, use 5 or 10 (5 is faster than 10)
 * @return pointer of image data, if not found, then nullptr and glyph should be loaded with function load()
 */
const uint8_t *PrjTgFontCache::getGlyphImage(const std::string &fontFilename, const float fontSize, const uint32_t character, int32_t &leftX, int32_t &rightX,
                                             int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY,
                                             int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const
{
    return m_private->getGlyphImage(fontFilename, fontSize, character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * clears font glyphs from the cache
 *
 * @param fontFilename
 * @param fontSize
 * @param rotate
 * @param move_glyph_x
 * @param move_glyph_y
 * @param quality
 */
void PrjTgFontCache::clear(const std::string &fontFilename, const float fontSize,
               const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    m_private->clear(fontFilename, fontSize, rotate, move_glyph_x, move_glyph_y, quality);
}

/**
 * generates fontFileNameIndex from character list and font files priority list
 *
 * @param listCharacter [in] character list
 * @param listFontFileName [in] font files priority list
 * @param fontFileNameIndex [out] this count will set same as listCharacter
 * it tells which font file belongs is set as certain character
 *
 * for example:
 * if fontFileNameIndex[0] == 1, it means 1st character (listCharacter[0]) is with 2nd font (listFontFileName[1])
 * if fontFileNameIndex[1] == 1, it means 2nd character (listCharacter[1]) is with 2nd font (listFontFileName[1])
 * if fontFileNameIndex[2] == 0, it means 3rd character (listCharacter[2]) is with 1st font (listFontFileName[0])
 * if fontFileNameIndex[3] == std::numeric_limits<size_t>::max(), then it means, 4th character doesn't have glyph
 * in any listFontFileName
 * @param listCommonCharacters list of characters, that can be taken from multiple font files
 *
 * If it's 1st character from the listCharacter, the 2nd character is the most priority font for this character
 * Other cases:
 * If it's character from the listCharacter, the previous character is the most priority font for this character
 *
 * For example:
 * If listCommonCharacters contains ' ' (space)
 * " ગુજર A ર " - in this case 1st space is taken from the same font file that contains 'ગુ'
 * and 2nd space is taken from the same font file that contains 'ર'
 * and 3rd space is taken from the same font file that contains 'A'
 * and 4th (last) space is taken from the same font file that contains 'ર'
 *
 * @return false if even one of the values in fontFileNameIndex is std::numeric_limits<size_t>::max()
 * true if all values are set correctly
 */
bool PrjTgFontCache::generateFontNameIndexForCharacters(const std::vector<uint32_t> &listCharacter,
                                        const std::vector<std::string> &listFontFileName,
                                        std::vector<size_t> &fontFileNameIndex,
                                        const std::vector<uint32_t> &listCommonCharacters)
{
    return m_private->generateFontNameIndexForCharacters(listCharacter,
                                        listFontFileName,
                                        fontFileNameIndex,
                                        listCommonCharacters);
}
