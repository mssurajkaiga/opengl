#include <glut.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include "imageloader.h"

using namespace std;

float _angle = 0;

float i;

int k=0;

const float BOX_SIZE = 2.0f;

GLuint white_textureId;

GLuint red_textureId;

GLuint blue_textureId;

GLuint green_textureId;

GLuint yellow_textureId;

GLuint orange_textureId;

GLuint _displayListId_smallcube; //The OpenGL id of the display list

//Makes the image into a texture, and returns the id of the texture

GLuint loadTexture(Image* image) {

    GLuint textureId;

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D,

                 0,

                 GL_RGB,

                 image->width, image->height,

                 0,

                 GL_RGB,

                 GL_UNSIGNED_BYTE,

                 image->pixels);

    return textureId;

}

void handleKeypress(unsigned char key,int x,int y)

{

    switch(key)

    {

        case 27:

        exit(0);

    }

}

 

void handleResize(int w,int h)

{

    glViewport(0,0,w,h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45.0,(double)w/(double)h,1.0,200);

    gluLookAt(0.0f,5.5f, 15.0f,

              0.0f,0.0f,0.0f,

              0.0f,1.0f,0.0f);

}

 

void draw_smallcube()

{

 

    Image* image = loadBMP("white.bmp");

    white_textureId = loadTexture(image);

    delete image;

 

        Image* image1 = loadBMP("red.bmp");

    red_textureId = loadTexture(image1);

    delete image1;

 

        Image* image2 = loadBMP("blue.bmp");

    blue_textureId = loadTexture(image2);

    delete image2;

 

        Image* image3 = loadBMP("orange.bmp");

    orange_textureId = loadTexture(image3);

    delete image3;

 

        Image* image4 = loadBMP("green.bmp");

    green_textureId = loadTexture(image4);

    delete image4;

 

        Image* image5 = loadBMP("yellow.bmp");

    yellow_textureId = loadTexture(image5);

    delete image5;

 

  

     glEnable(GL_TEXTURE_2D);

     glBindTexture(GL_TEXTURE_2D, orange_textureId);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

 

    //Top face

    //glNormal3f(0.0, 1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

 

    glEnd();

    glDisable(GL_TEXTURE_2D);

 

 

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, red_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

    //Bottom face

 

    //glNormal3f(0.0, -1.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

 

    glEnd();

 

 

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, green_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

 

    //Left face

    //glNormal3f(-1.0, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

 

    glEnd();

 

 

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, blue_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

 

    //Right face

    //glNormal3f(1.0, 0.0f, 0.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

 

    glEnd();

 

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, white_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

 

    //Front face

    //glNormal3f(0.0, 0.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);

 

    glEnd();

 

 

    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, yellow_textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 

    glBegin(GL_QUADS);

    //Back face

    //glNormal3f(0.0, 0.0f, -1.0f);

    glTexCoord2f(0.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 0.0f);

    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(1.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);

    glTexCoord2f(0.0f, 1.0f);

    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);

 

    glEnd();

    //glDisable(GL_TEXTURE_2D);

 

     //glutSwapBuffers();

}

 

 

void initRendering()

{

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_COLOR_MATERIAL);

    //glEnable(GL_NORMALIZE);

    //glEnable(GL_COLOR_MATERIAL);

    glClearColor(0.0f,0.0f,0.2f,1.0f);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

 

    

 

 

    //Set up a display list for drawing a cube

    _displayListId_smallcube = glGenLists(1); //Make room for the display list

    glNewList(_displayListId_smallcube, GL_COMPILE); //Begin the display list

    draw_smallcube(); //Add commands for drawing a black area to the display list

    glEndList(); //End the display list

 

 

}

void drawScene()

{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    glTranslatef(0,-5,-10);

    glRotatef(-_angle, 2.0f, 2.0f, 0.0f);

    

    for(int i=0;i<5;i+=2)

    {

        for(int j=0;j<5;j+=2)

        {

            for(int k=0;k<5;k+=2)

            {

            glPushMatrix();

            glTranslatef(i,j,k);

            glCallList(_displayListId_smallcube);

            glPopMatrix();

            }

        }

    }

 

    glutSwapBuffers();

}

void update(int value) {

    _angle += 2.0f;

    if (_angle > 360) {

        _angle -= 360;

    }

    glutPostRedisplay();

    glutTimerFunc(10, update, 0);

}

int main(int argc,char** argv)

{

    glutInit(&argc,argv);

    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);

    glutInitWindowSize(800,800);

 

    glutCreateWindow("basic shape");

    initRendering();

    glutFullScreen();

 

    glutDisplayFunc(drawScene);

    glutKeyboardFunc(handleKeypress);

    glutReshapeFunc(handleResize);

    glutTimerFunc(25, update, 0);

 

    glutMainLoop();

 

    return 0;
}