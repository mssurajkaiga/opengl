#include <GL/glut.h>
#include <glew.h>

void unnamed()
{
	GLuint abuffer;

	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);

	GLuint buffer;

	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, N);
	
	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Modern OpenGL - 1");

	glewInit();
	glutDisplayFunc(display);
	init();

	glutMainLoop();
	return 0;
}