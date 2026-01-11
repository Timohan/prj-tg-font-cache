/*!
 * \file
 * \brief file test_list_character.h
 *
 * test the class ListCharacter
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef TEST_LIST_CHARACTER_H
#define TEST_LIST_CHARACTER_H

#include <string>
#include <vector>
#include <cstdint>
#include <prj_tg_font_cache.h>

class TestListCharacter
{
public:
    static bool test();

private:
    static std::vector<uint32_t> utf8_to_codepoints(const std::string& utf8_string);
    static bool test(size_t fontOrder);
    static bool testCreatedCache(size_t fontOrder, PrjTgFontCache &cache);
    static bool testCreatedCacheSpace(size_t fontOrder, PrjTgFontCache &cache);
    static bool testCreatedCache65333(size_t fontOrder, PrjTgFontCache &cache);
    static bool testCreatedCache65333x2(size_t fontOrder, PrjTgFontCache &cache, bool onlySecondTo65333);

};

#endif // TEST_LIST_CHARACTER_H
