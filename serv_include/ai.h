void copy_vel(float data[],int i,float x, float y, int j)
{
	float ratio,vx,vy,cos_theta,sin_theta,d;
	d = sqrt((y-Y[i])*(y-Y[i]) + (x-X[i])*(x-X[i]));
	cos_theta = (x-X[i])/d;
	sin_theta = (y-Y[i])/d;
	vx = 2.5*cos_theta;
	vy = 2.5*sin_theta;
	if(j==1){vx = -vx; vy = -vy;}
	data[1]=vx;
	data[2]=vy;
	
}

void copy_vel_plus(float data[],float x1,float y1,float x2,float y2)
{
	float ratio,vx,vy,cos_theta,sin_theta,d;
	d = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
	cos_theta = (x2-x1)/d;
	sin_theta = (y2-y1)/d;
	vx = 3*cos_theta;
	vy = 3*sin_theta;
	data[1] = vx;
	data[2] = vy;

}

int dis_frm_line(float x1, float y1, float x2, float y2,int i, int a[], float cord[], float dist[], int g)
{
//this function calculates dis from all points available except ith
//returns 1 if all dis is more than r_str
//return 0 if any one of dis is less than r_str
//also stores dis from line in a[0] if its min than before(in a[0]) and stores i in a[1] and x1 and y1 in cord[0] and cord[1] respectively
	
	char c='t';
	int j;
	float a1,b1,c1,d,d_temp=2.0f,r;
	if(g==1) r = r_str+r_cn;
	else r = 2*r_cn;
	for(j=1;j<6;j++)
	{
		if(j==i || X[j]==2.0f) continue;
		a1 = y2-y1;
		b1 = x1-x2;
		c1 = y1*x2 - y2*x1;
		d = (a1*X[j] + b1*Y[j] + c1)/sqrt(a1*a1 + b1*b1);
		d = fabs(d);
		if(d < r)
		{
			c='f';
			if(g==1){if(d < d_temp) d_temp = d;}
		}
	}
	if(g==1){
	if(d_temp > dist[0] && c=='f')
	{
		dist[0] = d_temp;
		a[1] = i;
		cord[0] = x1;
		cord[1] = y1;
	}}
	if(c=='t') return 1;
	else return 0;
	
}

void pt_impact(float x,float y, int i,float points[])
{
	float tan_theta,cos_theta,sin_theta,r;
	if((X[i]-x) == 0.0f)
	{
		sin_theta = 1;
		cos_theta = 0;
	}
	else
	{
		tan_theta = (Y[i]-y)/(X[i]-x);
		sin_theta = fabs(sin(atan(tan_theta)));
		cos_theta = fabs(cos(atan(tan_theta)));
		if(tan_theta < 0.0f)
			cos_theta = -cos_theta;
	}
	if(Y[i] <= 1.275f) r = r_str + r_cn;
	if(Y[i] > 1.275f) r = -(r_str + r_cn);
	points[0] = X[i] + r*cos_theta;
	points[1] = Y[i] + r*sin_theta;

}

