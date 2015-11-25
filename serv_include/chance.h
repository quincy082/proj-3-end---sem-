int score_4p[2];//0-team1 1-team2 
int score_2p[2];//score_2p[0] is player1 score and score_2p[1] is player2 score
int score_ai[2];//score[0] is my score and score[1] is computer's score
int updateCount_me_ai(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1; }
	if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) { toReturn = 1;score_ai[0]=score_ai[0]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me = 'y';score_ai[0]=score_ai[0]+3; }
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int updateCount_me_2p(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1; }
	if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) {toReturn = 1;score_2p[0]=score_2p[0]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me = 'y';score_2p[0]=score_2p[0]+3;}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int updateCount_me_4p(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1;}
	if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[0]=score_4p[0]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me = 'y'; score_4p[0]=score_4p[0]+3;}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int updateCount_other_ai(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1; }
	if(((black_count - coinCount[0]) > 0) && X[0]!=2.0f) {toReturn = 1;score_ai[1]=score_ai[1]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_other = 'y';score_ai[1]=score_ai[1]+3;}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int updateCount_other_2p(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1; }
	if(((black_count - coinCount[0]) > 0) && X[0]!=2.0f) {toReturn = 1;score_2p[1]=score_2p[1]+2;}
	if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_other = 'y';score_2p[1]=score_2p[1]+3;}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int updateCount_other_4p(float X[],float Y[],int coinCount[])
{
	int black_count=0,white_count=0,red_count=0,toReturn=0;
	if(X[1]==2.0f)	black_count = black_count + 1;
	if(X[2]==2.0f)	black_count = black_count + 1;
	if(X[3]==2.0f)	white_count = white_count + 1;
	if(X[4]==2.0f)	white_count = white_count + 1;
	if(X[5]==2.0f)	{ red_count = red_count + 1;}
	if(chance_4p[1]=='y' || chance_4p[3]=='y')
	{	if(((black_count - coinCount[0]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[1]=score_4p[1]+2;}
		if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_other='y';score_4p[1]=score_4p[1]+3;}
	}
	else if(chance_4p[2]=='y')
	{	if(((white_count - coinCount[1]) > 0) && X[0]!=2.0f) {toReturn = 1;score_4p[0]=score_4p[0]+2;}
		if(((red_count - coinCount[2]) > 0) && X[0]!=2.0f) {toReturn = 1;isRed_me='y';score_4p[0]=score_4p[0]+3;}
	}
	coinCount[0] = black_count;
	coinCount[1] = white_count;
	coinCount[2] = red_count;
	return toReturn;
}

int position_replace(float X[], float Y[])
{
	int i,j1=0,j2=0,j3=0,j4=0,j5=0;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j1 = 1;
			break;
		}
	}
	if(j1 == 0) return 1;
	for(i=0;i<6;i++)
	{
		if(distance(0.41f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j2 = 1;
			break;
		}
	}
	if(j2 == 0) return 2;
	for(i=0;i<6;i++)
	{
		if(distance(-0.41f,0.0f,X[i],Y[i]) < 2*r_cn)
		{
			j3 = 1;
			break;
		}
	}
	if(j3 == 0) return 3;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,0.41f,X[i],Y[i]) < 2*r_cn)
		{
			j4 = 1;
			break;
		}
	}
	if(j4 == 0) return 4;
	for(i=0;i<6;i++)
	{
		if(distance(0.0f,-0.41f,X[i],Y[i]) < 2*r_cn)
		{
			j5 = 1;
			break;
		}
	}
	if(j5 == 0) return 5;
	return 6;
}

int present_b4(float x, float y)
{
	int i;
	for(i=1;i<6;i++)
	{
		if(distance(x,y,X[i],Y[i]) <= r_cn+r_str ) return 0;
	}
	return 1;
}

