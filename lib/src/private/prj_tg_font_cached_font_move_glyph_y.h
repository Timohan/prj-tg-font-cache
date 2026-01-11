/*!
 * \file
 * \brief file prj_tg_font_cached_font_move_glyph_y.h
 *
 * main head of PrjTgFontCachedFontMoveGlyphY
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_Y_H
#define PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_Y_H

#include <string>
#include <vector>
#include <cstdint>
class PrjTgFontCachedFontMoveGlyphX;
class PrjTgFontCachedFontQuality;

class PrjTgFontCachedFontMoveGlyphY
{
public:
    explicit PrjTgFontCachedFontMoveGlyphY(PrjTgFontCachedFontMoveGlyphX *parent, const float move_glyph_y);
    ~PrjTgFontCachedFontMoveGlyphY();

    bool clear(const int quality);
    const std::string getFilename() const;
    float getFontSize() const;
    float getRotate() const;
    float getMoveGlyphX() const;
    float getMoveGlyphY() const;
    bool load(const std::vector<uint32_t> &listCharacters, const int quality);
    bool isEqual(const float move_glyph_y) const;
    float getFontHeight(const int quality) const;
    float getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const int quality) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const int quality) const;

private:
    float m_move_glyph_y;
    PrjTgFontCachedFontMoveGlyphX *m_parent;
    std::vector<PrjTgFontCachedFontQuality *> m_listQuality;

    PrjTgFontCachedFontQuality *getCreateIfNotExists(const int quality);
    const PrjTgFontCachedFontQuality *get(const int quality) const;
};

#endif // PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_Y_H