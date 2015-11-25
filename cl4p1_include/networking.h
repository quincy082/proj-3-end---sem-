int sockfd;
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

void client(int argc, char *argv[])
{
    
    int portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
}
char isInHole[6] = {'n','n','n','n','n','n'},dir = 'y',isStrikerHitByMe='n',isStrikerHitByOther='n';
char chance[4] = {'y','n','n','n'};
int i_check = 0,alpha=0;
int coinCount[3]={0,0,0};//0-balck 1-white 2-red
char isRed_me='n',isRed_other='n';
int score_4p[2];//0-team1 1-team2
float strToFloat(char a[])
{
	return(atof(a));
	
}

void floatToStr(float x,char y[])
{
	sprintf(y, "%f", x);
	y[strlen(y)] = '\0';
}

void decode_copy(char a[])
{
	int i=0,j=0;
	char vx[10],vy[10],x[10],y[10],c;
	while(a[i]!='#')
	{
		vx[j]=a[i];
		j++;i++;
	}j=0;i++;
	while(a[i]!='#')
	{
		vy[j]=a[i];
		j++;i++;
	}j=0;i++;
	while(a[i]!='#')
	{
		x[j]=a[i];
		j++;i++;
	}j=0;i++;
	while(a[i]!='#')
	{
		y[j]=a[i];
		j++;i++;
	}j=0;i++;
	isStrikerHitByOther=a[i];
	if(chance[3]=='y')
	{
		Vx[0]=-strToFloat(vx);
		Vy[0]=-strToFloat(vy);
		X[0]=-strToFloat(x);
		Y[0]=-strToFloat(y);
	}
	if(chance[2]=='y')
	{
		Vx[0]=-strToFloat(vy);
		Vy[0]=strToFloat(vx);
		X[0]=-strToFloat(y);
		Y[0]=strToFloat(x);
	}
	if(chance[0]=='y')
	{
		Vx[0]=strToFloat(vy);
		Vy[0]=-strToFloat(vx);
		X[0]=strToFloat(y);
		Y[0]=-strToFloat(x);
	}
}
void copy(float vxx,float vyy,float xx,float yy, char buffer[],char isStrikerHitByMe)
{
	int i=0,j=0,k;
	char vx[10],vy[10],x[10],y[10];
	floatToStr(vxx,vx);
	floatToStr(vyy,vy);
	floatToStr(xx,x);
	floatToStr(yy,y);
	for(j=0;j<strlen(vx);j++)
		buffer[i++]=vx[j];
	buffer[i++] = '#';
	for(j=0;j<strlen(vy);j++)
		buffer[i++] = vy[j];
	buffer[i++] = '#';
	for(j=0;j<strlen(x);j++)
		buffer[i++] = x[j];
	buffer[i++] = '#';
	for(j=0;j<strlen(y);j++)
		buffer[i++] = y[j];
	buffer[i++] = '#';
	buffer[i++] = isStrikerHitByMe;
	buffer[i]='\0';//------------------------------------------------------------------
}

