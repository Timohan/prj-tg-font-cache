#include "test_font_character.h"
#include "libfiles/list_character/font_character.h"
#include "../../lib/src/private/tg_global_log.h"

bool TestFontCharacter::test()
{
    if (!testCharacterOrder()) {
        return false;
    }
    if (!testDoesContain()) {
        return false;
    }

    return true;
}

bool TestFontCharacter::testCharacterOrder()
{
    FontCharacter fontCharacter;
    fontCharacter.addCharacter(5);
    fontCharacter.addCharacter(3);
    fontCharacter.addCharacter(5);
    fontCharacter.addCharacter(3);
    fontCharacter.addCharacter(1);
    fontCharacter.addCharacter(6);

    if (fontCharacter.getCharacterCount() != 4) {
        TG_ERROR_LOG("Incorrect number of list", fontCharacter.getCharacterCount());
        return false;
    }

    if (fontCharacter.getCharacter(0) != 1) {
        TG_ERROR_LOG("Incorrect number of character", fontCharacter.getCharacter(0));
        return false;
    }
    if (fontCharacter.getCharacter(1) != 3) {
        TG_ERROR_LOG("Incorrect number of character", fontCharacter.getCharacter(1));
        return false;
    }
    if (fontCharacter.getCharacter(2) != 5) {
        TG_ERROR_LOG("Incorrect number of character", fontCharacter.getCharacter(2));
        return false;
    }
    if (fontCharacter.getCharacter(3) != 6) {
        TG_ERROR_LOG("Incorrect number of character", fontCharacter.getCharacter(3));
        return false;
    }
    return true;
}

bool TestFontCharacter::testDoesContain()
{
    for (uint32_t i=0;i<10;i++) {
        if (!testDoesContain(1+i, 100, 1+i)) {
            return false;
        }
        if (!testDoesContain(10+i, 1000, 1+i)) {
            return false;
        }
        if (!testDoesContain(11+i, 10000, 1+i)) {
            return false;
        }
        if (!testDoesContain(1+i, 100+i, 1+i)) {
            return false;
        }
        if (!testDoesContain(10+i, 1000+i, 1+i)) {
            return false;
        }
        if (!testDoesContain(11+i, 10000+i, 1+i)) {
            return false;
        }
        if (!testDoesContain(1, 100+i, 1+i)) {
            return false;
        }
        if (!testDoesContain(10, 1000+i, 1+i)) {
            return false;
        }
        if (!testDoesContain(11, 10000+i, 1+i)) {
            return false;
        }
    }
    return true;
}

bool TestFontCharacter::testDoesContain(const uint32_t fromIndex, const uint32_t toIndex, const uint32_t plus)
{
    FontCharacter fontCharacter;
    uint32_t currentIndex = fromIndex;
    while (1) {
        if (currentIndex > toIndex) {
            break;
        }
        fontCharacter.addCharacter(currentIndex);
        currentIndex += plus;
    }
    currentIndex = fromIndex;
    while (1) {
        if (currentIndex > toIndex) {
            if (fontCharacter.doesContain(currentIndex)) {
                TG_ERROR_LOG("Contain character", fromIndex, toIndex, plus);
                return false;
            }
            break;
        }
        if (!fontCharacter.doesContain(currentIndex)) {
            TG_ERROR_LOG("Not contain character", fromIndex, toIndex, plus, currentIndex);
            return false;
        }
        currentIndex += plus;
    }
    if (plus > 1) {
        currentIndex = fromIndex + plus/2;
        while (1) {
            if (currentIndex > toIndex) {
                if (fontCharacter.doesContain(currentIndex)) {
                    TG_ERROR_LOG("Contain character", fromIndex, toIndex, plus);
                    return false;
                }
                break;
            }
            if (fontCharacter.doesContain(currentIndex)) {
                TG_ERROR_LOG("Contain character", fromIndex, toIndex, plus, currentIndex);
                return false;
            }
            currentIndex += plus;
        }
    }
    return true;
}