int compu_intel_plus(float data[])
{
	int i,j,k,l,dummy[1];
	float dummy1[1],dummy2[1],points[2],x,y;
	for(l=0;l<3;l++)
	{
		if(l==0) i=5;
		if(l==1) i=1;
		if(l==2) i=2;
		if(X[i] == 2.0f) continue;
		if(Y[i] <= 1.275f)//solve for bottom two pockets
		{
			//solve for bottom left pockets			
			k = dis_frm_line(X[i],Y[i],-1.69f,-1.69f,i,dummy,dummy1,dummy2,0);
			if(k==1)
			{
				pt_impact(-1.69f,-1.69f,i,points);
				for(j=0;j<4;j++)
				{
					if(j==0)
					{
						if(X[i] <= 0.0f) x=-1.1f; else x=0.0f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==1)
					{
						if(X[i] <= 0.0f) x=-0.74f; else x=0.27f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==2)
					{
						if(X[i] <= 0.0f) x=-0.53f; else x=0.55f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==3)
					{
						if(X[i] <= 0.0f) x=-0.22f; else x=0.77f;
						x=0.55f,y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
				}
			}
			//solve for bottom right pocket
			k = dis_frm_line(X[i],Y[i],1.69f,-1.69f,i,dummy,dummy1,dummy2,0);
			if(k==1)
			{
				pt_impact(1.69f,-1.69f,i,points);
				for(j=0;j<4;j++)
				{
					if(j==0)
					{
						if(X[i] >= 0.0f) x=1.1f; else x=0.0f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==1)
					{
						if(X[i] >= 0.0f) x=0.73f; else x=-0.27f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==2)
					{
						if(X[i] >= 0.0f) x=0.55f; else x=-0.55f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==3)
					{
						if(X[i] >= 0.0f) x=0.25f; else x=-0.77f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
				}
			}
		}
		if(Y[i] >= 1.275f)//solve for upper two pockets
		{
			//solve for upper left pockets			
			k = dis_frm_line(X[i],Y[i],-1.69f,1.69f,i,dummy,dummy1,dummy2,0);
			if(k==1)
			{
				pt_impact(-1.69f,1.69f,i,points);
				for(j=0;j<3;j++)
				{
					if(j==0)
					{
						if(X[i] <= 0.0f) x=-1.1f; else x=0.0f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==1)
					{
						if(X[i] <= 0.0f) x=-0.74f; else x=0.27f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==2)
					{
						if(X[i] <= 0.0f) x=-0.53f; else x=0.55f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
				}
			}
			//solve for upper right pocket
			k = dis_frm_line(X[i],Y[i],1.69f,1.69f,i,dummy,dummy1,dummy2,0);
			if(k==1)
			{
				pt_impact(1.69f,1.69f,i,points);
				for(j=0;j<3;j++)
				{
					if(j==0)
					{
						if(X[i] >= 0.0f) x=1.1f; else x=0.0f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==1)
					{
						if(X[i] >= 0.0f) x=0.73f; else x=-0.27f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
					if(j==2)
					{
						if(X[i] >= 0.0f) x=0.55f; else x=-0.55f;
						y=1.275f;
						k = dis_frm_line(points[0],points[1],x,y,i,dummy,dummy1,dummy2,0);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel_plus(data,x,y,points[0],points[1]);
							return 1;	
						}
					}
				}
			}
		}
		
	}
	return 0;

}

int compu_intel_rebound(float data[])
{
	int i,j,k,l,dummy[1];
	float x,x_temp,y_temp,dummy1[1],dummy2[1];
	for(l=0;l<3;l++)
	{
		if(l==0) i=5;
		if(l==1) i=1;
		if(l==2) i=2;
		if(X[i]==2.0f) continue;
		//first solve for upper left hole
		//take reflection abt y = -1.7
		x = (1.275f+(1.7f+1.7f+1.69f))*((X[i]+1.69f)/((-Y[i]-3.4f)+5.09f)) - 1.69f;//5.09f = 1.7 + 1.7 + 1.69;
		if(x >= -1.1f && x <= 1.1f)
		{	//using x_temp put a check on gacha... 
			x_temp = (-1.7f+(1.7f+1.7f+1.69f))*((X[i]+1.69f)/((-Y[i]-3.4f)+5.09f)) - 1.69f; 
			k = dis_frm_line(x,1.275,x_temp,-1.7,i,dummy,dummy1,dummy2,0);
			if(x_temp <= -1.58f) k=0;//putting a check on striker going into the hole
			if(k==1)
			{
				k = dis_frm_line(x_temp,-1.7,X[i],Y[i],i,dummy,dummy1,dummy2,0);
				if(k==1)
				{
					if(present_b4(x,1.275f)==0) continue;
					data[0]=x;
					copy_vel_plus(data,x,1.275,x_temp,-1.7);
					return 1;
				}
			}
		}
		//secondly solve for upper right hole
		//take reflection abt y = -1.7
		x = (1.275f+(1.7f+1.7f+1.69f))*((X[i]-1.69f)/((-Y[i]-3.4f)+5.09f)) + 1.69f;//5.09f = 1.7 + 1.7 + 1.69;
		if(x >= -1.1f && x <= 1.1f)
		{	//using x_temp put a check on gacha... 
			x_temp = (-1.7f+(1.7f+1.7f+1.69f))*((X[i]-1.69f)/((-Y[i]-3.4f)+5.09f)) + 1.69f; 
			k = dis_frm_line(x,1.275,x_temp,-1.7,i,dummy,dummy1,dummy2,0);
			if(x_temp >= 1.58f) k=0;//putting a check on striker going into the hole
			if(k==1)
			{
				k = dis_frm_line(x_temp,-1.7,X[i],Y[i],i,dummy,dummy1,dummy2,0);
				if(k==1)
				{
					if(present_b4(x,1.275f)==0) continue;
					data[0]=x;
					copy_vel_plus(data,x,1.275,x_temp,-1.7);
					return 1;
				}
			}
		}
		//thirdly solve for bottom left hole
		//take reflection abt x = 1.7
		x = (1.275f+1.69f)*(((-X[i]+3.4f)-5.09f)/(Y[i]+1.69f)) + 5.09f;//5.09f = 1.7 + 1.7 - (-1.69);
		if(x >= -1.1f && x <= 1.1f)
		{	//using y_temp put a check on gacha... 
			y_temp = (1.7f-(1.7f+1.7f+1.69f))*((Y[i]+1.69f)/((-X[i]+3.4f)-5.09f)) - 1.69f;
			k = dis_frm_line(x,1.275,1.7,y_temp,i,dummy,dummy1,dummy2,0);
			if(y_temp <= -1.58f) k=0;//putting a check on striker going into the hole
			if(k==1)
			{
				k = dis_frm_line(1.7,y_temp,X[i],Y[i],i,dummy,dummy1,dummy2,0);
				if(k==1)
				{
					if(present_b4(x,1.275f)==0) continue;
					data[0]=x;
					copy_vel_plus(data,x,1.275f,1.7f,y_temp);
					return 1;
				}
			}
		}
		//fourthly solve for bottom right hole
		//take reflection abt x = -1.7
		x = (1.275f+1.69f)*(((-X[i]-3.4f)+5.09f)/(Y[i]+1.69f)) - 5.09f;//5.09f = 1.7 + 1.7 - (-1.69);
		if(x >= -1.1f && x <= 1.1f)
		{	//using y_temp put a check on gacha... 
			y_temp = (-1.7f+(1.7f+1.7f+1.69f))*((Y[i]+1.69f)/((-X[i]-3.4f)+5.09f)) - 1.69f;
			k = dis_frm_line(x,1.275,-1.7,y_temp,i,dummy,dummy1,dummy2,0);
			if(y_temp >= 1.58f) k=0;//putting a check on striker going into the hole
			if(k==1)
			{
				k = dis_frm_line(-1.7,y_temp,X[i],Y[i],i,dummy,dummy1,dummy2,0);
				if(k==1)
				{
					if(present_b4(x,1.275f)==0) continue;
					data[0]=x;
					copy_vel_plus(data,x,1.275f,-1.7f,y_temp);
					return 1;
				}
			}
		}
	}
	return 0;
}

void compu_intel(float data[])
{
	int i,j,k,l,m,mm,a[2],soln=0;
	float x,cord[2],dist[2]={-2.0f,-2.0f};
	for(l=5;l>2;l--)//priority = queen >> black coin
	{
		if(l==5) i=5;
		if(l==4) i=2;
		if(l==3) i=1;
		if(X[i] == 2.0f) continue;
		if(Y[i] <= 1.275f)//solve for bottom two pockets
		{
			for(j=0;j<2;j++)
			{
				if(j==0)//solve for bottom left pocket
				{
					x = (1.275f+1.69f)*((X[i]+1.69f)/(Y[i]+1.69f)) - 1.69f;
					if(x >= -1.1f && x <= 1.1f)
					{
						//check for coins in b/w
						soln=1;
						k = dis_frm_line(-1.69f,-1.69f,X[i],Y[i],i,a,cord,dist,1);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel(data,i,-1.69f,-1.69f,0);//copies appropriate velocity
							return;
						}
					}
				}
				if(j==1)//solve for bottom right pocket
				{
					x = (1.275f+1.69f)*((X[i]-1.69f)/(Y[i]+1.69f)) + 1.69f;
					if(x >= -1.1f && x <= 1.1f)
					{
						//check for coins in b/w
						soln=1;
						k = dis_frm_line(1.69f,-1.69f,X[i],Y[i],i,a,cord,dist,1);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel(data,i,1.69f,-1.69f,0);//copies appropriate velocity
							return;
						}
					}
				}
			}
		}
		if(Y[i] > 1.275f)//solve for upper two pockets
		{
			for(j=0;j<2;j++)
			{
				if(j==0)//solve for upper left pocket
				{
					x = (1.275f-1.69f)*((X[i]+1.69f)/(Y[i]-1.69f)) - 1.69f;
					if(x >= -1.1f && x <= 1.1f)
					{
						//check for coins in b/w
						soln=1;
						k = dis_frm_line(-1.69f,1.69f,X[i],Y[i],i,a,cord,dist,1);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel(data,i,-1.69f,1.69f,0);//copies appropriate velocity
							return;
						}
					}
				}
				if(j==1)//solve for upper right pocket
				{
					x = (1.275f-1.69f)*((X[i]-1.69f)/(Y[i]-1.69f)) + 1.69f;
					if(x >= -1.1f && x <= 1.1f)
					{
						//check for coins in b/w
						soln=1;
						k = dis_frm_line(1.69f,1.69f,X[i],Y[i],i,a,cord,dist,1);
						if(k==1)
						{
							if(present_b4(x,1.275f)==0) continue;
							data[0] = x;
							copy_vel(data,i,1.69f,1.69f,0);//copies appropriate velocity
							return;
						}
					}
				}
			}
		}
	}
	mm = compu_intel_rebound(data);
	if(mm==0){
	m = compu_intel_plus(data);
	if(m==0){
	if(soln==1)
	{
		x = (1.275f - cord[1])*((X[a[1]]-cord[0])/(Y[a[1]]-cord[1])) + cord[0];
		if(x >= -1.1f && x <= 1.1f && present_b4(x,1.275f)==1)
		{
			data[0] = x;
			copy_vel(data,a[1],cord[0],cord[1],0);//copies appropriate velocities at data[1] and data[2]
			return;
		}
	}
	for(l=5;l>2;l++)
	{
		if(l==5) i=5; if(l==4) i=2; if(l==3) i=1;
		if(X[i]==2.0f) continue;
		if(present_b4(0.5,1.275)==1)
		{data[0]=0.5f;copy_vel(data,i,0.5f,1.275f,1);}
		else 
		{data[0]=-0.5f;copy_vel(data,i,-0.5f,1.275f,1);}
		
		return;
	}
	data[0]=0.0f;
	data[1]=0.1f;
	data[2]=-0.1f;}}
	return;
}

