/*!
 * \file
 * \brief file test_font_character.h
 *
 * test the class FontCharacter
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef TEST_FONT_CHARACTER_H
#define TEST_FONT_CHARACTER_H

#include <string>
#include <vector>
#include <cstdint>

class TestFontCharacter
{
public:
    static bool test();

private:
    static bool testCharacterOrder();
    static bool testDoesContain();
    static bool testDoesContain(const uint32_t fromIndex, const uint32_t toIndex, const uint32_t plus);

};

#endif // TEST_FONT_CHARACTER_H
