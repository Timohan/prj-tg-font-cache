/*!
 * \file
 * \brief file font_character.h
 *
 * main head of FontCharacter
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef FONT_CHARACTER_H
#define FONT_CHARACTER_H

#include <string>
#include <vector>
#include <cstdint>

class FontCharacter
{
public:
    std::string getFontFile() const;
    bool load(const std::string &fontFile);

    bool doesContain(const uint32_t character) const;

    size_t getCharacterCount() const;
    void addCharacter(const uint32_t character);
    uint32_t getCharacter(size_t index) const;

private:
    std::string m_fontFile;
    std::vector<uint32_t> m_listCharacter;


    bool doesContain(const uint32_t character, const size_t fromIndex, const size_t toIndex) const;

};

#endif // FONT_CHARACTER_H
