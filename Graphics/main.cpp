// 206262719_208140111
#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include <time.h>

const int W = 600;
const int H = 600;
const int NUM_STARS = 100;
const int NUM_WINDOWS = 50;
const int NUM_FLOORS = 100;
double gx = 0;

int counter = 0;

int windows[NUM_FLOORS][NUM_WINDOWS];

typedef struct {
	double x;
	double y;
	int size;
} STAR;

STAR stars[NUM_STARS];

void init()
{
	int i, j;
	srand(time(0));
	glClearColor(0.01, 0.1, 0.2, 0);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // defines the main axis and their range

	for (i = 0; i < NUM_STARS; i++)
	{
		stars[i].x = (-1000 + rand() % 2000) / 1000.0; // random double in range (-1,1)
		stars[i].y = (-1000 + rand() % 2000) / 1000.0; // random double in range (-1,1)
		stars[i].size = 1 + rand() % 2;
	}

	// light windows (3 levels of light)
	for (i = 0; i < NUM_FLOORS; i++)
		for (j = 0; j < NUM_WINDOWS; j++)
			windows[i][j] = rand() % 3;
}


//buildings
void DrawBars()
{
	glEnable(GL_BLEND); //Enable blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function
	double x, y;
	int i, j, num_floors, num_windows;
	double dx = 0.03, dy = 0.05;
	//glColor3d(2, 0, 0);
	//back
	for (x = -1; x <= 1; x += 0.15)
	{
		y = fabs(0.8 * cos(2 * x) + 0.15 * cos(20 * x));
		if (y < 0.5)
			y += 0.3;

		glBegin(GL_POLYGON);
		glColor3d(0.1, 0.12, 0.01);
		glVertex2d(x, y); // left-top point
		glVertex2d(x + 0.1, y);// right -top point
		glColor3d(0.01, 0, 0.01);
		glVertex2d(x + 0.1, 0);// right -bottom point
		glVertex2d(x, 0);// left - bottom point
		glEnd();
		if (y >= 0.65)
		{
			glBegin(GL_POLYGON);
			glColor3d(0.1, 0.12, 0.01);
			glVertex2d(x, y); // left-top point
			glVertex2d(x + 0.1, y);// right -top point
			glVertex2d(x + 0.05, y + 0.05);// triangle top
			glEnd();
		}


		//add windows
		num_windows = 0.1 / dx;
		if (num_windows > NUM_WINDOWS) num_windows = NUM_WINDOWS;
		num_floors = y / dy;
		if (num_floors > NUM_FLOORS) num_floors = NUM_FLOORS;

		glPointSize(4);
		for (i = 0; i < num_floors; i++)
			for (j = 0; j < num_windows; j++)
			{
				glColor3d(0.15 * windows[i][j], 0.15 * windows[i][j], 0);
				glBegin(GL_POINTS);
				glVertex2d(x + 0.015 + j * dx, y - 0.03 - i * dy);
				glEnd();
			}
	}

	//front
	for (x = -1; x <= 1; x += 0.11)
	{
		y = fabs(0.6 * cos(2 * x) + 0.18 * cos(12 * x));
		if (y < 0.2)
			y += 0.2;

		glBegin(GL_POLYGON);
		glColor3d(y , y + 0.05 , fabs(x) / 2 + 150);
		glVertex2d(x, y); // left-top point
		glVertex2d(x + 0.1, y);// right -top point
		glColor3d(0.05, 0, 0.1);
		glVertex2d(x + 0.1, 0);// right -bottom point
		glVertex2d(x, 0);// left - bottom point
		glEnd();
		if (y >= 0.65)
		{
			glBegin(GL_POLYGON);
			glColor3d(y , y + 0.05 , fabs(x) / 2 + 150);
			glVertex2d(x, y); // left-top point
			glVertex2d(x + 0.1, y);// right -top point
			glVertex2d(x + 0.05, y + 0.05);// triangle top
			glEnd();
		}


		// add windows
		num_windows = 0.1 / dx;
		if (num_windows > NUM_WINDOWS) num_windows = NUM_WINDOWS;
		num_floors = y / dy;
		if (num_floors > NUM_FLOORS) num_floors = NUM_FLOORS;

		glPointSize(5.5);
		for (i = 0; i < num_floors; i++)
			for (j = 0; j < num_windows; j++)
			{
				glBegin(GL_POINTS);
				glColor3d(0.5 * windows[i][j], 0.5 * windows[i][j], 0);
				glVertex2d(x + 0.02 + j * dx, y - 0.03 - i * dy);
				glEnd();
			}
	}

	// water reflection
	//back
	for (x = -1; x <= 1; x += 0.15)
	{
		y = fabs(0.8 * cos(2 * x) + 0.15 * cos(20 * x));
		if (y < 0.5)
			y += 0.3;
		glBegin(GL_POLYGON);
		glColor4d(0.1, 0.12, 0.01, 0.5);
		glVertex2d(x, -y); // left-top point
		glVertex2d(x + 0.1, -y);// right -top point
		glColor3d(0.01, 0, 0.01);
		glVertex2d(x + 0.1, 0);// right -bottom point
		glVertex2d(x, 0);// left - bottom point
		glEnd();
		if (y >= 0.65)
		{
			glBegin(GL_POLYGON);
			glColor4d(0.1, 0.12, 0.01, 0.5);
			glVertex2d(x, -y); // left-top point
			glVertex2d(x + 0.1, -y);// right -top point
			glVertex2d(x + 0.05, -y - 0.05);// triangle top
			glEnd();
		}

		//add windows
		num_windows = 0.1 / dx;
		if (num_windows > NUM_WINDOWS) num_windows = NUM_WINDOWS;
		num_floors = y / dy;
		if (num_floors > NUM_FLOORS) num_floors = NUM_FLOORS;

		glPointSize(4);
		for (i = 0; i < num_floors; i++)
			for (j = 0; j < num_windows; j++)
			{
				glColor3d(0.15 * windows[i][j], 0.15 * windows[i][j], 0);
				glBegin(GL_POINTS);
				glVertex2d(x + 0.015 + j * dx, -y + 0.03 + i * dy);
				glEnd();
			}

	}

	//front
	for (x = -1; x <= 1; x += 0.11)
	{
		y = fabs(0.6 * cos(2 * x) + 0.18 * cos(12 * x));
		if (y < 0.2)
			y += 0.2;
		glBegin(GL_POLYGON);
		glColor4d(y / 2 , y / 2 + 0.5, fabs(x) / 4 +100, 0); //y , y + 0.05 , fabs(x) / 2 + 150
		glVertex2d(x, -y); // left-top point
		glVertex2d(x + 0.1, -y);// right -top point
		glColor3d(0.02, 0, 0.02);
		glVertex2d(x + 0.1, 0);// right -bottom point
		glVertex2d(x, 0);// left - bottom point
		glEnd();
		if (y >= 0.65)
		{
			glBegin(GL_POLYGON);
			glColor4d(y / 2, y / 2 +0.5, fabs(x) / 4 + 100,0);
			glVertex2d(x, -y); // left-top point
			glVertex2d(x + 0.1, -y);// right -top point
			glVertex2d(x + 0.05, -y - 0.05);// triangle top
			glEnd();
		}

		// add windows
		num_windows = 0.1 / dx;
		if (num_windows > NUM_WINDOWS) num_windows = NUM_WINDOWS;
		num_floors = y / dy;
		if (num_floors > NUM_FLOORS) num_floors = NUM_FLOORS;

		glPointSize(5.5);
		for (i = 0; i < num_floors; i++)
			for (j = 0; j < num_windows; j++)
			{
				glBegin(GL_POINTS);
				glColor4d(0.5 * windows[i][j], 0.5 * windows[i][j], 0, 0.2);
				glVertex2d(x + 0.02 + j * dx, -y + 0.03 + i * dy);

				glEnd();
			}

	}
}

