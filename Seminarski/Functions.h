#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "VisualElement.h"
#include "Reversi.h"
#include <sstream>
using namespace std;
#define FROM_START 100
#define SIZE 70
#define MAXN 8
#define MAXM 8

int game_board[MAXN][MAXM];
int moves = 0;
int fin = 0;
int odigrao = 0;

void init_game_board(){
    moves = 0;
    for(int i = 0; i < MAXN; i++)
        for(int j = 0; j < MAXM; j++)
            game_board[i][j] = 0;

        game_board [MAXN/2]  [MAXN/2-1] = 2;
        game_board [MAXN/2-1][MAXN/2]   = 2;
        game_board [MAXN/2-1][MAXN/2-1] = 1;
        game_board [MAXN/2]  [MAXN/2]   = 1;

}

int get_slot_status(int x, int y){
        return (x >= MAXN || y >= MAXM || x < 0 || y < 0) ? 0 : game_board[x][y];
}

int flip_count(int x, int y, int player){
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0)
            return 0;

        int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y, flip_count = 0;

        for(dir_x = -1; dir_x < 2; dir_x++){
                for(dir_y = -1; dir_y < 2; dir_y++){
                        dist = 1;
                        while(true){
                                cur_x = x + (dist * dir_x);
                                cur_y = y + (dist * dir_y);

                                if(cur_x < 0 || cur_y < 0 || cur_x >= MAXN || cur_y >= MAXM)
                                        break;

                                if(game_board[cur_x][cur_y] == 0)
                                        break;
                                if(game_board[cur_x][cur_y] == player){
                                        flip_count += dist - 1;
                                        break; }
                                if(dir_x == 0 && dir_y == 0)
                                        break;
                                dist++;
                        }
                }
        }
        return flip_count;
}

bool is_valid_move(int x, int y, int player){
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0)
            return false;

        if(get_slot_status(x,y) != 0)
            return false;

        return (flip_count(x,y,player) > 0) ? true:false;
}

void set_slot(int x, int y, int player){
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0)
            return;
        game_board[x][y] = player;
        findVisualAtXY(x*SIZE+FROM_START+1, y*SIZE + FROM_START+1)->setType(player);
}



int flip_slots(int x, int y, int player){
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0)
            return 0;

        int dir_x, dir_y, dist = 1, cur_x = x, cur_y = y, flip_count = 0;
        for(dir_x = -1; dir_x < 2; dir_x++){
                for(dir_y = -1; dir_y < 2; dir_y++){
                        dist = 1;
                        while(true){
                                cur_x = x + (dist * dir_x);
                                cur_y = y + (dist * dir_y);
                                if(cur_x < 0 || cur_y < 0 || cur_x >= 8|| cur_y >= 8){
                                        break;
                                }
                                if(game_board[cur_x][cur_y] == 0){ break; }
                                if(game_board[cur_x][cur_y] == player){
                                        for(dist--; dist > 0; dist--){
                                                cur_x = x + (dist * dir_x);
                                                cur_y = y + (dist * dir_y);
                                                set_slot(cur_x, cur_y, player); // flip slot
                                        }
                                        break;
                                }
                                if(dir_x == 0 && dir_y == 0){ break; }
                                dist++;
                        }
                }
        }
        return flip_count;
}

bool make_move(int x, int y, int player){
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0)
                return false;
        if(is_valid_move(x,y,player) == true){
                set_slot(x,y,player);
                flip_slots(x,y,player);
                return true;
        }
        else
                return false;
}

bool moves_exist(int player){
        int x,y;
        for(x = 0; x < MAXN; x++){
                for(y = 0; y < MAXM; y++){
                        if(get_slot_status(x,y) != 0){ continue; }
                        else if(flip_count(x,y,player) > 0){
                                return true;
                        }
                }
        }
        return false;
}

// counts the number of 0's on the board
int count_free_slots(){
        int x,y, cou = 0;
        for(x = 0; x < MAXN; x++){
                for(y = 0; y < MAXM; y++){
                        cou += ((get_slot_status(x,y) == 0)?1:0);
                }
        }
        return cou;
}

int count_pts(int player){
        int x,y, cou = 0;
        for(x = 0; x < MAXN; x++){
                for(y = 0; y < MAXM; y++){
                        cou += ((get_slot_status(x,y) == player)?1:0);
                }
        }
        return cou;
}
int testPobeda() {
        if(fin == 1){
            if (count_pts(1) < count_pts(2) ) return 2;
            else if (count_pts(1) > count_pts(2) ) return 1;
            else return 3;
        }
        return 0;
}

string toString(int t) {
 	ostringstream o;
	o <<endl << t;
 	return o.str();
}


#endif // FUNCTIONS_H_INCLUDED
