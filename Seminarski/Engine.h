#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include <iostream>
#include "Functions.h"
#include "AIPlayer.h"
using namespace std;
class God :virtual public VisualElement, virtual public MouseInteractive {
private:
    AIPlayer AIplayer;
    void mouseDown(int buttons, int shifts, int x, int y) {
        int px,py;
        px = (x-FROM_START)/SIZE;
        py = (y-FROM_START)/SIZE;

        while(!moves_exist(moves%2+1)){
            moves++;
            odigrao = 1;
            if(!moves_exist(moves%2+1)){
                fin = 1;

                break;
            }
            else {
               AIplayer.play(moves%2 + 1);
               odigrao = 0;
               if(count_free_slots() == 0) fin = 1;
               if(count_pts(1) == 0 || count_pts(2) == 0) fin = 1;
               currentGame()->nextMove();
               moves++;
            }
        }


        if(make_move(px,py,moves%2+1)){
            currentGame()->nextMove();
            odigrao = 1;
            moves++;
        }
        if(count_free_slots() == 0) fin = 1;
        if(count_pts(1) == 0 || count_pts(2) == 0) fin = 1;
        application.repaint();

    }


    void mouseUp(int buttons, int shifts, int x, int y) {

    if(!moves_exist(moves%2+1)){
            moves++;
            if(!moves_exist(moves%2+1)){
                fin = 1;
            }
    }

        if(moves%2+1 == 2 && odigrao){
            AIplayer.play(moves%2+1);
            currentGame()->nextMove();
            moves++;
            odigrao = 0;
        }
        if(count_free_slots() == 0) fin = 1;
        if(count_pts(1) == 0 || count_pts(2) == 0) fin = 1;
        application.repaint();

    }
    void mouseMove(int buttons, int shifts, int x, int y) {
            //this->setType(3);
    }

};

#endif // ENGINE_H_INCLUDED
