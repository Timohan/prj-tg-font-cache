/*!
 * \file
 * \brief file prj_tg_font_cached_file.h
 *
 * main head of PrjTgFontCachedFile
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_FILE_H
#define PRJ_TG_FONT_CACHED_FILE_H

#include <string>
#include <vector>
#include <cstdint>
#include "prj_tg_font_cached_font_size.h"

class PrjTgFontCachedFile
{
public:
    explicit PrjTgFontCachedFile(const std::string &filename);
    ~PrjTgFontCachedFile();
    const std::string &getFilename() const;

    bool clear(const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    bool load(const std::vector<uint32_t> &listCharacters, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    float getFontHeight(const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    float getKerning(const float fontSize, const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    const uint8_t *getGlyphImage(const float fontSize, const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;

private:
    std::string m_filename;
    std::vector<PrjTgFontCachedFontSize *> m_listCachedByFontSize;

    PrjTgFontCachedFontSize *getCreateIfNotExists(const float fontSize);
    const PrjTgFontCachedFontSize *get(const float fontSize) const;
};

#endif // PRJ_TG_FONT_CACHED_FILE_H
