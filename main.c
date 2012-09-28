#include<stdio.h>
#include<ctype.h>
#include<ncurses/ncurses.h>
#define ILEZNAKOW 10
int cx=0,cy=0,zn=1,row,col,tryb=1;
char cs[]={'o',' ','|','\\','/','_','-','^','V','U'};

void robto(int);
void info();	
void znak(int);	
void zmien();

int main(){
int co;	
initscr();
getmaxyx(stdscr,row,col);
raw();
info();
znak(-1);
keypad(stdscr,TRUE);
noecho();
mvprintw(row-2,2,"RYSUJ");
move(cy,cx);
co = getch();

while(co!='q'){
	robto(co);
	if(tryb==1){
		printw("%c",cs[zn]);
		//move(cy,col-cx-1);
		//printw("%c",cs[zn]);
		move(cy,cx);
	}
	refresh();
	co = getch();
	}

endwin();
return 0;
}


void robto(int co){
	switch (co){
	        case KEY_UP:
		        if(cy>0) cy-=1;
			break;
		case KEY_DOWN:
			if(cy<(row-6))cy+=1;
			break;
		case KEY_LEFT:
			if(cx>0)cx-=1;
			break;
		case KEY_RIGHT:
			if(cx<col-1)cx+=1;
			break;	
		case 'a':
			znak(-1);
			break;
		case 's':
			znak(+1);
			break;
		case 'z':
			tryb=tryb*-1+1;
			if(tryb==1)	mvprintw(row-2,2,"RYSUJ");
	          	else if(tryb==0)mvprintw(row-2,2,"RUCH  ");
			break;
		case 'd':
			printw("%c",cs[zn]);
			break;
		case 'x':
			printw(" ");
			break;
		case 'u':
			zmien();
			break;
	}
			move(cy,cx);
}

void info(){
	int i;
	for(i=0;i<10;i+=1){
		move(row-4,2*(i+1));
		printw("%c ",cs[i]);
		refresh();
		}
	for(i=0;i<col;i+=1){
		mvprintw(row-5,i,"=");
		}

mvprintw(row-4,(ILEZNAKOW+2)*2,"[a],[s] - Wybor znaku |[u]-znak uzytkownika");
mvprintw(row-3,(ILEZNAKOW+2)*2,"[z] - zmiana trybu ");
mvprintw(row-2,(ILEZNAKOW+2)*2,"[d],[x] - wstawienie lub usuniecie znaku w trybie ruchu");
mvprintw(row-1,(ILEZNAKOW+2)*2,"[q] - wyjscie     ");
move(cy,cx);
}

void znak(int wkt){
	mvprintw(row-3,2*(zn+1)," ");
	if((zn>0)&&(wkt==-1))zn-=1;
	else if((zn<ILEZNAKOW-1)&&(wkt==1))zn+=1;
	else if((zn==0)&&(wkt==-1)) zn=ILEZNAKOW-1;
	else if((zn==ILEZNAKOW-1)&&(wkt==1))zn=0;
	mvprintw(row-3,2*(zn+1),"^");
	move(cy,cx);
}

void zmien(){
	int tmp;
	tmp=getch();
	if(isprint(tmp)){
		cs[zn]=tmp;
		info();
	}
}
