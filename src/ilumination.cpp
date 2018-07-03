#include <stdio.h>
#include <GL/glut.h>



/* KIBEI HARD PARTE DE ILUMINAçÃO TEM QUE VER COMO FUNFA */
GLfloat mat_diffuse [] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_specular [] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess [] = {100};
GLfloat mat_emission [] = {0.05, 0.05, 0.05, 0.05};

void ilumination(){
     GLfloat light_position[] = {0, 1, 0, 0}; //Luz Emitida do x=0,y=0,z=0 (SOL)

     glLightfv(GL_LIGHT0,GL_POSITION, light_position);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
     glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
     glEnable (GL_LIGHTING);
     glEnable (GL_LIGHT0);
     glEnable(GL_COLOR_MATERIAL);
}

