/*!
 * \file
 * \brief file prj_tg_font_cached_font_rotate.h
 *
 * main head of PrjTgFontCachedFontRotate
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FONT_ROTATE_H
#define PRJ_TG_FONT_CACHED_FONT_ROTATE_H

#include <string>
#include <vector>
#include <cstdint>
class PrjTgFontCachedFontSize;
class PrjTgFontCachedFontMoveGlyphX;

class PrjTgFontCachedFontRotate
{
public:
    explicit PrjTgFontCachedFontRotate(PrjTgFontCachedFontSize *parent, const float rotate);
    ~PrjTgFontCachedFontRotate();

    bool load(const std::vector<uint32_t> &listCharacters, const float move_glyph_x, const float move_glyph_y, const int quality);
    bool clear(const float move_glyph_x, const float move_glyph_y, const int quality);

    const std::string getFilename() const;
    bool isEqual(const float rotate) const;
    float getFontSize() const;
    float getRotate() const;
    float getFontHeight(const float move_glyph_x, const float move_glyph_y, const int quality) const;
    float getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float move_glyph_x, const float move_glyph_y, const int quality) const;

private:
    float m_rotate;
//    float m_fontHeight;
    std::vector<PrjTgFontCachedFontMoveGlyphX *> m_listMoveGlyphX;
    PrjTgFontCachedFontSize *m_parent;

    PrjTgFontCachedFontMoveGlyphX *getCreateIfNotExists(const float move_glyph_x);
    const PrjTgFontCachedFontMoveGlyphX *get(const float move_glyph_x) const;
};

#endif // PRJ_TG_FONT_CACHED_FONT_ROTATE_H