#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#define r_str 0.1f
#define r_cn 0.075f
#define dt 0.03f

float X[6]={0.0f,0.16f,0.0f,-0.16f,0.0f,0.0f};
float Y[6]={-1.275f,0.0f,0.16f,0.0f,-0.16f,0.0f};
float Vx[6],Vy[6],fr_coeff = 0.62f;

#include "./serv_include/networking.h"
#include "./serv_include/figures.h"
#include "./serv_include/update_vel_pos.h"
#include "./serv_include/collision.h"
#include "./serv_include/chance.h"
#include "./serv_include/ai.h"
#include "./serv_include/gui.h"

//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y)//The key that was pressed //The current mouse coordinates
{    
	switch (key) {
		case 27: //Escape key
			exit(0); //Exit the program
		case 100://'d' key
			fr_coeff = fr_coeff-0.05f;
			break;
		case 105://'i' key
			fr_coeff = fr_coeff+0.05f;
			break;
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

//this function will update variable stage and gui as well
int gui=1;char** prt;
void handleGUI(int button,int state,float x,float y)
{
	static int cont=0;
	if(((x+1.5f)*(x+1.5f)+(y-0.84f)*(y-0.84f)-0.07f*0.07f) < 0.0f)
	{ gui_chek=1;game_type=1;}
	if(((x+1.5f)*(x+1.5f)+(y-0.64f)*(y-0.64f)-0.07f*0.07f) < 0.0f)
	{ gui_chek=2;game_type=2;}
	if(((x+1.5f)*(x+1.5f)+(y-0.44f)*(y-0.44f)-0.07f*0.07f) < 0.0f)
	{ gui_chek=3;game_type=3;} 
	if(((x+1.5f)*(x+1.5f)+(y+0.16f)*(y+0.16f)-0.07f*0.07f) < 0.0f && game_type==1)
	{ gui_chek=4;stage=3;}
	if(((x+1.5f)*(x+1.5f)+(y+0.36f)*(y+0.36f)-0.07f*0.07f) < 0.0f && game_type==1)
	{ gui_chek=5;stage=2;}
	if(((x+1.5f)*(x+1.5f)+(y+0.56f)*(y+0.56f)-0.07f*0.07f) < 0.0f && game_type==1)
	{ gui_chek=6;stage=1;}
	if(game_type!=0 && !(game_type==1 && gui_chek < 4))
	{
		if(x<0.3f && x>-0.6f && y<-1.2f && y>-1.5f)
		gui=0;
	}
	return;
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
	if(gui==1)
	{
		handleGUI(button,state,x,y);
	}
	else{
	if(i_check == 0)
	{
		x_prev=0.0f;
		y_prev = -1.275f;
		i_check++;	
	}
	
	//against computer
	if(chance_ai[0]=='y' && game_type==1)
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
			D_fac = distance(x,y,x_prev,y_prev)*4.0f;
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
			if(button==0)
				isStrikerHitByMe='n';
			else
				isStrikerHitByMe='y';
		
		}
	}
	
	//2 multiplayer
	if(chance_2p[0]=='y' && game_type==2)
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
			if(button==0)
				isStrikerHitByMe='n';
			else
				isStrikerHitByMe='y';
		
		}
		if(state==0 || (Vx[0]==0.0f && Vy[0]==0.0f))
		{
			bzero(buffer,256);
			copy(Vx[0],Vy[0],X[0],Y[0],buffer,isStrikerHitByMe);
			n = write(newsockfd,buffer,strlen(buffer));
    			if (n < 0) 
        			error("ERROR writing to socket");
        	}
        }
        	
	//4 multiplayer
	if(chance_4p[0]=='y' && game_type==3)
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
			D_fac = distance(x,y,x_prev,y_prev)*4.0f;
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
			if(button==0)
				isStrikerHitByMe='n';
			else
				isStrikerHitByMe='y';
		
		}
		
		//put under a if(playing 4 multiplayer)
		if(state==0 || (Vx[0]==0.0f && Vy[0]==0.0f))
		{
			bzero(buffer,256);
			copy(Vx[0],Vy[0],X[0],Y[0],buffer,isStrikerHitByMe);
			n = write(newsockfd1,buffer,strlen(buffer));
    			if (n < 0) 
        			error("ERROR writing to socket1");
        		n = write(newsockfd2,buffer,strlen(buffer));
    			if (n < 0) 
        			error("ERROR writing to socket2");
        		n = write(newsockfd3,buffer,strlen(buffer));
    			if (n < 0) 
        			error("ERROR writing to socket2");
        	}
        }}
        
}

