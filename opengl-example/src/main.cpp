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

#include "mainwindow.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <prj_tg_font_cache.h>

static MainWindow m_mainWindow;

static void help()
{
    printf("Usage: ./opengl-example -s <\"text string\"> -f <path to ttf> -z <font size> -r <rotate 0 to PI*2>\n");
    printf("-s \"text string\"\n");
    printf("-f \"full filepath to font.tff\"\n");
    printf("-z font size (float)\n");
    printf("-r rotate (float), must be between 0 to PI*2\n");
    printf("-a accurary of drawing (int), must be at least 2, prefer 5 or 10, 5 means each pixel is drawed by 5x5 subpixels\n");
    printf("-x subpixel move x (float), must be > 0 < accurary of drawing\n");
    printf("-y subpixel move y (float), must be > 0 < accurary of drawing\n");
    printf("For example:\n./opengl-example -s \"text goes here\" -f \"/tmp/font.ttf\" -z 25.0 -r 4.5 -x 1 -y 1\n");
}

std::vector<uint32_t> utf8_to_codepoints(const std::string& utf8_string)
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

/*!
 * \brief main
 * \param argc
 * \param argv
 * \return
 */
int main(int argc , char *argv[])
{
    int ret = EXIT_SUCCESS;
    int opt;
    char *textString = nullptr;
    char *fileFont = nullptr;
    float fontSize = 60;
    float rotate = 0;
    float move_x = 0, move_y = 0;
    int accuracy_quality = 5;
    PrjTgFontCache cache;


    while((opt = getopt(argc, argv, "hs:f:z:r:x:y:a:")) != -1)  {
        switch(opt)
        {
            case 'h':
                help();
                free(textString);
                free(fileFont);
                exit(0);
                break;
            case 's':
                textString = strdup(optarg);
                break;
            case 'f':
                fileFont = strdup(optarg);
                break;
            case 'a':
                accuracy_quality = atoi(optarg);
                break;
            case 'z':
                fontSize = static_cast<float>(atof(optarg));
                break;
            case 'r':
                rotate = static_cast<float>(atof(optarg));
                break;
            case 'x':
                move_x = static_cast<float>(atof(optarg));
                break;
            case 'y':
                move_y = static_cast<float>(atof(optarg));
                break;
            default:
                break;
        }
    }

    if (!textString) {
        printf("Error: Text string is missing\n");
        help();
        ret = EXIT_FAILURE;
    } else if (!fileFont) {
        printf("Error: Full filepath to font is missing\n");
        help();
        ret = EXIT_FAILURE;
    } else if (fontSize <= 0) {
        printf("Error: Font size must be larger than 0\n");
        help();
        ret = EXIT_FAILURE;
    }

    if (ret != EXIT_FAILURE) {
        std::vector<uint32_t> listOfCharacters = utf8_to_codepoints(textString);
        if (cache.load(listOfCharacters, fileFont, fontSize, rotate, move_x, move_y, accuracy_quality)) {
            m_mainWindow.initWindow(cache, listOfCharacters, fileFont, fontSize, rotate, move_x, move_y, accuracy_quality);
            m_mainWindow.render();
        } else {
            printf("Error: .tff file parsing is failed\n");
            ret = EXIT_FAILURE;
        }
    }

    free(textString);
    free(fileFont);
    return ret;
}
