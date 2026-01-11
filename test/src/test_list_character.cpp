#include "test_list_character.h"
#include "../../lib/src/private/tg_global_log.h"

std::vector<uint32_t> TestListCharacter::utf8_to_codepoints(const std::string& utf8_string)
{
    std::vector<uint32_t> codepoints;
    for (size_t i = 0; i < utf8_string.length();) {
        uint32_t codepoint = 0;
        unsigned char first_byte = utf8_string[i];

        if ((first_byte & 0x80) == 0x00) { // 1-byte character
            codepoint = first_byte;
            i += 1;
        } else if ((first_byte & 0xE0) == 0xC0) { // 2-byte character
            if (i + 1 >= utf8_string.length()) break;
            codepoint = ((first_byte & 0x1F) << 6) | (utf8_string[i+1] & 0x3F);
            i += 2;
        } else if ((first_byte & 0xF0) == 0xE0) { // 3-byte character
            if (i + 2 >= utf8_string.length()) break;
            codepoint = ((first_byte & 0x0F) << 12) | ((utf8_string[i+1] & 0x3F) << 6) | (utf8_string[i+2] & 0x3F);
            i += 3;
        } else if ((first_byte & 0xF8) == 0xF0) { // 4-byte character
            if (i + 3 >= utf8_string.length()) break;
            codepoint = ((first_byte & 0x07) << 18) | ((utf8_string[i+1] & 0x3F) << 12) | ((utf8_string[i+2] & 0x3F) << 6) | (utf8_string[i+3] & 0x3F);
            i += 4;
        } else {
            // Invalid UTF-8 sequence, skip a byte
            i++;
        }
        codepoints.push_back(codepoint);
    }
    return codepoints;
}

bool TestListCharacter::test()
{
    PrjTgFontCache cache;
    return test(0) && test(1) && test(2)
            && testCreatedCache(0, cache)
            && testCreatedCache(1, cache)
            && testCreatedCache(2, cache)
            && testCreatedCacheSpace(0, cache)
            && testCreatedCacheSpace(1, cache)
            && testCreatedCacheSpace(2, cache)
            && testCreatedCache65333(0, cache)
            && testCreatedCache65333(1, cache)
            && testCreatedCache65333x2(0, cache, false)
            && testCreatedCache65333x2(1, cache, false)
            && testCreatedCache65333x2(0, cache, true)
            && testCreatedCache65333x2(1, cache, true);
}