void DrawStars()
{
	int i;

	// start defining points
	glColor3d(1, 1, 0); // yellow

	for (i = 0; i < NUM_STARS; i++)
	{
		if (stars[i].y >= -0.3)
		{
			glPointSize(stars[i].size);
			glBegin(GL_POINTS);
			glVertex2d(stars[i].x, stars[i].y);
			glEnd();
		}
	}
}

void DrawSky()
{
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.
	glBegin(GL_POLYGON);
	glColor3d(0.15, 0.15, 0.2);
	glVertex2d(-1, 1);
	glVertex2d(1, 1);
	glColor3d(0.05, 0.5, 0.9);
	glVertex2d(1, 0);
	glVertex2d(-1, 0);
	glEnd();
}

// Moon
void DrawMoon() {
	// Draw the moon (a circle) with a gray color
	float theta = 0, x, y;
	glColor3d(0.8,0.8,0.8); // White color
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.14159 / 180.0;
		x = 0.08 * cos(theta - 0.2) ;
		y = 0.08 * sin(theta - 0.2) ;
		glVertex2d(x+ 0.85,y +0.75);
	}
	glEnd();

	// reflaction
	glColor3d(0.015, 0.15, 0.25); // White color
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = i * 3.14159 / 180.0;
		x = 0.08 * cos(theta - 0.2);
		y = 0.08 * sin(theta - 0.2);
		glVertex2d(x + 0.85, y - 0.75);
	}
	glEnd();

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawSky();
	DrawStars();
	DrawBars();
	DrawMoon();

	glutSwapBuffers(); // show all
}

void idle()
{
	int i, j;
	gx += 0.1;
	// change randomly the size of a star
	if (counter % 5 == 0) {
		i = rand() % NUM_STARS;
		stars[i].size = 1 + rand() % 3;
	}
	// change randomly the light level of a window
	i = rand() % NUM_FLOORS;
	j = rand() % NUM_WINDOWS;
	windows[i][j] = rand() % 3;

	glutPostRedisplay(); // sends a message to the window to run display function
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display); // display is a name of refresh function
	glutIdleFunc(idle);// idle is a function that runs in background

	init();

	glutMainLoop();
}