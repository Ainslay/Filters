#include "Renderer.h"

void Renderer::DrawPicture(const Picture& picture)
{
	glBegin(GL_POINTS);

	glPushMatrix();

	/*for (int x = 0; x < picture.resolution.width; x++)
	{
		for (int y = 0; y < picture.resolution.height; y++)
		{
			gl
		}
	}*/

	glEnd();

	glPopMatrix();

	glutSwapBuffers();
}
