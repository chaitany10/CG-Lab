
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

void display();
using namespace std;

int N;
float xd1,yd1,xd2,yd2,xd3,yd3;

void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

void drawTri(float x1,float y1,float x2,float y2,float x3,float y3)
{   
    glColor3f(0.0,1.0,0.0);
  glBegin(GL_LINE_LOOP);
   glVertex2i(x1,y1);
   glVertex2i(x2,y2);
   glVertex2i(x3,y3);
   glEnd();
   glFlush();
}
void serpenski(float x1,float y1,float x2,float y2,float x3,float y3,int n)
{
    if(n <= 0)
    {
      drawTri(x1,y1,x2,y2,x3,y3);
      return;
    }

    
    n--;
    serpenski(x1,y1,((x1+x2)/2),y1,((3*x1+x2)/4),((y1+y3)/2),n);
    serpenski(((x1+x2)/2),y1,x2,y2,((3*x2+x1)/4),((y2+y3)/2),n);
    serpenski(((3*x1+x2)/4),((y1+y3)/2),((3*x2+x1)/4),((y2+y3)/2),x3,y3,n);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
   serpenski(xd1,yd1,xd2,yd2,xd3,yd3,N);

}


int main(int argc,char** argv)
{
    cout<<"Enter N"<<endl;
    cin>>N;
    printf("Enter triangle co-ordinates:");
    cout<<"Enter x1 y1"<<endl;
    cin>>xd1>>yd1;
    cout<<"Enter x2 y2"<<endl;  
    cin>>xd2>>yd2;
    cout<<"Enter x3 y3"<<endl;
    cin>>xd3>>yd3;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("tri");
    glutDisplayFunc(display);
    // glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}