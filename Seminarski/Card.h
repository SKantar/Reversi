#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include "VisualImage.h"
#include "DragNDrop.h"

Bitmap cardBack("karta_back.bmp");


class Card: public VisualImage, public DragElement {
protected:
    char _sign;
    int  _number;
    bool _isTurned;
    void paintCard(Canvas& c) {
        if(_isTurned) c.drawBitmap(0,0,cardBack);
          else        c.drawBitmap(0,0,bmp);
    }
public:
    Card(char sign, int number):
       VisualImage( string("karta")+sign+toString(number)+".bmp" ),
       _isTurned(false),
       _sign(sign),
       _number(number)
    {}
    void paint(Canvas &canvas) {
        if(isDragging()) {
          MemoryCanvas mc(canvas,_width,_height);
          paintCard(mc);
          mc.drawAlpha(canvas,180);
        }
        else paintCard(canvas);
    }
    void mouseDblClick(int buttons, int shifts, int x, int y) {
        flipCard();
    }
    void flipCard() {
        _isTurned=!_isTurned;
        application.repaint();
    }
    void turnCard(bool down=false) {
        if(_isTurned!=down) flipCard();
    }
    char getSign() {
        return _sign;
    }
    int getNumber() {
        return _number;
    }
};

class CardDeck : public DropTarget {
public:
    bool acceptElement(DragElement *e) {
        return is_a(Card,*e);
    }
    CardDeck() {
        setWidth(cardBack.getWidth());
        setHeight(cardBack.getHeight());

    }
    void addElement(DragElement *e) {
        DropTarget::addElement(e);
        if(e) e->setPosition(_left,_top);
    }
    void paint(Canvas& canvas) {
        MemoryCanvas mc(canvas,_width,_height);
        mc.pen.setColor(RGB(255,255,255));
        mc.brush.setColor(RGB(0,0,0));
        mc.roundRect(0,0,_width,_height,6,6);
        mc.drawAlpha(canvas,160);
    }
    void shuffle() {
        random_shuffle ( elements.begin(), elements.end() );
    }
};

#endif // CARD_H_INCLUDED
