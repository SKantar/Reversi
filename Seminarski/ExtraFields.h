#ifndef EXTRAFIELDS_H_INCLUDED
#define EXTRAFIELDS_H_INCLUDED
#include "VisualText.h"
#include "Functions.h"
class Points{
public:
    VisualText* player1;
    VisualText* player2;
    void init(){
        player1=new VisualText(toString(count_pts(1)),taCenter);
        player1->setDimension(50,50);
        player1->setPosition(20,100);
        player1->setAlpha(0);
        player1->setBackColor(RGB(20,20,20));
        player2=new VisualText(toString(count_pts(2)),taCenter);
        player2->setDimension(50,50);
        player2->setPosition(690,100);
        player2->setAlpha(0);
    }
public:
    Points(){
        init();
    }

    void setPts(){
        player1->setText(toString(count_pts(1)));
        player2->setText(toString(count_pts(2)));
    }

};


#endif // EXTRAFIELDS_H_INCLUDED
