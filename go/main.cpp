#define _CRT_SECURE_NO_WARNINGS
#define HEIGHT_SIZE 9//zamienic na strukture
#define WIDTH_SIZE 9
#include"conio2.h"
#include<stdio.h>
#include <stdlib.h>
//liczenie zbitych i wypisywanie,


struct coord{
	int x;
	int y;
};

struct coord_set{
	coord set[WIDTH_SIZE * HEIGHT_SIZE];
	int last = 0;
};
struct board_size_t {
	int height_s;
	int width_s;
};

typedef struct el{	
	coord c;
	struct el* next;
} el_t;//??

struct board_position_t {
	int  top = 10;
	int left = 10;
};
struct menu_position_t {
	int top = 7;
	int left = 60;
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
	board_size.height_s = 9;
	board_size.width_s =9;
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

void write_number(int number) {
	if (number == 0) return;
	char sign = number % 10+'0';
	write_number(number / 10);
	putch(sign);
}
void current_star_position(int x, int y, board_position_t board_position, menu_position_t menu_position) {
	gotoxy(menu_position.left + 28, menu_position.top + 16);
	cputs("x="); write_number((x- board_position.left)/2+1);
	gotoxy(menu_position.left + 33, menu_position.top + 16);
	cputs("y="); write_number(y- board_position.top+1);
}
void print_scores(menu_position_t menu_position) {
	gotoxy(menu_position.left, menu_position.top=menu_position.top+5);
	cputs("SCORE:");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("PLAYER 1:");
	gotoxy(menu_position.left + 25, menu_position.top);
	cputs("PLAYER 2:");
}
void print_size(menu_position_t menu_position) {
	gotoxy(menu_position.left, menu_position.top);
	cputs("CHOOSE SIZE:");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("a) 9 x 9");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("b) 13 x 13");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("c) 19 x 19");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("d) enter your own size:");
}
void print_menu(menu_position_t menu_position) {
	textcolor(BLACK);
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 8);
	cputs("Weronika Koterba,193127");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("implmented functionalities:a,b,c,d");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("q = exit");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("n = start a new game");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("i= palce a stone on the board");
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
	putch('*');
}
int save_player_moves(char stones[WIDTH_SIZE][HEIGHT_SIZE],int x,int y,PLAYER player, board_position_t board_position) {
	int board_x = (x - board_position.left)/2;
	int board_y = y - board_position.top;//??
	if (stones[board_x][board_y] != PLAYER_1 && stones[board_x][board_y] != PLAYER_2){
		if ((board_x+1==WIDTH_SIZE||stones[board_x + 1][board_y]== PLAYER_2)&& (board_x==0 || stones[board_x - 1][board_y] == PLAYER_2) && (board_y + 1 == HEIGHT_SIZE||stones[board_x][board_y + 1] == PLAYER_2)&& (board_y==0 || stones[board_x][board_y - 1] == PLAYER_2)&&player==PLAYER_1) {
			return 1;
		}
		else if ((board_x + 1 == WIDTH_SIZE || stones[board_x + 1][board_y] == PLAYER_1) && (board_x ==0 || stones[board_x - 1][board_y] == PLAYER_1) && (board_y + 1 == HEIGHT_SIZE|| stones[board_x][board_y + 1] == PLAYER_1) && (board_y == 0 || stones[board_x][board_y - 1] == PLAYER_1) && player == PLAYER_2) {
			return 1;
		}
		stones[board_x][board_y] = player;
		return 0;
	}
	else return 1;
}
void print_mess(int zn, menu_position_t menu_position, char stones[WIDTH_SIZE][HEIGHT_SIZE],int x, int y, PLAYER player, board_position_t board_position,int result,bool block_move) {

	textcolor(BLACK);
	if (player == PLAYER_1) {
		gotoxy(board_position.left - 5, board_position.top - 3);
		cputs("playing: PLAYER 1");
	}
	if (player == PLAYER_2) {
		gotoxy(board_position.left - 5, board_position.top - 3);
		cputs("playing: PLAYER 2");
	}
	if (result == 1) {
		gotoxy(menu_position.left - 5, menu_position.top - 3);
		cputs("this place is taken, find another one");
	}
	else if (zn == 'i') {
		gotoxy(menu_position.left - 5, menu_position.top -3);
		cputs("press enter to cofirm your choice and change player or esc to quit your acction");
	}
	else if (block_move==true&&zn!='n') {
		gotoxy(menu_position.left + 5, menu_position.top - 3);
		cputs("player has to be changed");
	}	
}


