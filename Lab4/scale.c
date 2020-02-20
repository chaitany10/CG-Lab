#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#define pi 3.142857 
float a[100];
float b[100];
int n;
float x1,y11,x2,y2,s,xa,ya,xb,yb;
float tx,ty;
int choice;

float xc,yc,R;

void myInit (void) 
{ 
   glClearColor(0.0, 0.0, 0.0, 1.0); 
   glColor3f(0.0, 1.0, 0.0); 
   glPointSize(1.0); 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   gluOrtho2D(-780, 780, -420, 420); 
} 

void DDA(float X1,float Y1,float X2,float Y2)
{
    float dy,dx,step,x,y,k,Xin,Yin;
     dx=X2-X1;
     dy=Y2-Y1;
      
     if(abs(dx)> abs(dy))
     {
     step = abs(dx);
     }
     else
     step = abs(dy);
      
     Xin = dx/step;
     Yin = dy/step;
      
     x= X1;
     y=Y1;
     glBegin(GL_POINTS);
     glVertex2i(x,y);
     glEnd();
      
     for (k=1 ;k<=step;k++)
     {
        x= x + Xin;
        y= y + Yin;
         
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
     }
}
void drawCircle(int c1, int c2, int x, int y) 
{ 
   
   glBegin(GL_POINTS);
   glVertex2i(c1+x, c2+y); 
   glVertex2i(c1-x, c2+y); 
   glVertex2i(c1+x, c2-y); 
   glVertex2i(c1-x, c2-y); 
   glVertex2i(c1+y, c2+x); 
   glVertex2i(c1-y, c2+x); 
   glVertex2i(c1+y, c2-x); 
   glVertex2i(c1-y, c2-x); 
   glEnd();
} 
void bresenCircle(int c1,int c2,int r)
{
   int x = 0, y = r; 
   int d = 3 - 2 * r; 
   drawCircle(c1, c2, x, y); 
   while (y >= x) 
   { 
      x++; 
      if (d > 0) 
      { 
         y--; 
         d = d + 4 * (x - y) + 10; 
      } 
      else
         d = d + 4 * x + 6; 
      drawCircle(c1, c2, x, y); 
      // delay(50); 
   } 
}

void display (void) 
{ 
    if(choice==1)
    {
        glClear(GL_COLOR_BUFFER_BIT); 
  
        // update 
        float px = x1 * tx; 
        float py = y11 * ty; 
  
        float px1 = x2*tx;
        float py1 = y2*ty;


        glColor3f( 0.5, 1, 0.5 );
        glBegin(GL_LINES);
        glVertex2f(px, py);
        glVertex2f(px1, py1);
        glEnd();

        glColor3f( 1, 1, 1 );
        glBegin(GL_LINES);
        glVertex2f(x1, y11);
        glVertex2f(x2, y2);
        glEnd();
        glFlush(); 
    }
    if(choice == 2)
    {
        glClear(GL_COLOR_BUFFER_BIT); 
   bresenCircle(xc,yc,R);
   bresenCircle(xc,yc,R*s);
   glFlush();

    }
    if(choice == 3)
    {
        glClear(GL_COLOR_BUFFER_BIT); 
        int i;
        glColor3f( 1, 1, 1 );
        glBegin(GL_LINE_LOOP);
        for(i=0;i<n;i++)
        {
            glVertex2f(a[i], b[i]);
        }
        glEnd();
        glColor3f( 0.5, 1, 0.5 );
        glBegin(GL_LINE_LOOP);
        for(i=0;i<n;i++)
        {	
            glVertex2f(a[i]*tx, b[i]*ty);
        }
        glEnd();
        
        glFlush(); 
    }
} 

int main (int argc, char** argv) 
{ 
    

    printf("Translate\n1.Line\n2.Circle\n3.Polygon\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        printf("Enter x1,y1,x2,y2\n");
	    scanf("%f %f %f %f",&x1,&y11,&x2,&y2);
        printf("Enter Scale\n");
	    scanf("%f %f",&tx,&ty);
    }
    if(choice == 2)
    {
        printf("Enter xc,yc\n");
        scanf("%f %f",&xc,&yc);
        printf("Enter r\n");
        scanf("%f",&R);
        printf("Enter s\n");
        scanf("%f",&s);
    }
    if(choice == 3)
    {
        printf("Enter sides count\n");
        scanf("%d",&n);
        printf("Enter %d sides\n",n);
        int i;
        for(i=0;i<n;i++){
            scanf("%f %f",&a[i],&b[i]);
        }
        
	
        printf("Enter Scale\n");
        scanf("%f %f",&tx,&ty);
    }
   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
   // giving window size in X- and Y- direction 
   glutInitWindowSize(1366, 768); 
   glutInitWindowPosition(0, 0); 
   
   // Giving name to window 
   glutCreateWindow("Chess Board"); 
   myInit(); 
   
   glutDisplayFunc(display); 
   glutMainLoop(); 
} 