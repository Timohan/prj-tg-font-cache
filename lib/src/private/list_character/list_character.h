/*!
 * \file
 * \brief file list_character.h
 *
 * main head of ListCharacter
 * collection of characters for fonts
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef LIST_CHARACTER_H
#define LIST_CHARACTER_H

#include <string>
#include <vector>
#include <cstdint>

#include "font_character.h"

class ListCharacter
{
public:
    bool generateFontNameIndexForCharacters(const std::vector<uint32_t> &listCharacter,
                                            const std::vector<std::string> &listFontFileName,
                                            std::vector<size_t> &fontNameIndex,
                                            const std::vector<uint32_t> &listCommonCharacters);

private:
    std::vector<FontCharacter> m_listCharacter;

    std::vector<size_t> getFontIndex(const std::vector<std::string> &listFontFileName);
    size_t getFontIndex(const std::string &fontFileName);

    size_t getCharacterFontNameIndex(const size_t indexOfCharacter, const std::vector<size_t> &listCharacterFontNameIndex, const std::vector<uint32_t> &listCharacter, const std::vector<size_t> &listAvailableFontNameIndex);
    size_t getCharacterFontNameIndex(const uint32_t character, const std::vector<size_t> &listAvailableFontNameIndex);

    static bool doesContain(const uint32_t character, const std::vector<uint32_t> &listCharacter);
    static size_t findFirstCharacterThatIsNotOnTheList(const std::vector<uint32_t> &listCharacter,
                                                       const std::vector<uint32_t> &listCommonCharacters);
    static uint32_t convertCharacter(const uint32_t character);


};

#endif // LIST_CHARACTER_H
