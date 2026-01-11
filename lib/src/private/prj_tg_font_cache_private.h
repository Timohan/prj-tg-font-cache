/*!
 * \file
 * \brief file prj_tg_font_cache_private.h
 *
 * main head of PrjTgFontCachePrivate
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHE_PRIVATE_H
#define PRJ_TG_FONT_CACHE_PRIVATE_H

#include <string>
#include <vector>
#include <cstdint>
#include <mutex>
class PrjTgFontCachedFile;
#include "list_character/list_character.h"

class PrjTgFontCachePrivate
{
public:
    PrjTgFontCachePrivate();
    ~PrjTgFontCachePrivate();

    bool load(const std::vector<uint32_t> &listCharacters, const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    float getFontHeight(const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    float getKerning(const std::string &fontFilename, const float fontSize, const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    const uint8_t *getGlyphImage(const std::string &fontFilename, const float fontSize, const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality) const;
    void clear(const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);

    bool generateFontNameIndexForCharacters(const std::vector<uint32_t> &listCharacter,
                                        const std::vector<std::string> &listFontFileName,
                                        std::vector<size_t> &fontNameIndex,
                                        const std::vector<uint32_t> &listCommonCharacters);
private:
    std::vector<PrjTgFontCachedFile *> m_listCacheFile;
    ListCharacter m_listCharacter;
    std::mutex m_mutex;

    PrjTgFontCachedFile *getCreateIfNotExists(const std::string &fontFilename);
    const PrjTgFontCachedFile *get(const std::string &fontFilename) const;
};

#endif // PRJ_TG_FONT_CACHE_PRIVATE_H
