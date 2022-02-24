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

char dookdik[4][5] = {   ' ','_','_','_',' ',
						 '(','o','>','o',')',
						 '/','_','_','_','\\',
						 ' ','l',' ','l',' '  };
					

//     ___ 
//    (o>o)
// 	  /___\
//	   l l 
//    
//    dookdik


	int STX = 50 ,  STY = 32 ;	//ตำแหน่ง X Y เริ่ม  ( บนน้อย , ล่างมาก )  **

	int DDposx = STX ; int DDposy = STY ;
	int dx = STX ;         //ตำแหน่ง X ในอนาคต
	int vx = 2 ;     		//ความเร็ว X  **
	
    
    double dy = DDposy ; 	 //ตำแหน่ง Y ในอนาคต  
	double uy = 3 ;  //ความเร็วต้น Y **
	double vy = -uy ; //ความเร็ว Y
	double ay = 0.4 ; //แรงโน้มถ่วง


void drawDD(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(DDposx+j-3,DDposy+i-3); cout<<dookdik[i][j];
		}
	}
	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
}

void eraseDD(){
	for(int i=0; i<4; i++){
		for(int j=0; j<5; j++){
			gotoxy(DDposx+j-3,DDposy+i-3); cout<<' ';
		}
	}
	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
}

class ABC
{  
	public :
	int posx;
	int posy;
	bool appear = 1 ;
	void gen(int,int);
	void showdata(int,int);
	bool check();
};

void ABC::gen(int,int)
{
	
}


bool ABC::check()
{
	bool x = ( DDposx >= posx-2) && ( DDposx <= posx+2);
	bool y = ( DDposy >= posy-4);
	if( x&&y)
	{
		appear = 0;
		posx=0;
		posy=0;
		return 1;
	}
	return 0;
}

void ABC::showdata(int i ,int j )
{
	gotoxy(40+i*40,50+j); 	cout<<"posx = "<<posx ;
					 		cout<<"  posy = "<<posy;
							cout<<"  AP = "<<appear;
}



void play()   
{

	double fps = 30 , ptime = time(0)-2 ;
	int countfps = 0 ;

	int point = 0;

	while(1)
	{
		char CT = control() ;
		if(CT =='x') { break ; } //exit ( esc )
		if(CT =='w') { }
		if(CT =='s') { }
		if(CT =='a') { dx =  -vx ; }
		if(CT =='d') { dx =  vx ; }

		gotoxy(70,46); cout<<" dy= "<< dy <<"  ";
		gotoxy(70,56); cout<<" vy= "<< vy <<"  ";
		gotoxy(70,66); cout<<" P= "<< point <<"  ";

		//รอเขียน dy ใหม่
		dy += vy ;
		vy += ay ;
		if( vy > uy ) vy = -uy;

		DDposx += dx ;
		DDposy = dy ;

		if(DDposx<7) { DDposx = SCREEN_WIDTH-2 ; }  if(DDposx>SCREEN_WIDTH-2)  { DDposx = 7 ;}  //ชนขอบ X
		if(DDposy<1) { DDposy = 1 ; }  if(DDposy>WIN_HEIGHT-1)    { DDposy = WIN_HEIGHT-1 ; }  //ชนขอบ Y

		gotoxy(40,45); cout<<"  CT = "<<CT;             //Show data ปุ่มกด wasd-
		gotoxy(50,45); cout<<"  X = " <<DDposx<<" ";    //Show data DDposX
		gotoxy(60,45); cout<<"  Y = " <<DDposy<<" ";    //Show data DDposY
	    gotoxy(10,45); cout<<"  FPS = ";                //Show data FPS

		if(time(0)-ptime == 2 ) { ptime=time(0) ; gotoxy(18,45); fps = countfps/2 ; cout<<(fps)<<"   " ;  countfps=0 ; }  //update data FPS every 2sec
		else { countfps++; }  


	//draw
		drawDD();
		Sleep(10); 	
	//erase
		eraseDD();
	

	gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); // กันcursor กระพริบ
	}
}


int main()
{
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 

    do{
		system("cls");
        drawBorder();
		gotoxy(10,5); cout<<" -------------------------- "; 
		gotoxy(10,6); cout<<" |      test.exe       | "; 
		gotoxy(10,7); cout<<" --------------------------";
		gotoxy(10,9); cout<<"1. Start Game";
		gotoxy(10,10); cout<<"2. Instructions";	 
		gotoxy(10,11); cout<<"3. Quit";
		gotoxy(10,13); cout<<"Select option: ";


		DDposx = 50 ;
		DDposy = 35 ;

		char op = getche();
		     if( op=='1') { system("cls"); drawBorder(); play(); }
		else if( op=='2') {drawDD();getche();}
		else if( op=='3') exit(0);

	}while(1);


	return 0;
}
