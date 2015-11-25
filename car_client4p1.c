#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define r_str 0.1f
#define r_cn 0.075f
#define dt 0.03f

float X[6]={-1.275f,0.0f,0.16f,0.0f,-0.16f,0.0f};
float Y[6]={0.0f,-0.16f,0.0f,0.16f,0.0f,0.0f};
float fr_coeff = 0.62f,dir_x = 0.0f,dir_y = -1.275;
float Vx[6],Vy[6];

#include "./cl4p1_include/networking.h"
#include "./cl4p1_include/figures.h"
#include "./cl4p1_include/update_vel_pos.h"
#include "./cl4p1_include/collision.h"
#include "./cl4p1_include/chance.h"

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)//The key that was pressed //The current mouse coordinates
{    
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
	}
}

//Initializes 3D rendering
void initRendering() {
	//Makes 3D drawing work when something is in front of something else
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.6f, 0.8f, 1.0f);
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);//The camera angle
				                   //The width-to-height ratio
				                   //The near z clipping coordinate
				                  //The far z clipping coordinate
}

void update(int value) 
{
	glutPostRedisplay(); //Tell GLUT that the display has changed
	update_vel_pos(Vx,Vy,X,Y);
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}
void move(int x1,int y1)
{
	float x = (float)x1;
	float y = (float)y1;
	x = (x-300.0f)/150.0f;
	y = (300.0f-y)/150.0f;
	float theta = atan((Y[0]-y)/(X[0]-x)),ux,uy;
	ux = cos(theta);
	uy = sin(theta);
	if(uy < 0.0f)
	{
		uy = -uy;
		ux = -ux;
	}
	if(dir == 'y')
	{
		dir_x = X[0] + 1.5*ux;
		dir_y = Y[0] + 1.5*uy;
	}
}
void pressedMotion(int button, int state, int x1, int y1)
{
	static float x_prev;
	static float y_prev;
	char buffer[256];
	int n;
	float vx,vy,X_fac=0.0f,Y_fac=0.0f,D_fac=0.0f;
	float x = (float)x1;
	float y = (float)y1;
	x = (x-300.0f)/150.0f;
	y = (300.0f-y)/150.0f;
	if(i_check == 0)
	{
		x_prev=0.0f;
		y_prev = -1.275f;
		i_check++;	
	}
	if(chance[1]=='y')
	{
		if(button==0 && state==0)
		{
			X[0] = x;
			if(X[0] > 1.1f) X[0] = 1.1f;
			if(X[0] < -1.1f) X[0] = -1.1f;
		}
		if(button==2 && state==0)
		{
			dir = 'n';
			X_fac = (x_prev-x);
			Y_fac = (y_prev-y);
			D_fac = distance(x,y,x_prev,y_prev)*4.0f;//*40.0f)/0.73f;
			if(X_fac == 0.0f)
				Vx[0] = 0.0f;
			else
				vx = ((x_prev-x)/fabs(x_prev-x))*D_fac*cos(atan(Y_fac/X_fac));
			vy = ((y_prev-y)/fabs(y_prev-y))*D_fac*fabs(sin(atan(Y_fac/X_fac)));
			if(fabs(vx) > 3.0f) { vx = 3.0f*(fabs(vx)/vx)*cos(atan(Y_fac/X_fac));vy = 3.0f*(fabs(vy)/vy)*fabs(sin(atan(Y_fac/X_fac)));}
			else if(fabs(vy) > 3.0f) { vx = 3.0f*(fabs(vx)/vx)*cos(atan(Y_fac/X_fac));vy = 3.0f*(fabs(vy)/vy)*fabs(sin(atan(Y_fac/X_fac)));}
			Vx[0] = vx;
			Vy[0] = vy;
		}
		x_prev = X[0];
		y_prev = -1.275f;
		if(isStrikerHitByMe=='n')
		{
			if(button==0 )
				isStrikerHitByMe='n';
			else
				isStrikerHitByMe='y';
		
		}
		if(state==0 || (Vx[0]==0.0f && Vy[0]==0.0f))
		{
			bzero(buffer,256);
			copy(Vx[0],Vy[0],X[0],Y[0],buffer,isStrikerHitByMe);
			n = write(sockfd,buffer,strlen(buffer));
    			if (n < 0) 
        			error("ERROR writing to socket");
        	}
        }
	
}

