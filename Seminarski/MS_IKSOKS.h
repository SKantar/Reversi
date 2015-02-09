#ifndef MS_IKSOKS_H_INCLUDED
#define MS_IKSOKS_H_INCLUDED
#include "VisualText.h"
#include "BasicGame.h"
#include "Canvas.h"
#include "Board.h"

class IksOksBE : public BoardElement, public Timer {
protected:
   int _alpha;
   int _direction;
public:
   IksOksBE(int row, int column) : BoardElement(row,column), Timer(1), _direction(1), _alpha((_row+_col)*20+150) {}
   void paint(Canvas &canvas) {
       //canvas.brush.setColor(_backColor);
       canvas.alphaRect(0,0,_width,_height,_alpha);
       //MemoryCanvas mc(canvas,_width,_height);
       //VisualElement::paint(mc);
       //mc.drawAlpha(canvas,_alpha,_left,_top);
       //canvas.brush.setNoColor();
       //canvas.rectangle(0,0,_width,_height);
    }
    void step(int counter) {
       _alpha+=_direction*10;
       if(_alpha>255) { _alpha=255; _direction=-1; }
       else if( _alpha<180) { _alpha=180; _direction=1; }

       application.repaint();
    }
};


class IksOks : public BasicGame {
private:
   Bitmap iksImg;//("house1.bmp",true);
   Bitmap oksImg;//("house2.bmp",true);
   Board<IksOksBE> board;


   int getFieldCode(int i, int j);


   int testPobeda() {
        //rows

		for(int i=0; i<3; i++) {
		   int s=0;
		   for(int j=0; j<3; j++)
			  s+=getFieldCode(i,j);
           if (abs(s)==3) return s;
		}
		//columns
		for(int i=0; i<3; i++) {
		   int s=0;
		   for(int j=0; j<3; j++)
			  s+=getFieldCode(j,i);
		   if (abs(s)==3) return s;
		}
		//diag1
		int s=0;
		for(int i=0; i<3;i++)
			s+=getFieldCode(i,i);
		if (abs(s)==3) return s;
		//diag2
		s=0;
		for(int i=0; i<3;i++)
			s+=getFieldCode(i,2-i);
		if (abs(s)==3) return s;

		int t=0;
		for(int i=0; i<3; i++)
		   for(int j=0; j<3; j++)
			  if(getFieldCode(i,j)!=0) t++;

		return t==9?1:0;
   }


public:
    IksOks() {
       iksImg.load("crni.bmp");
       iksImg.setTransparent(true);
       oksImg.load("beli.bmp");
       oksImg.setTransparent(true);
       board.setSize(3,3);
       board.setLeft(250);
       board.setTop(100);
       board.setWidth(198);
       board.setHeight(198);
       startGame();
   }

   void testVictoryCondition() {
       cout<<"kurac"<<endl;
        switch(testPobeda()) {
            case 1: endGame(NULL); break;
            case 3:
                {Player p("First");
                endGame(&p);
                break;}
            case -3:
                {Player p("Second");
                endGame(&p);
                break;}
        }
   }

   friend class IksOksFigura;
};

IksOks iksOks;

class IksOksFigura: public DragElement {
private:
   bool _iks;
public:
   bool isIks() {
       return _iks;
   }
   IksOksFigura(bool iks, int x, int y) {
	   _iks=iks;
       setPosition(x,y);
       setDimension(iksOks.iksImg.getWidth(), iksOks.iksImg.getHeight());
   }
   void paintFigura(Canvas& c) {
        if(_iks) c.drawBitmap(0,0,iksOks.iksImg);
          else   c.drawBitmap(0,0,iksOks.oksImg);
   }
   void paint(Canvas &canvas) {
        if(isDragging()) {
          MemoryCanvas mc(canvas,_width,_height);
          paintFigura(mc);
          mc.drawAlpha(canvas,180);
        }
        else paintFigura(canvas);
   }
   bool isMovable() {
       return !getTarget() && currentGame()->isActive();
   }
   bool acceptTarget(DropTarget *t) {
        if(!(is_a(BoardElement,*t) && t->elements.size()==0 && !getTarget())) return false;
        currentGame()->nextMove();
        return true;
   }

};

int IksOks::getFieldCode(int i, int j) {
		BoardElement *be=board.getElement(i,j);
		if (be->isEmpty()) return 0;
		IksOksFigura *f=cast(IksOksFigura,*(be->elements[0]));
		return f->isIks()?1:-1;
}















#endif // MS_IKSOKS_H_INCLUDED
