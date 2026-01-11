#include "list_character.h"
#include <limits>
#include <algorithm>

bool ListCharacter::generateFontNameIndexForCharacters(const std::vector<uint32_t> &listCharacter,
                                                       const std::vector<std::string> &listFontFileName,
                                                       std::vector<size_t> &fontNameIndex,
                                                       const std::vector<uint32_t> &listCommonCharacters)
{
    bool ret = true;
    fontNameIndex.clear();
    std::vector<size_t> listAvailableFontNameIndex = getFontIndex(listFontFileName);
    size_t index;
    size_t firstNonCommonCharacterIndex;
    uint32_t character;
    for (size_t i=0;i<listCharacter.size();i++) {
        character = convertCharacter(listCharacter.at(i));
        if (listCharacter.size() > 1 && doesContain(character, listCommonCharacters)) {
            if (i == 0) {
                firstNonCommonCharacterIndex = findFirstCharacterThatIsNotOnTheList(listCharacter, listCommonCharacters);
                if (firstNonCommonCharacterIndex != std::numeric_limits<size_t>::max()) {
                    index = getCharacterFontNameIndex(firstNonCommonCharacterIndex,
                                          fontNameIndex,
                                          listCharacter,
                                          listAvailableFontNameIndex);
                    if (index != std::numeric_limits<size_t>::max()) {
                        fontNameIndex.push_back(index);
                        continue;
                    }
                }
            } else {
                if (fontNameIndex[i-1] != std::numeric_limits<size_t>::max()) {
                    const size_t fontIndex = getFontIndex(listFontFileName[ fontNameIndex[i-1] ]);
                    if (m_listCharacter[fontIndex].doesContain(character)) {
                        fontNameIndex.push_back(fontNameIndex[i-1]);
                        continue;
                    }
                }
            }
        }
        index = getCharacterFontNameIndex(i,
                                          fontNameIndex,
                                          listCharacter,
                                          listAvailableFontNameIndex);
        fontNameIndex.push_back(index);
        if (index == std::numeric_limits<size_t>::max()) {
            ret = false;
        }
    }
    return ret;
}

size_t ListCharacter::findFirstCharacterThatIsNotOnTheList(const std::vector<uint32_t> &listCharacter,
                                                           const std::vector<uint32_t> &listCommonCharacters)
{
    for (size_t i=1;listCharacter.size();i++) {
        if (!doesContain(convertCharacter(listCharacter.at(i)), listCommonCharacters)) {
            return i;
        }
    }
    return std::numeric_limits<size_t>::max();
}

bool ListCharacter::doesContain(const uint32_t character, const std::vector<uint32_t> &listCharacter)
{
    return std::find(listCharacter.begin(), listCharacter.end(), character) != listCharacter.end();
}

size_t ListCharacter::getCharacterFontNameIndex(const size_t indexOfCharacter,
                                                const std::vector<size_t> &listCharacterFontNameIndex,
                                                const std::vector<uint32_t> &listCharacter,
                                                const std::vector<size_t> &listAvailableFontNameIndex)
{
    // check if character's font index was already found
    for (size_t i=0;i<indexOfCharacter;i++) {
        if (listCharacter[indexOfCharacter] == convertCharacter(listCharacter.at(i))) {
            return listCharacterFontNameIndex[i];
        }
    }

    return getCharacterFontNameIndex(convertCharacter(listCharacter[indexOfCharacter]), listAvailableFontNameIndex);
}

size_t ListCharacter::getCharacterFontNameIndex(const uint32_t character, const std::vector<size_t> &listAvailableFontNameIndex)
{
    for (size_t i=0;i<listAvailableFontNameIndex.size();i++) {
        if (m_listCharacter[listAvailableFontNameIndex[i]].doesContain(character)) {
            return i;
        }
    }
    return std::numeric_limits<size_t>::max();
}

/**
 * get index list of font files from FontCharacter
 *
 * @param listFontFileName
 * @return
 */
std::vector<size_t> ListCharacter::getFontIndex(const std::vector<std::string> &listFontFileName)
{
    std::vector<size_t> ret;
    for (size_t i=0;i<listFontFileName.size();i++) {
        ret.push_back(getFontIndex(listFontFileName[i]));
    }
    return ret;
}

/**
 * get index of font from m_listCharacter
 * if font doesn't exits, this does create new FontCharacter
 * into m_listCharacter
 *
 * @param fontFileName
 * @return
 */
size_t ListCharacter::getFontIndex(const std::string &fontFileName)
{
    for (size_t i=0;i<m_listCharacter.size();i++) {
        if (m_listCharacter[i].getFontFile() == fontFileName) {
            return i;
        }
    }
    m_listCharacter.push_back(FontCharacter());
    m_listCharacter.back().load(fontFileName);
    return m_listCharacter.size() - 1;
}

uint32_t ListCharacter::convertCharacter(const uint32_t character)
{
    if (character == '\n' || character == '\r') {
        return ' ';
    }
    return character;
}