bool TestListCharacter::test(size_t fontOrder)
{
    PrjTgFontCache cache;

    std::vector<std::string> listFontFiles;
    std::vector<size_t> fontNameIndex;
    std::vector<size_t> correctIndex;

    switch (fontOrder) {
        case 0:
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(0);
            correctIndex.push_back(1);
            correctIndex.push_back(2);
            break;
        case 1:
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            correctIndex.push_back(2);
            break;
        case 2:
        default:
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            correctIndex.push_back(2);
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            break;
    }


    std::vector<uint32_t> listCharacter = utf8_to_codepoints("WsaWતી中国");

    if (!cache.generateFontNameIndexForCharacters(listCharacter, listFontFiles, fontNameIndex)) {
        TG_ERROR_LOG("Generating character index failed");
        return false;
    }

    for (size_t i=0;i<4;i++) {
        if (fontNameIndex[i] != correctIndex.at(0)) {
            TG_ERROR_LOG("Incorrect font index", fontOrder, fontNameIndex[i], i);
            return false;
        }
    }
    for (size_t i=4;i<6;i++) {
        if (fontNameIndex[i] != correctIndex.at(1)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    for (size_t i=6;i<8;i++) {
        if (fontNameIndex[i] != correctIndex.at(2)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    return true;
}

bool TestListCharacter::testCreatedCache(size_t fontOrder, PrjTgFontCache &cache)
{
    std::vector<std::string> listFontFiles;
    std::vector<size_t> fontNameIndex;
    std::vector<size_t> correctIndex;

    switch (fontOrder) {
        case 0:
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(0);
            correctIndex.push_back(1);
            correctIndex.push_back(2);
            break;
        case 1:
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            correctIndex.push_back(2);
            break;
        case 2:
        default:
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            correctIndex.push_back(2);
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            break;
    }


    std::vector<uint32_t> listCharacter = utf8_to_codepoints("WsaWતી中国");

    if (!cache.generateFontNameIndexForCharacters(listCharacter, listFontFiles, fontNameIndex)) {
        TG_ERROR_LOG("Generating character index failed");
        return false;
    }

    for (size_t i=0;i<4;i++) {
        if (fontNameIndex[i] != correctIndex.at(0)) {
            TG_ERROR_LOG("Incorrect font index", fontOrder, fontNameIndex[i], i);
            return false;
        }
    }
    for (size_t i=4;i<6;i++) {
        if (fontNameIndex[i] != correctIndex.at(1)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    for (size_t i=6;i<8;i++) {
        if (fontNameIndex[i] != correctIndex.at(2)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    return true;
}

bool TestListCharacter::testCreatedCacheSpace(size_t fontOrder, PrjTgFontCache &cache)
{
    std::vector<std::string> listFontFiles;
    std::vector<size_t> fontNameIndex;
    std::vector<size_t> correctIndex;

    switch (fontOrder) {
        case 0:
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(0);
            correctIndex.push_back(1);
            correctIndex.push_back(2);
            break;
        case 1:
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            correctIndex.push_back(2);
            break;
        case 2:
        default:
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/samyak-fonts/Samyak-Gujarati.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            correctIndex.push_back(2);
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            break;
    }

    std::vector<uint32_t> listCharacter = utf8_to_codepoints(" WsaW તી 中国 ");

    if (!cache.generateFontNameIndexForCharacters(listCharacter, listFontFiles, fontNameIndex)) {
        TG_ERROR_LOG("Generating character index failed");
        return false;
    }

    for (size_t i=0;i<6;i++) {
        if (fontNameIndex[i] != correctIndex.at(0)) {
            TG_ERROR_LOG("Incorrect font index", fontOrder, fontNameIndex[i], i);
            return false;
        }
    }
    for (size_t i=6;i<9;i++) {
        if (fontNameIndex[i] != correctIndex.at(1)) {
            TG_ERROR_LOG("Incorrect font index", i, fontNameIndex[i]);
            return false;
        }
    }
    for (size_t i=9;i<12;i++) {
        if (fontNameIndex[i] != correctIndex.at(2)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    return true;
}

bool TestListCharacter::testCreatedCache65333(size_t fontOrder, PrjTgFontCache &cache)
{
    std::vector<std::string> listFontFiles;
    std::vector<size_t> fontNameIndex;
    std::vector<size_t> correctIndex;

    switch (fontOrder) {
        case 0:
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(0);
            correctIndex.push_back(1);
            break;
        case 1:
        default:
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            break;
    }

    std::vector<uint32_t> listCharacter = utf8_to_codepoints(" WsaW 中国 ");
    for (size_t i=0;i<listCharacter.size();i++) {
        if (listCharacter[i] == ' ') {
            listCharacter[i] = 65333;
        }
    }
    std::vector<uint32_t> listCommonCharacters;
    listCommonCharacters.push_back(' ');
    listCommonCharacters.push_back(65333);
    if (!cache.generateFontNameIndexForCharacters(listCharacter, listFontFiles, fontNameIndex, listCommonCharacters)) {
        TG_ERROR_LOG("Generating character index failed");
        return false;
    }

    for (size_t i=0;i<6;i++) {
        if (fontNameIndex[i] != correctIndex.at(0)) {
            TG_ERROR_LOG("Incorrect font index", fontOrder, fontNameIndex[i], i);
            return false;
        }
    }
    for (size_t i=6;i<9;i++) {
        if (fontNameIndex[i] != correctIndex.at(1)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    return true;
}

bool TestListCharacter::testCreatedCache65333x2(size_t fontOrder, PrjTgFontCache &cache, bool onlySecondTo65333)
{
    std::vector<std::string> listFontFiles;
    std::vector<size_t> fontNameIndex;
    std::vector<size_t> correctIndex;

    switch (fontOrder) {
        case 0:
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            correctIndex.push_back(0);
            correctIndex.push_back(1);
            break;
        case 1:
        default:
            listFontFiles.push_back("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");
            listFontFiles.push_back("/usr/share/fonts/truetype/freefont/FreeSans.ttf");
            correctIndex.push_back(1);
            correctIndex.push_back(0);
            break;
    }

    int count = 0;
    std::vector<uint32_t> listCharacter = utf8_to_codepoints("  WsaW  中国  ");
    for (size_t i=0;i<listCharacter.size();i++) {
        if (listCharacter[i] == ' ') {
            if (!onlySecondTo65333 || (count & 2) == 0) {
                listCharacter[i] = 65333;
            }
            count++;
        }
    }
    std::vector<uint32_t> listCommonCharacters;
    listCommonCharacters.push_back(' ');
    listCommonCharacters.push_back(65333);
    if (!cache.generateFontNameIndexForCharacters(listCharacter, listFontFiles, fontNameIndex, listCommonCharacters)) {
        TG_ERROR_LOG("Generating character index failed");
        return false;
    }

    for (size_t i=0;i<8;i++) {
        if (fontNameIndex[i] != correctIndex.at(0)) {
            TG_ERROR_LOG("Incorrect font index", fontOrder, fontNameIndex[i], i);
            return false;
        }
    }
    for (size_t i=8;i<listCharacter.size();i++) {
        if (fontNameIndex[i] != correctIndex.at(1)) {
            TG_ERROR_LOG("Incorrect font index");
            return false;
        }
    }
    return true;
}