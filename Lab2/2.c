
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


int xc,yc,r;
GLfloat angle = 1;  // rotational angle of the shapes


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
  
  draw_line(0, 640, 40, 40);
  glPushMatrix(); 
    glTranslatef(320, 240, 0);
    glRotatef(angle, 0, 0, 1);
    glTranslatef(-320, -240, 0);
    xc = 320;
    yc = 240;
    r = 200;
    bresenham_circle(r);
    xc = 320;
    yc = 240;
    r = 30;
    bresenham_circle(r);
    
    draw_line(350, 520, 240, 240);
    draw_line(120, 290, 240, 240);
    draw_line(320, 320, 440, 270);
    draw_line(320, 320, 210, 40);
  glPopMatrix();      
                      // Save model-view matrix setting
  glutSwapBuffers();   // Double buffered - swap the front and back buffers
 
   // Change the rotational angle after each display()
 
 
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
  glutDisplayFunc(display);
  glutTimerFunc(25, Timer, 0);
  glutMainLoop();
}
