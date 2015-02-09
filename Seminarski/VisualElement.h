#ifndef VISUALELEMENT_H_INCLUDED
#define VISUALELEMENT_H_INCLUDED

#include "Application.h"
#include "Interactive.h"
#include "Utils.h"

#include <vector>

using namespace std;

class VisualElement;
vector<VisualElement*> visualElements;

class VisualElement {
protected:
   int _top;
   int _left;
   int _height;
   int _width;
   int _type;
   bool _visible;
   COLORREF _backColor;
public:
   VisualElement() {
       _top=0;
       _left=0;
       _width=100;
       _height=70;
       _backColor=GetSysColor(COLOR_WINDOW);
       _type = 0;
       visualElements.push_back(this);
   }
   virtual ~VisualElement() {
       izbaci(visualElements,this);
   }
   virtual void paint(Canvas& canvas) {
       canvas.brush.setColor(_backColor);
       canvas.rectangle(0,0,_width,_height);
   }
   virtual void setTop(int top) { _top=top; application.repaint(); }
   virtual void setLeft(int left) { _left=left; application.repaint(); }
   virtual void setWidth(int width) { _width=width>0? width:0; application.repaint(); }
   virtual void setHeight(int height) { _height=height>0? height:0; application.repaint(); }

   int getTop() { return _top; }
   int getLeft() { return _left; }
   int getWidth() { return _width; }
   int getHeight() { return _height; }

   int getType() const { return _type; }
   void setType(int x) { _type = x; }

   virtual void toFront() {
       pomeriNaKraj(visualElements,this);
   }
   virtual void toBack() {
       pomeriNaPocetak(visualElements,this);
   }

   virtual void setPosition(int left, int top) {
       setTop(top); setLeft(left);
   }
   virtual void setDimension(int width, int height) {
       setWidth(width); setHeight(height);
   }
   RECT getRect() {
       return rect(_left,_top, _left+_width, _top+_height);
   }
   bool isVisible() { return _visible; }
   virtual void setVisible(bool visible) { _visible = visible; application.repaint(); }
   virtual void setBackColor(COLORREF color) {
       _backColor=color;
       application.repaint();
   }
};

VisualElement* findVisualAtXY(int x, int y, VisualElement* from=NULL) {

    int p=visualElements.size()-1;
    if(from)
       for(int i=p; i>=0 ; i--)
           if(visualElements[i]==from) { p=i-1; break; }

    for(int i=p; i>=0; i--)
       if(pointInRect(x,y,visualElements[i]->getRect()))
           return visualElements[i];

    return NULL;
}

#endif // VISUALELEMENT_H_INCLUDED
