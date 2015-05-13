#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
float pointsArray[30 * 3];
float controlPoints[4*3];
int controlPointCount = 0;



void
renderCurveWithOpenGL()
{
	
					

			glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, controlPoints);
			glEnable(GL_MAP1_VERTEX_3);
			glLineWidth(.5);
			glColor3f(0, 1.0, .3);
			glBegin(GL_LINE_STRIP);

			for (float mu = 0; mu <= 1; mu += 0.001)
				glEvalCoord1f(mu);

			glEnd();
		
	
}


void display(void)
{
	int controlPointIndex = 0, i;
	float t, x, y, genX, genY;
	if (controlPointCount >= 4)
	{
		if (controlPointCount % 3 == 1)
		{
			genX = pointsArray[1*3+0];
			genY = pointsArray[1 * 3 + 1];

			

			while (controlPointIndex + 3 < controlPointCount)
			{

				controlPoints[0 * 3 + 0] = pointsArray[(controlPointIndex)* 3 + 0];
				controlPoints[0 * 3 + 1] = pointsArray[(controlPointIndex)* 3 + 1];

				controlPoints[1 * 3 + 0] = genX;
				controlPoints[1 * 3 + 1] = genY;

				controlPoints[2 * 3 + 0] = pointsArray[(controlPointIndex+2)* 3 + 0];
				controlPoints[2 * 3 + 1] = pointsArray[(controlPointIndex + 2) * 3 + 1];

				controlPoints[3 * 3 + 0] = pointsArray[(controlPointIndex + 3) * 3 + 0];
				controlPoints[3 * 3 + 1] = pointsArray[(controlPointIndex + 3) * 3 + 1];

				renderCurveWithOpenGL();

				genX = 2 * pointsArray[(controlPointIndex + 3)*3+0] - pointsArray[(controlPointIndex + 2)*3+0];
				genY = 2 * pointsArray[(controlPointIndex + 3)*3+1] - pointsArray[(controlPointIndex + 2)*3+1];
				controlPointIndex = controlPointIndex + 3;

			}
		}
	}
		
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	
	if (button == GLUT_LEFT_BUTTON)
	if (state == GLUT_UP)
	{
		printf("x:%d\ty:%d\n", x, y);
		pointsArray[controlPointCount * 3 + 0] = (((float)x) / 512) * 2 - 1;
		pointsArray[controlPointCount * 3 + 1] = ((512 - ((float)y)) / 512) * 2 - 1;
		pointsArray[controlPointCount*3+2] = 0;

		glBegin(GL_POINTS);
		glVertex3f(pointsArray[controlPointCount * 3 + 0], pointsArray[controlPointCount * 3 + 1], 0.0f);
		glEnd();

		printf("x:%f\ty:%f\n", pointsArray[controlPointCount * 3 + 0], pointsArray[controlPointCount * 3 + 1]);
		controlPointCount++;

	}
	glutPostRedisplay();
}




int main(int argc, char** argv)
{
	glutInitWindowSize(512, 512);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("OpenGLBezier");

	glutDisplayFunc(display);
	glutMouseFunc(mouse);


	glutMainLoop();
	return 0;
}