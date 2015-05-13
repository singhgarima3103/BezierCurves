#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
int controlPoints[30][2];
int controlPointCount = 0;
GLfloat  pixels[512][512][3];
int dcount = 0;
void init(void)
{

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);

}


void display(void)
{
	int controlPointIndex = 0, i;
	float t, x, y, q0x, q0y, q1x, q1y, q2x, q2y, r0x, r0y, r1x, r1y, bx, by,genX,genY;

	//de casteljau's case - linear interpolation
	//printf("inside d");
	if (controlPointCount >= 4)
	{
		if (controlPointCount % 3 == 1)
		{
			genX = controlPoints[controlPointIndex + 1][0];
			genY = controlPoints[controlPointIndex + 1][1];
			while (controlPointIndex + 3 < controlPointCount)
			{
				t = 0;
				while (t <= 1)
				{
					/*for (i = 0; i < 3; i++)
					{

					}*/

					q0x = t*controlPoints[controlPointIndex][0] + (1 - t)*genX;
					q0y = t*controlPoints[controlPointIndex][1] + (1 - t)*genY;
					//printf("q0x:%f\tq0y:%f\n", q0x, q0y);

					q1x = t*genX + (1 - t)*controlPoints[controlPointIndex + 2][0];
					q1y = t*genY + (1 - t)*controlPoints[controlPointIndex + 2][1];
					//printf("q1x:%f\tq1y:%f\n", q1x, q1y);

					q2x = t*controlPoints[controlPointIndex + 2][0] + (1 - t)*controlPoints[controlPointIndex + 3][0];
					q2y = t*controlPoints[controlPointIndex + 2][1] + (1 - t)*controlPoints[controlPointIndex + 3][1];
					//printf("q2x:%f\tq2y:%f\n", q2x, q2y);

					r0x = t* q0x + (1 - t)*q1x;
					r0y = t* q0y + (1 - t)*q1y;
					//printf("r0x:%f\tr0y:%f\n", r0x, r0y);

					r1x = t* q1x + (1 - t)*q2x;
					r1y = t* q1y + (1 - t)*q2y;
					//printf("r1x:%f\tr1y:%f\n", r1x, r1y);

					bx = t* r0x + (1 - t) * r1x;
					by = t* r0y + (1 - t) * r1y;

					//printf("bx:%f\tby:%f\n", bx, by);

					pixels[512 - (int)by][(int)bx][0] = 1;
					pixels[512 - (int)by][(int)bx][1] = 0;
					pixels[512 - (int)by][(int)bx][2] = 0;

					t = t + 0.001;
				}
				genX = 2 * controlPoints[controlPointIndex + 3][0] - controlPoints[controlPointIndex + 2][0];
				genY = 2 * controlPoints[controlPointIndex + 3][1] - controlPoints[controlPointIndex + 2][1];
				controlPointIndex = controlPointIndex + 3;
			}
		}
	}







}

void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 'r':
	{
				glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixels);
				glutSwapBuffers();
				break;
	}
		glutPostRedisplay();

	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	if (state == GLUT_UP)
	{
		controlPoints[controlPointCount][0] = x;
		controlPoints[controlPointCount][1] = y;

		pixels[512 - (int)y][(int)x][0] = 1;
		pixels[512 - (int)y][(int)x][1] = 0;
		pixels[512 - (int)y][(int)x][2] = 0;

		printf("x:%d\ty:%d\n", controlPoints[controlPointCount][0], controlPoints[controlPointCount][1] = y);
		controlPointCount++;

	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInitWindowSize(512, 512);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("De Casteljau");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);



	init();

	glutMainLoop();
	return 0;
}