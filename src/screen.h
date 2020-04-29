#ifdef __linux__
    #include <GL/glu.h>
#endif
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#endif

#include <stdio.h>
#include <stdbool.h>

bool initGL(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
GLuint loadMedia(int color);
void drawTexture();
void render(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);