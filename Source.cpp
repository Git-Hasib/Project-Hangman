#include "iGraphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define MAXATTEMPT 5

int tryleft = MAXATTEMPT;
char word_to_guess[100];
char str[15];
char str1[15];
char c[3];
int len=0;


int easycnt;
int hardcnt;
int wordnumber;

int ispresent[26];
int isguessed[26];
int totword;


int step=0;			//Controlling VAriable
int flag=0;
int flag2=0;
int difficulty=0;


int x11=450;		//for (iMouse Function)
int x22=250+x11;
int y11=500;
int y22=50+y11;


int cartoon_posX = 210;		//Cartoon-Line Variable
int cartoon_posY = 70;
int cartoon_go_up = 32;		//cartoon_posY 32 kore barbe
int line_x1 = 256;			//Line position x1 y1 fixed thakbe
int line_y1 = 463;
int line_x2 = 256;
int line_y2 = 253;
int line_go_up = 42;		//y2 ta 46 kore barbe
						

							//Function_Part
void clearstate(){
	int i = 0;
	for(i = 0;i<26;++i){
		ispresent[i] = 0;
		isguessed[i] = 0;
	}
}

int cnteasy(){
	FILE *fp = fopen("words_easy.txt","r");
	char s[100];
	int tot = 0;
	while(fscanf(fp,"%s",s)!=EOF){
		tot++;
	}
	fclose(fp);
	return tot;
}
 

int cnthard(){
	FILE *fp = fopen("words_hard.txt","r");
	char s[100];
	int tot = 0;
	while(fscanf(fp,"%s",s)!=EOF){
		tot++;
	}
	fclose(fp);
	return tot;
}
 

 
void setword(FILE *fp, int wordnumber){
	int cur = 0;
	do{
		fscanf(fp,"%s",word_to_guess);
		cur++;
	}while(cur<=wordnumber);
 
	fclose(fp);
}
 
void setpresence(){
	
	int l = strlen(word_to_guess);
	int i;
	for(i = 0; i<l; ++i){
		ispresent[word_to_guess[i]-'a'] = 1;
	}
}
 
void printpresence(){
	int i;
	for(i = 0; i<26; ++i){
		if(ispresent[i]){
			//printf("%c is present\n",i+'a');
		}
	}
}

int printword(){
	int l = strlen(word_to_guess);
	int i; int gap = 0;
	for(i = 0; i<l; ++i){
		if(isguessed[word_to_guess[i]-'a']){
			str1[i]=word_to_guess[i];
		}
		else{
			str1[i] = '*';
			gap = gap + 1;
		}
	iSetColor(0, 0, 160);
	iText(463, 225, str1, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	
	return (gap);  //str1 ta iText e print korte hobe
}
 
void updatestate(char c){
	if(ispresent[c-'a']){
		printf("Correct Guess\n");
		isguessed[c-'a'] = 1;
	}
	else{
		printf("Wrong Guess\n");
		tryleft--;
	}
	//printf("%d chances left\n",*left);
}

void drawRectangle()
{
	if(flag==0)
	{
		iSetColor(0, 0, 0);
		iRectangle(450, 500, 250, 50);
	}
	if(flag==1)
	{
		iSetColor(255, 13, 37);
		iRectangle(450, 500, 250, 50);
		
		if(flag==1)
		{
			iSetColor(0, 0, 0);
			iText(460, 520, str, GLUT_BITMAP_TIMES_ROMAN_24);
		}
	}
}
void drawRectangle_2()
{
	iSetColor(255, 0, 0);
	iFilledRectangle(600, 500, 100, 50);
	iSetColor(0, 0, 0);
	iText(615, 515, "HARD", GLUT_BITMAP_TIMES_ROMAN_24);
	
	iSetColor(41, 52, 180);
	iFilledRectangle(450, 500, 100, 50);
	iSetColor(255, 255, 255);
	iText(465, 515, "EASY", GLUT_BITMAP_TIMES_ROMAN_24);
	
}

void drawRectangle3()
{
	iSetColor(255, 255,255);
	iFilledRectangle(450, 115, 250, 350);
}

void iDraw()
{	
	iClear();
	iShowBMP(0, 0, "Background\\background.bmp");

	printword();
	
	if(step==0)
	{
		drawRectangle();
	}
	
	if(step==1)
	{
		iShowBMP(cartoon_posX, cartoon_posY, "Background//hangman.bmp");
		iSetColor(0, 0, 0);
		iLine(line_x1, line_y1, line_x2, line_y2);
		drawRectangle_2();	
	}
	if(step==2)
	{
		iShowBMP(cartoon_posX, cartoon_posY, "Background//hangman.bmp");
		iSetColor(0, 0, 0);
		iLine(line_x1, line_y1, line_x2, line_y2);
		drawRectangle3;
		if(flag2==1)
		{
			iText(460, 120, "WIN", GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else
		{
			iText(460, 120, "LOOSE", GLUT_BITMAP_TIMES_ROMAN_24);
		}

	}


	
}

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{

}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/


void iMouse(int button, int state, int mx, int my)
{
	if(step==0)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			printf("%d  %d\n", mx, my);
			if(mx>=x11 && mx<=x22 && my>=y11 && my<=y22)
			{
				flag=1;
			}
			else
			{
				flag=0;
			}
		}
	}
	if(step==1)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(mx>=450 && mx<=550 && my>=500 && my<=550)
			{	
				difficulty=1;
				step=2;
			}
			if(mx>=600 && mx<=700 && my>=500 && my<=550)
			{
				difficulty=2;
				step=2;
			}	
		}
	}
	if(step==2)
	{
		if(difficulty==1)
		{
			srand(time(0));

			FILE *fread;
			fread = fopen("words_easy.txt","r");
			totword = easycnt;

			wordnumber = rand()%totword;
			setword(fread,wordnumber);
			fclose(fread);
			setpresence();

				//printpresence();

				
				
				int gap = printword();
				if(gap==0){
					flag2=1;
				}
				else
					flag2=0;
			
						

			//printf("Guess a character: ");
			//scanf("%s",c);
						
			//3rd part
			updatestate(c[0]);
			//3rd part
		}
		if(difficulty==2)
		{
			srand(time(0));
			FILE *fread;
			fread = fopen("words_hard.txt","r");
			totword = hardcnt;
			wordnumber = rand()%totword;
			setword(fread,wordnumber);
			fclose(fread);
			setpresence();
			printpresence();
	
				
				int gap = printword();
				if(gap==0){
					 flag2=1;	//akta flag dhore nibi and sei flag ta idraw te print korb j win
				}
				else
				{
					flag2=0;
				}

			updatestate(c[0]);    //j charecter tar input nibi oi string tar nam c db 
		}
	}
	
	
}
	


/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed. 
*/

void iKeyboard(unsigned char key)
{
		if(step==0)
		{
			if(flag == 1)
			{
				if(key== '\r')
				{
					step=1;
				}
				else
				{
					str[len] = key;
					len++;
				}
			}
		}
	
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);	
	}
	
}

int main(){
	
	easycnt = cnteasy();
	hardcnt = cnthard();
	printf("%d %d\n",easycnt,hardcnt);
	
	//clearstate();
		
	iInitialize(800, 600, "HangMan");

		
		
		/*if(tryleft==0){
			printf("You lose\n");
		}
		else{
			printf("Congratulations! You have beaten the hangman\n");
		}*/
	
	return 0;
}