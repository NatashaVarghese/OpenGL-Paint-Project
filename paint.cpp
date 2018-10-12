#define _USE_MATH_DEFINES

#include <stdlib.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
#include <math.h>

using namespace std;

const float PI = M_PI;

int x_start;
int y_start;
int x_end;
int y_end;
int first=0;

int window_w=600;
int window_h=600;

bool Point=false;
bool Motion=false;
bool Rectangle=false;
bool Line=false;
bool Circle=false;

void drawPoint(float x, float y)
{
         glBegin(GL_POINTS);
         glVertex2i(x,y);
         glEnd();
         glutSwapBuffers();
}

void drawVerticalLine(int x_start, int y_start, int y_end)
{
	int y_inc = y_start;
	while (y_inc<y_end)
	{
		glBegin(GL_POINTS);
		glVertex2i(x_start,y_inc);
		y_inc++;
		glEnd();
		glutSwapBuffers();
	}
}

void drawHorizontalLine(int x_start, int y_start, int x_end)
{
	int x_inc = x_start;
	while (x_inc<x_end)
	{
		glBegin(GL_POINTS);
		glVertex2i(x_inc,y_start);
		x_inc++;
		glEnd();
		glutSwapBuffers();
	}
}

void drawLine(int x_start, int y_start, int x_end, int y_end) 
{ 
	int temp;
	if(x_start>x_end)
	{
		int temp=x_start;
		x_start=x_end;
		x_end=temp;
		temp=y_start;
		y_start=y_end;
		y_end=temp;
	}

	int dy = y_end-y_start;
	int dx = x_end-x_start;  

	if(x_start==x_end)
	{
		drawVerticalLine(x_start, y_start, y_end);
	}
	
	if(y_start==y_end)
	{
		drawHorizontalLine(x_start, y_start, x_end);
	}

	else 
	{
		int x=x_start;
		int y=y_start;
		dx=abs(dx);
		dy=abs(dy);
		int sx=1;
		int sy=1;
		int Interchange;
		if(x_end-x_start<0)
		{
			sx=-1;
		}
		if(y_end-y_start<0)
		{
			sy=-1;
		}
		if(x_end-x_start==0)
		{
			sx=0;
		}
		if(y_end-y_start==0)
		{
			sy=0;
		}
		if(dy>dx)
		{
			int T=dx;
			dx=dy;
			dy=T;
			Interchange=1;
		}
		else 
		{
			Interchange=0;
		}	
		int E=2*dy-dx;
		int A=2*dy;
		int B=2*dy-2*dx;
		for(int i=1; i<=dx; i++)
		{
			if (E<0)
			{
				if(Interchange==1)
				{
					y=y+sy;
				}
				else
				{
					x=x+sx;
				}
				E=E+A;
			}
			else
			{
				y=y+sy;
				x=x+sx;
				E=E+B;
			}
			glBegin(GL_POINTS);
			glVertex2i(x,y);
			glEnd();
			glutSwapBuffers();
		}
	}
}

void drawRectangle(int x_start, int y_start, int x_end, int y_end) 
{
	int temp;
	if (y_start>y_end)
	{
		temp=y_start;
		y_start=y_end;
		y_end=temp;
	}
	if (x_start>x_end)
	{
		temp=x_start;
		x_start=x_end;
		x_end=temp;
	}
	drawVerticalLine(x_start, y_start, y_end);
	drawVerticalLine(x_end, y_start, y_end);
	drawHorizontalLine(x_start, y_start, x_end);
	drawHorizontalLine(x_start, y_end, x_end);
}

void drawCircle(int cx, int cy, int x_end, int y_end) 
{
	float x, y;	
	float r = sqrt(pow((x_end-cx),2)+pow((y_end-cy),2));
	
	for(float angle = 0; angle<=2*PI; angle+=0.01)
	{
		glBegin(GL_POINTS);
		x=r*cos(angle)+cx;
		y=r*sin(angle)+cy;
		glVertex2f(x,y);
		glEnd();
		glutSwapBuffers();
	}
}

void motion(int mouse_x, int mouse_y)
{
	Motion=true;
	int x=mouse_x;
	int y=600-mouse_y;
	if(Point)
	{
		drawPoint(x, y);
	}
}

