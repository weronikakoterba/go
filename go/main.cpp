#define _CRT_SECURE_NO_WARNINGS
#define HEIGHT_SIZE 13//?
#define WIDTH_SIZE 13
#include"conio2.h"
#include<stdio.h>

struct position_t {
	int  top = 10;
	int left = 20;
};

enum PLAYER {
	PLAYER_1,
	PLAYER_2,
	INVALID_PLAYER
};

enum cmd_key {
	key_enter = 0x0d,
	key_left_arrow = 0x4b,
	key_right_arrow = 0x4d,
	key_up_arrow = 0x48,
	key_down_arrow= 0x50,
};

void print_board(position_t board_position) {
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

void write_number(int number) {
	if (number == 0) return;
	char sign = number % 10+'0';
	write_number(number / 10);
	putch(sign);
}
void current_star_position(int x, int y, position_t board_position) {
	cputs("x="); write_number((x- board_position.left)/2+1);
	cputs("  ");
	cputs("y="); write_number(y- board_position.top+1);
}	
void print_menu() {
	textcolor(BLACK);
	position_t menu_position;
	menu_position.left = 50;
	menu_position.top = 10;
	gotoxy(menu_position.left,menu_position.top);
	cputs("SCORE:");
	gotoxy(menu_position.left,menu_position.top= menu_position.top+1);
	cputs("PLAYER 1:");
	gotoxy(menu_position.left + 25,menu_position.top);
	cputs("PLAYER 2:");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 2);
	cputs("Weronika Koterba,193127");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("implmented functionalities:a,b");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("q = exit");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("n = start a new game");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("i= palce a stone on the board");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("cursors = moving");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("space = change color");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("enter = change background color");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("current position of cursor: ");

}
void print_star(int x, int y) {
	gotoxy(x, y);
	textbackground(YELLOW);
	putch('*');// putch prints one character and moves the cursor to the right
}
int save_player_moves(char stones[WIDTH_SIZE][HEIGHT_SIZE],int x,int y,PLAYER player, position_t board_position) {
	int board_x = (x - board_position.left)/2;
	int board_y = y - board_position.top;//??
	if (stones[board_x][board_y] != PLAYER_1 && stones[board_x][board_y] != PLAYER_2){
		if (stones[board_x + 2][board_y]== PLAYER_2 && stones[board_x - 2][board_y] == PLAYER_2 && stones[board_x][board_y + 1] == PLAYER_2 && stones[board_x][board_y - 1] == PLAYER_2) {
			stones[board_x][board_y] != PLAYER_1;
		}
		else if (stones[board_x + 2][board_y] == PLAYER_1 && stones[board_x - 2][board_y] == PLAYER_1 && stones[board_x][board_y + 1] == PLAYER_1 && stones[board_x][board_y - 1] == PLAYER_1) {
			stones[board_x][board_y] != PLAYER_2;
		}
		stones[board_x][board_y] = player;
		return 0;
	}
	else return 1;
}

void seek_and_print_stones(char stones[WIDTH_SIZE][HEIGHT_SIZE], position_t board_position) {
	for (int i = 0; i <= WIDTH_SIZE; i++) {
		for (int j = 0; j <= HEIGHT_SIZE; j++) {
			if (stones[i][j]==PLAYER_1) {
				textcolor(BLACK);
				gotoxy(board_position.left+2*i, board_position.top+j);
				putch('*');
			}
			else if (stones[i][j]==PLAYER_2) {
				textcolor(WHITE);
				gotoxy(board_position.left + 2*i, board_position.top + j);
				putch('*');
			}
		}
	}
}

void switch_players(PLAYER* player) {
	if (*player == PLAYER_1) {
		*player = PLAYER_2;
	}
	else
	{
		*player = PLAYER_1;
	}
}

int get_player_color(PLAYER player) {
	if (player == PLAYER_1) {
		return BLACK;
	}
	else {
		return WHITE;
	}
}
void count_stars(char stones[WIDTH_SIZE][HEIGHT_SIZE]) {
	int count_cought_stars_1 = 0;//bia³e gwiazdki zdobyte przez gracza 2
	int count_cought_stars_2 = 0;//czarne gwiazdki zdobyte przez gracza 1
	for (int i = 0; i < WIDTH_SIZE; i++) {
		for (int j = 0; j < HEIGHT_SIZE; j++) {
			if (stones[i][j] == PLAYER_1) count_cought_stars_1++;
			if (stones[i][j] == PLAYER_2) count_cought_stars_2++;
		}
	}
}

//char  reset_state(char stones[WIDTH_SIZE][HEIGHT_SIZE], position_t board_position, int x, int y) {//????

	//if (stones[x - board_position.left][y - board_position.top] == '*') putch('|');
	//x = board_position.left;
	//y = board_position.top;
//}
void init_stones(char stones[WIDTH_SIZE][HEIGHT_SIZE]){//??
	for (int i = 0; i < WIDTH_SIZE; i++) {
		for (int j = 0; j < HEIGHT_SIZE; j++) {
			stones[i][j] = INVALID_PLAYER;
		}
	}
}

int main() {
	position_t board_position;

	char stones[WIDTH_SIZE][HEIGHT_SIZE]; // trzeba inicjalizowac
	init_stones(stones);//??

	PLAYER player;

	//int current_color;

	int zn = 30, x = board_position.left, y = board_position.top, attr = 7, back = 0, zero = 0;
	char txt[32];

#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle sets the window title
	settitle("Weronika Koterba, 193127");

	// hide the blinking cursor
	_setcursortype(_NOCURSOR);
	//player=player_number.player1;
	player = PLAYER_1;

	do {

		textbackground(WHITE);

		clrscr();

		print_menu();
		current_star_position(x, y, board_position);
		print_board(board_position);
		// seek - prints stones
		seek_and_print_stones(stones, board_position);
		print_star(x,y);
		

		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;		// if this is the case then we read
			zn = getch();		// the next code knowing that this
			if (zn == key_up_arrow) {
				if (y > board_position.top)y--;
			}
			else if (zn == key_down_arrow) {
				if (y < HEIGHT_SIZE + board_position.top)y++;
			}
			else if (zn == key_left_arrow) {
				if (x > board_position.left)x = x - 2;
			}
			else if (zn == key_right_arrow) {
				if (x < 2 * WIDTH_SIZE + board_position.left)x = x + 2;
			}
		}
		else if (zn == key_enter) {
			switch_players(&player);
		}
		else if (zn == 'n') {

			// powinnismy czekac na enter

			//reset_state();
			
		}
		else if (zn == 'i') {
			save_player_moves(stones, x, y, player, board_position);	
		}
	} while (zn != 'q');

	_setcursortype(_NORMALCURSOR);	// show the cursor so it will be
					// visible after the program ends
	
	return 0;
	}
