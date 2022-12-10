#define _CRT_SECURE_NO_WARNINGS
#define PAWN '*'//pionek
#define FILENAME 100//max d³ugoœæ pliku
#include"conio2.h"
#include<stdio.h>
#include <stdlib.h>

struct board_size_t {
	int height_s=9;
	int width_s=9;
};
struct board_position_t {
	int  top = 5;
	int left = 10;
};
struct menu_position_t {
	int top = 4;
	int left = 75;
};
struct size_option_t {
	int top = 10;
	int left = 10;
};

enum PLAYER {
	PLAYER_1,
	PLAYER_2,
	INVALID_PLAYER
};
enum KEYS {
	key_enter = 0x0d,
	key_escape=0x1b,
	key_left_arrow = 0x4b,
	key_right_arrow = 0x4d,
	key_up_arrow = 0x48,
	key_down_arrow= 0x50,
};
void print_board(board_position_t board_position,board_size_t board_size) {
	textbackground(YELLOW);
	textcolor(BLACK);
	for ( int y = 0; y < board_size.height_s; y++) {
		for ( int x = 0; x < 2*board_size.width_s-1; x++) {
			gotoxy(board_position.left+x, board_position.top+y);
				 if (x % 2 == 0 ) putch('|');
				else if (x % 2 == 1) putch('-');
		}
	}
	for (int y = 0; y <board_size.height_s+2; y++) {
		for (int x = 0; x < 2 * board_size.width_s+1; x++) {
			gotoxy(board_position.left-1 + x, board_position.top-1 + y);
			if (x == 0||x== 2 * board_size.width_s||y==0||y== board_size.height_s+ 1) {
				textcolor(BLACK);
				textbackground(BLACK);
				putch('M');
				textbackground(YELLOW);
			}
		}
	}
}
void write_score(int number) {
	if (number == 0) {
		putch('0');
		return;
	}
	char sign = number % 10+'0';
	write_score(number / 10);
	putch(sign);
}
void write_number(int number) {
	if (number == 0) {
		return;
	}
	char sign = number % 10 + '0';
	write_number(number / 10);
	putch(sign);
}
void current_star_position(int x, int y, board_position_t board_position, menu_position_t menu_position) {
	gotoxy(menu_position.left + 28, menu_position.top + 19);
	cputs("x="); write_number((x- board_position.left)/2+1);
	gotoxy(menu_position.left + 33, menu_position.top + 19);
	cputs("y="); write_number(y- board_position.top+1);
}
void print_scores(menu_position_t menu_position, int result_1, int result_2) {
	gotoxy(menu_position.left, menu_position.top=menu_position.top+5);
	cputs("SCORE:");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("PLAYER 1:"); write_score(result_1);
	gotoxy(menu_position.left + 25, menu_position.top);
	cputs("PLAYER 2:"); write_score(result_2);
}
void print_beginning(size_option_t size_option) {
	textcolor(BLACK);
	gotoxy(size_option.left, size_option.top);
	cputs("CHOOSE SIZE OF YOUR BOARD:");
	gotoxy(size_option.left, size_option.top = size_option.top + 1);
	cputs("a) 9 x 9");
	gotoxy(size_option.left, size_option.top = size_option.top + 1);
	cputs("b) 13 x 13");
	gotoxy(size_option.left, size_option.top = size_option.top + 1);
	cputs("c) 19 x 19");
	gotoxy(size_option.left, size_option.top = size_option.top + 1);
	cputs("d) enter your own size:");
	gotoxy(size_option.left, size_option.top = size_option.top + 2);
	cputs("To load the state of a previous game enter 'l'.");
}
void print_menu(menu_position_t menu_position) {
	textcolor(BLACK);
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 8);
	cputs("Weronika Koterba,193127");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("implmented functionalities:a,b,c,d,e,f,h");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("q = exit");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("k= end handicap");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("n = start a new game");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("i= palce a stone on the board");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("s=save the game state to file");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("l= load the game state from file");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("cursors = moving");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("enter = confirm choice and end turn");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("esc = cancel current action");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("current position of cursor: ");
}
void print_star(int x, int y) {
	gotoxy(x, y);
	textbackground(YELLOW);
	putch(PAWN);
}
int save_player_moves(char** stones,int x,int y,PLAYER player, board_position_t board_position, board_size_t board_size) {
	int board_x = (x - board_position.left)/2;
	int board_y = y - board_position.top;
	if (stones[board_x][board_y] != PLAYER_1 && stones[board_x][board_y] != PLAYER_2){
		if ((board_x+1==board_size.width_s||stones[board_x + 1][board_y]== PLAYER_2)&&
			(board_x==0 || stones[board_x - 1][board_y] == PLAYER_2) && 
			(board_y + 1 == board_size.height_s||stones[board_x][board_y + 1] == PLAYER_2)&&
			(board_y==0 || stones[board_x][board_y - 1] == PLAYER_2)&&player==PLAYER_1) {
			return 1;
		}
		else if ((board_x + 1 == board_size.width_s || stones[board_x + 1][board_y] == PLAYER_1) && 
			(board_x ==0 || stones[board_x - 1][board_y] == PLAYER_1) &&
			(board_y + 1 == board_size.height_s || stones[board_x][board_y + 1] == PLAYER_1) && 
			(board_y == 0 || stones[board_x][board_y - 1] == PLAYER_1) && player == PLAYER_2) {
			return 1;
		}
		stones[board_x][board_y] = player;
		return 0;
	}
	else return 1;
}

