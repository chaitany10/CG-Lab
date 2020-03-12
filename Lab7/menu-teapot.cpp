
#include <GL/glut.h> 
static int window;
static int menu_id;
static int submenu_id;
static int value = 0; 
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
    submenu_id = glutCreateMenu(menu);
    
    glutAddMenuEntry("wired-teapot", 2);
    glutAddMenuEntry("Solid-Teapot", 3);
    
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