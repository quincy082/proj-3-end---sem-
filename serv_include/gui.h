
int gui_chek=0;
void print_bitmap_string(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

void displayResult()
{
	glColor3f(0.92f,0.68f,0.92f);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f,-2.0f,-5.0f);
	glVertex3f(-2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,-2.0f,-5.0f);
	glEnd();
	glColor3f(0.0f,0.0f,0.0f);
	void* bitmap_fonts[7] = {
      	GLUT_BITMAP_9_BY_15,
      	GLUT_BITMAP_8_BY_13,
      	GLUT_BITMAP_TIMES_ROMAN_10,
      	GLUT_BITMAP_TIMES_ROMAN_24,
      	GLUT_BITMAP_HELVETICA_10,
      	GLUT_BITMAP_HELVETICA_12,
      	GLUT_BITMAP_HELVETICA_18     
   	};
	char* bitmap_font_names[6] = {
     	"PLAYER1 WINS!!",
      	"COMPUTER WINS!!",
      	"PLAYER2 WINS!!",
      	"TEAM1 WINS!!",
      	"TEAM2 WINS!!"
      	"MATCH TIE!!"     
   	};
   	glColor3f(0.0f,0.0f,0.0f);
   	glRasterPos3f(-0.6f, 0.0f,-5.0f);
   	if(game_type==1)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_ai[0] > score_ai[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[0]);
			else if(score_ai[0] < score_ai[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[1]);
			else print_bitmap_string(bitmap_fonts[6], bitmap_font_names[5]);
		}
	}
	if(game_type==2)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_2p[0] > score_2p[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[0]);
			else if(score_2p[0] < score_2p[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[2]);
			else print_bitmap_string(bitmap_fonts[6], bitmap_font_names[5]);
		}
	}
	if(game_type==3)
	{
		if(isInHole[5]=='y' && ((isInHole[1]=='y' && isInHole[2]=='y') || (isInHole[3]=='y' && isInHole[4]=='y') ))
		{
			if(score_4p[0] > score_4p[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[3]);
			else if(score_4p[0] < score_4p[1]) print_bitmap_string(bitmap_fonts[6], bitmap_font_names[4]);
			else print_bitmap_string(bitmap_fonts[6], bitmap_font_names[5]);
		}
	}
}

void drawGUI()
{
	glColor3f(0.92f,0.68f,0.92f);
	glBegin(GL_QUADS);
	glVertex3f(-2.0f,-2.0f,-5.0f);
	glVertex3f(-2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,2.0f,-5.0f);
	glVertex3f(2.0f,-2.0f,-5.0f);
	glEnd();
	glColor3f(0.0f,0.0f,0.0f);
	void* bitmap_fonts[7] = {
      	GLUT_BITMAP_9_BY_15,
      	GLUT_BITMAP_8_BY_13,
      	GLUT_BITMAP_TIMES_ROMAN_10,
      	GLUT_BITMAP_TIMES_ROMAN_24,
      	GLUT_BITMAP_HELVETICA_10,
      	GLUT_BITMAP_HELVETICA_12,
      	GLUT_BITMAP_HELVETICA_18     
   	};
	char* bitmap_font_names[11] = {
     	"***WELCOME***",
      	"GAME OPTIONS:",
      	"Play against Computer",
      	"Play with 2 players(over LAN)",
      	"Play with 4 players(over LAN)",
      	"CHOOSE LEVEL:",
      	"Newbie",
      	"Amateur",
      	"Expert",
      	"CONTINUE",
      	"waiting for users...."     
   	};
	glRasterPos3f(-0.6f, 1.6f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[0]);//6 and 3---6 is more acptbl!
      	glRasterPos3f(-1.6f, 1.0f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[1]);
      	glRasterPos3f(-1.4f, 0.8f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[2]);
      	glRasterPos3f(-1.4f, 0.6f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[3]);
      	glRasterPos3f(-1.4f, 0.4f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[4]);
      	glRasterPos3f(-1.6f, 0.0f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[5]);
      	glRasterPos3f(-1.4f, -0.2f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[6]);
      	glRasterPos3f(-1.4f, -0.4f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[7]);
      	glRasterPos3f(-1.4f, -0.6f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[8]);
      	//87,52,69
      	glColor3f(0.86f,0.44f,0.58f);
      	glBegin(GL_QUADS);
	glVertex3f(-0.6f,-1.2f,-5.0f);
	glVertex3f(-0.6f,-1.5f,-5.0f);
	glVertex3f(0.3f,-1.5f,-5.0f);
	glVertex3f(0.3f,-1.2f,-5.0f);
	glEnd();
	glColor3f(0.0f,0.0f,0.0f);
      	glRasterPos3f(-0.5f, -1.4f,-5.0f);
      	print_bitmap_string(bitmap_fonts[6], bitmap_font_names[9]);
      	glColor3f(0.93f,0.93f,0.93f);
      	drawDisc(-1.5f,0.84f,0.06f,1000);
      	drawDisc(-1.5f,0.64f,0.06f,1000);
      	drawDisc(-1.5f,0.44f,0.06f,1000);
      	drawDisc(-1.5f,-0.16f,0.06f,1000);
      	drawDisc(-1.5f,-0.36f,0.06f,1000);
      	drawDisc(-1.5f,-0.56f,0.06f,1000);
      	if(gui_chek == 1)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,0.84f,0.03f,1000);
      	}
      	if(gui_chek == 2)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,0.64f,0.03f,1000);
      	}
      	if(gui_chek == 3)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,0.44f,0.03f,1000);
      	}
      	if(gui_chek == 4)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,-0.16f,0.03f,1000);
      		drawDisc(-1.5f,0.84f,0.03f,1000);
      	}
      	if(gui_chek == 5)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,-0.36f,0.03f,1000);
      		drawDisc(-1.5f,0.84f,0.03f,1000);
      	}
      	if(gui_chek == 6)
      	{
      		glColor3f(0.43f,0.43f,0.43f);
      		drawDisc(-1.5f,-0.56f,0.03f,1000);
      		drawDisc(-1.5f,0.84f,0.03f,1000);
      	}
	return ;
	
	
}