void print_mess(int symbol, menu_position_t menu_position, char** stones,int x, int y, PLAYER player, board_position_t board_position,int result,bool block_move,bool handicap) {
	int space = 3;
	textcolor(BLACK);
	if (player == PLAYER_1) {
		gotoxy(board_position.left - space, board_position.top - space);
		cputs("playing: PLAYER 1");
	}
	if (player == PLAYER_2) {
		gotoxy(board_position.left - space, board_position.top - space);
		cputs("playing: PLAYER 2");
	}
	if (result == 1) {
		gotoxy(menu_position.left, menu_position.top);
		cputs("stone can not be place here");
	}
	else if (symbol == 'i'&&!handicap) {
		gotoxy(menu_position.left, menu_position.top);
		cputs("press enter to change turn");
	}
	else if (block_move==true&&symbol!='n'&&!handicap) {
		gotoxy(menu_position.left, menu_position.top);
		cputs("player has to be changed");
	}
	else if (handicap==true) {
		gotoxy(menu_position.left, menu_position.top);
		cputs("press enter to continue or 'k' to end handicap");
	}
}
void seek_and_print_stones(char** stones, board_position_t board_position,board_size_t board_size) {
	for (int i = 0; i < board_size.width_s; i++) {
		for (int j = 0; j < board_size.height_s; j++) {
			if (stones[i][j]==PLAYER_1) {
				textcolor(BLACK);
				gotoxy(board_position.left+2*i, board_position.top+j);
				putch(PAWN);
			}
			else if (stones[i][j]==PLAYER_2) {
				textcolor(WHITE);
				gotoxy(board_position.left + 2*i, board_position.top + j);
				putch(PAWN);
			}
		}
	}
}