void update_chance_ai(float Vx[], float Vy[], char chance_ai[])
{
	int i,j,k,l;
	float x_r,y_r,x_of_str=0.0f;
	char cchek='x';
	if(isStrikerHitByMe=='y' && chance_ai[0]=='y')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			j = updateCount_me_ai(X,Y,coinCount);
			if(j == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed white coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(isRed_me == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_me = 'n';
						score_ai[0]=score_ai[0]-3;
					}
					else if(X[3] == 2.0f)
					{
						X[3] = x_r;
						Y[3] = y_r;
						isInHole[3] = 'n';
						coinCount[1] = coinCount[1]-1;
						score_ai[0]=score_ai[0]-2;
					}
					else if(X[4] == 2.0f)
					{
						X[4] = x_r;
						Y[4] = y_r;
						isInHole[4] = 'n';
						coinCount[1] = coinCount[1]-1;
						score_ai[0]=score_ai[0]-2;
					}
				}
				chance_ai[0]='n';
				chance_ai[1]='y';
				while(1)
				{
					if(present_b4(x_of_str,1.275f) == 1) break;
					x_of_str = x_of_str-0.2f;
				}
				X[0]=x_of_str;				
				Y[0]=1.275f;
				dir = 'n';
			}
			if(j == 1)
			{
				chance_ai[0]='y';
				chance_ai[1]='n';
				x_of_str=0.0f;				
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			isStrikerHitByMe='n';
			isStrikerHitByOther='n';
			isInHole[0]='n';
			
		}
	}
	if(isStrikerHitByOther=='y' && chance_ai[0]=='n')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			//call another chek function i.e rule to chek if chance_ai of other person continues or not,
			//this will also take care of updating coins pocketed by other person
			k = updateCount_other_ai(X,Y,coinCount);
			if(k == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed black coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(isRed_other == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_other = 'n';
						score_ai[1]=score_ai[1]-3;
					}
					else if(X[1] == 2.0f)
					{
						X[1] = x_r;
						Y[1] = y_r;
						isInHole[1] = 'n';
						coinCount[0] = coinCount[0]-1;//chek
						score_ai[1]=score_ai[1]-2;
					}
					else if(X[2] == 2.0f)
					{
						X[2] = x_r;
						Y[2] = y_r;
						isInHole[2] = 'n';
						coinCount[0] = coinCount[0]-1;
						score_ai[1]=score_ai[1]-2;
					}
				}
				chance_ai[0]='y';
				chance_ai[1]='n';
				x_of_str=0.0f;
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			if(k == 1)
			{
				chance_ai[0]='n';
				chance_ai[1]='y';
				x_of_str=0.0f;				
				while(1)
				{
					if(present_b4(x_of_str,1.275f) == 1) break;
					x_of_str = x_of_str-0.2f;
				}
				X[0]=x_of_str;
				Y[0]=1.275f;
				dir = 'n';
			}
			isStrikerHitByOther='n';
			isStrikerHitByMe='n';
			isInHole[0]='n';
		}
	}
}

void update_chance_2p(float Vx[], float Vy[], char chance_2p[])
{
	int i,j,k,l;
	float x_r,y_r,x_of_str=0.0f;
	char cchek='x';
	if(isStrikerHitByMe=='y' && chance_2p[0]=='y')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			j = updateCount_me_2p(X,Y,coinCount);
			if(j == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed white coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(isRed_me == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_me = 'n';
						score_2p[0]=score_2p[0]-3;
					}
					else if(X[3] == 2.0f)
					{
						X[3] = x_r;
						Y[3] = y_r;
						isInHole[3] = 'n';
						coinCount[1] = coinCount[1]-1;//chek
						score_2p[0]=score_2p[0]-2;
					}
					else if(X[4] == 2.0f)
					{
						X[4] = x_r;
						Y[4] = y_r;
						isInHole[4] = 'n';
						coinCount[1] = coinCount[1]-1;
						score_2p[0]=score_2p[0]-2;
					}
				}
				chance_2p[0]='n';
				chance_2p[1]='y';
				while(1)
				{
					if(present_b4(x_of_str,1.275f) == 1) break;
					x_of_str = x_of_str-0.2f;
				}
				X[0]=x_of_str;
				Y[0]=1.275f;
				dir = 'n';
			}
			if(j == 1)
			{
				chance_2p[0]='y';
				chance_2p[1]='n';
				x_of_str=0.0f;				
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			isStrikerHitByMe='n';
			isStrikerHitByOther='n';
			isInHole[0]='n';
			alpha=0;
			
		}
	}
	if(isStrikerHitByOther=='y' && chance_2p[0]=='n')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			//call another chek function i.e rule to chek if chance_2p of other person continues or not,
			//this will also take care of updating coins pocketed by other person
			k = updateCount_other_2p(X,Y,coinCount);
			if(k == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed black coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(isRed_other == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_other = 'n';
						score_2p[1]=score_2p[1]-3;
					}
					else if(X[1] == 2.0f)
					{
						X[1] = x_r;
						Y[1] = y_r;
						isInHole[1] = 'n';
						coinCount[0] = coinCount[0]-1;//chek
						score_2p[1]=score_2p[1]-2;
					}
					else if(X[2] == 2.0f)
					{
						X[2] = x_r;
						Y[2] = y_r;
						isInHole[2] = 'n';
						coinCount[0] = coinCount[0]-1;
						score_2p[1]=score_2p[1]-2;
					}
				}
				chance_2p[0]='y';
				chance_2p[1]='n';
				x_of_str=0.0f;
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			if(k == 1)
			{
				chance_2p[0]='n';
				chance_2p[1]='y';
				x_of_str=0.0f;				
				while(1)
				{
					if(present_b4(x_of_str,1.275f) == 1) break;
					x_of_str = x_of_str-0.2f;
				}
				X[0]=x_of_str;
				Y[0]=1.275f;
				dir = 'n';
			}
			isStrikerHitByOther='n';
			isStrikerHitByMe='n';
			isInHole[0]='n';
			alpha=0;
		}
	}
}

