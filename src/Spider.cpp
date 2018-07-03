#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <GL/glut.h>
#include <limits.h>
#include <string>
#include <vector>
#include <string.h>
#include <Spider.h>
#include <T2.h>


using namespace std;


	/* Creates a random spyder, can be changed later */
	Spider::Spider(){
		
			// cephalo initial position and size
			cephalo.r = 0.25f;
			

			// abdomen initial position and size relative to cephalo
			abdomen.r = cephalo.r*2;

			cephalo.c = createPoint(0.0f,0.0f,0.0f);
			abdomen.c = createPoint((-1.0f)*(cephalo.r+abdomen.r),0.0f,0.0f);

			direction = createNormalizedVector(abdomen.c,cephalo.c);
			speed = 0.1f;
			angle = 0.0f;
	
			initLegs();

			startLegAnimation();

			counter = 0;
			legSDir= 1.0f;
			legUpDir= 1.0f;
	}

	Circle Spider::getCephalo(){
	return cephalo;
	}

	Circle Spider::getAbdomen(){
		return abdomen;
	}


	void Spider::initLegs(){
 
		//Patas da direita

		// Pata da frente
		rightLeg[0].joint[0] = createPoint(cephalo.r*sin(M_PI/7),0.0f,cephalo.r*cos(M_PI/4));
		rightLeg[0].joint[1] = createPoint(3*cephalo.r*sin(M_PI/3),cephalo.r,3*cephalo.r*cos(M_PI/3));
		rightLeg[0].joint[2] = createPoint(4.5*cephalo.r*sin((M_PI/3)-(M_PI/36)),-1.75*cephalo.r,4.5*cephalo.r*cos((M_PI/3)-(M_PI/36)));
		
		// Primeira pata pequena
		rightLeg[1].joint[0] = createPoint(cephalo.r*sin(M_PI/18),0.0f,cephalo.r*cos(M_PI/9));
		rightLeg[1].joint[1] = createPoint(cephalo.r*sin(M_PI/8),0.75*cephalo.r,1.75*cephalo.r);
		rightLeg[1].joint[2] = createPoint(cephalo.r*sin(M_PI/8),-1.75*cephalo.r,2.25*cephalo.r);

		// Segunda pata pequena
		rightLeg[2].joint[0] = createPoint(0.0f,0.0f,cephalo.r);
		rightLeg[2].joint[1] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/18),0.75*cephalo.r, 1.75*cephalo.r);
		rightLeg[2].joint[2] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/18),-1.75*cephalo.r, 2.25*cephalo.r);

		//Pata de tras
		rightLeg[3].joint[0] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/9),0.0f,cephalo.r*cos(M_PI/9));
		rightLeg[3].joint[1] = createPoint(2*cephalo.r*(-1.0f)*sin(M_PI/7.5),cephalo.r,2*cephalo.r*cos(M_PI/7.5));
		rightLeg[3].joint[2] = createPoint(3.5*cephalo.r*(-1.0f)*sin(M_PI/5),-1.75*cephalo.r,3.5*cephalo.r*cos(M_PI/5));

		// --------------------------------

		//Patas da Esquerda

		// Pata da frente
		leftLeg[0].joint[0] = createPoint(cephalo.r*sin(M_PI/7),0.0f,(-1.0)*cephalo.r*cos(M_PI/4));
		leftLeg[0].joint[1] = createPoint(3*cephalo.r*sin(M_PI/3),cephalo.r,(-3.0)*cephalo.r*cos(M_PI/3));
		leftLeg[0].joint[2] = createPoint(4.5*cephalo.r*sin((M_PI/3)-(M_PI/36)),-1.75*cephalo.r,(-4.5)*cephalo.r*cos((M_PI/3)-(M_PI/36)));
		
		// Primeira pata pequena
		leftLeg[1].joint[0] = createPoint(cephalo.r*sin(M_PI/18),0.0f,(-1.0)*cephalo.r*cos(M_PI/9));
		leftLeg[1].joint[1] = createPoint(cephalo.r*sin(M_PI/8),0.75*cephalo.r,(-1.75)*cephalo.r);
		leftLeg[1].joint[2] = createPoint(cephalo.r*sin(M_PI/8),-1.75*cephalo.r,(-2.25)*cephalo.r);

		// Segunda pata pequena
		leftLeg[2].joint[0] = createPoint(0.0f,0.0f,(-1.0)*cephalo.r);
		leftLeg[2].joint[1] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/18),0.75*cephalo.r, (-1.75)*cephalo.r);
		leftLeg[2].joint[2] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/18),-1.75*cephalo.r, (-2.25)*cephalo.r);

		//Pata de tras
		leftLeg[3].joint[0] = createPoint(cephalo.r*(-1.0f)*sin(M_PI/9),0.0f,(-1.0)*cephalo.r*cos(M_PI/9));
		leftLeg[3].joint[1] = createPoint(2*cephalo.r*(-1.0f)*sin(M_PI/7.5),cephalo.r,(-2.0)*cephalo.r*cos(M_PI/7.5));
		leftLeg[3].joint[2] = createPoint(3.5*cephalo.r*(-1.0f)*sin(M_PI/5),-1.75*cephalo.r,(-3.5)*cephalo.r*cos(M_PI/5));


	}

	// desenha uma perna
	void drawLeg(Leg l){
		for(int i=1;i<3;i++){
			

			glRotatef(l.sideAngle,0.0,1.0,0.0);	
			glRotatef(l.upAngle,1.0,0.0,0.0);
			
			glBegin(GL_LINES);

			glVertex3d(l.joint[i-1].x,l.joint[i-1].y,l.joint[i-1].z);
			glVertex3d(l.joint[i].x,l.joint[i].y,l.joint[i].z);


			glEnd();

			glRotatef((-1.0)*l.upAngle,1.0,0.0,0.0);
			glRotatef((-1.0)*l.sideAngle,0.0,1.0,0.0);	
			
		}	 
	}

	// Desenha todas as pernas da aranha
	void Spider::drawLegs(){
		glLineWidth(2);
		 // pega pontos dois a dois
		
		for (int i=0;i<4;i++) drawLeg(rightLeg[i]);
		for (int i=0;i<4;i++) drawLeg(leftLeg[i]);	

		
		glLineWidth(1);
	}

	// Desenha a aranha
	void Spider::draw(){
		// Red color used to draw.
   		glColor3f(1, 0, 0);


	    // Desenha abdomen no meio da tela

   		// Levar centro ate a posicao atual para rotacionar
   		glTranslatef(cephalo.c.x, cephalo.c.y, cephalo.c.z);
   		glRotatef(angle,0.0f,1.0f,0.0f);
   		
	    

		//glColor3f(0, 1, 0);

		// Tranlada pra cima do abdomen e desenha o cephalotorax
	    
		glutSolidSphere(cephalo.r,100,100);	
		//glColor3f(0,0,0);
		drawLegs();
		

		glTranslatef(abdomen.c.x, abdomen.c.y, abdomen.c.z);
   		glutSolidSphere(abdomen.r,100,100);	
   		glTranslatef((-1.0f)*abdomen.c.x, (-1.0f)*abdomen.c.y, (-1.0f)*abdomen.c.z);

		glRotatef((-1.0f)*angle,0.0f,1.0f,0.0f);
   		glTranslatef((-1.0f)*cephalo.c.x, (-1.0f)*cephalo.c.y, (-1.0f)*cephalo.c.z);
		
		// desenho do vetor direcao para testes
		/*glBegin(GL_LINES);
		glVertex3d(0.0f,0.0f,0.0f);
		glVertex3d(direction.x,direction.y,direction.z);
		glEnd();*/
		
	}

	void Spider::oneSideAnimation(Leg *l,float sdir,float updir){

		//primeira pata
		l[0].sideAngle += sdir*(2.0);
		l[0].upAngle += updir*(2.0);
		printf("%f\n",l[0].upAngle);
		// primeira pata pequena
		l[1].sideAngle += sdir*(-0.5);
		l[1].upAngle += updir*(1.0);
		// segunda pata pequena
		l[2].sideAngle += sdir*(0.5);
		l[2].upAngle += updir*(1.0);

		// ultima pata
		l[3].sideAngle += sdir*(-0.5);
		l[3].upAngle += updir*(2.0);
	}

	void Spider::startLegAnimation(){
		for(int i=0;i<5;i++){
				oneSideAnimation(rightLeg,-1.0,0.0);
				oneSideAnimation(leftLeg,-1.0,0.0);
		}
	}

	void Spider::endLegAnimation(){		
		while(counter!=5){
			oneSideAnimation(rightLeg,legSDir,legUpDir);
			oneSideAnimation(leftLeg,legSDir,(-1.0)*legUpDir);
		
			if(counter>5) counter--;
			else counter++;	
		}
		counter = 0;
		legSDir= 1.0f;
		legUpDir= 1.0f;

	}
	// Animacoes das patas
	void Spider::legsAnimation(){	

		oneSideAnimation(rightLeg,legSDir,(-1.0)*legUpDir);
		oneSideAnimation(leftLeg,legSDir,legUpDir);

		if(counter == 4)legUpDir = (-1.0)*legUpDir; 

		if(counter == 9){
			counter = 0;
			legSDir = (-1.0)*legSDir;
			legUpDir = (-1.0)*legUpDir;
		}else counter++;
	
	}

	// Movimentacao da Aranha em uma direcao
	void Spider::move(){

		// inicia as animacoes das pernas enquanto a aranha se movimenta
		legsAnimation();

		cephalo.c.x += (direction.x)*speed;
		cephalo.c.y += (direction.y)*speed;
		cephalo.c.z += (direction.z)*speed;
		
	}	

	// Mudanca de direcao da aranha
	void Spider::turn(float ang){

		legsAnimation();
		
		double zT = direction.z;
		direction.z = direction.z*cos(ang*(M_PI/(180.0f))) - direction.x*sin(ang*(M_PI/(180.0f)));
		direction.x = zT*sin(ang*(M_PI/(180.0f))) + direction.x*cos(ang*(M_PI/(180.0f)));

		angle += ang;

	}

