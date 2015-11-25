int sockfd,newsockfd,newsockfd1,newsockfd2,newsockfd3;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void server_2p(int argc, char argv[])
{
     int portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
}

void server_4p(int argc, char argv[])
{
     int i,portno;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
    for (i=0;i<3;i++)
    {
        if(i==0){ newsockfd1 = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
               if (newsockfd1 < 0) 
             error("ERROR on accept1");}
        if(i==1) { newsockfd2 = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
               if (newsockfd2 < 0) 
             error("ERROR on accept2");}
        if(i==2){  newsockfd3 = accept(sockfd, 
               (struct sockaddr *) &cli_addr, &clilen);
               if (newsockfd3 < 0) 
             error("ERROR on accept3");}
     }
}

float strToFloat(char a[])
{
	return(atof(a));
	
}

void floatToStr(float x,char y[])
{
	sprintf(y, "%f", x);
	y[strlen(y)] = '\0';
}

char isInHole[6] = {'n','n','n','n','n','n'},dir = 'y',isStrikerHitByMe='n',isStrikerHitByOther='n';

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

void decode_copy_2p(char a[])
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
	Vx[0]=-strToFloat(vx);
	Vy[0]=-strToFloat(vy);
	X[0]=-strToFloat(x);
	Y[0]=-strToFloat(y);
}

char chance_4p[4] = {'y','n','n','n'};//chance_4p[0] and chance_4p[1]..[2]..[3] are chance_4ps of server,and first,second and third client respectively
char chance_2p[2] = {'y','n'};//chance_2p[0] and chance_2p[1] are chance_2ps of server and first client respectively
char chance_ai[2] = {'y','n'};//chance_ai[0] and chance_ai[1] are chances of player and computer respectively


void decode_copy_4p(char a[])
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
	if(chance_4p[2]=='y')
	{
		Vx[0]=-strToFloat(vx);
		Vy[0]=-strToFloat(vy);
		X[0]=-strToFloat(x);
		Y[0]=-strToFloat(y);
	}
	if(chance_4p[1]=='y')
	{
		Vx[0]=-strToFloat(vy);
		Vy[0]=strToFloat(vx);
		X[0]=-strToFloat(y);
		Y[0]=strToFloat(x);
	}
	if(chance_4p[3]=='y')
	{
		Vx[0]=strToFloat(vy);
		Vy[0]=-strToFloat(vx);
		X[0]=strToFloat(y);
		Y[0]=-strToFloat(x);
	}
}

