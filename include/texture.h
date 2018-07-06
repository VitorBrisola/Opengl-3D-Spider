#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glut.h>

void loadTexture(const char *,GLuint *);
void loadTexture2d(const char *,GLuint *);
void loadTextureCubeMap(const char *,GLuint *);
void FreeTexture( GLuint );

#endif