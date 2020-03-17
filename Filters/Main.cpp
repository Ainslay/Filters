#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>

#include "src\Picture.h"
#include "src\Filters.h"

Picture picture("res/zd3.txt");

void ChangeViewPort(int width, int height)
{
	const float aspectRatio = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100 / aspectRatio, 100 / aspectRatio, -100 / aspectRatio, 100 / aspectRatio, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu()
{
	system("cls");
	cout << "Change brightness: [+] / [-]\n";
	cout << "Change gamma: [F] / [G]\n";
	cout << "Change red channel: [Q] / [W]\n";
	cout << "Change green channel: [A] / [S]\n";
	cout << "Change blue channel: [Z] / [X]\n";
	cout << "Restore the picture: [R]\n";
	cout << "Filters:\n";
	cout << "High pass filter: [1]\n";
	cout << "Low pass filter: [2]\n";
	cout << "Edge filter: [3]\n";
	cout << "Exit: [E]\n\n";

	cout << "Brightness: " << brightness << " Gamma: " << gamma << endl;
	cout << "R: " << red_filter << " G: " << green_filter << " B: " << blue_filter << endl;
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glBegin(GL_POINTS);
    
    for (int i = -(picture.resolution.width)/2, k = 0; i < picture.resolution.width/2 && k < picture.resolution.width; i++, k++) 
	{
        for (int j = -(picture.resolution.height)/2, l = 0; j < picture.resolution.height/2 && l<picture.resolution.height; j++, l++)
		{
            glColor3d(pow(picture.pointsColors[k][l].red/255.0+brightness+red_filter/255.0, 1.0/gamma),
					  pow(picture.pointsColors[k][l].green/255.0+brightness+green_filter/255.0, 1.0/gamma),
                      pow(picture.pointsColors[k][l].blue/255.0+brightness+blue_filter/255.0, 1.0/gamma));
            glVertex2d(j, i);
        }
    }

    glEnd();
    glPopMatrix();
    glutSwapBuffers();
}

void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
	{
		if(red_filter < 255)
			red_filter += 5;
	}
		break;
	case 'w':
	{
		if (red_filter > 0)
			red_filter -= 5;
	}
		break;
	case 'a':
	{
		if(green_filter < 255)
			green_filter += 5;
	}
		break;
	case 's':
	{
		if (green_filter > 0)
			green_filter -= 5;
	}
		break;
	case 'z':
	{
		if (blue_filter < 255)
			blue_filter += 5;
	}
		break;
	case 'x':
	{
		if (blue_filter > 0)
			blue_filter -= 5;
	}
		break;
	case 'f':
	{
		if(gamma < 1.0)
			gamma += 0.02;
	}
		break;
	case 'g':
		if (gamma > -1.0)
			gamma -= 0.02;
		break;
	case '+':
	{
		if (brightness < 1.0)
			brightness += 0.02;
	}
		break;
	case '-':
	{
		if (brightness > -1.0)
			brightness -= 0.02;
	}
		break;
	case 'r':
		{
			ClearFilters(picture);
			cout << "Restored default picture" << endl;
		}
		break;
	case 'e':
		exit(0);
		break;
	case '1':
		for (int i = 0; i < 9; i++)
		{
			mask[i] = 1;
		}

		ChangeRedChannel(picture);
		ChangeGreenChannel(picture);
		ChangeBlueChannel(picture);
		cout << "Filtr dolnoprzepustowy wlaczony" << endl;
		break;

	case '2':
		mask[0] = -1;
		mask[1] = -1;
		mask[2] = -1;
		mask[3] = -1;
		mask[4] = -1;
		mask[5] = -1;
		mask[6] = -1;
		mask[7] = -1;
		mask[8] = -1;

		ChangeRedChannel(picture);
		ChangeGreenChannel(picture);
		ChangeBlueChannel(picture);
		cout << "Filtr gornoprzepustowy zostal wlaczony" << endl;
		break;

	case '3':
		mask[0] = 0;
		mask[1] = -1;
		mask[2] = 0;
		mask[3] = -1;
		mask[4] = 4;
		mask[5] = -1;
		mask[6] = 0;
		mask[7] = -1;
		mask[8] = 0;

		ChangeRedChannel(picture);
		ChangeGreenChannel(picture);
		ChangeBlueChannel(picture);
		cout << "Filtr krawedziowy zostal wlaczony" << endl;
		break;
	}
	Menu();
}

void Idle()
{
	glutPostRedisplay();
}


int main(int argc, char* argv[]) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(200, 200);
	glutCreateWindow("Filters");

	// Binding essential fuctions
	glutReshapeFunc(ChangeViewPort);
	glutDisplayFunc(Render);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Key);

	glClearColor(1, 1, 1, 1);

	if (GLEW_OK != glewInit()) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	Menu();

	glutMainLoop();

	return 0;
}