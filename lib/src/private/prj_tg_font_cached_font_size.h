/*!
 * \file
 * \brief file prj_tg_font_cached_font_size.h
 *
 * main head of PrjTgFontCachedFontSize
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FONT_SIZE_H
#define PRJ_TG_FONT_CACHED_FONT_SIZE_H

#include <string>
#include <vector>
#include <cstdint>
class PrjTgFontCachedFile;
class PrjTgFontCachedFontRotate;

class PrjTgFontCachedFontSize
{
public:
    explicit PrjTgFontCachedFontSize(PrjTgFontCachedFile *parent, const float fontSize);
    ~PrjTgFontCachedFontSize();

    bool load(const std::vector<uint32_t> &listCharacters, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    const std::string getFilename() const;

    bool clear(const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    bool isEqual(const float fontSize) const;
    float getFontSize() const;
    float getFontHeight(const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    float getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
private:
    float m_fontSize;
    std::vector<PrjTgFontCachedFontRotate *> m_listRotate;
    PrjTgFontCachedFile *m_parent;

    PrjTgFontCachedFontRotate *getCreateIfNotExists(const float rotate);
    const PrjTgFontCachedFontRotate *get(const float rotate) const;
};

#endif // PRJ_TG_FONT_CACHED_FONT_SIZE_H