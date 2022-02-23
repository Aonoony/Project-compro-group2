#include<iostream>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define SCREEN_WIDTH 100  // **
#define SCREEN_HEIGHT 50  // **
#define WIN_HEIGHT 40     // **


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int DDposx , DDposy ;
int baseposx[4] ;
int baseposy[4] ;

void gotoxy(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void drawBorder(){ 
	
	for(int i=0; i<SCREEN_WIDTH; i++){
		gotoxy(i,0); cout<<"±";
		gotoxy(i,SCREEN_HEIGHT); cout<<"±";
	}
	
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(0,i); cout<<"±";
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	}
	for(int i=0; i<SCREEN_WIDTH-2; i++){
		gotoxy(i+1,WIN_HEIGHT); cout<<"±";
	}
}

void setcursor(bool visible, DWORD size) 
{
	if(size == 0)
		size = 10;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}


char dookdik[2][6] = { '/','-','-','o','\\',' ',   // น้องdookdik  **
					'|','_','_','_',' ','>' };

//     ___ 
//    (o>o)
// 	  /___\
//	   ll
//    
//    dookdik

/*void drawDD(){
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			gotoxy(j+2,i+6); cout<<dookdik[i][j];
		}
	}
}*/


char control()   //เช็คการกดปุ่ม ตอนเล่น
{
	if(kbhit()){
		char ch = getch();
		if(ch=='w') {return 'w' ;}
		if(ch=='a') {return 'a' ;}
		if(ch=='s') {return 's' ;}
		if(ch=='d') {return 'd' ;}
		if(ch== 27) {return 'x' ;}	//ESC
	}return '-' ;  // non
}




void drawDD()    //แสดงDD
{ 
	gotoxy(DDposx,DDposy) ; cout<<'*' ; 
}
void eraseDD()  //ลบDD
{ 
	gotoxy(DDposx,DDposy) ; cout<<' ' ; 
}

class base
{  
	public :
	int posx;
	int posy;
	bool appear;
	base(int,int);
};

base :: base(int i , int j)
{
	posx = (i+1)*20-rand()%8;
	posy = (j+1)*8+rand()%4;
}

void drawbase(base *base)   //แสดงDD
{ 
	if(base->appear){gotoxy(base->posx,base->posy) ; cout<<"==========" ;}
	else 			{gotoxy(base->posx,base->posy) ; cout<<"          " ;}
}

void play()   
{
	double fps = 30 , ptime = time(0)-2 ;
	int countfps = 0 ;

	int STX = 50 ,  STY = 35 ;	//ตำแหน่ง X Y เริ่ม  ( บนน้อย , ล่างมาก )  **

	DDposx = STX ; DDposy = STY ;
	int dx ;         //ตำแหน่ง X ในอนาคต
	int vx = 1 ;     //ความเร็ว X  **
	
    
	int high  = 15 ; 	//ความสูงที่กระโดดได้  **
	int slow  = 10 ;    //gravity น้อย=ตกเร็ว   ( น้อยกว่า high )  **
	double dy = 0 ;		//ตำแหน่ง Y ในอนาคต
	bool SY = 0 ;		//Status 0ขึ้น  1ลง

	while(1)
	{
		char CT = control() ;
		if(CT =='x') { break ; } //exit ( esc )
		if(CT =='w') { }
		if(CT =='s') { }
		if(CT =='a') { dx -=  vx ; }
		if(CT =='d') { dx +=  vx ; }

		gotoxy(70,46); cout<<" dy= "<< dy <<"  ";

		//รอเขียน dy ใหม่
		
		DDposx = dx ;
		DDposy = dy ;

		if(DDposx<2) { DDposx = SCREEN_WIDTH-2 ; }  if(DDposx>SCREEN_WIDTH-2)  { DDposx = 2 ;}  //ชนขอบ X
		if(DDposy<1) { DDposy = 1 ; }  if(DDposy>WIN_HEIGHT-1)    { DDposy = WIN_HEIGHT-1 ; }  //ชนขอบ Y

		gotoxy(40,45); cout<<"  CT = "<<CT;             //Show data ปุ่มกด wasd-
		gotoxy(50,45); cout<<"  X = " <<DDposx<<" ";    //Show data DDposX
		gotoxy(60,45); cout<<"  Y = " <<DDposy<<" ";    //Show data DDposY
	    gotoxy(10,45); cout<<"  FPS = ";                //Show data FPS

		if(time(0)-ptime == 2 ) { ptime=time(0) ; gotoxy(18,45); fps = countfps/2 ; cout<<(fps)<<"   " ;  countfps=0 ; }  //update data FPS every 2sec
		else { countfps++; }  

	//draw
		drawDD();
		Sleep(20); 	
	//erase
		eraseDD();
	

	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
	}
}

void EndScreen(){
	system("cls"); drawBorder();
	gotoxy(10,6); cout << "------------------------------------------------------------------------- "<<endl;
	gotoxy(10,8); cout << "|    *****      *     *       * ******       ****  *       ****** ****    |"<<endl;
	gotoxy(10,9); cout << "|   *          * *    * *   * * *           *    *  *     * *     *   *   |"<<endl;
	gotoxy(10,10); cout << "|   *  ****   *   *   *  * *  * *****       *    *   *   *  ****  ****    |"<<endl;
	gotoxy(10,11); cout << "|   *  *  *  *******  *   *   * *           *    *    * *   *     * *     |"<<endl;
	gotoxy(10,12); cout << "|    *****  *       * *       * ******       ****      *    ***** *   *   |"<<endl;
	gotoxy(10,13); cout << " ------------------------------------------------------------------------- "<<endl;
	gotoxy(10,15); //showscore();
	gotoxy(10, 17); cout << "Press x to return to menu";
	char op = getch();
	if(op == 'x'){system("cls"); drawBordr(); menu();}
}


void menu(){
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |      test.exe       | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";
}

void instructions(){
	system("cls"); drawBorder();
	gotoxy(10,6); cout << "Instructions";
	gotoxy(10,8); cout << "Climb up high to gain points.";
	gotoxy(10,9); cout << "The base will be removed when you once step on it.";
	gotoxy(10,10); cout << "If you falling down the game is over.";
	gotoxy(10,11); cout << "Along the journey,It will be items supporting you";
	gotoxy(22,13); cout << "Press x to return to menu.";
	char op = getche();
	if(op == 'x'){system("cls"); drawBorder(); menu();}
}

int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 

    do{
		system("cls");
                drawBorder();
		menu();



		char op = getche();
		     if( op=='1') { system("cls"); drawBorder(); play(); }
		else if( op=='2') {instructions();}
		else if( op=='3') exit(0);

	}while(1);


	return 0;
}
