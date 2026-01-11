#include "prj_tg_font_cached_font_quality.h"
#include "prj_tg_font_cached_data.h"
#include "tg_global_log.h"
#include "prj_tg_font_cached_font_move_glyph_y.h"
#include <algorithm>
#include <limits>

PrjTgFontCachedFontQuality::PrjTgFontCachedFontQuality(PrjTgFontCachedFontMoveGlyphY *parent, const int quality)
    : m_fontHeight(0)
    , m_quality(quality)
    , m_parent(parent)
{

}
PrjTgFontCachedFontQuality::~PrjTgFontCachedFontQuality()
{
    for (PrjTgFontCachedData *f : m_listData) {
        delete f;
    }
    m_listData.clear();
}

bool PrjTgFontCachedFontQuality::load(const std::vector<uint32_t> &listCharacters)
{
    std::vector<uint32_t> tmpListCharacters(listCharacters);
    for (PrjTgFontCachedData *data : m_listData) {
        data->removeLoadedCharacters(tmpListCharacters);
    }
    if (tmpListCharacters.empty()) {
        TG_FUNCTION_END();
        return true;
    }
    std::sort(tmpListCharacters.begin(), tmpListCharacters.end());
    PrjTgFontCachedData *data = new PrjTgFontCachedData(this);

    if (m_listData.empty()) {
        data->addRequiredCharacters(tmpListCharacters);
    }
    bool ret = data->load(tmpListCharacters);
    if (ret) {
        if (m_listData.empty()) {
            ret = data->calculateFontHeight(tmpListCharacters, m_fontHeight);
        }
    }
    if (ret) {
        m_listData.push_back(data);
    } else {
        delete data;
    }
    TG_FUNCTION_END();
    return true;
}

bool PrjTgFontCachedFontQuality::isEqual(const int quality) const
{
    return m_quality == quality;
}

const std::string PrjTgFontCachedFontQuality::getFilename() const
{
    return m_parent->getFilename();
}

int PrjTgFontCachedFontQuality::getQuality() const
{
    return m_quality;
}

float PrjTgFontCachedFontQuality::getFontSize() const
{
    return m_parent->getFontSize();
}

float PrjTgFontCachedFontQuality::getRotate() const
{
    return m_parent->getRotate();
}

float PrjTgFontCachedFontQuality::getMoveGlyphX() const
{
    return m_parent->getMoveGlyphX();
}

float PrjTgFontCachedFontQuality::getMoveGlyphY() const
{
    return m_parent->getMoveGlyphY();
}

float PrjTgFontCachedFontQuality::getFontHeight() const
{
    return m_fontHeight;
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
float PrjTgFontCachedFontQuality::getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter,
                                          float &advance, float &leftBearing, float &rightBearing) const
{
    if (m_listData.empty()) {
        return std::numeric_limits<float>::min();
    }
    float kerning;
    for (const PrjTgFontCachedData *data: m_listData) {
        if (data->getKerning(leftCharacter, rightCharacter, advance, leftBearing, rightBearing, kerning)) {
            return kerning;
        }
    }
    return std::numeric_limits<float>::min();
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
const uint8_t *PrjTgFontCachedFontQuality::getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex) const
{
    for (const PrjTgFontCachedData *data : m_listData) {
        const uint8_t *ret = data->getGlyphImage(character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex);
        if (ret) {
            return ret;
        }
    }
    return nullptr;
}
