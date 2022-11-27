#define _CRT_SECURE_NO_WARNINGS
#define HEIGHT_SIZE 9//?
#define WIDTH_SIZE 9
#include"conio2.h"
#include<stdio.h>

struct position_t {
	int  top = 10;
	int left = 20;
};//?

void print_board(position_t board_position) {
	board_position.left;
	board_position.top;
	textbackground(YELLOW);
	textcolor(BLACK);
	for ( int y = 0; y <= HEIGHT_SIZE+1; y++) {
		for ( int x = 0; x <= 2*WIDTH_SIZE; x++) {
			gotoxy(board_position.left+x, board_position.top+y);
				 if (x % 2 == 0 ) putch('|');
				else if (x % 2 == 1) putch('-');
		}
	}
	for (int y = 0; y <= HEIGHT_SIZE+2; y++) {
		for (int x = 0; x <= 2 * WIDTH_SIZE+2; x++) {
			gotoxy(board_position.left-1 + x, board_position.top-1 + y);
			if (x == 0||x== 2 * WIDTH_SIZE + 2||y==0||y== HEIGHT_SIZE + 2) {
				textcolor(BLACK);
				textbackground(BLACK);
				putch('M');
				textbackground(YELLOW);
			}
		}
	}
}
void current_star_position(int x, int y) {
	cputs("x="); putch(x + '0');
	cputs("  ");
	cputs("y="); putch(y +'0');
}	
void print_menu(int zn,int zero,int attr,int back) {//???????
	textcolor(BLACK);
	int x=70;
	int y=10;
	char txt[32];
	gotoxy(x, y);
	cputs("SCORE:");
	gotoxy(x, y=y+1);
	cputs("PLAYER 1:");
	gotoxy(x + 25, y);
	cputs("PLAYER 2:");
	gotoxy(x, y=y+2);
	cputs("Weronika Koterba,193127");
	gotoxy(x, y=y+1);
	cputs("implmented functionalities:a");
	gotoxy(x, y=y+1);
	cputs("q = exit");
	gotoxy(x, y=y+1);
	cputs("n = start a new game");
	gotoxy(x, y = y + 1);
	cputs("i= palce a stone on the board");
	gotoxy(x, y = y + 1);
	cputs("cursors = moving");
	gotoxy(x, y=y+1);
	cputs("space = change color");
	gotoxy(x, y=y+1);
	cputs("enter = change background color");
	gotoxy(x, y = y + 1);
	cputs("current position of cursor: ");

}
void print_star(int x, int y) {
	gotoxy(x, y);
	textcolor(BLACK);
	textbackground(YELLOW);
	putch('*');// putch prints one character and moves the cursor to the right
}

int main(position_t board_position) {

	//board_position_t board_position;
	//board_position.left = 5;
	//putch(board_position.left+'0');
	
	//atrr kolor gwiazdki,back kolor t³a za gwiazdk¹,zn???
	int zn = 30, x = board_position.left, y = board_position.top, attr = 7, back = 0, zero = 0;
	char txt[32];

#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Weronika Koterba, 193127");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);

	do {

		textbackground(WHITE);

		clrscr();

		print_menu(zn,zero,attr,back);
		current_star_position(x, y);
		print_board(board_position);
		print_star(x,y);
		

		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == 0x48) {
				if (y > board_position.top)y--;
			}							// will be a special key
			else if (zn == 0x50) {
				if (y < HEIGHT_SIZE + board_position.top)y++;
			}
			else if (zn == 0x4b) {
				if (x > board_position.left)x = x - 2;
			}
			else if (zn == 0x4d) {
				if (x < 2 * WIDTH_SIZE + board_position.left)x = x + 2;
			}
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;
		else if (zn == 'n') clrscr();
	} while (zn != 'q');

	
	
	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends
	
	return 0;
	}
