#include "font_character.h"
#include <prj-ttf-reader.h>

std::string FontCharacter::getFontFile() const
{
    return m_fontFile;
}

/**/
bool FontCharacter::load(const std::string &fontFile)
{
    m_fontFile = fontFile;
    prj_ttf_reader_supported_characters_t *supported_characters = prj_ttf_reader_init_supported_character();
    if (prj_ttf_reader_get_supported_characters(fontFile.c_str(), supported_characters) != 0) {
        prj_ttf_reader_clear_supported_character(&supported_characters);
        return false;
    }
    for (uint32_t i=0;i<supported_characters->character_list_count;i++) {
        addCharacter(supported_characters->list_character[i]);
    }
    prj_ttf_reader_clear_supported_character(&supported_characters);
    return true;
}

/**
 * checks if the character is on the list
 *
 * @param character
 * @return true if character is on the list
 */
bool FontCharacter::doesContain(const uint32_t character) const
{
    if (m_listCharacter.empty()
        || m_listCharacter.back() < character
        || m_listCharacter.front() > character) {
        return false;
    }

    size_t middlePosition = m_listCharacter.size()/2;
    return (middlePosition > 0 && doesContain(character, 0, middlePosition - 1))
            || doesContain(character, middlePosition, m_listCharacter.size() - 1);
}

/**
 * checks if character is on the list - between fromIndex and toIndex
 *
 * @param character
 * @param fromIndex
 * @param toIndex
 * @return true if character is on the list
 */
bool FontCharacter::doesContain(const uint32_t character, const size_t fromIndex, const size_t toIndex) const
{
    if (m_listCharacter[fromIndex] == character || m_listCharacter[toIndex] == character) {
        return true;
    }
    if (m_listCharacter[fromIndex] > character) {
        return false;
    }
    if (m_listCharacter[toIndex] < character) {
        return false;
    }
    if (fromIndex == toIndex || fromIndex + 1 == toIndex) {
        return false;
    }
    const size_t middlePosition = (toIndex + fromIndex)/2;
    if (middlePosition > fromIndex + 1) {
        if (doesContain(character, fromIndex + 1, middlePosition - 1)) {
            return true;
        }
    }
    if (middlePosition < toIndex) {
        if (doesContain(character, middlePosition, toIndex - 1)) {
            return true;
        }
    }
    return false;
}

/**
 * add character to list
 *
 * @param character
 */
void FontCharacter::addCharacter(const uint32_t character)
{
    if (m_listCharacter.empty() || m_listCharacter.back() < character) {
        m_listCharacter.push_back(character);
        return;
    }
    if (m_listCharacter.front() > character) {
        m_listCharacter.insert(m_listCharacter.begin(), character);
        return;
    }
    for (size_t i=0;i<m_listCharacter.size();i++) {
        if (m_listCharacter[i] == character) {
            // this should not happen
            return;
        }
        if (m_listCharacter[i] < character) {
            continue;
        }
        m_listCharacter.insert(m_listCharacter.begin()+i, character);
        return;
    }
    // this should not happen
    m_listCharacter.push_back(character);
}

size_t FontCharacter::getCharacterCount() const
{
    return m_listCharacter.size();
}

uint32_t FontCharacter::getCharacter(size_t index) const
{
    return m_listCharacter.at(index);
}
