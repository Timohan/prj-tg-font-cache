/*!
 * \file
 * \brief file prj_tg_font_cache.h
 *
 * main head of PrjTgFontCache
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHE_H
#define PRJ_TG_FONT_CACHE_H

#ifndef TG_EXPORT_FONT_CACHE
#define TG_EXPORT_FONT_CACHE
#endif // TG_EXPORT_FONT_CACHE

#include <string>
#include <vector>
#include <cstdint>

#define DEFAULT_FONT_QUALITY_VALUE 5

class PrjTgFontCachePrivate;

class TG_EXPORT_FONT_CACHE PrjTgFontCache
{
public:
    PrjTgFontCache();
    ~PrjTgFontCache();

    void clear(const std::string &fontFilename, const float fontSize,
               const float rotate = 0.0f, const float move_glyph_x = 0.0f, const float move_glyph_y = 0.0f, const int quality = DEFAULT_FONT_QUALITY_VALUE);
    bool load(const std::vector<uint32_t> &listCharacters, const std::string &fontFilename, const float fontSize, const float rotate = 0.0f, const float move_glyph_x = 0.0f, const float move_glyph_y = 0.0f, const int quality = DEFAULT_FONT_QUALITY_VALUE);
    float getFontHeight(const std::string &fontFilename, const float fontSize, const float rotate = 0.0f, const float move_glyph_x = 0.0f, const float move_glyph_y = 0.0f, const int quality = DEFAULT_FONT_QUALITY_VALUE) const;
    float getKerning(const std::string &fontFilename, const float fontSize, const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, const float rotate = 0.0f, const float move_glyph_x = 0.0f, const float move_glyph_y = 0.0f, const int quality = DEFAULT_FONT_QUALITY_VALUE) const;
    const uint8_t *getGlyphImage(const std::string &fontFilename, const float fontSize, const uint32_t character,
                                 int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY,
                                 int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex,
                                 const float rotate = 0.0f, const float move_glyph_x = 0.0f, const float move_glyph_y = 0.0f, const int quality = DEFAULT_FONT_QUALITY_VALUE) const;

    bool generateFontNameIndexForCharacters(const std::vector<uint32_t> &listCharacter,
                                            const std::vector<std::string> &listFontFileName,
                                            std::vector<size_t> &fontFileNameIndex,
                                            const std::vector<uint32_t> &listCommonCharacters = {' '});
private:
    PrjTgFontCachePrivate *m_private;
};

#endif // TG_EXPORT_FONT_CACHE
