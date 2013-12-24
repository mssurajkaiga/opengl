#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <Eigen/Dense>
#include <GL/glew.h>
#include <GL/glut.h>
using namespace Eigen;

#define BUFFER_OFFSET(bytes) ((GLvoid*) (bytes))
const int NumPoints = 5000;

static char* readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "r");
	if ( fp == NULL ) { return NULL; }
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	buf[size] = ' ';
	fclose(fp);
	return buf;
}

GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
{
	struct Shader {
		const char* filename;
		GLenum type;
		GLchar* source;
		};

	Shader shaders[2] = {
		{ vShaderFile, GL_VERTEX_SHADER, NULL },
		{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
	};

	GLuint program;
	program = glCreateProgram();

	for ( int i = 0; i < 2; ++i ) {
		Shader& s = shaders[i];
		s.source = readShaderSource( s.filename );
		if ( shaders[i].source == NULL ) {
			std::cout << "Failed to read " << s.filename << std::endl;
			exit( EXIT_FAILURE );
		}

		GLuint shader = glCreateShader( s.type );
		glShaderSource( shader, 1, (const GLchar**) &s.source, NULL );
		glCompileShader( shader );
		GLint compiled;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
		if (!compiled) {
			std::cout << s.filename << " failed to compile:" << std::endl;
			GLint logSize;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
			char* logMsg = new char[logSize];
			glGetShaderInfoLog( shader, logSize, NULL, logMsg );
			std::cout << logMsg << std::endl;
			delete [] logMsg;
			exit( EXIT_FAILURE );
		}
	delete [] s.source;
	glAttachShader( program, shader );
	}
// link and error check
	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if ( !linked ) {
		std::cout << "Shader program failed to link"<< std::endl;
		GLint logSize;
		glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cout << logMsg << std::endl;
		delete [] logMsg;
		exit( EXIT_FAILURE );
	}
	// use program object
	glUseProgram(program);
	return program;
}


void init()
{
	Vector3f points[NumPoints];

	// Triangle vertices
	Vector3f vertices[3] = {Vector3f(-1,-1,0), Vector3f(0,1,0), Vector3f(1,-1,0)};
	points[0] = Vector3f(0.25, 0.25, 0);

	// Computing points
	for(int i=1; i<NumPoints; i++) {
		int j = rand() % 3;
		points[i] = (points[i-1] + vertices[j])/2;
	}

	
	GLuint program;
	program = InitShader("vshader.glsl", "fshader.glsl");
	glUseProgram(program);
/*
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	GLuint loc;
	loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	glClearColor(1, 1, 1, 1);
	*/
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_POINTS, 0, NumPoints);
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	
	//glutInitContextVersion( 3, 2 );
	//glutInitContextProfile( GLUT_CORE_PROFILE );

	glutCreateWindow("Sierpinskit Gasket");

	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}