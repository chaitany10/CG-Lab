
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

void display();
using namespace std;

float xmin=-100;
float ymin=-100;
float xmax=100;
int s=0;

float ymax=100;

float xd1,yd1,xd2,yd2;
float xi1,yi1,xi2,yi2,xi3,yi3;


void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

int reg_code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}
  
void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=reg_code(x1,y1);
    int c2=reg_code(x2,y2);
    float m=(y2-y1)/(x2-x1);

    while((c1|c2)>0)
    {
          if((c1 & c2)>0) // outside else inside
          {
            xd1=0;
            yd1=0;
            xd2=0;
            yd2=0;
            break;
          }

          float xi=x1;float yi=y1;

          int cout=c1;

          if(cout==0)
          {
               cout=c2;
               xi=x2;
               yi=y2;
          }
          float x,y;

          if((cout & 8)>0) // top
          {
             y=ymax;
             x=xi+ 1.0/m*(ymax-yi);
          }
          else if((cout & 4)>0) //bottom
          {
              y=ymin;
              x=xi+1.0/m*(ymin-yi);
          } 
          else if((cout & 2)>0) // right
          {
              x=xmax;
              y=yi+m*(xmax-xi);
          }
          else if((cout & 1)>0) //left
          {
              x=xmin;
              y=yi+m*(xmin-xi);
          }

         if(cout==c1)
         {
             xd1=x;
             yd1=y;
             c1=reg_code(xd1,yd1);
         }

         if(cout==c2)
         {
             xd2=x;
             yd2=y;
             c2=reg_code(xd2,yd2);
         }
      }

 // display();

}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  
      s=1;
      display();
    }
}
void display()
{
    if(s==0){
   glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);

   glBegin(GL_LINE_LOOP);
   glVertex2i(xmin,ymin);
   glVertex2i(xmin,ymax);
   glVertex2i(xmax,ymax);
   glVertex2i(xmax,ymin);
   glEnd();
   glColor3f(1.0,0.0,0.0);
   glBegin(GL_LINES);
   glVertex2i(xi1,yi1);
   glVertex2i(xi2,yi2);
   glVertex2i(xi2,yi2);
   glVertex2i(xi3,yi3);
   glVertex2i(xi3,yi3);
   glVertex2i(xi1,yi1);
   glEnd();
   glFlush();}
   else
   {
       glClear(GL_COLOR_BUFFER_BIT);
       glColor3f(0.0,1.0,0.0);
       glBegin(GL_LINE_LOOP);
   glVertex2i(xmin,ymin);
   glVertex2i(xmin,ymax);
   glVertex2i(xmax,ymax);
   glVertex2i(xmax,ymin);
   glEnd();
         
   xd1=xi1;
   yd1=yi1;
   xd2=xi2;
   yd2=yi2;
   cohen_Line(xi1,yi1,xi2,yi2);
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_LINES);
   glVertex2i(xd1,yd1);
   glVertex2i(xd2,yd2);
   glEnd();

   xd1=xi2;
   yd1=yi2;
   xd2=xi3;
   yd2=yi3;
   cohen_Line(xi2,yi2,xi3,yi3);
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_LINES);
   glVertex2i(xd1,yd1);
   glVertex2i(xd2,yd2);
   glEnd();

   xd1=xi3;
   yd1=yi3;
   xd2=xi1;
   yd2=yi1;
   cohen_Line(xi3,yi3,xi1,yi1);
   glColor3f(0.0,0.0,1.0);
   glBegin(GL_LINES);
   glVertex2i(xd1,yd1);
   glVertex2i(xd2,yd2);
   glEnd();
   glFlush();
   }


   
}


int main(int argc,char** argv)
{
    printf("Enter triangle co-ordinates:");
    cout<<"Enter x1 y1"<<endl;
    cin>>xi1>>yi1;
    cout<<"Enter x2 y2"<<endl;
    cin>>xi2>>yi2;
    cout<<"Enter x3 y3"<<endl;
    cin>>xi3>>yi3;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    glutKeyboardFunc(mykey);
    init();
    glutMainLoop();
    return 0;
}