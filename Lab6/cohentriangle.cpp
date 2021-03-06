#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>

void display();
using namespace std;
int s=0;

float xmin=-100;
float ymin=-100;
float xmax=100;
float ymax=100;

float xd1,yd1,xd2,yd2,xd3,yd3;


void init(void)
{

    glClearColor(0.0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-300,300,-300,300);

}

int region(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}
  
void cohen_Line(float x1,float y1,float x2,float y2,float x3,float y3)
{
    int c1=region(x1,y1);
    int c2=region(x2,y2);
    int c3=region(x3,y3);
    float slope[3];
    slope[0]=(y2-y1)/(x2-x1);
    slope[1]=(y3-y2)/(x3-x2);
    slope[2]=(y1-y3)/(x1-x3);
    while((c1|c2|c3)>0)
    {
        /*
        xi = x1,yi = y1
        test
        
        
        
        */
          if((c1 & c2 & c3)>0) // outside else inside
          {
            xd1=0;
            yd1=0;
            xd2=0;
            yd2=0;
            xd3=0;
            yd3=0;
            break;
          }

          float xi=x1;float yi=y1;

          int tempc=c1;
            s=0;
          if(tempc==0)
          {s=1;
               tempc=c2;
               xi=x2;
               yi=y2;
               if(tempc==0)
               {
                   s=2;
                    tempc=c3;
                    xi=x3;
                    yi=y3;    
               }
          }
          
          float x,y;

          if((tempc & 8)>0) // top
          {
             y=ymax;
             x=xi+ 1.0/slope[s]*(ymax-yi);
          }
          else if((tempc & 4)>0) //bottom
          {
              y=ymin;
              x=xi+1.0/slope[s]*(ymin-yi);
          } 
          else if((tempc & 2)>0) // right
          {
              x=xmax;
              y=yi+slope[s]*(xmax-xi);
          }
          else if((tempc & 1)>0) //left
          {
              x=xmin;
              y=yi+slope[s]*(xmin-xi);
          }

         if(tempc==c1)
         {
             xd1=x;
             yd1=y;
             c1=region(xd1,yd1);
         }

         if(tempc==c2)
         {
             xd2=x;
             yd2=y;
             c2=region(xd2,yd2);
         }
         if(tempc==c3)
         {
             xd3=x;
             yd3=y;
             c1=region(xd3,yd3);
         }
      }

 display();

}

void mykey(unsigned char key,int x,int y)
{
    if(key=='c')
    {  
        cohen_Line(xd1,yd1,xd2,yd2,xd3,yd3);
        glFlush();
    }
}
void display()
{
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
   glVertex2i(xd1,yd1);
   glVertex2i(xd2,yd2);
   glEnd();
   glBegin(GL_LINES);
   glVertex2i(xd2,yd2);
   glVertex2i(xd3,yd3);
   glEnd();
   glBegin(GL_LINES);
   glVertex2i(xd1,yd1);
   glVertex2i(xd3,yd3);
   glEnd();
   glFlush();
}


int main(int argc,char** argv)
{
    printf("Enter line co-ordinates: x1,y1,x2,y2,x3,y3:");
    cin>>xd1>>yd1>>xd2>>yd2>>xd3>>yd3;

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