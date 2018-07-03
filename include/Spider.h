#ifndef _SPIDER_H_
#define _SPIDER_H_

#include <Transformations.h>
#include <Geometrics.h>

typedef struct {
	Point joint[3]; /* Leg has 3 joints */ 
	float sideAngle = 0.0f,upAngle = 0.0f;
}Leg;

/* Spider class its atributes and methods */
class Spider{
	private:	
		// Body properties variables
		Circle cephalo, abdomen;
		Leg leftLeg[4], rightLeg[4];
		// Spider Moviment variables
		Vector direction;
		float speed, angle, legSDir,legUpDir;
		int counter;

		void initLegs();
		void drawLegs();
		void oneSideAnimation(Leg *,float ,float );
		void startLegAnimation();
		void endLegAnimation();

	public:

		Spider(); 

		void setBody(Circle, Circle);
		void setLegs(Leg [], Leg[]);

		Circle getCephalo();
		Circle getAbdomen();	

		void draw();
		
		void move();
		void turn(float);
		void legsAnimation();
		
};

#endif 