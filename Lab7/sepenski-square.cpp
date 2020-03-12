
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

void display();
using namespace std;

int N;
float xd1,yd1,xd2,yd2,xd3,yd3,xd4,yd4;

void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

void drawSq(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{   
    glColor3f(0.0,1.0,0.0);
  glBegin(GL_QUADS);
   glVertex2i(x1,y1);
   glVertex2i(x2,y2);
   glVertex2i(x3,y3);
   glVertex2i(x4,y4);
   glEnd();
   glFlush();
}
void serpenski(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,int n)
{
    if(n <= 0)
    {
      drawSq(x1,y1,x2,y2,x3,y3,x4,y4);
      return;
    }
    n--;
    
  float d = (x2-x1)/3;

  serpenski(x1,y1,x1+d,y1,x1+d,y1+d,x1,y1+d,n);
  serpenski(x1+d,y1,x1+2*d,y1,x1+2*d,y1+d,x1+d,y1+d,n);
  serpenski(x1+2*d,y1,x2,y2,x2,y1+d,x1+2*d,y1+d,n);

  serpenski(x1,y1+d,x1+d,y1+d,x1+d,y1+2*d,x1,y1+2*d,n);
  serpenski(x1+2*d,y1+d,x2,y1+d,x2,y1+2*d,x1+2*d,y1+2*d,n);

  serpenski(x1,y1+2*d,x1+d,y1+2*d,x1+d,y4,x4,y4,n);
  serpenski(x1+d,y1+2*d,x1+2*d,y1+2*d,x1+2*d,y4,x1+d,y4,n);
  serpenski(x1+2*d,y1+2*d,x2,y2+2*d,x3,y3,x1+2*d,y3,n);

    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
   serpenski(xd1,yd1,xd2,yd2,xd3,yd3,xd4,yd4,N);

}


int main(int argc,char** argv)
{
    cout<<"Enter N"<<endl;
    cin>>N;
    printf("Enter Square co-ordinates:");
    cout<<"Enter x1 y1"<<endl;
    cin>>xd1>>yd1;
    cout<<"Enter x2 y2"<<endl;
    cin>>xd2>>yd2;
    cout<<"Enter x3 y3"<<endl;
    cin>>xd3>>yd3;
    cout<<"Enter x4 y4"<<endl;
    cin>>xd4>>yd4;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    // glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}