void update_chance_4p(float Vx[], float Vy[], char chance_4p[])
{
	int i,j,k,l;
	float x_r,y_r,x_of_str=0.0f,y_of_str=0.0f;
	char cchek='x';
	if(isStrikerHitByMe=='y' && chance_4p[0]=='y')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			j = updateCount_me_4p(X,Y,coinCount);//j=1 if chance_4p of player continues and 0 otherwise
			if(j == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed white coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(isRed_me == 'y')
					{
						X[5] = x_r;
						Y[5] = y_r;
						isInHole[5] = 'n';
						coinCount[2] = coinCount[2] - 1;
						isRed_me = 'n';
						score_4p[0]=score_4p[0]-3;
					}
					else if(X[3] == 2.0f)
					{
						X[3] = x_r;
						Y[3] = y_r;
						isInHole[3] = 'n';
						coinCount[1] = coinCount[1]-1;//chek
						score_4p[0]=score_4p[0]-2;
					}
					else if(X[4] == 2.0f)
					{
						X[4] = x_r;
						Y[4] = y_r;
						isInHole[4] = 'n';
						coinCount[1] = coinCount[1]-1;
						score_4p[0]=score_4p[0]-2;
					}
				}
				chance_4p[0]='n';chance_4p[2]='n';chance_4p[3]='n';
				chance_4p[1]='y';
				y_of_str=0.0f;
				while(1)
				{
					if(present_b4(1.275f,y_of_str) == 1) break;
					y_of_str = y_of_str+0.2f;
				}
				X[0]=1.275f;
				Y[0]=y_of_str;
				dir = 'n';
			}
			if(j == 1)
			{
				chance_4p[0]='y';
				chance_4p[1]='n';chance_4p[2]='n';chance_4p[3]='n';
				x_of_str=0.0f;				
				while(1)
				{
					if(present_b4(x_of_str,-1.275f) == 1) break;
					x_of_str = x_of_str+0.2f;
				}
				X[0]=x_of_str;
				Y[0]=-1.275f;
				dir = 'y';
			}
			isStrikerHitByMe='n';
			isStrikerHitByOther='n';
			isInHole[0]='n';
			alpha=0;
			
		}
	}
	if(isStrikerHitByOther=='y' && chance_4p[0]=='n')
	{
		for(i=0;i<6;i++)
		{
			if(Vx[i]!=0.0f || Vy[i]!=0.0f)
			{
				cchek='y';
				break;
			}
		}
		if(cchek=='x')
		{
			//call another chek function i.e rule to chek if chance_4p of other person continues or not,
			//this will also take care of updating coins pocketed by other person
			k = updateCount_other_4p(X,Y,coinCount);//k is 1 if chance_4p of other continues and 0 otherwise
			if(k == 0)
			{
				if(X[0]==2.0f)//striker goes into the hole,penalty:return pocketed black coin to board
				{
					l = position_replace(X,Y);//the positon to bring in penalty
					if(l==1) { x_r=0.0f;y_r=0.0f; }
					if(l==2) { x_r=0.41f;y_r=0.0f; }
					if(l==3) { x_r=-0.41f;y_r=0.0f; }
					if(l==4) { x_r=0.0f;y_r=0.41f; }
					if(l==5) { x_r=0.0f;y_r=-0.41f; }
					if(l==6) { x_r=1.4f;y_r=1.4f; }
					
					if(chance_4p[1]=='y' || chance_4p[3]=='y')
					{
						if(isRed_other == 'y')
						{
							X[5] = x_r;
							Y[5] = y_r;
							isInHole[5] = 'n';
							coinCount[2] = coinCount[2] - 1;
							isRed_other = 'n';
							score_4p[1]=score_4p[1]-3;
						}
						else if(X[1] == 2.0f)
						{
							X[1] = x_r;
							Y[1] = y_r;
							isInHole[1] = 'n';
							coinCount[0] = coinCount[0]-1;//chek
							score_4p[1]=score_4p[1]-2;
						}
						else if(X[2] == 2.0f)
						{	
							X[2] = x_r;
							Y[2] = y_r;
							isInHole[2] = 'n';
							coinCount[0] = coinCount[0]-1;
							score_4p[1]=score_4p[1]-2;
						}
					}
					else if(chance_4p[2]=='y')
					{
						if(isRed_me == 'y')
						{
							X[5] = x_r;
							Y[5] = y_r;
							isInHole[5] = 'n';
							coinCount[2] = coinCount[2] - 1;
							isRed_me = 'n';
							score_4p[0]=score_4p[0]-3;
						}
						else if(X[3] == 2.0f)
						{
							X[3] = x_r;
							Y[3] = y_r;
							isInHole[3] = 'n';
							coinCount[1] = coinCount[1]-1;//chek
							score_4p[0]=score_4p[0]-2;
						}
						else if(X[4] == 2.0f)
						{
							X[4] = x_r;
							Y[4] = y_r;
							isInHole[4] = 'n';
							coinCount[1] = coinCount[1]-1;
							score_4p[0]=score_4p[0]-2;
						}
					}
				}
				//giving chance_4p to other needs to be done carefully
				if(chance_4p[1]=='y')
				{	
					chance_4p[2]='y';
					chance_4p[0]='n';chance_4p[1]='n';chance_4p[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,1.275f) == 1) break;
						x_of_str = x_of_str-0.2f;
					}
					X[0]=x_of_str;
					Y[0]=1.275f;
				}
				else if(chance_4p[2]=='y')
				{	
					chance_4p[3]='y';
					chance_4p[0]='n';chance_4p[1]='n';chance_4p[2]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(-1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str-0.2f;
					}
					X[0]=-1.275f;
					Y[0]=y_of_str;
				}
				else if(chance_4p[3]=='y')
				{	
					chance_4p[0]='y';
					chance_4p[1]='n';chance_4p[2]='n';chance_4p[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,1.275f) == 1) break;
						x_of_str = x_of_str+0.2f;
					}
					X[0]=x_of_str;
					Y[0]=-1.275f;
				}
				dir = 'y';
			}
			if(k == 1)
			{
				if(chance_4p[1]=='y')
				{	
					chance_4p[1]='y';
					chance_4p[0]='n';chance_4p[2]='n';chance_4p[3]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str+0.2f;
					}
					X[0]=1.275f;
					Y[0]=y_of_str;
				}
				else if(chance_4p[2]=='y')
				{	
					chance_4p[2]='y';
					chance_4p[0]='n';chance_4p[1]='n';chance_4p[3]='n';
					//will have to give coordinates of striker here
					x_of_str=0.0f;
					while(1)
					{
						if(present_b4(x_of_str,1.275f) == 1) break;
						x_of_str = x_of_str-0.2f;
					}
					X[0]=x_of_str;
					Y[0]=1.275f;
				}
				else if(chance_4p[3]=='y')
				{	
					chance_4p[3]='y';
					chance_4p[0]='n';chance_4p[1]='n';chance_4p[2]='n';
					//will have to give coordinates of striker here
					y_of_str=0.0f;
					while(1)
					{
						if(present_b4(-1.275f,y_of_str) == 1) break;
						y_of_str = y_of_str-0.2f;
					}
					X[0]=-1.275f;
					Y[0]=y_of_str;
				}
				dir = 'n';
			}
			isStrikerHitByOther='n';
			isStrikerHitByMe='n';
			isInHole[0]='n';
			alpha=0;
		}
	}
}

