/*!
 * \file
 * \brief file prj_tg_font_cached_font_quality.h
 *
 * main head of PrjTgFontCachedFontQuality
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FONT_QUALITY_H
#define PRJ_TG_FONT_CACHED_FONT_QUALITY_H

#include <string>
#include <vector>
#include <cstdint>
class PrjTgFontCachedFontMoveGlyphY;
class PrjTgFontCachedData;

class PrjTgFontCachedFontQuality
{
public:
    explicit PrjTgFontCachedFontQuality(PrjTgFontCachedFontMoveGlyphY *parent, const int quality);
    ~PrjTgFontCachedFontQuality();

    const std::string getFilename() const;
    bool load(const std::vector<uint32_t> &listCharacters);
    bool isEqual(const int quality) const;
    int getQuality() const;
    float getFontSize() const;
    float getRotate() const;
    float getMoveGlyphX() const;
    float getMoveGlyphY() const;
    float getFontHeight() const;

    float getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex) const;
private:
    float m_fontHeight;
    int m_quality;
    PrjTgFontCachedFontMoveGlyphY *m_parent;
    std::vector<PrjTgFontCachedData *> m_listData;
};

#endif // PRJ_TG_FONT_CACHED_FONT_QUALITY_H