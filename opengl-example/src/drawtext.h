/*!
 * \file
 * \brief file drawtext.h
 *
 * Inits and draws the text
 *
 * Copyright of Timo Hannukkala. All rights reserved.
 *
 * \author Timo Hannukkala <timohannukkala@hotmail.com>
 */

#ifndef DRAWTEXT_H
#define DRAWTEXT_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <prj_tg_font_cache.h>

/*!
 * \brief The Vertice struct
 *
 * 2D texture vertice point
 */
struct Vertice
{
    float x, y;
    float s, t;
};

class DrawText
{
public:
    DrawText();
    bool init(PrjTgFontCache &cache, const std::vector<uint32_t> &listOfCharacters, const std::string &fontFilename, const float fontSize, const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
    void render();

private:
    GLuint m_vertexBufferObject;
    GLuint m_vertexArrayObject;
    std::vector<GLuint> m_listTextureImage;
    bool addImage(float positionLeftX, float positionBottomY, PrjTgFontCache &cache, uint32_t character, const std::string &fontFilename, const float fontSize, Vertice *vertices, int &verticesIndex,
                  const float rotate, const float move_glyph_x, const float move_glyph_y, const int quality);
};

#endif // DRAWTEXT_H
