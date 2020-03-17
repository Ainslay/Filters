#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "src\Picture.h"
#include "src\Exception.h"

void changeViewPort(int w, int h)
{
	glViewport(0, 0, w, h);
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();
}

int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Filters");

	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewPort);
	glutDisplayFunc(render);

	if (GLEW_OK != glewInit()) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	try
	{
		Picture picture("res/zd3.txt");
	}
	catch (Exception ex)
	{
		ex.PrintInfo();
		exit(ex.GetErrorCode());
	}

	glutMainLoop();

	return 0;
}