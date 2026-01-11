/*!
 * \file
 * \brief file prj_tg_font_cached_data.cpp
 *
 * main head of PrjTgFontCachedData
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include "prj_tg_font_cached_data.h"
#include <algorithm>
#include "tg_global_log.h"
#include "prj_tg_font_cached_font_quality.h"

 uint64_t PrjTgFontCachedData::m_globalImageIndex = 0;

PrjTgFontCachedData::PrjTgFontCachedData(PrjTgFontCachedFontQuality *parent)
    : m_parent(parent)
    , m_data(nullptr)
    , m_imageIndex(0)
{

}
PrjTgFontCachedData::~PrjTgFontCachedData()
{
    if (m_data) {
        prj_ttf_reader_clear_data(&m_data);
    }
}

bool PrjTgFontCachedData::load(const std::vector<uint32_t> &listCharacters)
{
    TG_FUNCTION_BEGIN();
    m_data = prj_ttf_reader_init_data();
    if (!m_data) {
        TG_ERROR_LOG("prj_ttf_reader_init_data return failed");
        TG_FUNCTION_END();
        return false;
    }
    if (prj_ttf_reader_generate_glyphs_list_characters_rotate(listCharacters.data(), static_cast<uint32_t>(listCharacters.size()),
            m_parent->getFilename().c_str(), m_parent->getFontSize(), m_parent->getQuality(), m_data,
            m_parent->getRotate(), m_parent->getMoveGlyphX(), m_parent->getMoveGlyphY())
        || !m_data->image.width
        || !m_data->image.height) {
        prj_ttf_reader_clear_data(&m_data);
        TG_ERROR_LOG("generating glyphs failed");
        TG_FUNCTION_END();
        return false;
    }
    m_mutex.lock();
    m_globalImageIndex++;
    m_imageIndex = m_globalImageIndex;
    m_mutex.unlock();
    TG_FUNCTION_END();
    return true;
}

/**
 * removes already loaded characters from the listCharacters
 *
 * @param listCharacters [in/out] removes loaded characters from the list
 */
void PrjTgFontCachedData::removeLoadedCharacters(std::vector<uint32_t> &listCharacters)
{
    std::vector<uint32_t>::reverse_iterator it;
    for (it=listCharacters.rbegin();it!=listCharacters.rend();it++) {
        if (std::find(m_listCharacter.begin(), m_listCharacter.end(), *it) != m_listCharacter.end()) {
            listCharacters.erase(it.base());
        }
    }
}

/**
 * add already loaded characters from the listCharacters
 *
 * @param listCharacters [in/out] removes loaded characters from the list
 */
void PrjTgFontCachedData::addRequiredCharacters(std::vector<uint32_t> &listCharacters)
{
    if (std::find(listCharacters.begin(), listCharacters.end(), 'A') != listCharacters.end()) {
        return;
    }

    prj_ttf_reader_supported_characters_t *supported_characters = prj_ttf_reader_init_supported_character();
    if (!supported_characters) {
        TG_ERROR_LOG("Failed to init supported characters");
        return;
    }
    if (prj_ttf_reader_get_supported_characters(m_parent->getFilename().c_str(), supported_characters)) {
        TG_ERROR_LOG("Could not get supported characters from font: ", m_parent->getFilename().c_str());
        prj_ttf_reader_clear_supported_character(&supported_characters);
        return;
    }
    for (uint32_t i=0;i<supported_characters->character_list_count;i++) {
        if (supported_characters->list_character[i] == 'A') {
            listCharacters.push_back('A');
        }
    }
    prj_ttf_reader_clear_supported_character(&supported_characters);
}

bool PrjTgFontCachedData::calculateFontHeight(const std::vector<uint32_t> &listCharacters, float &fontHeight)
{
    TG_FUNCTION_BEGIN();
    size_t i, c = listCharacters.size();
    const prj_ttf_reader_glyph_data_t *glyph;
    glyph = prj_ttf_reader_get_character_glyph_data('A', m_data);
    if (glyph) {
        fontHeight = static_cast<float>(glyph->image_pixel_bottom_y-glyph->image_pixel_top_y+glyph->image_pixel_offset_line_y);
        return true;
    }

    for (i=0;i<c;i++) {
        glyph = prj_ttf_reader_get_character_glyph_data(listCharacters.at(i), m_data);
        if (!glyph) {
            continue;
        }

        // set the line y position
        fontHeight = static_cast<float>(glyph->image_pixel_bottom_y-glyph->image_pixel_top_y+glyph->image_pixel_offset_line_y);
        return true;
    }

    TG_FUNCTION_END();
    return false;
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
bool PrjTgFontCachedData::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter,
                                      float &advance, float &leftBearing, float &rightBearing, float &kerning) const
{
    const prj_ttf_reader_glyph_data_t *glyph;
    if (leftCharacter != 0) {
        glyph = prj_ttf_reader_get_character_glyph_data(leftCharacter, m_data);
        if (!glyph) {
            return false;
        }
        advance = glyph->image_pixel_advance_x;
        leftBearing = glyph->image_pixel_bearing;
    } else {
        leftBearing = 0;
        advance = 0;
    }
    if (rightCharacter != 0) {
        glyph = prj_ttf_reader_get_character_glyph_data(rightCharacter, m_data);
        if (!glyph) {
            rightBearing = 0;
            return false;
        }
        rightBearing = glyph->image_pixel_bearing;
    } else {
        rightBearing = 0;
    }
    kerning = prj_ttf_reader_get_kerning(leftCharacter, rightCharacter, m_data);
    return true;
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
 * @param imageIndex index of the image
 * @return pointer of image data, if not found, then nullptr and glyph should be loaded with function load()
 */
const uint8_t *PrjTgFontCachedData::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX,
                                                  int32_t &topY, int32_t &bottomY,
                                                  int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex) const
{
    const prj_ttf_reader_glyph_data_t *glyph = prj_ttf_reader_get_character_glyph_data(character, m_data);
    if (!glyph) {
        return nullptr;
    }
    leftX = glyph->image_pixel_left_x;
    rightX = glyph->image_pixel_right_x;
    topY = glyph->image_pixel_top_y;
    bottomY = glyph->image_pixel_bottom_y;
    offsetX = glyph->image_pixel_offset_line_x;
    offsetY = glyph->image_pixel_offset_line_y;
    dataWidth = m_data->image.width;
    dataHeight = m_data->image.height;
    imageIndex = m_imageIndex;
    return m_data->image.data;
}