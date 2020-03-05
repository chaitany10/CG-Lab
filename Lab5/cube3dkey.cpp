#include<iostream>
#include<math.h>
#include<GL/glut.h>
using namespace std;

typedef float Matrix4 [4][4];

Matrix4 theMatrix;
static GLfloat input[8][3]=
{
    {40,40,-50},{90,40,-50},{90,90,-50},{40,90,-50},
    {30,30,0},{80,30,0},{80,80,0},{30,80,0}

};
int gl=0;
float output[8][3];
float tx,ty,tz;
float sx,sy,sz;
float angle;

int choice,choiceRot,choiceRfl;

void setIdentityM(Matrix4 m)
{
for(int i=0;i<4;i++)
    for(int j=0;j<4;j++)
        m[i][j]=(i==j);
}

void translate(int tx,int ty,int tz)
{

    for(int i=0;i<8;i++)
    {
    output[i][0]=input[i][0]+tx;
    output[i][1]=input[i][1]+ty;
    output[i][2]=input[i][2]+tz;
    }
}

void scale(int sx,int sy,int sz)
{
    theMatrix[0][0]=sx;
    theMatrix[1][1]=sy;
    theMatrix[2][2]=sz;
}

 // Rotation
void RotateX(float angle) //Parallel to x
{

 angle = angle*3.142/180;
  theMatrix[1][1] = cos(angle);
 theMatrix[1][2] = -sin(angle);
 theMatrix[2][1] = sin(angle);
 theMatrix[2][2] = cos(angle);

}
void RotateY(float angle) //parallel to y
{

 angle = angle*3.14/180;
 theMatrix[0][0] = cos(angle);
 theMatrix[0][2] = -sin(angle);
 theMatrix[2][0] = sin(angle);
 theMatrix[2][2] = cos(angle);

}
void RotateZ(float angle) //parallel to z
{

 angle = angle*3.14/180;
 theMatrix[0][0] = cos(angle);
 theMatrix[0][1] = sin(angle);
 theMatrix[1][0] = -sin(angle);
 theMatrix[1][1] = cos(angle);

}
 
void multiplyM()
{
for(int i=0;i<8;i++)
 {
    for(int j=0;j<3;j++)
    {
        output[i][j]=0;
        for(int k=0;k<3;k++)
        {
            output[i][j]=output[i][j]+input[i][k]*theMatrix[k][j];
        }
    }
}

}
void draw(float a[8][3])
{


glBegin(GL_QUADS);
glColor3f(0.6,0.6,1); //behind
glVertex3fv(a[0]);
glVertex3fv(a[1]);
glVertex3fv(a[2]);
glVertex3fv(a[3]);

glColor3f(0.8,1.0,0.4);  //bottom
glVertex3fv(a[0]);
glVertex3fv(a[1]);
glVertex3fv(a[5]);
glVertex3fv(a[4]);

glColor3f(1.0,0,0); //left
glVertex3fv(a[0]);
glColor3f(0,1.0,1.0);
glVertex3fv(a[4]);
glColor3f(1.0,0,0);
glVertex3fv(a[7]);
glColor3f(0,1.0,1.0);
glVertex3fv(a[3]);

glColor3f(0,1.0,0);  //right
glVertex3fv(a[1]);
glColor3f(0,0,1.0);
glVertex3fv(a[2]);
glColor3f(0,1.0,0);
glVertex3fv(a[6]);
glColor3f(0,0,1.0);
glVertex3fv(a[5]);

glColor3f(1.0,0,0); //up
glVertex3fv(a[2]);
glColor3f(0,1.0,0);
glVertex3fv(a[3]);
glColor3f(1.0,0,0);
glVertex3fv(a[7]);
glColor3f(0,1.0,0);
glVertex3fv(a[6]);

glColor3f(0.2f, 0.2f, 0.2f);;//front
glVertex3fv(a[4]);
glColor3f(1.0f, 1.0f, 1.0f); 
glVertex3fv(a[5]);
glColor3f(0.2f, 0.2f, 0.2f);
glVertex3fv(a[6]);
glColor3f(1.0f, 1.0f, 1.0f); 
glVertex3fv(a[7]);

glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
	if(gl==1)
    {
	if(key=='x')
	{
         translate(100,0,0);
         glutPostRedisplay();
         draw(output);
	}
	else if(key=='y')
	{
		
         translate(0,100,0);
         glutPostRedisplay();
           draw(output);
	}
	else if(key=='z')
	{
		
         translate(0,0,100);
         glutPostRedisplay();
           draw(output);
	}
    }
    else if(gl == 3)
    {
      if(key=='x')
	{
         RotateX(30);
         multiplyM();
         glutPostRedisplay();
         draw(output);
	}
	else if(key=='y')
	{
		
        RotateY(50);
          multiplyM();
         glutPostRedisplay();
         draw(output);
	}
	else if(key=='z')
	{
		
         RotateZ(90);
         multiplyM();
         glutPostRedisplay();
         draw(output);
	}  
    }
    else if(gl == 2)
    {
        if(key=='x')
	{
        scale(2 ,1,1);
         multiplyM();
         glutPostRedisplay();
         draw(output);
	}
	else if(key=='y')
	{
		
            scale(1 ,2,1);
             multiplyM();
         glutPostRedisplay();
         draw(output);
	}
	else if(key=='z')
	{
		
              scale(1 ,1,2);
               multiplyM();
         glutPostRedisplay();
         draw(output);
	}  
    }
	
}

void init()
{
    glClearColor(0.0,0.0,0.0,1.0); 
    glOrtho(-454.0,454.0,-250.0,250.0,-250.0,250.0);
    
    glEnable(GL_DEPTH_TEST);
     
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

glColor3f(1.0,0.0,0.0);

draw(input);

setIdentityM(theMatrix);




draw(output);

glFlush();

}

int main(int argc, char** argv)
{
    cout<<"Enter your choice number:\n1.Translation\n2.Scaling\n3.Rotation\n=>";
    cin>>choice;
    switch (choice) {
    case 1:
       gl=1;
        break;
    case 2:
        gl=2;
        break;
    case 3:
        gl=3;
       
        break;
    default:
        break;
    }

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1362,750);
    glutInitWindowPosition(0,0);
    glutCreateWindow("3D TRANSFORMATIONS");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    
    init();
    glutMainLoop();
return 0;
}