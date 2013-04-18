#include <iostream>
#include "Snake.h"
#include <GL/glut.h>
#include <cassert>
using namespace std;

template <class t>
void DEBUG(t s)
{
	cout << "DEBUGGING from main :: " << s << " :: " << endl;
}

template <class t1, class t2>
void DEBUG(t1 s, t2 t)
{
	cout << "DEBUGGING from main :: " << s << " | " << t << " :: " << endl;
}

void draw_line(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
		glVertex3f(x1, y1, 0.0f);
		glVertex3f(x2, y2, 0.0f);
	glEnd();
}

void draw_rect(float x1, float y1, float x2, float y2, bool vertical)
{
	if(!vertical)
	{
	glBegin(GL_QUADS);
		glVertex3f(x1, y1 + 0.01f, 0.0f);
		glVertex3f(x1, y1 - 0.01f, 0.0f);
		glVertex3f(x2, y2 - 0.01f, 0.0f);
		glVertex3f(x2, y2 + 0.01f, 0.0f);
	glEnd();
	}
	else
	{
	glBegin(GL_QUADS);
		glVertex3f(x1 + 0.01f, y1, 0.0f);
		glVertex3f(x1 - 0.01f, y1, 0.0f);
		glVertex3f(x2 - 0.01f, y2, 0.0f);
		glVertex3f(x2 + 0.01f, y2, 0.0f);
	glEnd();
	}

}

snake Player(0.0002f);

void draw(snake& S)
{
	for(int i = 0; i < S.body.size()-1; ++i)
	{
		snake::dir d = (snake::dir) (S.body.at(i+1) - S.body.at(i));
		if(d == snake::left || d == snake::right) 
			draw_rect(S.body.at(i).x, S.body.at(i).y,
				S.body.at(i+1).x, S.body.at(i+1).y, false);
		else
			draw_rect(S.body.at(i).x, S.body.at(i).y,
				S.body.at(i+1).x, S.body.at(i+1).y, true);
	}
	S.move();
}

void showPoints(snake& s)
{
	cout << "{ ";
	for(int i = 0; i < s.body.size(); ++i)
	{
		cout << "(" << s.body.at(i).x << ", " << s.body.at(i).y << ") ";
	}
	cout << "} " << endl;
}

void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	// draw_line(0.0f, 0.0f, 0.8f, 0.8f);
	draw(Player);
	glutSwapBuffers();
}

void handleSpecialpress(int key, int a, int b)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
			Player.change_direction(snake::left);
			break;
		case GLUT_KEY_RIGHT:
			Player.change_direction(snake::right);
			break;
		case GLUT_KEY_UP:
			Player.change_direction(snake::up);
			break;
		case GLUT_KEY_DOWN:
			Player.change_direction(snake::down);
			break;
		case GLUT_KEY_F1:
			showPoints(Player);
			break;
	}
}

int main(int argC, char** argV)
{
	glutInit(&argC, argV);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(10,10);
	glutCreateWindow("Snake");

	glutDisplayFunc(draw);
/*	glutKeyboardFunc(handleKeypress);
*/	glutSpecialFunc(handleSpecialpress);
	glutIdleFunc(draw);
	glutMainLoop();

	return 0;
}
