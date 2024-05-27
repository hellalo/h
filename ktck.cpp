#include <GL/glut.h>
#include <cstdlib>
#include<iostream>
using namespace std;

struct Point
{
    float x, y;
};

void initGL()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glOrtho(-500, 500, -300, 300, -1, 1);
}
//khai bao bien
bool moveRight = false;
bool moveLeft = false;

Point A = {-25, -220};
Point B = {25,-220};
Point C = {25, -270};
Point D = {-25,-270};
Point a = {A.x+20, -220};
Point b = {B.x-20,-220};
Point c = {B.x-20, -230};
Point d = {A.x+20,-230};
Point a1 = {-25, 220};
Point b1 = {25,220};
Point c1 = {25, 270};
Point d1 = {-25,270};
float step = 0.02;
bool check=true;

//ham random
int random(int minN, int maxN){
 return minN + rand() % (maxN + 1 - minN);
}
//ve
void draw()
{
	glBegin(GL_LINE_LOOP);
    glVertex2f(A.x, A.y);
    glVertex2f(B.x, B.y);
    glVertex2f(C.x, C.y);
    glVertex2f(D.x, D.y);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(a.x, a.y);
    glVertex2f(b.x, b.y);
    glVertex2f(c.x, c.y);
    glVertex2f(d.x, d.y);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f(a1.x, a1.y);
    glVertex2f(b1.x, b1.y);
    glVertex2f(c1.x, c1.y);
    glVertex2f(d1.x, d1.y);
    glEnd();
    glFlush();
}

//di chuyen trai phai
void move()
{
	if(check==true)
	{
	    if (moveRight)
	    {
	        if(B.x<500)
			{
			    A.x += 0.2;
			    B.x += 0.2;
			    C.x += 0.2;
			    D.x += 0.2;
			}
			if(b.x<480)
			{
			    a.x += 0.2;
			    b.x += 0.2;
			    c.x += 0.2;
			    d.x += 0.2;
			}
	    }
	    if (moveLeft)
	    {
	        if(A.x>-500)
			{
				A.x -= 0.2;
			    B.x -= 0.2;
			    C.x -= 0.2;
			    D.x -= 0.2;
			}
			if(a.x>-480)
		    {
		    	a.x -= 0.2;
			    b.x -= 0.2;
			    c.x -= 0.2;
			    d.x -= 0.2;
		    }
	    }
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    draw();
    move();
    a1.y-=step;
	b1.y-=step;
	c1.y-=step;
	d1.y-=step;
    
}


//di chuyen trai phai
void keypressSpecial(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        moveRight = true;
    }
    if (key == GLUT_KEY_LEFT)
    {
        moveLeft = true;
    }
}

void keyupSpecial(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
    {
        moveRight = false;
    }
    if (key == GLUT_KEY_LEFT)
    {
        moveLeft = false;
    }
}

void movePoints(int value)
{
    a.y += 6;
    b.y += 6;
    c.y += 6;
    d.y += 6;
    //xu ly khi dan ra ngoai man hinh
    if (d.y > 300)
    {
    	a.x=A.x+20;	a.y=-220;
		b.x=B.x-20;	b.y=-220;
		c.x=B.x-20;	c.y=-230;
		d.x=A.x+20;	d.y=-230;
		check=true;	
        return;
    }
    //khi dan va cham voi thien thach
    int ran=random(-480,430);
    if((a.x > d1.x-11 && a.y > d1.y) && (b.x < c1.x+11 && b.y > c1.y))
	{		
		a1.x = ran;
		b1.x = ran+50;
		c1.x = ran+50;
		d1.x = ran;
		a1.y=320;
		b1.y=320;
		c1.y=370;
		d1.y=370;
		a.x=A.x+20;	a.y=-220;
		b.x=B.x-20;	b.y=-220;
		c.x=B.x-20;	c.y=-230;
		d.x=A.x+20;	d.y=-230;
		step+=0.01;
		check=true;	
    	return;
	}
	if (d1.y < -300) {
        cout << "Game Over!" << endl;
        exit(0); // Thoát chuong trình
    }

    glutPostRedisplay();
    glutTimerFunc(1000 / 60, movePoints, 0);
}

void keypress(unsigned char key, int x, int y)
{
	if(check==true)
	    if (key == ' ') 
	    {
	    	check=false;
	        glutTimerFunc(0, movePoints, 0);
	    }
    
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 50);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("ban thien thach");
    initGL();
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutKeyboardFunc(keypress);
    glutSpecialUpFunc(keyupSpecial); 
    glutSpecialFunc(keypressSpecial);
	glutMainLoop();
    
}
