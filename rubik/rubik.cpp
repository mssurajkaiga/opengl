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

GLuint smallcube; //The OpenGL id of the display list

void handleKeypress(unsigned char key,int x,int y)
{
    switch(key) {
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

 

void draw_smallcube(float BOX_SIZE)

{
 
    //Red face
    glBegin(GL_QUADS);
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();
 
    //Green face
    glBegin(GL_QUADS);
    glColor3f(0.0,1.0,0.0);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();
 
    //Blue face
    glBegin(GL_QUADS);
    glColor3f(0.0,0.0,1.0);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    //Yellow face
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,0.0);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();
 
    //Orange face
    glBegin(GL_QUADS);
    glColor3f(1.0,0.4,0.0);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    //White face
    glBegin(GL_QUADS);
    glColor3f(1.0,1.0,1.0);
    glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    glFlush();

}

 

 

void initRendering()

{

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f,0.0f,0.2f,1.0f);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    //Set up a display list for drawing a cube

    smallcube = glGenLists(1); //Make room for the display list
    glNewList(smallcube, GL_COMPILE); //Begin the display list
    draw_smallcube(2.0); //Add commands for drawing a black area to the display list
    glEndList(); //End the display list

}

void drawScene()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glCallList(smallcube);
    glutSwapBuffers();

}

void update(int value) 
{

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

    //glutTimerFunc(25, update, 0);

    glutMainLoop();

    return 0;
}