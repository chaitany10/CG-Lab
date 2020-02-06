#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h> 
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
int xc = 320,yc = 300,r1 = 100 ,r2 ;int rotate = 0, translater =0 ,translatel=0, clear =0; int reset=0;int scale=0;
GLfloat angle = 0.05;  // rotational angle of the shapes
int in = 0;

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
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
void Timer(int value) {
  angle +=0.05;
  // if(angle>360)
  //   angle-=360;
  glClear(GL_COLOR_BUFFER_BIT);
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(60, Timer, 0); // next Timer call milliseconds later
}


void keyPressed (unsigned char key, int x, int y) {  
  if(key == 'r')
  {
    rotate=1;
  }
  if(key == 's')
  {
    rotate = 0;
    reset=1;
  }
  if(key == 't')
  {
    translater = 1;
    translatel = 0;
    reset=0;
    
  }
  if(key == 'h')
  {
      reset=0;
    translatel = 1;
    translater = 0;
  }
  if(key == 'i')
  {
    scale = 1;
  }
  if(key == 'd')
  {
    scale =-1;
  }
  if(key == 'c')
  {
    clear = 1;
  }
  if(key == 'e')
  {
    exit(0);
  }

  
} 
void plot_point_semi(int x, int y)
{
  glBegin(GL_POINTS);
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc-y, yc+x);
  
  glEnd();
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