void reDraw()
{
	//draw GUI here and take input which game to play,and then accordingly create server
	static int ser_once=0;
	//yahan pe appropriate setting krna hoga ke server call sirf ek bar ho!!
	//game_type=2;
	if(gui==1)
	{
		drawGUI();//when u get data for game_type and stage then change gui to 0
	}
	else if(gui > 1)
		displayResult();
	else if(gui==0){
	if(ser_once==0)
	{
		if(game_type==2)
		{
			server_2p(2,prt[1]);
			ser_once=1;
		}
		if(game_type==3) 
		{
			server_4p(2,prt[1]);
			ser_once=1;
		}
	}
	
	//for score
	if(game_type==1)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_ai[0] > score_ai[1]) gui=2;//("PLAYER1 WINS\n");
			else if(score_ai[0] < score_ai[1]) gui=3;//printf("COMPUTER WINS\n");
			else gui=7;//printf("TIE!!\n");
		}
	}
	if(game_type==2)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_2p[0] > score_2p[1]) gui=2;//printf("PLAYER1 WINS\n");
			else if(score_2p[0] < score_2p[1]) gui=4;//printf("PLAYER2 WINS\n");
			else gui=7;//printf("TIE!!\n");
		}
	}
	if(game_type==3)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_4p[0] > score_4p[1]) gui=5;//printf("TEAM1 WINS\n");
			else if(score_4p[0] < score_4p[1]) gui=6;//printf("TEAM2 WINS\n");
			else gui=7;//printf("TIE!!\n");
		}
	}
	
	char buffer[256];
	int i,n;
	//draw dir arrows
	if(dir == 'y' && chance_4p[0] == 'y')
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
			if(i==5)//queen red
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
	
	if(game_type==1)
	{
		//put under if(playing against compu)
		if(chance_ai[0]=='n')
		{
			if(isStrikerHitByOther=='n')
			{
				compu_work();
			}
		}
		update_chance_ai(Vx,Vy,chance_ai);
		//if(playing against compu)
	}
	
	if(game_type==2)
	{
		//put under if(playing 2 multiplayer)
		if(chance_2p[0]=='n')
		{
			if(alpha!=0 && isStrikerHitByOther=='n')
			{
				bzero(buffer,256);
				n = read(newsockfd,buffer,255);
    				if (n < 0) 
         			error("ERROR reading from socket");//data reading
         			//perform decode
         			decode_copy_2p(buffer);
				dir = 'n';
			}
			alpha=1;
		}
		update_chance_2p(Vx,Vy,chance_2p);
		//if(playing 2 multiplayer)
	}
	
	if(game_type==3)
	{
	//put under if(playing 4 multiplayer)
	if(chance_4p[0]=='n')
	{
		if(alpha!=0 && isStrikerHitByOther=='n')
		{
			bzero(buffer,256);
			if(chance_4p[1]=='y')
			{
				n = read(newsockfd1,buffer,255);
    				if (n < 0) 
         			error("ERROR reading from socket");//data reading
         			//sending data to rest of clients
         			n = write(newsockfd2,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
        			n = write(newsockfd3,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
         		}
         		if(chance_4p[2]=='y')
			{
				n = read(newsockfd2,buffer,255);
    				if (n < 0) 
         			error("ERROR reading from socket");//data reading
         			//sending data to rest of clients
         			n = write(newsockfd1,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
        			n = write(newsockfd3,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
         		}
         		if(chance_4p[3]=='y')
			{
				n = read(newsockfd3,buffer,255);
    				if (n < 0) 
         			error("ERROR reading from socket");//data reading
         			//sending data to rest of clients
         			n = write(newsockfd1,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
        			n = write(newsockfd2,buffer,strlen(buffer));
    				if (n < 0) 
        			error("ERROR writing to socket");
         		}
         		//perform decode
         		decode_copy_4p(buffer);
			dir = 'n';
		}
		alpha=1;
	}
	update_chance_4p(Vx,Vy,chance_4p);
	//if(playing 4 multiplayer)
	}}
}


//Draws the 2D scene
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
	
	//create server
	//server(argc,argv);
	//create server above and not here
	prt = argv;
	
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(400, 75);//sets coordinate of left most upper corner
	glutInitWindowSize(600, 600); //Set the window size
	
	//Create the window
	glutCreateWindow("server");
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
























