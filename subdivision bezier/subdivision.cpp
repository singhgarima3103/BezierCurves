#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
float controlPoints[30][2];
int controlPointCount = 0;
float t = 0;
BOOLEAN dPressed = FALSE;
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



void recursive_bezier(double x1, double y1,
	double x2, double y2,
	double x3, double y3,
	double x4, double y4,int check)
{
	// Calculate all the mid-points of the line segments
	//----------------------
	//printf("inside recursive bezier");
	//float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
	
		float x12 = (x1 + x2) / 2;
		float y12 = (y1 + y2) / 2;
		float x23 = (x2 + x3) / 2;
		float y23 = (y2 + y3) / 2;
		float x34 = (x3 + x4) / 2;
		float y34 = (y3 + y4) / 2;
		float x123 = (x12 + x23) / 2;
		float y123 = (y12 + y23) / 2;
		float x234 = (x23 + x34) / 2;
		float y234 = (y23 + y34) / 2;
		float x1234 = (x123 + x234) / 2;
		float y1234 = (y123 + y234) / 2;

		if (check == 0){

		// Draw and stop
		//----------------------
		//draw_line(x1, y1, x4, y4);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(x1, y1, 0.0);
		glVertex3f(x2, y2, 0.0);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(x2, y2, 0.0);
		glVertex3f(x3, y3, 0.0);
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(x3, y3, 0.0);
		glVertex3f(x4, y4, 0.0);
		glEnd();
	}
		// Continue subdivision
		//----------------------
	else{
			recursive_bezier(x1, y1, x12, y12, x123, y123, x1234, y1234,check-1);

			recursive_bezier(x1234, y1234, x234, y234, x34, y34, x4, y4,check-1);
		}
		
	
}


void display2()
{
	if (controlPointCount == 4)
		recursive_bezier(controlPoints[0][0], controlPoints[0][1], controlPoints[1][0], controlPoints[1][1], controlPoints[2][0], controlPoints[2][1], controlPoints[3][0], controlPoints[3][1],dcount);
	glutSwapBuffers();
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 'r':
	{
				//glDrawPixels(512, 512, GL_RGB, GL_FLOAT, pixels);
				glutSwapBuffers();
				break;
	}

	case 'd':
	{
				//t = 0.5;
				//dPressed = TRUE;
				dcount++;
				printf("dcount:%d", dcount);
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
		controlPoints[controlPointCount][0] = (((float)x) / 512) * 2 - 1;;
		controlPoints[controlPointCount][1] = ((512 - ((float)y)) / 512) * 2 - 1;;

		/*pixels[512 - (int)y][(int)x][0] = 1;
		pixels[512 - (int)y][(int)x][1] = 0;
		pixels[512 - (int)y][(int)x][2] = 0;*/

		glBegin(GL_POINTS);
		glVertex3f(controlPoints[controlPointCount][0], controlPoints[controlPointCount][1], 0.0f);
		glEnd();

		printf("x:%f\ty:%f\n", controlPoints[controlPointCount][0], controlPoints[controlPointCount][1]);
		controlPointCount++;

	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInitWindowSize(512, 512);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("subdivision");

	glutDisplayFunc(display2);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);



	init();

	glutMainLoop();
	return 0;
}