void semi_circle(int r)
{
  int x=0,y=r;
  float d=3 - 2*r;
  plot_point_semi(x,y);
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
    plot_point_semi(x,y);

  }
  glFlush();
}
void display(void)
{
    
  if(rotate == 1 )
  {
      if(scale==1)
    {glScaled(1.01, 1.01, 1.01);scale=0;}
    if(scale==-1)
    {glScaled(0.9, 0.9, 0.9);scale=0;}
    if(translater == 1 && reset==0)
    {
        glTranslatef(1, 0, 0);reset=1;
    }
    if(translatel == 1 && reset==0)
    {
        glTranslatef(-1, 0, 0);reset=1;
    }
    xc=320;
      yc=300;
      r1=100;
    semi_circle(r1+in);
    draw_line(xc-r1-in,xc+r1+in,yc+in,yc+in);
    xc=280+in,yc=330+in,r1=20+in/2;
    bresenham_circle(r1+in);
    xc=360+in,yc=330+in,r1=20+in/2;
    bresenham_circle(r1+in);
    xc=320;
      yc=300;
      r1=100;
    draw_line(xc-r1-in,xc+r1+in,yc-10+in,yc-10+in);
    draw_line(xc-r1-in,xc-r1-in,yc-10+in,yc-150+in);
    draw_line(xc+r1+in,xc+r1+in,yc-10+in,yc-150+in);
    draw_line(xc-r1-in,xc+r1+in,yc-150+in,yc-150+in);
    glPushMatrix(); 
        glTranslatef(0, yc+in/2, 0);
        glRotatef(angle,1, 0, 0);
        glTranslatef(0, -yc-in/2, 0);
            draw_line(xc-r1-10-in,xc-r1-10-in,yc-10+in,yc-150+in);
            draw_line(xc-r1-50-in,xc-r1-50-in,yc-10+in,yc-150+in);
            draw_line(xc-r1-10-in,xc-r1-50-in,yc-10+in,yc-10+in);
            draw_line(xc-10-r1-in,xc-r1-50-in,yc-150+in,yc-150+in);
    glPopMatrix();
    glPushMatrix(); 
        glTranslatef(0, yc+in/2, 0);
        glRotatef(angle, 1, 0, 0);
        glTranslatef(-0, -yc-in/2, 0);
            draw_line(xc+r1+in+10,xc+r1+in+10,yc-10+in,yc-150+in);
            draw_line(xc+r1+in+50,xc+r1+in+50,yc-10+in,yc-150+in);
            draw_line(xc+r1+10+in,xc+r1+50+in,yc-10+in,yc-10+in);
            draw_line(xc+r1+in+10,xc+r1+in+50,yc-150+in,yc-150+in);
    glPopMatrix();
    
    xc=280+in,yc=330+in,r1=20+in/2;
    draw_line(xc-r1-in,xc+r1+in,yc-150-100+in,yc-150-100+in);
    draw_line(xc-r1-in,xc-r1-in,yc-150-30+in,yc-150-100+in);
    draw_line(xc+r1+in,xc+r1+in,yc-150-30+in,yc-150-100+in);
    xc=360+in,yc=330+in,r1=20+in/2;
    draw_line(xc-r1-in,xc+r1+in,yc-150-100+in,yc-150-100+in);
    draw_line(xc+r1+in,xc+r1+in,yc-150-30+in,yc-150-100+in);
    draw_line(xc-r1-in,xc-r1-in,yc-150-30+in,yc-150-100+in);
    glutSwapBuffers(); 
   // Change the rotational angle after each display()
  }
  if(rotate == 0)
  {
    if(scale==1)
    {glScaled(1.01, 1.01, 1.01);scale=0;}
    if(scale==-1)
    {glScaled(0.9, 0.9, 0.9);scale=0;}
    if(translater == 1 && reset==0)
    {
        glTranslatef(1, 0, 0);reset=1;
    }
    if(translatel == 1 && reset==0)
    {
        glTranslatef(-1, 0, 0);reset=1;
    }
      xc=320;
      yc=300;
      r1=100;
    semi_circle(r1+in);
    draw_line(xc-r1-in,xc+r1+in,yc+in,yc+in);
    xc=280+in,yc=330+in,r1=20+in/2;
    bresenham_circle(r1+in);
    xc=360+in,yc=330+in,r1=20+in/2;
    bresenham_circle(r1+in);
    xc=320;
      yc=300;
      r1=100;
    draw_line(xc-r1-in,xc+r1+in,yc-10+in,yc-10+in);
    draw_line(xc-r1-in,xc-r1-in,yc-10+in,yc-150+in);
    draw_line(xc+r1+in,xc+r1+in,yc-10+in,yc-150+in);
    draw_line(xc-r1-in,xc+r1+in,yc-150+in,yc-150+in);
    draw_line(xc-r1-10-in,xc-r1-10-in,yc-10+in,yc-150+in);
    draw_line(xc-r1-50-in,xc-r1-50-in,yc-10+in,yc-150+in);
    draw_line(xc+r1+in+10,xc+r1+in+10,yc-10+in,yc-150+in);
    draw_line(xc+r1+in+50,xc+r1+in+50,yc-10+in,yc-150+in);
    draw_line(xc-r1-10-in,xc-r1-50-in,yc-10+in,yc-10+in);
    draw_line(xc+r1+10+in,xc+r1+50+in,yc-10+in,yc-10+in);
    draw_line(xc-10-r1-in,xc-r1-50-in,yc-150+in,yc-150+in);
    draw_line(xc+r1+in+10,xc+r1+in+50,yc-150+in,yc-150+in);
    xc=280+in,yc=330+in,r1=20+in/2;
    draw_line(xc-r1-in,xc+r1+in,yc-150-100+in,yc-150-100+in);
    draw_line(xc-r1-in,xc-r1-in,yc-150-30+in,yc-150-100+in);
    draw_line(xc+r1+in,xc+r1+in,yc-150-30+in,yc-150-100+in);
    xc=360+in,yc=330+in,r1=20+in/2;
    draw_line(xc-r1-in,xc+r1+in,yc-150-100+in,yc-150-100+in);
    draw_line(xc+r1+in,xc+r1+in,yc-150-30+in,yc-150-100+in);
    draw_line(xc-r1-in,xc-r1-in,yc-150-30+in,yc-150-100+in);
    glutSwapBuffers(); 
  }
  if(clear==1)
  {
    glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  }
 
}

void Init()
{
  glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0,1.0,1.0);
  glMatrixMode(GL_PROJECTION);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
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
