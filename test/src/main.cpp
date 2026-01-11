/*!
 * \file
 * \brief file main.cpp
 *
 * Main of opengl example via glfw
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <prj_tg_font_cache.h>
#include <limits>
#include "../../lib/src/private/tg_global_log.h"
#include "test_font_character.h"
#include "test_list_character.h"

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc , char *argv[])
{
    const char *fontFile = "/usr/share/fonts/truetype/freefont/FreeSans.ttf";
    std::vector<uint32_t> listCharacters;
    PrjTgFontCache cache;
    float advance, leftBearing, rightBearing;
    listCharacters.push_back(32);
    listCharacters.push_back('a');
    if (!cache.load(listCharacters, fontFile, 20)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    if (!cache.load(listCharacters, fontFile, 21)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    if (!cache.load(listCharacters, fontFile, 20)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    if (!cache.load(listCharacters, fontFile, 21)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    listCharacters.push_back('A');
    if (!cache.load(listCharacters, fontFile, 20)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    if (!cache.load(listCharacters, fontFile, 21)) {
        TG_ERROR_LOG("Failed to load fonts", fontFile);
    }
    float fontHeight = cache.getFontHeight(fontFile, 20);
    if (std::abs(fontHeight - std::numeric_limits<float>::min()) <= 0) {
        TG_ERROR_LOG("Failed to get font height", fontFile, "size: ", 20);
    } else {
        TG_INFO_LOG("Font size for (20): ", fontHeight);
    }
    fontHeight = cache.getFontHeight(fontFile, 21);
    if (std::abs(fontHeight - std::numeric_limits<float>::min()) <= 0) {
        TG_ERROR_LOG("Failed to get font height", fontFile, "size: ", 21);
    } else {
        TG_INFO_LOG("Font size for (21): ", fontHeight);
    }
    float kerning = cache.getKerning(fontFile, 20, 'A', 'j', advance, leftBearing, rightBearing);
    TG_INFO_LOG("Font kerning for (20): ", kerning, advance, leftBearing, rightBearing);
    kerning = cache.getKerning(fontFile, 21, 'A', 'j', advance, leftBearing, rightBearing);
    TG_INFO_LOG("Font kerning for (21): ", kerning, advance, leftBearing, rightBearing);
    kerning = cache.getKerning(fontFile, 20, 'A', ' ', advance, leftBearing, rightBearing);
    TG_INFO_LOG("Font kerning for (20): ", kerning, advance, leftBearing, rightBearing);
    kerning = cache.getKerning(fontFile, 21, 'A', ' ', advance, leftBearing, rightBearing);
    TG_INFO_LOG("Font kerning for (21): ", kerning, advance, leftBearing, rightBearing);

    TestFontCharacter testFontCharacter;
    if (!testFontCharacter.test()) {
        TG_ERROR_LOG("TestFontCharacter failed");
        return false;
    }
    if (!TestListCharacter::test()) {
        TG_ERROR_LOG("TestListCharacter failed");
        return false;
    }

    return true;
}
