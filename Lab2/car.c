
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h> 
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
int xc,yc,r1,r2;
GLfloat angle = 1;  // rotational angle of the shapes
int timer1= 0;
int forward =1;

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Storing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < start_time + milli_seconds) 
        ; 
} 

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Timer(int value) {
  angle +=1;
  // if(angle>360)
  //   angle-=360;
  glClear(GL_COLOR_BUFFER_BIT);
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(25, Timer, 0); // next Timer call milliseconds later
}

void draw_line(int x1, int x2, int y1, int y2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = x2-x1;
	dy = y2-y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (x2 < x1) incx = -1;
	incy = 1;
	if (y2 < y1) incy = -1;
	x = x1; y = y1;
	x = x1; y = y1;
	if (dx > dy) {
		draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			draw_pixel(x, y);
		}

	} else {
		draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			draw_pixel(x, y);
		}
	}
}

void plot_point(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}

void bresenham_circle(int r)
{
  int x=0,y=r;
  float d=3 - 2*r;
  plot_point(x,y);
  int k;
  while(x <= y)
  {
    x = x + 1;
    if(d > 0)
    {
	y--;  
            d = d + 4 * (x - y) + 10; 
    }
    else
    {
      d = d + 4 * x + 6;
    }
    plot_point(x,y);

  }
  glFlush();
}
void display(void)
{
  if(forward == 1)
  {
    draw_line(0, 640, 50, 50);
 glTranslatef(1, 0, 0);
  xc = 120;
  yc = 100;
  r1 = 50;
  r2 = 10;
  draw_line(xc-r1, xc-r1-50, yc, yc);
  draw_line(xc-r1-50, xc-r1-50, yc, yc+100);
  draw_line(xc, xc-r1-50, yc+100, yc+100);
  draw_line(xc, xc, yc+100, yc+150);
  draw_line(xc, 360, yc+150, yc+150);
  draw_line(xc+r1, 310, yc, yc);
  glPushMatrix(); 
    glTranslatef(xc, yc, 0);
    glRotatef(angle, 0, 0, -1);
    glTranslatef(-xc, -yc, 0);
    
    bresenham_circle(r1);
    
    bresenham_circle(r2);
    
    draw_line(xc+r2, xc+r1, yc, yc);
    draw_line(xc-r1, xc-r2, yc, yc);
    draw_line(xc, xc, yc+r1, yc+r2);
    draw_line(xc, xc, yc-r2, yc-r1);
  glPopMatrix(); 
  
  xc = 360;
  yc = 100;
  r1 = 50;
  r2 = 10;
  draw_line(xc+r1, xc+r1+50, yc, yc);
  draw_line(xc+r1+50, xc+r1+50, yc, yc+100);
  draw_line(xc, xc+r1+50, yc+100, yc+100);
   draw_line(xc, xc, yc+100, yc+150);
  glPushMatrix(); 
    glTranslatef(xc, yc, 0);
    glRotatef(angle, 0, 0, -1);
    glTranslatef(-xc, -yc, 0);
    
    bresenham_circle(r1);
    
    bresenham_circle(r2);
    
    draw_line(xc+r2, xc+r1, yc, yc);
    draw_line(xc-r1, xc-r2, yc, yc);
    draw_line(xc, xc, yc+r1, yc+r2);
    draw_line(xc, xc, yc-r2, yc-r1);
  glPopMatrix();     
 
                      // Save model-view matrix setting
  glutSwapBuffers(); 
  
 }
 else
 {
   draw_line(0, 640, 50, 50);
   glTranslatef(-1, 0, 0);
  xc = 120;
  yc = 100;
  r1 = 50;
  r2 = 10;
  draw_line(xc-r1, xc-r1-50, yc, yc);
  draw_line(xc-r1-50, xc-r1-50, yc, yc+100);
  draw_line(xc, xc-r1-50, yc+100, yc+100);
  draw_line(xc, xc, yc+100, yc+150);
  draw_line(xc, 360, yc+150, yc+150);
  draw_line(xc+r1, 310, yc, yc);
  glPushMatrix(); 
    glTranslatef(xc, yc, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-xc, -yc, 0);
    
    bresenham_circle(r1);
    
    bresenham_circle(r2);
    
    draw_line(xc+r2, xc+r1, yc, yc);
    draw_line(xc-r1, xc-r2, yc, yc);
    draw_line(xc, xc, yc+r1, yc+r2);
    draw_line(xc, xc, yc-r2, yc-r1);
  glPopMatrix(); 
  xc = 360;
  yc = 100;
  r1 = 50;
  r2 = 10;
  draw_line(xc+r1, xc+r1+50, yc, yc);
  draw_line(xc+r1+50, xc+r1+50, yc, yc+100);
  draw_line(xc, xc+r1+50, yc+100, yc+100);
   draw_line(xc, xc, yc+100, yc+150);
  glPushMatrix(); 
    glTranslatef(xc, yc, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-xc, -yc, 0);
    
    bresenham_circle(r1);
    
    bresenham_circle(r2);
    
    draw_line(xc+r2, xc+r1, yc, yc);
    draw_line(xc-r1, xc-r2, yc, yc);
    draw_line(xc, xc, yc+r1, yc+r2);
    draw_line(xc, xc, yc-r2, yc-r1);
  glPopMatrix();     
  
  draw_line(0, 640, yc-r1, yc-r1);
                      // Save model-view matrix setting
  glutSwapBuffers(); 
 }
 
}
void keyPressed (unsigned char key, int x, int y) {  
  if(key == 'f')
  {
    forward= 1;

  }
  if(key == 'b')
  {
    forward =0;
  }
  
} 
void Init()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
   
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("bresenham_circle");
  Init();
  glutKeyboardFunc(keyPressed);
  glutDisplayFunc(display);
  glutTimerFunc(25, Timer, 0);
  glutMainLoop();
}