void mouse(int button, int state, int mouse_x, int mouse_y)
{
	if(button==GLUT_LEFT_BUTTON and state==GLUT_DOWN)
	{
		if(Point)
		{
			int x=mouse_x;
			int y=600-mouse_y;
			drawPoint(x, y);
		}
		if(Line or Rectangle or Circle)
		{
			switch(first)
			{
				case 0:
					x_start = mouse_x;
					y_start = 600-mouse_y;
					first=1;
					break;
				case 1:
					x_end = mouse_x;
					y_end = 600-mouse_y;
					if(Line)
					{
						drawLine(x_start, y_start, x_end, y_end);
					} 
					if (Rectangle) 
					{
						drawRectangle(x_start, y_start, x_end, y_end);
					}
					if (Circle) 
					{
						drawCircle(x_start, y_start, x_end, y_end);
					}
					first=0;
					break;
			}			
		}	
	}
}

void menuColor(int value)
{
	switch(value)
	{
		case 1:
			glColor3f(1,0,0);
			break;
		case 2:
			glColor3f(0,1,0);
			break;
		case 3:
			glColor3f(0,0,1);
			break;
		case 4:
			glColor3f(1,0,1);
			break;
		case 5:
			glColor3f(1,1,0);
			break;
		case 6:
			unsigned char r = (unsigned char) rand() % 256;
			unsigned char g = (unsigned char) rand() % 256;
			unsigned char b = (unsigned char) rand() % 256; 
			glColor3ub(r,g,b);
			break;
	}
}

void menuShape(int value)
{
	switch(value)
	{
		case 1:
			Point=true;
			Line=false;
			Rectangle=false;
			Circle=false;
			break;
		case 2:
			Line=true;
			Point=false;
			Rectangle=false;
			Circle=false;
			break;
		case 3:
			Rectangle=true;
			Line=false;
			Point=false;
			Circle=false;
			break;
		case 4:
			Circle=true;
			Rectangle=false;
			Line=false;
			Point=false;
			break;
	}
}

void otherMenu(int value)
{
	switch(value)
	{
		case 1:
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
			glLoadIdentity();
			glutSwapBuffers();
			break;
		case 2:
			exit(0);
			break;

	}
}


void createPopUpMenus() 
{

    int shape_id = glutCreateMenu(menuShape);
    glutAddMenuEntry("Point",1);
    glutAddMenuEntry("Line",2);
    glutAddMenuEntry("Rectangle",3);
    glutAddMenuEntry("Circle",4);
    
    int color_id = glutCreateMenu(menuColor);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("Purple",4);
    glutAddMenuEntry("Yellow",5);
    glutAddMenuEntry("Random",6);
    
    int other = glutCreateMenu(otherMenu); 
    glutAddMenuEntry("Clear", 1);
    glutAddMenuEntry("Quit", 2);

    	glutCreateMenu(menuColor);
    	glutCreateMenu(menuShape);
        glutCreateMenu(otherMenu);
  
    glutAddSubMenu("Colors", color_id);
    glutAddSubMenu("Shapes", shape_id);
    glutAddSubMenu("Other", other); 
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, 0, h, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
}

void Timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(5, Timer, 0);
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, window_w, window_h,0,15,-15);
	glMatrixMode(GL_MODELVIEW);
}

void callBackInit()
{

    glutTimerFunc(50, Timer, 0);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
}

int main(int argc, char** argv)
{
    cout << "===========================================================\n";	
    cout << "Welcome to OpenGL Paint!\n";
    cout << "To begin: RIGHT CLICK to access the menu!\n";
    cout << "Make sure to pick both a COLOR and a SHAPE to get started drawing!\n";
    cout << "Click on CLEAR to clear the screen.\n";
    cout << "Click on QUIT to quit the program.\n";
    cout << "To get new random colors click the RANDOM button under Colors each time you want a new random color\n";  
    cout << "===========================================================\n";	
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); //creates double buffer
    
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint"); 
    
    init();    
    callBackInit();

    createPopUpMenus();

    glutMainLoop();

    return 0;
}
