#include<stdio.h> 
#include<GL/glut.h> 
#include<math.h> 
#define pi 3.142857 
float a[100];
float b[100];
int n;
int xa,ya,xb,yb;
int xr,yr;
int choice;
float angle;
float xc,yc,R,x1,y11,x2,y2,tx;

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
void rotateArnd(int pxa, int pya,int pxb,int pyb, int cx, int cy,float theta) 
{ 
  
    // glClear(GL_COLOR_BUFFER_BIT); 
    int xfa, yfa,xfb,yfb; 

    // check overflow 
    if (theta >= (2.0 * 3.14159)) 
      theta = theta - (2.0 * 3.14159); 

    // actual calculations.. 
    xfa = cx + (int)((float)(pxa - cx) * cos(theta)) 
      - ((float)(pya - cy) * sin(theta)); 
    yfa = cy + (int)((float)(pxa - cx) * sin(theta)) 
      + ((float)(pya - cy) * cos(theta)); 

    xfb = cx + (int)((float)(pxb - cx) * cos(theta)) 
      - ((float)(pyb - cy) * sin(theta)); 
    yfb = cy + (int)((float)(pxb - cx) * sin(theta)) 
      + ((float)(pyb - cy) * cos(theta)); 

    glBegin(GL_LINES);
   glVertex2f(xfa, yfa); 
   glVertex2f(xfb, yfb);  
   glEnd();

    glFlush(); 
} 
void display (void) 
{ 
    if(choice==1)
    {
        glClear(GL_COLOR_BUFFER_BIT); 
        glBegin(GL_LINES);
        glVertex2f(xa, ya); 
        glVertex2f(xb, yb);  
        glEnd();
        rotateArnd(xa,ya,xb,yb,xr,yr,angle);
        glFlush();
    }
    
    if(choice == 2)
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
            float xx = a[i]*cos(0.7)-b[i]*sin(0.7);
	        float yy = b[i]*cos(0.7)+a[i]*sin(0.7);
	        glVertex2f(xx, yy);
        }
        glEnd();
        glFlush(); 
    }
} 


int main (int argc, char** argv) 
{ 
    

    printf("Translate\n1.Line\n2.Polygon\n");
    scanf("%d",&choice);
    if(choice == 1)
    {
        printf("Enter x1,y1\n");
    scanf("%d %d",&xa,&ya);
    printf("Enter x2,y2\n");
    scanf("%d %d",&xb,&yb);
    printf("Enter angle\n");
    scanf("%f",&angle);
    printf("Enter rot axis x,y\n");
    scanf("%d %d",&xr,&yr);
            
    }
    
    if(choice == 2)
    {
        printf("Enter sides count\n");
        scanf("%d",&n);
        printf("Enter %d sides\n",n);
        int i;
        for(i=0;i<n;i++){
            scanf("%f %f",&a[i],&b[i]);
        }
        float tx,ty;
        printf("Enter degree for rotation\n");
        scanf("%f",&tx);
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