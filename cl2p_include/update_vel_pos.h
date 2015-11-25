float distance(float x1, float y1, float x2, float y2)
{
	float d1 = (x1-x2)*(x1-x2);
	float d2 = (y1-y2)*(y1-y2);
	return (sqrt(d1+d2));
}
void update_vel_pos(float Vx[], float Vy[], float X[], float Y[])
{
	int i;
	float theta,fr_x,fr_y;
	for(i=0;i<6;i++)
	{
		theta = atan(fabs(Vy[i]/Vx[i]));
		fr_x = fabs(fr_coeff*cos(theta));
		fr_y = fabs(fr_coeff*sin(theta));
		if(Vx[i] > 0.0f)
		{
			Vx[i] = Vx[i]-fr_x*dt;
			if(Vx[i] < 0.0f)
				Vx[i]=0.0f;
		}
		else if(Vx[i] < 0.0f)
		{
			Vx[i] = Vx[i]+fr_x*dt;
			if(Vx[i] > 0.0f)
				Vx[i]=0.0f;
		}		
		if(Vy[i] > 0.0f)
		{
			Vy[i] = Vy[i]-fr_y*dt;
			if(Vy[i] < 0.0f)
				Vy[i]=0.0f;
		}
		else if (Vy[i] < 0.0f)
		{
			Vy[i] = Vy[i]+fr_y*dt;
			if(Vy[i] > 0.0f)
				Vy[i]=0.0f;
		}	
		
	}
	for(i=0;i<6;i++)
	{
		X[i] = X[i] + Vx[i]*dt;
		Y[i] = Y[i] + Vy[i]*dt;
	}
}

