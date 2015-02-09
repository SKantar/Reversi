#ifndef AIPLAYER_H_INCLUDED
#define AIPLAYER_H_INCLUDED
#include "Functions.h"
#include <time.h>
#define corner_value 6
class AIPlayer: public Player{
public:
    AIPlayer() : Player("Computer"){}

    int rate_move(int x, int y, int player){
        int eval = 0;
        if(x >= MAXN || y >= MAXM || x < 0 || y < 0) return 0;
        if(get_slot_status(x,y) != 0) return 0;
        if(is_valid_move(x,y, player) == 0) return 0;

        int temp = flip_count(x,y, player);

        if((x == 0) || (x == (8 - 1))){
                temp +=  corner_value;
        }
        if((y == 0) || (y == (8 - 1))){
                temp +=  corner_value;
        }
        if((x == 1) || (x == (8 - 2))){
                temp -=  corner_value;
        }
        if((y == 1) || (y == (8 - 2))){
                temp -=  corner_value;
        }
        if( x == 1 && (y == 1 || y == 6))
                temp -= corner_value;

        if( y == 1 && (x == 1 || x == 6))
                temp -= corner_value;

        if( x == 0 && (y == 1 || y == 6))
                temp -= 5;
        if(y == 0 && (x == 1 || x == 6))
                temp-=5;
        if(y == 0 && (x == 0 || x == 7))
                temp +=corner_value;

        if(x == 0 && (y == 0 || y == 7))
                temp +=corner_value;

        if(temp > eval){
                eval = temp;
        }

        if(eval < 1){ eval = 1; }

        return eval;
}


void play(int player){
        int x = 0,y = 0, cur_max = 0, best_x = 0, best_y = 0, temp = 0, rand_n = 0;
        srand(time(NULL));

        for(x = 0; x < SIZE; x++){
                for(y = 0; y < SIZE; y++){
                        temp = rate_move(x,y,player);
                        if(temp > cur_max){
                                cur_max = temp;
                                best_x = x;
                                best_y = y;
                        }else if(temp == cur_max){
                                rand_n = rand() % 2;
                                if(rand_n  == 1){
                                        best_x = x;
                                        best_y = y;
                                }
                        }
                }
        }
        for(int i = 0 ; i < 3500; i++)
            for(int j = 0; j < 10000; j++)
        make_move(best_x,best_y, player);
}



};


#endif // AIPLAYER_H_INCLUDED
