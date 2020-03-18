#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>

#include "src\Picture.h"
#include "src\Filter.h"
#include "src\StatisticalFilters.h"

Picture picture("res/zd3.txt");

Filter highPass({ 0.0, -1.0, 0.0, -1.0, 20.0, -1.0, 0.0, -1.0, 0.0 });
Filter lowPass({ 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 });
Filter edge({ 0.0, -1.0, 0.0, -1.0, 8.0, -1.0, 0.0, -1.0, 0.0 });

void ChangeViewPort(int width, int height)
{
	const float aspectRatio = (float)width / (float)height;
	
	//glPointSize((width/picture.resolution.width) + (height/200));
	
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 200, 0 / aspectRatio, 200 / aspectRatio, -10, 10);
	//glOrtho(-100, 100 / aspectRatio, -100 / aspectRatio, 100 / aspectRatio, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu()
{
	system("cls");
	cout << " ---=== Controls ===---\n";
	cout << " Change brightness:    [+]/[-]\n";
	cout << " Change gamma:         [F]/[G]\n";
	cout << " Change red channel:   [Q]/[W]\n";
	cout << " Change green channel: [A]/[S]\n";
	cout << " Change blue channel:  [Z]/[X]\n";
	cout << "\n ---=== Filters ===---\n";
	cout << " High pass filter: [1]\n";
	cout << " Low pass filter:  [2]\n";
	cout << " Edge filter:      [3]\n";
	cout << " Median filter:    [4]\n";
	cout << " Maximum filter:   [5]\n";
	cout << " Minimum filter:   [6]\n";
	cout << "\n Restore the picture: [R]\n";
	cout << " Exit: [E]\n\n";

	cout << " ---=== Image info ===---\n";
	cout << " Brightness: " << Filter::brightness << " Gamma: " << Filter::gamma << endl;
	cout << " R: " << Filter::red_filter << " G: " << Filter::green_filter << " B: " << Filter::blue_filter << endl;
}

void Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
	glPointSize(10);

    glBegin(GL_POINTS);
    
    for (int x = 0; x < picture.resolution.width; x++) 
	{
        for (int y = 0; y < picture.resolution.height; y++)
		{
            glColor3d(pow(picture.pointsColors[x][y].red   /255.0 + Filter::brightness + Filter::red_filter   /255.0, 1.0 / Filter::gamma),
					  pow(picture.pointsColors[x][y].green /255.0 + Filter::brightness + Filter::green_filter /255.0, 1.0 / Filter::gamma),
                      pow(picture.pointsColors[x][y].blue  /255.0 + Filter::brightness + Filter::blue_filter  /255.0, 1.0 / Filter::gamma)
					 );
            glVertex2d(y, x);
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
		case 'q': Filter::ChangeRedChannel(-5);   break;
		case 'w': Filter::ChangeRedChannel(5);    break;

		case 'a': Filter::ChangeGreenChannel(-5); break;
		case 's': Filter::ChangeGreenChannel(5);  break;

		case 'z': Filter::ChangeBlueChannel(-5);  break;
		case 'x': Filter::ChangeBlueChannel(5);   break;

		case 'f': Filter::ChangeGamma(-0.02);     break;
		case 'g': Filter::ChangeGamma(0.02);      break;

		case '+': Filter::ChangeBrightness(0.02); break;
		case '-': Filter::ChangeBrightness(-0.02);break;

		case 'r': Filter::ClearFilters(picture);  break;

		case 'e': exit(0);						  break;

		case '1': highPass.Apply(picture);		  break;
		case '2': lowPass.Apply(picture);		  break;
		case '3': edge.Apply(picture);			  break;

		case '4': StatisticalFilters::MedianFilter(picture);  break;
		case '5': StatisticalFilters::MaximumFilter(picture); break;
		case '6': StatisticalFilters::MinimumFilter(picture); break;
	}
	Menu();
}

void Idle()
{
	glutPostRedisplay();
}


int main(int argc, char* argv[]) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(200, 200);
	glutCreateWindow("Filters assigment - Jakub Spalek Lab1 Gr1 INF II");
	glEnable(GL_POINT_SIZE);

	glutReshapeFunc(ChangeViewPort);
	glutDisplayFunc(Render);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Key);

	glClearColor(1, 1, 1, 1);

	Menu();

	glutMainLoop();
	return 0;
}