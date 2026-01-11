/*!
 * \file
 * \brief file prj_tg_font_cached_data.h
 *
 * main head of PrjTgFontCachedData
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef PRJ_TG_FONT_CACHED_DATA_H
#define PRJ_TG_FONT_CACHED_DATA_H

#include <string>
#include <vector>
#include <cstdint>
#include <mutex>
#include <prj-ttf-reader.h>
class PrjTgFontCachedFontQuality;

class PrjTgFontCachedData
{
public:
    explicit PrjTgFontCachedData(PrjTgFontCachedFontQuality *parent);
    ~PrjTgFontCachedData();

    bool load(const std::vector<uint32_t> &listCharacters);
    void removeLoadedCharacters(std::vector<uint32_t> &listCharacters);
    void addRequiredCharacters(std::vector<uint32_t> &listCharacters);
    bool calculateFontHeight(const std::vector<uint32_t> &listCharacters, float &fontHeight);
    bool getKerning(const uint32_t leftCharacter, const uint32_t rightCharacter, float &advance, float &leftBearing, float &rightBearing, float &kerning) const;
    const uint8_t *getGlyphImage(const uint32_t character, int32_t &leftX, int32_t &rightX, int32_t &topY, int32_t &bottomY, int32_t &offsetX, int32_t &offsetY, int32_t &dataWidth, int32_t &dataHeight, uint64_t &imageIndex) const;
private:
    std::vector<uint32_t>m_listCharacter;
    PrjTgFontCachedFontQuality *m_parent;
    prj_ttf_reader_data_t *m_data;
    std::mutex m_mutex;
    static uint64_t m_globalImageIndex;
    uint64_t m_imageIndex;

};

#endif // PRJ_TG_FONT_CACHED_DATA_H