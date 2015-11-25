void drawDisc(float cx, float cy, float r, int num_segments) 
{
int i=0;float angle;
glBegin(GL_LINE_LOOP);
    for(i =0;i<num_segments;i++)
    {    
    angle = i*2*3.14159/num_segments;
    glVertex3f(cx,cy,-5.0f);
    glVertex3f(cx+r*cosf(angle),cy+r*sinf(angle),-5.0f);
    }
glEnd();
}
void drawCircle(float cx, float cy, float r)
{
	float i,theta,fi;
	fi = 2.0f*3.14f/100.0f;
 	glBegin(GL_LINE_STRIP);
    	for(i=0;i<100;i++){
    		theta = i*2.0f*3.14f/100.0f;
		glVertex3f(cx + r*cos(theta),cy + r*sin(theta),-5.0f);
		glVertex3f(cx + r*cos(theta + fi),cy + r*sin(theta+fi),-5.0f);
    	}
    	glEnd();
}
void drawTri()
{
	int i=0;
	for(i=0;i<8;i++)
	{
		glBegin(GL_TRIANGLES);
		glColor3f(0.62f, 0.37f, 0.62f);
		glVertex3f(0.08f*cos(22.5*3.14/180),0.08f*sin(22.5*3.14/180),-5.0f);
		glColor3f(0.69f, 0.19f, 0.38f);
		glVertex3f(0.08f*cos(67.5*3.14/180),0.08f*sin(67.5*3.14/180),-5.0f);
		glColor3f(0.0f, 0.38f, 0.0f);
		glVertex3f(0.42f*0.707f,0.42f*0.707f,-5.0f);
		glEnd();
		glRotatef(45.0f,0.0f,0.0f,1.0f);
	}
}
void drawArc(float cx, float cy, float r)
{
	float i,j,theta,fi;
	for(j=0;j<2.1;j++){fi = 2.0f*3.14f/100.0f;
 	glColor3f(0.0f,0.0f,0.0f);
 	glBegin(GL_LINE_STRIP);
    	for(i=21;i<105;i++){
    		theta = i*2.0f*3.14f/100.0f;
    		//glVertex3f(cx,cx,-5.0f);
		glVertex3f(cx + r*cos(theta),cy + r*sin(theta),-5.0f);
		glVertex3f(cx + r*cos(theta + fi),cy + r*sin(theta+fi),-5.0f);
    	}
    	glEnd();}
    	//glColor3f(0.99f, 0.84f, 0.61f);
    	//drawDisc(cx,cy,r-0.02,1000);
}

