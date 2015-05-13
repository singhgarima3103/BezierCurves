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
	int controlPointIndex = 0,i;
	float t, x, y, genX, genY;

		if (controlPointCount >= 4){
			if (controlPointCount % 3 == 1)
			{
				genX = controlPoints[controlPointIndex + 1][0];
				genY = controlPoints[controlPointIndex + 1][1];
				while (controlPointIndex + 3 < controlPointCount)
				{
					//printf("here!");
					t = 0;
					while (t <= 1)
					{
						x = (1 - t)*(1 - t)*(1 - t)*controlPoints[controlPointIndex][0] + 3 * t*(1 - t)*(1 - t)*genX
							+ 3 * t*t*(1 - t)*controlPoints[controlPointIndex + 2][0] + t*t*t*controlPoints[controlPointIndex + 3][0];
						y = (1 - t)*(1 - t)*(1 - t)*controlPoints[controlPointIndex][1] + 3 * t*(1 - t)*(1 - t)*genY
							+ 3 * t*t*(1 - t)*controlPoints[controlPointIndex + 2][1] + t*t*t*controlPoints[controlPointIndex + 3][1];

						//printf("x:%f\ty:%f\n", x, y);

						pixels[512 - (int)y][(int)x][0] = 1;
						pixels[512 - (int)y][(int)x][1] = 0;
						pixels[512 - (int)y][(int)x][2] = 0;


						t = t + 0.001;
					}
					genX = 2 * controlPoints[controlPointIndex + 3][0] - controlPoints[controlPointIndex + 2][0];
					genY = 2 * controlPoints[controlPointIndex + 3][1] - controlPoints[controlPointIndex + 2][1];

					pixels[512 - (int)y][(int)x][0] = 0;
					pixels[512 - (int)y][(int)x][1] = 1;
					pixels[512 - (int)y][(int)x][2] = 0.3;

					controlPointIndex = controlPointIndex + 3;
				}
				
			}
		}
	//}


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

		pixels[512 - (int)y][(int)x][0] = 0;
		pixels[512 - (int)y][(int)x][1] = 1;
		pixels[512 - (int)y][(int)x][2] = 0.3;

		/*glBegin(GL_POINTS);
		glVertex3f((((float)x) / 512) * 2 - 1, ((512 - ((float)y)) / 512) * 2 - 1, 0.0f);
		glEnd();*/

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
	glutCreateWindow("Bezier");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);



	init();

	glutMainLoop();
	return 0;
}
