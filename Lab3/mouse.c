#include <stdio.h> 
#include <GL/glut.h> 
#include <math.h> 
#define pi 3.142857 
    
float scalf=1.0;

GLfloat angle = 0.0f;  // rotational angle of the shapes
int refreshMills = 30;


void Timer(int value) {
   glutPostRedisplay();      // Post re-paint request to activate display()
   glutTimerFunc(refreshMills, Timer, 0); // next Timer call milliseconds later
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
   } 
}

void keyboard(unsigned char key, int x, int y)
{
  
  if(key=='a')
  {
     angle+=5.0f;
    if(angle>360.0)
    {
      angle=angle-360.0;
    }
    glutPostRedisplay();
  }
  else if(key=='b')
  {
    angle-=5.0f;
    if(angle<-360.0)
    {
      angle=360.0-angle;
    }
    glutPostRedisplay();
  }
   else if(key=='l')
  {
    angle-=5.0f;
    if(angle<-360.0)
    {
      angle=360.0-angle;
    }
    glutPostRedisplay();
  }
}

void myInit (void) 
{ 
   glClearColor(0.0, 0.0, 0.0, 1.0); 
   glColor3f(0.0, 1.0, 0.0); 
   glPointSize(1.0); 
   glMatrixMode(GL_PROJECTION); 
   glLoadIdentity(); 
   gluOrtho2D(0, 500, 500, 0); 
} 
void drawLeft()
{
  glPushMatrix();
  float x_a,y_a;
  x_a = xb;
  y_a = yb;
  glTranslatef(x_a*1.0f, y_a*1.0f, 0.0f);
    glRotatef(angle,0.0f,0.0f, 1.0f); // rotate by angle in degrees
   glTranslatef(-x_a*1.0f, -y_a*1.0f, 0.0f);
    bresenCircle(150,230,10); // xc1 yc1
     glPopMatrix();   
}
void drawRight()
{
   glPushMatrix();
  float x_a,y_a;
  x_a = xc;
  y_a = yc;
   glTranslatef(x_a*1.0f, y_a*1.0f, 0.0f);
    glRotatef(angle,0.0f,0.0f, 1.0f); // rotate by angle in degrees
   glTranslatef(-x_a*1.0f, -y_a*1.0f, 0.0f);
     bresenCircle(350,230,10); // xc2 yc2
      glPopMatrix();   
}
void display (void) 
{ 
  glClear(GL_COLOR_BUFFER_BIT); 
  glMatrixMode(GL_MODELVIEW);    // To operate on the model-view matrix
  glLoadIdentity();              // Reset model-view matrix
  glPushMatrix();
  bresenCircle(250,250,200); // xa ya

  bresenCircle(150,200,50); // xb yb
  bresenCircle(350,200,50); // xc yc

  drawLeft();
  drawRight();

  glPopMatrix();   
   glutSwapBuffers();
} 

int main (int argc, char** argv) 
{ 

   glutInit(&argc, argv); 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
   // giving window size in X- and Y- direction 
   glutInitWindowSize(500, 500); 
   glutInitWindowPosition(100, 100);
   
   // Giving name to window 
   glutCreateWindow("face"); 
   myInit(); 
   glutDisplayFunc(display); 
   // glutMouseFunc(mouse);
   glutTimerFunc(0, Timer, 0);
   glutKeyboardFunc(keyboard);
   glutMainLoop(); 
} 
