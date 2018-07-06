#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>

#include <T2.h>
#include <Spider.h>
//#include <Transformations.h>
#include <math.h>
#include <ilumination.h>
#include <texture.h>

//Point p;

Spider spider;
GLuint groundTex,skyTex;


void drawGround(){
	glTranslatef(0,-0.5,0);	
	//glColor3f(0.3, 0.3, 0.3);
	glEnable ( GL_TEXTURE_2D );
	glBindTexture ( GL_TEXTURE_2D, groundTex);
	//printf("GROUND[%d]\n",groundTex);
    glBegin(GL_QUADS);
		glTexCoord2f(0,0);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glTexCoord2f(50.0,0);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glTexCoord2f(50.0,50.0);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glTexCoord2f(0,50.0);
		glVertex3f( 100.0f, 0.0f, -100.0f);
 
	glEnd();
	glDisable ( GL_TEXTURE_2D );
	glTranslatef(0,0.5,0);
			
}

void drawSky(){
	float x = 100.0f;
	glTranslatef(0,-0.5,0);	
	glDepthMask(GL_FALSE);
	glEnable ( GL_TEXTURE_CUBE_MAP );
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyTex);
	glBegin(GL_QUADS);

	glTexCoord2f(0,0);glVertex3f(-100.0f, 0.0f, -100.0f);
	glTexCoord2f(x,0);glVertex3f(-100.0f, 0.0f,  100.0f);
	glTexCoord2f(x,x);glVertex3f( -100.0f, 100.0f,  100.0f);
	glTexCoord2f(0,x);glVertex3f( -100.0f, 100.0f, -100.0f);

	glTexCoord2f(0,0);glVertex3f(-100.0f, 0.0f, 100.0f);
    glTexCoord2f(x,0);glVertex3f(100.0f, 0.0f,  100.0f);
    glTexCoord2f(x,x);glVertex3f( 100.0f, 100.0f,  100.0f);
	glTexCoord2f(0,x);glVertex3f( -100.0f, 100.0f, 100.0f);

	glTexCoord2f(0,0);glVertex3f(100.0f, 0.0f, 100.0f);
	glTexCoord2f(x,0);glVertex3f(100.0f, 0.0f, -100.0f);
	glTexCoord2f(x,x);glVertex3f( 100.0f, 100.0f,  -100.0f);
	glTexCoord2f(0,x);glVertex3f( 100.0f, 100.0f, 100.0f);

	glTexCoord2f(0,0);glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(x,0);glVertex3f(-10.0f, 0.0f,  -10.0f);
	glTexCoord2f(x,x);glVertex3f( -10.0f, 10.0f,  -10.0f);
	glTexCoord2f(0,x);glVertex3f( 10.0f, 10.0f, -10.0f);


	glEnd();
	glDisable (GL_TEXTURE_CUBE_MAP);
	glDepthMask(GL_TRUE);
	glTranslatef(0,0.5,0);
}

// Display all drawings and atualizations on the screen
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    ilumination();


    Point c = spider.getCephalo().c;
	
    /* Tela esquerda de baixo Por cima em Y */
    glPushMatrix();
    glViewport(0, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(c.x, 5.0+c.y,c.z,c.x,c.y,c.z, 1.0, 0.0, 0.0);
	//drawSky();
	drawGround();
	spider.draw();

	
 	


	glPopMatrix();

    /*Tela direita de baixo De frente por Z*/
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(5.0+c.x,c.y,c.z,c.x,c.y,c.z, 0.0, 1.0, 0.0);
	//drawSky();
	drawGround();
    spider.draw();
	//glFogf(GL_FOG_COLOR,( 0.5, 0.5, 0.5, 1.0));

    glPopMatrix();

    /* Tela esquerda de cima Na de lado por X */ 
    glPushMatrix();
    glViewport(0, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(c.x, c.y, 5.0+c.z, c.x, c.y, c.z, 0.0, 1.0, 0.0);
	//drawSky();
	drawGround();
    spider.draw();
    glPopMatrix();

    /* Tela direita de cima Aleatório */
    glPushMatrix();
    glViewport(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    glLoadIdentity();
    gluLookAt(3.0+c.x, 2.0+c.y, 10.0+c.z, c.x, c.y, c.z, 1.0, 1.0, 1.0);
	//drawSky();
	drawGround();
    spider.draw();
    glPopMatrix();

	/*Dispara os comandos APENAS uma vez */
  	glFlush();
}

// checks for keyboard input
void keyboardSpecial(GLint key, GLint x, GLint y){ 
    switch(key){
	  	case GLUT_KEY_UP:
	  		printf("Andando pra frente\n");
	  		spider.move();
	  		break;
	  	case GLUT_KEY_DOWN:
	  		printf("Andando pra tras? De ré???\n");

	  		break;
	  	case GLUT_KEY_LEFT:
	  		printf("Rotacionando/virando pra esquerda\n");
	  		spider.turn(0.5f);
	  		break;
	  	case GLUT_KEY_RIGHT:
	  		printf("Rotacionando/virando pra direita\n");
	  		spider.turn(-0.5f);
	  		break;
	  }
	  
  std::cout<<"Tecla: "<<(GLint) key<<" (x:"<<x<<", y:"<<y<<")\n"; 
  
}

void update(int val){
	glutTimerFunc(fps, update, 0); // Calls update again
	glutPostRedisplay(); // Calls the display function again
}

// Initiates the screen 
void defaultInit(){
	// Sets the color thar glClear will 'paint' in RGBA
	glClearColor(1, 1, 1, 1);

	
	//glEnable(GL_TEXTURE_2D);

	// Sets the matrix with projection wich will do alot of matrix operations
	glMatrixMode(GL_PROJECTION); // signal that I want to work with the projection stack
	glLoadIdentity(); // make sure that the projection stack doesn't already have anything on it
	glMatrixMode(GL_MODELVIEW); // the rest of my app will only change MODELVIEW 
	glLoadIdentity();	

	glEnable(GL_DEPTH_TEST);
	
	//glEnable ( GL_TEXTURE_3D );
	spider = Spider();
	loadTexture2d("texture/ground.jpeg",&groundTex);
	loadTextureCubeMap("texture/sky.jpg",&skyTex);

	/////////////////////// DISTANCE FOGGING ///////////////////////
	glEnable(GL_FOG);
	glFogf(GL_FOG_MODE,GL_LINEAR);
	float FogCol[4]={0.5, 0.5, 0.5, 1.0}; // Define a nice light grey
	glFogfv(GL_FOG_COLOR,FogCol);

	glFogf(GL_FOG_DENSITY, GL_EXP);
	glFogf(GL_FOG_HINT,GL_NICEST);
	glFogf(GL_FOG_START, 1.0f);
 	glFogf(GL_FOG_END, 200.f);


}


void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}



int main(int argc, char *argv[]){

	// Start up the glut	
	glutInit(&argc, argv);
	// Info for openGL about the screen/buffers
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
	// Getting device screen WINDOW_WIDTH and height
	GLint screen_width = glutGet(GLUT_SCREEN_WIDTH), screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	// Centering the window
	glutInitWindowPosition((screen_width - WINDOW_WIDTH)/2, (screen_height - WINDOW_HEIGHT)/2);
	// Window size
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	// Creating window passing a title
	glutCreateWindow(".");

	defaultInit();

	glutDisplayFunc(display);
	glutSpecialFunc(keyboardSpecial);
	glutReshapeFunc(reshape);
	glutTimerFunc(fps, update, 0);
	
	glutMainLoop();

	spider.destroy();

	return EXIT_SUCCESS;
}