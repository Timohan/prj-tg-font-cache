/*!
 * \file
 * \brief file drawtext.cpp
 *
 * Inits and draws the text
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#include "drawtext.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

/*!
 * \brief DrawText::DrawText
 *
 * Constructor
 */
DrawText::DrawText()
{

}

/*!
 * \brief DrawText::init
 *
 * inits the text
 * Generates the texture & vertices with function addImage()
 *
 * \param cache cache
 * \param listOfCharacters list of character
 * \param character character
 * \param fontFilename full file path of the font
 * \param fontSize font size
 * \param rotate rotate
 * \param move_glyph_x move glyph (x)
 * \param move_glyph_y move glyph (y)
 * \param quality quality
 * \return true on success
 */
bool DrawText::init(PrjTgFontCache &cache, const std::vector<uint32_t> &listOfCharacters, const std::string &fontFilename, const float fontSize,
                    const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    int verticesIndex = 0;
    uint32_t i;
    float positionLeftX, positionBottomY;
    Vertice *vertices;
    float advance = 0, leftBearning = 0, rightBearning = 0;
    float kerning;


    glGenVertexArrays(1, &m_vertexArrayObject);
    glGenBuffers(1, &m_vertexBufferObject);
    glBindVertexArray(m_vertexArrayObject);

    vertices = new Vertice[listOfCharacters.size()*4];
    positionLeftX = 20;
    for (i=0;i<listOfCharacters.size();i++) {
        if (i==0) {
            // set the line y position
            int32_t leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight;
            uint64_t imageIndex;
            cache.getGlyphImage(fontFilename, fontSize, listOfCharacters.at(i), leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, rotate, move_glyph_x, move_glyph_y, quality);
            positionBottomY = static_cast<float>(bottomY-topY+offsetY) + 20;
        } else {
            kerning = cache.getKerning(fontFilename, fontSize, listOfCharacters.at(i-1), listOfCharacters.at(i), advance, leftBearning, rightBearning, rotate, move_glyph_x, move_glyph_y, quality);
            advance = std::roundf(advance);
            if (leftBearning < 0 && leftBearning > -1) {
                leftBearning = -1;
            } else {
                leftBearning = static_cast<float>(static_cast<int>(leftBearning));
            }
            advance -= leftBearning;
            if (rightBearning < 0 && rightBearning > -1) {
                rightBearning = -1;
            } else {
                rightBearning = static_cast<float>(static_cast<int>(rightBearning));
            }
            kerning += static_cast<float>(rightBearning + advance);
            positionLeftX += kerning;
            positionLeftX = std::roundf(positionLeftX);
        }
        addImage(positionLeftX, positionBottomY, cache, listOfCharacters.at(i), fontFilename, fontSize, vertices, verticesIndex, rotate, move_glyph_x, move_glyph_y, quality);
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice)*listOfCharacters.size()*4, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    delete[]vertices;
    return true;
}

/*!
 * \brief DrawText::render
 *
 * Renders the text
 */
void DrawText::render()
{
    size_t i;
    glBindVertexArray(m_vertexArrayObject);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    for (i=0;i<m_listTextureImage.size();i++) {
        glBindTexture(GL_TEXTURE_2D, m_listTextureImage.at(i));
        glDrawArrays(GL_TRIANGLE_STRIP, static_cast<int>(i)*4, 4);
    }
    glBindVertexArray(0);
}

/*!
 * \brief DrawText::addImage
 *
 * Create image and vertices
 * \param positionLeftX current x position
 * \param positionBottomY current y position
 * \param character character
 * \param fontFilename full file path of the font
 * \param fontSize font size
 * \param vertices [in/out] fills vertices to here
 * \param verticesIndex [in/out] current vertixes index of vertices
 * \param rotate rotate
 * \param move_glyph_x move glyph (x)
 * \param move_glyph_y move glyph (y)
 * \param quality quality
 * \return true on success
 */

bool DrawText::addImage(float positionLeftX, float positionBottomY, PrjTgFontCache &cache, uint32_t character,
                        const std::string &fontFilename, const float fontSize, Vertice *vertices, int &verticesIndex,
                        const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality)
{
    int x, y, i;
    unsigned char* imageData = nullptr;
    GLuint textureImage;

    glGenTextures(1, &textureImage);

    if (!textureImage) {
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, textureImage);

    int32_t leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight;
    uint64_t imageIndex;
    const uint8_t *data = cache.getGlyphImage(fontFilename, fontSize, character, leftX, rightX, topY, bottomY, offsetX, offsetY, dataWidth, dataHeight, imageIndex, rotate, move_glyph_x, move_glyph_y, quality);
    int32_t h = (bottomY-topY);
    int32_t w = (rightX-leftX);

    imageData = new unsigned char[w*h*4];
    for (y=0;y<h;y++) {
        for (x=0;x<w;x++) {
            for (i=0;i<4;i++) {
                if (data[((y+topY)*dataWidth+x+leftX)]) {
                    if (i == 3) {
                        imageData[(y*w+x)*4+i] = 255;
                    } else {
                        imageData[(y*w+x)*4+i] = data[((y+topY)*dataWidth+x+leftX)];
                    }
                } else {
                    imageData[(y*w+x)*4+i] = 0;
                }
            }
        }
    }

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    delete[]imageData;

    vertices[verticesIndex].x = positionLeftX;
    vertices[verticesIndex].y = positionBottomY - static_cast<float>(h) - static_cast<float>(offsetY);
    vertices[verticesIndex].s = 0;
    vertices[verticesIndex].t = 0;
    verticesIndex++;
    vertices[verticesIndex].x = positionLeftX + static_cast<float>(w);
    vertices[verticesIndex].y = positionBottomY - static_cast<float>(h) - static_cast<float>(offsetY);
    vertices[verticesIndex].s = 1;
    vertices[verticesIndex].t = 0;
    verticesIndex++;
    vertices[verticesIndex].x = positionLeftX;
    vertices[verticesIndex].y = positionBottomY - static_cast<float>(offsetY);
    vertices[verticesIndex].s = 0;
    vertices[verticesIndex].t = 1;
    verticesIndex++;
    vertices[verticesIndex].x = positionLeftX + static_cast<float>(w);
    vertices[verticesIndex].y = positionBottomY - static_cast<float>(offsetY);
    vertices[verticesIndex].s = 1;
    vertices[verticesIndex].t = 1;
    verticesIndex++;

    if (textureImage == 0) {
        return false;
    }
    m_listTextureImage.push_back(textureImage);
    return true;
}
