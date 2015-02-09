#ifndef VISUALTEXT_H_INCLUDED
#define VISUALTEXT_H_INCLUDED

#include "visualelement.h"



class VisualText : public VisualElement {
private:
    string _text;
    int _textAlign;
    int _alpha;
    void paintText(Canvas& canvas) {
        int x,y,th,tw;
        canvas.getTextSize(tw,th);
        tw*=_text.size();
        if(taCenter & _textAlign) x=(_width-tw)/2;
        else if(taRight & _textAlign) x=_width-tw;
        else x=10;
        if(taVCenter & _textAlign) y=(_height-th)/2;
        else if(taBottom & _textAlign) y=_height-th;
        else y=10;
        canvas.text(x,y,_text);
    }
public:
    VisualText(string text="", int textAlign=taTop+taLeft) {
        _text=text;
        _textAlign=textAlign;
    }
    void paint(Canvas& canvas) {
        if(_alpha>0)
            canvas.alphaRect(0,0,_width,_height,_alpha);
        else VisualElement::paint(canvas);
        paintText(canvas);
    }
    void setText(string text) {
        _text=text;
        application.repaint();
    }
    void setAlpha(int alpha) {
        _alpha=alpha;
        application.repaint();
    }
};

#endif // VISUALTEXT_H_INCLUDED