void reDraw()
{
	if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
	{
		if(score_4p[0] > score_4p[1]) printf("TEAM1 WINS\n");
		else if(score_4p[0] < score_4p[1]) printf("TEAM2 WINS\n");
		else printf("TIE!!\n");
	}
	
	char buffer[256];
	int i,n;
	//draw dir arrows
	if(dir == 'y' && chance[1] == 'y')
	{
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_LINE_STRIP);
		glVertex3f(dir_x,dir_y,-5.0f);
		glVertex3f(X[0],Y[0],-5.0f);
		glEnd();
	}
	//condition for collision
	check_collision(Vx,Vy,r_str,r_cn);
	//striker
	if(isInHole[0] == 'n')  check_str_wall(Vx,Vy);
	//condition for striker going into the holes
	if((distance(X[0],Y[0],1.69f,1.69f)<=0.11f||distance(X[0],Y[0],1.69f,-1.69f)<=0.11f||distance(X[0],Y[0],-1.69f,-1.69f)<=0.11f||
	distance(X[0],Y[0],-1.69f,1.69f)<=0.11f))
	{
		isInHole[0]='y';
		X[0] = 2.0f;
		Y[0] = 2.0f;
		Vx[0] = 0.0f;
		Vy[0] = 0.0f;
	}
	if(isInHole[0]=='n') //draw striker
	{
		glColor3f(0.8f,0.5f,0.2f);
		drawDisc(X[0],Y[0],r_str,1000);
		glColor3f(0.8f,0.2f,0.2f);
		drawDisc(X[0],Y[0],r_str-0.04f,1000);
		glColor3f(0.8f,0.5f,0.2f);
		drawDisc(X[0],Y[0],r_str-0.05f,1000);
		glColor3f(0.8f,0.2f,0.2f);
		drawDisc(X[0],Y[0],0.01f,1000);
	}
	//coins
	for(i=1;i<6;i++)
	{
		glColor3f(0.0f,0.0f,1.0f);
		if(isInHole[i] == 'n') check_cn_wall(Vx,Vy,i);//for striking with wall
		//condition for coin1 going into holes
		if((distance(X[i],Y[i],1.69f,1.69f)<=0.11f||distance(X[i],Y[i],1.69f,-1.69f)<=0.11f||distance(X[i],Y[i],-1.69f,-1.69f)<=0.11f||
		distance(X[i],Y[i],-1.69f,1.69f)<=0.11f))
		{	
			isInHole[i]='y';
			X[i] = 2.0f;
			Y[i] = 2.0f;
			Vx[i] = 0.0f;
			Vy[i] = 0.0f;
		}
		if(isInHole[i] == 'n')
		{
			if(i==1 || i==2)//black coins			
			{
				glColor3f(0.19f,0.19f,0.19f);
				drawDisc(X[i],Y[i],r_cn,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],r_cn-0.03f,1000);
				glColor3f(0.19f,0.19f,0.19f);
				drawDisc(X[i],Y[i],r_cn-0.04f,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],0.01f,1000);
			}
			if(i==3 || i==4)//white coins
			{
				glColor3f(0.76f,0.76f,0.76f);
				drawDisc(X[i],Y[i],r_cn,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],r_cn-0.03f,1000);
				glColor3f(0.76f,0.76f,0.76f);
				drawDisc(X[i],Y[i],r_cn-0.04f,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],0.01f,1000);
			}
			if(i==5)
			{
				glColor3f(0.8f,0.0f,0.0f);
				drawDisc(X[i],Y[i],r_cn,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],r_cn-0.03f,1000);
				glColor3f(0.8f,0.0f,0.0f);
				drawDisc(X[i],Y[i],r_cn-0.04f,1000);
				glColor3f(0.8f,0.2f,0.2f);
				drawDisc(X[i],Y[i],0.01f,1000);
			}
		}
	}
	//variable alpha exists so as to make sure that board is made once and then it waits for data
	if(chance[1]=='n')
	{
		if(alpha!=0 && isStrikerHitByOther=='n')
		{
			bzero(buffer,256);
			n = read(sockfd,buffer,255);
    			if (n < 0) 
        	 	error("ERROR reading from socket");//data reading
        	 	//perform decode
        	 	decode_copy(buffer);
			dir = 'n';
		}
		alpha=1;
	}	
	update_chance(Vx,Vy,chance);
}
//Draws the 3D scene
void drawScene() {
	int i;
	//Clear information from last draw
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f,-2.0f,-5.0f);
	glVertex3f(-2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,-2.0f,-5.0f);
	glEnd();//outer black quad
	
	glColor3f(0.99f, 0.84f, 0.61f);
	glBegin(GL_QUADS);
	glVertex3f(-1.8f,-1.8f,-5.0f);
	glVertex3f(-1.8f,1.8f,-5.0f);
	glVertex3f(1.8f,1.8f,-5.0f);
	glVertex3f(1.8f,-1.8f,-5.0f);
	glEnd();//board 
	
	glColor3f(0.0f,0.0f,0.0f);
	drawDisc(0.0f,0.0f,0.42f,1000);
	glColor3f(0.99f, 0.84f, 0.61f);
	drawDisc(0.0f,0.0f,0.40f,1000);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawDisc(0.0f,0.0f,0.38f,1000);
	glColor3f(0.99f, 0.84f, 0.61f);
	drawDisc(0.0f,0.0f,0.36f,1000);//central circle
	
	glColor3f(0.0f,0.0f,0.0f);
	drawDisc(0.0f,0.0f,0.08f,1000);
	glColor3f(1.0f,0.0f,0.0f);
	drawDisc(0.0f,0.0f,0.06f,1000);//central disc
	
	
	
	drawCircle(0.0f,0.0f,0.08f);
	drawTri();//for stars
	
	for(i=0;i<4;i++){
	//symmetric codes
	glColor3f(0.52f, 0.37f, 0.26f);
	drawDisc(1.69f, 1.69f, 0.11f,1000);//holes
	
	//drawArc(0.6f,0.6f,0.2121f);
	glColor3f(0.0f, 0.0f, 0.0f);
	//drawArc(0.6f,0.6f,0.2121f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.45f,0.45f,-5.0f);//45 degree line
	glVertex3f(1.4f,1.4f,-5.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(1.4f,1.4f,-5.0f);//arrows
	glVertex3f(1.36f,1.4f,-5.0f);
	glVertex3f(1.4f,1.4f,-5.0f);//arrows
	glVertex3f(1.4f,1.36f,-5.0f);
	glEnd();
	drawArc(0.6f,0.6f,0.2121f);
		
	glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS);//base line
	glVertex3f(1.1f, 1.2f, -5.0f);
	glVertex3f(1.1f, 1.21f, -5.0f);
	glVertex3f(-1.1f, 1.21f, -5.0f);
	glVertex3f(-1.1f, 1.2f, -5.0f);
	
	glVertex3f(1.1f, 1.35f, -5.0f);
	glVertex3f(1.1f, 1.33f, -5.0f);
	glVertex3f(-1.1f, 1.33f, -5.0f);
	glVertex3f(-1.1f, 1.35f, -5.0f);
	glEnd();
	
	glColor3f(1.0f, 0.0f, 0.0f);//base line circles
	drawDisc(1.1f, 1.275f, 0.075f,1000);
	drawDisc(-1.1f, 1.275f, 0.075f,1000);
	glColor3f(0.0f,0.0f,0.0f);
	drawCircle(1.1f, 1.275f, 0.075f);
	drawCircle(-1.1f, 1.275f, 0.075f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);
	}
	reDraw();
	glutSwapBuffers(); //Send the 3D scene to the screen
}

int main(int argc, char** argv) {
	
	//create client here
	client(argc,argv);
	
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(700, 0);//sets coordinate of left most upper corner
	glutInitWindowSize(600, 600); //Set the window size
	
	//Create the window
	glutCreateWindow("client1");
	initRendering(); //Initialize rendering
	
	//Set handler functions for drawing, keypresses, and window resizes
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMouseFunc(pressedMotion);
	glutPassiveMotionFunc(move);

	
	
	
	glutTimerFunc(25, update, 0);
	glutMainLoop();//Start the main loop.  glutMainLoop doesn't return.
	return 0; 
}









