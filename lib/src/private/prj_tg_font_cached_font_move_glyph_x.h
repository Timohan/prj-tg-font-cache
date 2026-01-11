/*!
 * \file
 * \brief file prj_tg_font_cached_font_move_glyph_x.h
 *
 * main head of PrjTgFontCachedFontMoveGlyphX
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_X_H
#define PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_X_H

#include <string>
#include <vector>
#include <cstdint>
class PrjTgFontCachedFontRotate;
class PrjTgFontCachedFontMoveGlyphY;

class PrjTgFontCachedFontMoveGlyphX
{
public:
    explicit PrjTgFontCachedFontMoveGlyphX(PrjTgFontCachedFontRotate *parent, const float move_glyph_x);
    ~PrjTgFontCachedFontMoveGlyphX();

    bool clear(const float move_glyph_y, const int quality);
    const std::string getFilename() const;
    float getFontSize() const;
    float getRotate() const;
    float getMoveGlyphX() const;
    bool load(const std::vector<uint32_t> &listCharacters, const float move_glyph_y, const int quality);
    bool isEqual(const float move_glyph_x) const;
    float getFontHeight(const float move_glyph_y, const int quality) const;
    float getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float move_glyph_y, const int quality) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float move_glyph_y, const int quality) const;
private:
    float m_move_glyph_x;
    PrjTgFontCachedFontRotate *m_parent;
    std::vector<PrjTgFontCachedFontMoveGlyphY *> m_listMoveGlyphY;

    PrjTgFontCachedFontMoveGlyphY *getCreateIfNotExists(const float move_glyph_y);
    const PrjTgFontCachedFontMoveGlyphY *get(const float move_glyph_y) const;
};

#endif // PRJ_TG_FONT_CACHED_FONT_MOVE_GLYPH_X_H