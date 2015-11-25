
void epsx(int i)
{
	float eps;
	if(Vx[i] >= 0.0f)
	{
		eps = X[i] - 1.7;
		X[i] = 1.7 -eps;
		Vx[i] = -Vx[i];
		return;
	}
	if(Vx[i] <= 0.0f)
	{
		eps = fabs(X[i] + 1.7);
		X[i] = -1.7 + eps;
		Vx[i] = -Vx[i];
		return;
	}
}
void epsy(int i)
{
	float eps;
	if(Vy[i] >= 0.0f)
	{
		eps = Y[i] - 1.7;
		Y[i] = 1.7 -eps;
		Vy[i] = -Vy[i];
		return;
	}
	if(Vy[i] <= 0.0f)
	{
		eps = fabs(Y[i] + 1.7);
		Y[i] = -1.7 + eps;
		Vy[i] = -Vy[i];
		return;
	}
}
void check_str_wall(float Vx[], float Vy[])
{
	
	if(X[0] >= 1.7f || X[0] <= -1.7f)//1.66f should be 1.69f
	{
		epsx(0);
	}
	if(Y[0] >= 1.7f || Y[0] <= -1.7f)
	{
		epsy(0);
	}
}
void check_cn_wall(float Vx[], float Vy[], int i)
{
	
	if(X[i] >= 1.725f || X[i] <= -1.725f)//1.69 should be actually 1.725
	{
		epsx(i);
	}
	if(Y[i] >= 1.725f || Y[i] <= -1.725f)
	{
		epsy(i);
	}
	return;
}
void exchange_vel(float Vx[], float Vy[], int i, int j, float r1, float r2)
{
	float k;
	//if(r1>r2) k = (r1*r1)/(r2*r2);
	k = 1;
	float dx = X[j]-X[i], dy = Y[j]-Y[i];
	// where x1,y1 are center of ball1, and x2,y2 are center of ball2
	float dist = sqrt(dx*dx+dy*dy);
	// Unit vector in the direction of the collision
	float ax=dx/dist, ay=dy/dist;
	// Projection of the velocities in these axes
	float va1=(Vx[i]*ax+Vy[i]*ay), vb1=(-Vx[i]*ay+Vy[i]*ax);
	float va2=(Vx[j]*ax+Vy[j]*ay), vb2=(-Vx[j]*ay+Vy[j]*ax);
	// New velocities in these axes (after collision): ed<=1,  for elastic collision ed=1
	int ed = 1;
	float vaP1=va1 + (1+ed)*(va2-va1)/(1.0f+k);
	float vaP2=va2 + (1+ed)*(va1-va2)/(1.0f+(1/k));
	// Undo the projections
	Vx[i]=vaP1*ax-vb1*ay;  Vy[i]=vaP1*ay+vb1*ax;// new vx,vy for ball 1 after collision
	Vx[j]=vaP2*ax-vb2*ay;  Vy[j]=vaP2*ay+vb2*ax;// new vx,vy for ball 2 after collision
}
void check_collision(float Vx[], float Vy[], float r1, float r2)
{
	int i,j;
	float st,dx,dy,d,vp1,vp2;
	for(i=0;i<6;i++)
	{
		if(X[i] == 2.0f) continue;
		if(i!=0) r1 = r2; 
		for(j=i+1;j<6;j++)
		{
			if(distance(X[i],Y[i],X[j],Y[j]) <= r1+r2)//collision happens
			{
				//making appropriate changes to x and y coordinates
				//dx=x2-x1, dy=y2-y1; d=sqrt(dx*dx+dy*dy);
				dx=X[j]-X[i];
				dy=Y[j]-Y[i];
				d = sqrt(dx*dx + dy*dy);
				vp1= Vx[i]*dx/d + Vy[i]*dy/d;
				vp2= Vx[j]*dx/d + Vy[j]*dy/d;
				st =(r1+r2-d)/(vp1-vp2);
				X[i] = X[i] - Vx[i]*st;
 				Y[i] = Y[i] - Vy[i]*st;
 				X[j] = X[j] - Vx[j]*st;
 				Y[j] = Y[j] - Vy[j]*st;
				
				//function to exchange velocities appropriately
				exchange_vel(Vx,Vy,i,j,r1,r2);
				
				//restore back coordiantes
				X[i] = X[i] + Vx[i]*st;
  				Y[i] = Y[i] + Vy[i]*st;
  				X[j] = X[j] + Vx[j]*st;
  				Y[j] = Y[j] + Vy[j]*st;
				
			}
		}
	}
}