void switch_players(PLAYER* player) {
	if (*player == PLAYER_1) {
		*player = PLAYER_2;}
	else{
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
void delete_all(char** stones,board_size_t board_size){
	for (int i = 0; i < board_size.width_s; i++) {
		for (int j = 0; j <board_size.height_s; j++) {
			stones[i][j] = INVALID_PLAYER;
		}
	}
}
bool captured(char** stones, int opposite_x, int opposite_y, board_size_t board_size,PLAYER current_color) {
	if ((opposite_x + 1 == board_size.width_s || stones[opposite_x + 1][opposite_y] == current_color) &&
		(opposite_x == 0 || stones[opposite_x - 1][opposite_y] == current_color) && 
		(opposite_y + 1 == board_size.height_s || stones[opposite_x][opposite_y + 1] == current_color) && 
		(opposite_y == 0 || stones[opposite_x][opposite_y - 1] == current_color)) {		
		stones[opposite_x][opposite_y] = INVALID_PLAYER;
		return true;
	}
	else return false;
}
int remove_if_captured(char** stones,int screen_x, int screen_y,board_size_t board_size,board_position_t board_position){
	int points = 0;
	int x= (screen_x - board_position.left)/2;
	int y= screen_y - board_position.top;
	PLAYER opposite_player = stones[x][y] == PLAYER_2 ? PLAYER_1: PLAYER_2;//2222
	PLAYER current_player = (PLAYER)stones[x][y];
	if (current_player == INVALID_PLAYER)
		return 0;
	if(x+1<board_size.width_s&&stones[x+1][y]==opposite_player) {
		if (captured(stones, x + 1, y, board_size, current_player)) points++;	
	}
	if(y + 1 < board_size.height_s && stones[x][y+1] == opposite_player) {
		if (captured(stones, x, y+1, board_size, current_player)) points++;
	}
	if(x-1>=0 && stones[x-1][y] == opposite_player) {
		if (captured(stones, x - 1, y, board_size, current_player)) points++;
	}
	if(y-1>=0 && stones[x][y-1] == opposite_player) {
		if (captured(stones, x, y-1, board_size, current_player)) points++;
	}
	return points;
}

int load_from_file(char* file_name, char*** stones, int* result_1, int* result_2,board_size_t* board_size,PLAYER* player){//wskaznik na tablice dwymiarowa,zaalokowac miejsce
	int return_value = 0;
	FILE* file_ptr;
	file_ptr = fopen(file_name, "r");
	if (!file_ptr){//2222
		return 1;
	}
	fscanf(file_ptr, "%c,", player);
	return_value+=fscanf(file_ptr, "%d,",&board_size->width_s);//tez sprawdzic 
	return_value+=fscanf(file_ptr, "%d,",&board_size->height_s);
	if (return_value != 2) {
		return 1;
	}
	fscanf(file_ptr, "%d,", result_1);
	fscanf(file_ptr, "%d", result_2);
	*stones = (char**)malloc(board_size->width_s * sizeof(char*));//222
	for (int i = 0; i < board_size->width_s; i++) (*stones)[i] = (char*)malloc(board_size->height_s * sizeof(char));
	for (int i = 0; i <board_size->width_s; i++){
		for (int j = 0; j <board_size->height_s; j++){
			fscanf(file_ptr, "%c", ( * stones)[i] + j);
		}
	}
	fclose(file_ptr);
	return 0;
}
int save_to_file(char* file_name, char** stones, int result_1, int result_2,board_size_t board_size,PLAYER player){
	FILE* file_ptr;
	file_ptr = fopen(file_name, "w");
	if (!file_ptr){
		return 1;
	}
	fprintf(file_ptr, "%c,",player );
	fprintf(file_ptr, "%d,", board_size.width_s);
	fprintf(file_ptr, "%d,", board_size.height_s);
	fprintf(file_ptr, "%d,", result_1);
	fprintf(file_ptr, "%d", result_2);
	for (int i = 0; i < board_size.width_s; i++){
		for (int j = 0; j < board_size.height_s; j++){
			if (stones[i][j] != PLAYER_1 && stones[i][j] != PLAYER_2) {
				fprintf(file_ptr, "%c", INVALID_PLAYER);
			}
			else fprintf(file_ptr, "%c", stones[i][j]);
		}
	}
	fclose(file_ptr);
	return 0;
}
int read_input(char buffer[FILENAME], int x, int y)
{
	textcolor(BLACK);
	gotoxy(x, y);
	int i = 0;
	int zn = 0;
	while (i < FILENAME)
	{
		zn = getche();
		if (zn != key_enter)
		{
			buffer[i] = zn;
			i++;
		}
		else
			break;
	}
	buffer[i] = '\0';
	return i;
}
void file_mess(int x,int y) {
	textcolor(BLACK);
	textbackground(WHITE);
	gotoxy(x,y);
	cputs("File name:");
}

int main() {
	board_position_t board_position;
	menu_position_t menu_position;
	board_size_t board_size;
	size_option_t size_option;
	PLAYER player;
	char** stones=NULL;
	int result = 0;
	bool block_move = false;
	int last_x = -1; //ostatna po³o¿ona gwiazdka przez przeciwnika(wspó³rzêdna x)
	int last_y = -1; //ostatna po³o¿ona gwiazdka przez przeciwnika(wspó³rzêdnia y)
	int ret = 0;
	int result_1 = 0;// wynik gracza 1
	int result_2 = 0;//wynik gracza 2
	int symbol = 0;//znak wpisywany z klawiatury
	int x = board_position.left;
	int y = board_position.top;
	int zero = 0;
	bool handicap = false;
	bool load = false;


#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Weronika Koterba, 193127");
	_setcursortype(_NOCURSOR);
	player = PLAYER_1;

	textbackground(WHITE);
	clrscr();
	print_beginning(size_option);

	bool repeat = false;//sprawdzanie czy wpisywane s¹ dobre litery
	int ret_val = 0;
	int i = 0;
	do {
		repeat = false;
		char choice = getch();
		switch (choice) {
		case 'a':
			board_size.height_s = 9;
			board_size.width_s = 9;
			break;
		case 'b':
			board_size.height_s = 13;
			board_size.width_s = 13;
			break;
		case'c':
			board_size.height_s = 19;
			board_size.width_s = 19;
			break;
		case'd':
			gotoxy(20, 20);
			cputs("enter numbers greatest than 0 and lower than 25 to get a board in choosen size");
			char num_string[3];
			read_input(num_string, size_option.left+25, size_option.left+4);
			board_size.width_s = atoi(num_string);
			read_input(num_string, size_option.left+30, size_option.top+4);
			board_size.height_s = atoi(num_string);
			if (board_size.height_s <= 0 || board_size.height_s >= 25 || board_size.width_s <= 0 || board_size.width_s >= 25)
			{
				board_size.height_s = 9;
				board_size.width_s = 9;
			}
			break;
		case 'l':
			file_mess(5,2);
			char file_name[FILENAME];
			read_input(file_name,15,2);
			ret_val = load_from_file(file_name, &stones, &result_1, &result_2, &board_size,&player);
			if (ret_val)
			{
				gotoxy(5,4);
				cputs("loading file filed");
			}
			else load = true;
			break;

		default:
			repeat = true;
			break;
		}
	} while (repeat);
	if (stones == NULL) {//
		stones = (char**)malloc(board_size.width_s * sizeof(char*));
		for (int i = 0; i < board_size.width_s; i++) stones[i] = (char*)malloc(board_size.height_s * sizeof(char));
		for (int i = 0; i < board_size.width_s; i++) {
			for (int j = 0; j < board_size.height_s; j++) {
				stones[i][j] = INVALID_PLAYER;
			}
		}
	
	}
	if (!load) {
		gotoxy(menu_position.left, menu_position.top);
		cputs("Do you want to edit game state (y/n)?");
		bool correct_answer = false;
		while (!correct_answer)
		{
			char answer = getch();
			if (answer == 'y')
			{
				handicap = true;
				correct_answer = true;
			}
			else if (answer == 'n')
			{
				handicap = false;
				correct_answer = true;
			}
		}
	}

	do {
		textbackground(WHITE);
		clrscr();
		print_menu(menu_position);
		current_star_position(x, y, board_position, menu_position);
		print_mess(symbol, menu_position, stones, x, y, player, board_position, result, block_move,handicap);
		print_scores(menu_position, result_1, result_2);
		print_board(board_position, board_size);
		print_star(x, y);
		seek_and_print_stones(stones, board_position,board_size);

		zero = 0;
		symbol = getch();
		if (symbol == 0) {
			zero = 1;
			symbol = getch();
			if (symbol == key_up_arrow) {
				if (y > board_position.top)y--;
			}
			else if (symbol == key_down_arrow) {
				if (y <board_size.height_s - 1 + board_position.top)y++;
			}
			else if (symbol == key_left_arrow) {
				if (x > board_position.left)x = x - 2;
			}
			else if (symbol == key_right_arrow) {
				if (x < 2 * board_size.width_s - 2 + board_position.left)x = x + 2;
			}
		}
		else if (symbol == key_enter)
		{
			block_move = false;
			int result = remove_if_captured(stones, x, y, board_size, board_position);
			if (player == PLAYER_1)
				result_1 += result;
			if (player == PLAYER_2)
				result_2 += result;
			if (!handicap&&last_x!=-1&&last_y!=-1)//jesli nie, handicap false
			{
				switch_players(&player);
				last_x = -1;
				last_y = -1;
			}

		}
		else if (symbol == 'k')
		{
			handicap = false;
			switch_players(&player);
			last_x = -1;
			last_y = -1;
		}
		else if (symbol == 'n') {
			delete_all(stones,board_size);
			x = board_position.left;
			y = board_position.top;
			player = PLAYER_1;
			result_1 = 0;
			result_2 = 0;

		}
		else if (symbol == 'i') {
				if (block_move == false) {
					result = save_player_moves(stones, x, y, player, board_position,board_size);
					print_mess(symbol, menu_position, stones, x, y, player, board_position, result, block_move,handicap);
					if (result == 0) {
						last_x = x;
						last_y = y;
						block_move = true;
					}
				}
		}
		else if (symbol == key_escape) {
			block_move = false;
			if (last_x >= 0 && last_y >= 0) {
				stones[(last_x - board_position.left) / 2][last_y - board_position.top] = INVALID_PLAYER;
			}
		}
		else if (symbol == 's')
		{
			file_mess(menu_position.left,menu_position.top+22);
			char file_name[50];
			read_input(file_name, menu_position.left+10, menu_position.top + 22);
			int ret_val = save_to_file(file_name, stones, result_1, result_2,board_size,player);
			if (ret_val){
				gotoxy(menu_position.left + 10, menu_position.top + 24);
				cputs("saving to file filed");
			}
		}
		else if (symbol == 'l'){
			file_mess(menu_position.left, menu_position.top + 22);
			char file_name[50];
			read_input(file_name, menu_position.left + 10, menu_position.top + 22);
			int ret_val = load_from_file(file_name, &stones, &result_1, &result_2 ,&board_size,&player);
			if (ret_val){
				gotoxy(menu_position.left + 10, menu_position.top + 24);
				cputs("loading file filed");
			}
		}

	} while (symbol != 'q');
	_setcursortype(_NORMALCURSOR);
	for (int i = 0; i < board_size.width_s; i++)
		free(stones[i]);
	free(stones);
	return 0;
}


		

