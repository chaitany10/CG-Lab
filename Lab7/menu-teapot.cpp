
#include <GL/glut.h> 
static int window;
static int menu_id;
static int color_menu_wired;
static int color_menu_solid;
static int submenu_id;
static int value = 0; 

GLfloat xRotated, yRotated, zRotated;
GLdouble size=0.5;
void menu(int num){
  if(num == 0){
    glutDestroyWindow(window);
    exit(0);
  }else{
    value = num;
  }
  glutPostRedisplay();
} 
void createMenu(void){     
    color_menu_wired = glutCreateMenu(menu);
    glutAddMenuEntry("yellow", 4);
    glutAddMenuEntry("blue", 2);
    color_menu_solid = glutCreateMenu(menu);
    glutAddMenuEntry("yellow", 5);
    glutAddMenuEntry("red", 3);

    menu_id = glutCreateMenu(menu);
    glutAddSubMenu("wired-teapot", color_menu_wired);
    glutAddSubMenu("Solid-Teapot", color_menu_solid);     
    
    glutAddMenuEntry("Clear", 1);
    //glutAddMenuEntry("Rotate", 6);
    glutAddMenuEntry("Quit", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
void display(void){
  glClear(GL_COLOR_BUFFER_BIT);
  if(value == 1)
  {
    return; //glutPostRedisplay();
  }
  else if(value == 2)
  {
    glPushMatrix();
    glColor3d(0.0, 0.0, 1.0);
    glutWireTeapot(0.5);
    glPopMatrix();
  }else if(value == 3)
  {
    glPushMatrix();
    glColor3d(1.0, 0.0, 1.0);
    glutSolidTeapot(0.5);
    glPopMatrix();
  } 
  else if( value == 4)
  {
    
    glPushMatrix();
    glColor3d(1.0, 1.0, 0.0);
    glutWireTeapot(0.5);
    glPopMatrix();
  }
  else if(value == 5)
  {
    
    glPushMatrix();
    glPushMatrix();
    glColor3d(1.0, 1.0, 0.0);
    glutSolidTeapot(0.5);
    glPopMatrix();
  }
  else if(value ==6)
  {
       
  }
  glFlush();
} 
int main(int argc, char **argv)
{   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    window = glutCreateWindow("Menu");
    createMenu();
    glClearColor(0.0,0.0,0.0,0.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return EXIT_SUCCESS;
}