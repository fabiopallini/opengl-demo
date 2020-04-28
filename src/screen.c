#include "screen.h"

GLuint texture_1;
GLuint texture_2;
void drawCube();

bool initGL(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	bool success = true;
	GLenum error = GL_NO_ERROR;
	glViewport(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT);
    //Initialize Projection Matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);
	gluPerspective(45.0, (float)SCREEN_WIDTH/(float)SCREEN_HEIGHT, 0.1f, 200.0);
	gluLookAt(0.0, 0.0, 5.0,0.0, 0.0, 0.0,0.0, 1.0, 0.0); 
    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glClearColor( 0.f, 0.f, 0.f, 1.f );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	error = glGetError();
	if( error != GL_NO_ERROR )
	{
		printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
		success = false;
	}

	texture_1 = loadMedia(0);
	texture_2 = loadMedia(1);

	return success;
}

void render(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//drawTexture(texture_1, 100, 100, 100, 100);
	//drawTexture(texture_2, 280, 100, 100, 100);
	drawCube();
}

GLuint loadTexture(GLuint* pixels, GLuint width, GLuint height){
	GLuint texture;
	glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glBindTexture(GL_TEXTURE_2D, NULL);
    GLenum error = glGetError();
    if(error != GL_NO_ERROR){
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return 0;
    }
	
    return texture;
}

GLuint loadMedia(int color){
	const int CHECKERBOARD_WIDTH = 128;
    const int CHECKERBOARD_HEIGHT = 128;
    const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
    GLuint checkerBoard[CHECKERBOARD_PIXEL_COUNT];
	//Go through pixels
    for(int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i)
    {
        //Get the individual color components
        GLubyte* colors = (GLubyte*)&checkerBoard[i];
		//If the 5th bit of the x and y offsets of the pixel do not match
		if(color == 0){
			if(i / 128 & 16 ^ i % 128 & 16)
			{
				//Set pixel to white
				colors[0] = 0xFF;
				colors[1] = 0xFF;
				colors[2] = 0xFF;
				colors[3] = 0xFF;
			}
			else
			{
				//Set pixel to red
				colors[0] = 0xFF;
				colors[1] = 0x00;
				colors[2] = 0x00;
				colors[3] = 0xFF;
			}
		}
		else{
			if(i / 128 & 16 ^ i % 128 & 16)
			{
				//Set pixel to white
				colors[0] = 0xFF;
				colors[1] = 0xFF;
				colors[2] = 0xFF;
				colors[3] = 0xFF;
			}
			else
			{
				//Set pixel to green
				colors[0] = 0x00;
				colors[1] = 0xFF;
				colors[2] = 0x00;
				colors[3] = 0xFF;
			}
		}
    }
	//Load texture
    return loadTexture(checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT);
}

void drawTexture(GLuint texture, int x, int y, int w, int h){
    if(texture != 0){
		glLoadIdentity();
		glTranslatef(x, y, 0.f);
		glScalef(w, h, 1.f);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(0.f, 0.f); glVertex2f(0.f, 0.f);
            glTexCoord2f(1.f, 0.f); glVertex2f(1.f, 0.f);
            glTexCoord2f(1.f, 1.f); glVertex2f(1.f, 1.f);
            glTexCoord2f(0.f, 1.f); glVertex2f(0.f, 1.f);
        glEnd();
    }
}

int rot = 0;
void drawCube(){
	glLoadIdentity();
	glTranslatef(-0.5f, -0.5f, 0.f);
	glScalef(1, 1, 1.f);
	rot++;
	glRotatef(rot, rot, rot, 0);

	if(texture_1 == 0)
		return;
	glBindTexture(GL_TEXTURE_2D, texture_1);
	glBegin(GL_QUADS);
		// front
		//glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 1.0f, 0.0f);
		// back
		//glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 1.0f, -1.0f);
		// right
		//glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(1.0f, 1.0f, 0.0f);
		// left
		//glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(0.0f, 0.0f, -1.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(0.0f, 1.0f, -1.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 1.0f, 0.0f);
		// top
		//glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 1.0f, -1.0f);
		// bottom
		//glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.f, 0.f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 0.f); glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.f, 1.f); glVertex3f(1.0f, 0.0f, -1.0f);
		glTexCoord2f(0.f, 1.f); glVertex3f(0.0f, 0.0f, -1.0f);
	glEnd();
}