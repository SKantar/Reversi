#ifndef REVERSI_H_INCLUDED
#define REVERSI_H_INCLUDED
#include "Functions.h"
#include "ReversiBE.h"
#include "ExtraFields.h"
#include "Engine.h"
#include <iostream>
using namespace std;

class Reversi : public BasicGame{

private:
   Bitmap BlackImg;
   Bitmap WhiteImg;

   Board<ReversiBE> board;
   Points p;

public:
    Reversi() {
        BlackImg.load("crni.bmp");
        BlackImg.setTransparent(true);
        WhiteImg.load("beli.bmp");
        WhiteImg.setTransparent(true);
        board.setSize(MAXN,MAXM);
        board.setLeft(FROM_START);
        board.setTop(FROM_START);
        board.setWidth(MAXN * SIZE);
        board.setHeight(MAXM * SIZE);
        init_game_board();
        startGame();

   }

   void testVictoryCondition() {
       p.setPts();
        switch(testPobeda()) {
            case 3: endGame(NULL); break;
            case 1:
                {Player p("Black player");
                endGame(&p);
                break;}
            case 2:
                {Player p("White player");
                endGame(&p);
                break;}
        }
   }

   friend class ReversiFigura;
};
Reversi reversi;
class ReversiFigura: public God{
public:

   ReversiFigura(int iks, int x, int y) {
	   setType(iks);
       setPosition(x*SIZE+FROM_START,y*SIZE+FROM_START);
       setDimension(reversi.WhiteImg.getWidth(), reversi.WhiteImg.getHeight());
   }
   void paintFigura(Canvas& c) {
        if(getType() == 0) return;
        if(getType() == 1) c.drawBitmap(0,0,reversi.BlackImg);
        if(getType() == 2) c.drawBitmap(0,0,reversi.WhiteImg);
   }
   void paint(Canvas &canvas) {
         paintFigura(canvas);

   }
};

#endif // REVERSI_H_INCLUDED
