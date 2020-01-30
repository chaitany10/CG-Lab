
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>


int xc,yc,r;

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
  glClear(GL_COLOR_BUFFER_BIT);
  bresenham_circle(r);
}

void Init()
{
  glClearColor(1.0,1.0,1.0,0);
  glColor3f(0.0,0.0,0.0);
  gluOrtho2D(0 , 640 , 0 , 480);
}

void main(int argc, char **argv)
{
  printf("Choose center coordinates\n");
  scanf("%d %d",&xc,&yc);
  printf("Enter radius\n");
  scanf("%d",&r);
  
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("bresenham_circle");
  Init();
  glutDisplayFunc(display);
  glutMainLoop();
}