void seek_and_print_stones(char stones[WIDTH_SIZE][HEIGHT_SIZE], board_position_t board_position) {
	for (int i = 0; i < WIDTH_SIZE; i++) {
		for (int j = 0; j <HEIGHT_SIZE; j++) {
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

void delete_all(char stones[WIDTH_SIZE][HEIGHT_SIZE]){
	for (int i = 0; i < WIDTH_SIZE; i++) {
		for (int j = 0; j < HEIGHT_SIZE; j++) {
			stones[i][j] = INVALID_PLAYER;
		}
	}
}

void queue(el_t** head, coord c)
{
	el_t* new_el = (el_t*)malloc(sizeof(el_t));
	if (!new_el)
		return;
	new_el->c = c;
	new_el->next = *head;
	*head = new_el;
}

coord dequeue(el_t** head){
	el_t* curr, * prev = NULL;
	curr = *head;
	while (curr->next != NULL){
		prev = curr;
		curr = curr->next;
	}
	coord result = curr->c;
	free(curr);
	if (prev){
		prev->next = NULL;
	}
	else{
		*head = NULL;
	}
	return result;
}

bool is_in_set(coord c, coord_set cset){
	for (int i = 0; i <= cset.last; i++){
		if (cset.set[i].x == c.x && cset.set[i].y == c.y)
			return true;
	}
	return false;
}

void coord_set_add(coord_set* pset, coord c){
	if (!is_in_set(c, *pset)){
		pset->set[pset->last] = c;
		pset->last++;
	}
}

int get_neighbours(coord curr, coord* neighbours){
	int num = 0;
	if (curr.x - 1 >= 0){
		neighbours[num].x = curr.x - 1;
		neighbours[num].y = curr.y;
		num++;
	}
	if (curr.y - 1 >= 0){
		neighbours[num].x = curr.x;
		neighbours[num].y = curr.y - 1;
		num++;
	}
	if (curr.x + 1 < WIDTH_SIZE){
		neighbours[num].x = curr.x + 1;
		neighbours[num].y = curr.y;
		num++;
	}
	if (curr.y + 1 < HEIGHT_SIZE){
		neighbours[num].x = curr.x;
		neighbours[num].y = curr.y + 1;
		num++;
	}
	return num;
}

void find_reach(char board[WIDTH_SIZE][HEIGHT_SIZE], coord current, coord_set* chain, coord_set* reach){
	char color = board[current.x][current.y];
	coord next_coords = current;
	el_t* frontier = NULL;
	queue(&frontier, current);
	while (frontier){
		next_coords = dequeue(&frontier);
		coord_set_add(chain, next_coords);
		coord neighbours[4];
		int n = get_neighbours(next_coords, neighbours);
		for (int i = 0; i < n; i++){
			coord xy = neighbours[i];
			if (board[xy.x][xy.y] == color && !is_in_set(xy, *chain)){//??
				queue(&frontier, xy);
			}
			else if (board[xy.x][xy.y] != color){
				coord_set_add(reach, xy);
			}
		}
	}
	return;
}

bool if_all_color(char board[WIDTH_SIZE][HEIGHT_SIZE], coord_set* set, PLAYER color)
{
	for (int i = 0; i < set->last; i++){
		coord c = set->set[i];
		if (board[c.x][c.y] != color)
			return false;
	}
	return true;
}

void remove_stones(char board[WIDTH_SIZE][HEIGHT_SIZE], coord_set* to_remove){
	for (int i = 0; i < to_remove->last; i++){
		coord c = to_remove->set[i];
		board[c.x][c.y] = INVALID_PLAYER;
	}
}

int remove_if_captured(char board[WIDTH_SIZE][HEIGHT_SIZE], coord current, coord_set* chain, coord_set* reach){
	int points = 0;
	PLAYER opposite_color = board[current.x][current.y] == PLAYER_2 ? PLAYER_1: PLAYER_2;
	if (if_all_color(board, reach, opposite_color)){
		remove_stones(board, chain);
		points = chain->last;
	}
	return points;
	gotoxy(70, 20);
	write_number(points);
}
void print_scores(menu_position_t menu_position, char stones[WIDTH_SIZE][HEIGHT_SIZE], coord current) {
	coord_set chain, reach;
	gotoxy(menu_position.left, menu_position.top);
	cputs("SCORE:");
	gotoxy(menu_position.left, menu_position.top = menu_position.top + 1);
	cputs("PLAYER 1:");
	gotoxy(menu_position.left + 25, menu_position.top);
	cputs("PLAYER 2:");
}
int check(char board[WIDTH_SIZE][HEIGHT_SIZE], coord current, menu_position_t menu_position) {
	coord_set chain, reach;
	find_reach(board, current, &chain, &reach);
	remove_if_captured(board, current, &chain, &reach);
	coord neighbours[4];
	int n = get_neighbours(current, neighbours);
	PLAYER opposite_color = board[current.x][current.y] == PLAYER_2 ? PLAYER_1 : PLAYER_2;
	for (int i = 0; i < n; i++){
		if (board[neighbours[i].x][neighbours[i].y] == opposite_color){
			coord_set n_chain, n_reach;
			find_reach(board, neighbours[i], &n_chain, &n_reach);
			remove_if_captured(board, neighbours[i], &n_chain, &n_reach);
		}
	}
	return 0;
}

int main() {
	board_position_t board_position;
	menu_position_t menu_position;
	board_size_t board_size;
	PLAYER player;
	char stones[WIDTH_SIZE][HEIGHT_SIZE];
	int result = 0;
	bool block_move=false;
	int last_x=-1;
	int last_y=-1;
	board_size.height_s=9;
	board_size.width_s=9;
	coord_set chain, reach;
	coord current{};

	int zn = 30, x = board_position.left, y = board_position.top, zero = 0;
			 //if (zn == 'a') {
			//board_size.height_s = 9;
			//board_size.width_s = 9;
		//}
			/// if (zn == 'b') {
			//board_size.height_s = 13;
			///board_size.width_s = 13;
		///}
			// if (zn == 'c') {
			//board_size.height_s = 19;
			//board_size.width_s = 19;
		//}

#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Weronika Koterba, 193127");
	_setcursortype(_NOCURSOR);
	player = PLAYER_1;

	do {
		textbackground(WHITE);
		clrscr();
		print_menu(menu_position);
		current_star_position(x, y, board_position, menu_position);
		print_mess(zn, menu_position, stones, x, y, player, board_position,result, block_move);
		print_scores(menu_position);
		print_size(menu_position);
		print_board(board_position,board_size);
		print_star(x,y);
		seek_and_print_stones(stones, board_position);
		remove_if_captured(stones, current, &chain, &reach);


		zero = 0;
		zn = getch();
		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == key_up_arrow) {
				if (y > board_position.top)y--;
			}
			else if (zn == key_down_arrow) {
				if (y < HEIGHT_SIZE-1 + board_position.top)y++;
			}
			else if (zn == key_left_arrow) {
				if (x > board_position.left)x = x - 2;
			}
			else if (zn == key_right_arrow) {
				if (x < 2 * WIDTH_SIZE-2 + board_position.left)x = x + 2;
			}
		}
		else if (zn == key_enter) {
			block_move = false;
			switch_players(&player);
			coord current_coord;
			current_coord.x = (last_x- board_position.left) / 2;
			current_coord.y = last_y - board_position.top;
			check(stones, current_coord, menu_position);
			last_x = -1;
			last_y = -1;
		}
		else if (zn == 'n') {
				delete_all(stones);
				x = board_position.left;
				y = board_position.top;
				player = PLAYER_1;

		}
		else if (zn == 'i') {
			if (block_move == false) {
				result = save_player_moves(stones, x, y, player, board_position);
				print_mess(zn, menu_position, stones, x, y, player, board_position, result,block_move);
				if (result == 0) {
					last_x = x;
					last_y = y;
					block_move = true;
				}
			}
		}
		else if (zn == key_escape) {
			block_move = false;
			if (last_x >= 0 && last_y >= 0) {
				stones[(last_x-board_position.left)/2][last_y- board_position.top] = INVALID_PLAYER;
			}
		}

	} while (zn != 'q');
	_setcursortype(_NORMALCURSOR);	
	return 0;
}