void stage_update(int stage,float data[])
{
	static int stage_count=0;
	if(stage==1)//expert stage do no changes
		return;
	else if(stage==2)//medium stage
	{
		if(stage_count % 2 != 0)
		{
			stage_count++;
			data[1]=0.6*data[1];
			return;
		}
		else
		{
			stage_count++;
			return;
		}
	}
	else if(stage==3)//low(most easy) stage_count
	{
		if(stage_count % 3 != 0)
		{
			stage_count++;
			data[1]=0.6*data[1];
			return;
		}
		else
		{
			stage_count++;
			return;
		}
	}
	
}

void compu_work()
{
	static int delay=0,del=0,once=0;
	delay++;
	float x_of_str=0.7f;
	if(once == 0) { compu_intel(data);stage_update(stage,data);once=1; }
	if(del == 0) {delay = 0; del =1;}
	while(1)
	{
		if(present_b4(x_of_str,1.275f) == 1) break;
		x_of_str = x_of_str-0.2f;
	}
	X[0]=x_of_str;Y[0]=1.275f;
	if (delay>25)
	{
		x_of_str = -0.5f;
		while(1)
		{
			if(present_b4(x_of_str,1.275f) == 1) break;
			x_of_str = x_of_str-0.2f;
		}
		X[0]=x_of_str;Y[0]=1.275f;
		if (delay>50)
		{
			//call the function to find coordinates here
			X[0] = data[0]; Y[0]=1.275f;
			if (delay>75)
			{
				//call the function to calculate velocity here
				Vx[0] = data[1];
				Vy[0] = data[2];
				dir = 'n';
				isStrikerHitByOther='y';
				isStrikerHitByMe='n';
				delay = 0;
				del = 0;
				once=0;
			}
		}
	}
	
}

