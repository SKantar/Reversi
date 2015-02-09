#ifndef REVERSIBE_H_INCLUDED
#define REVERSIBE_H_INCLUDED
#include "Functions.h"
#include "VisualText.h"
#include "ExtraFields.h"
class ReversiBE : public BoardElement, public Timer {
protected:
   int _direction;
   int _alpha;

public:
   ReversiBE(int row, int column) : BoardElement(row,column), Timer(1), _direction(1), _alpha((_row+_col)*20+150) {


   }
   void paint(Canvas &canvas) {
       canvas.alphaRect(0,0,_width,_height,_alpha);

    }

    void step(int counter) {
       _alpha+=_direction*10;
       if(_alpha>255) { _alpha=255; _direction=-1; }
       else if( _alpha<180) { _alpha=180; _direction=1; }
       application.repaint();
    }

};



#endif // REVERSIBE_H_INCLUDED
