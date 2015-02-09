#ifndef TESTELEMENT_H_INCLUDED
#define TESTELEMENT_H_INCLUDED

#include "VisualImage.h"
#include "DragNDrop.h"

class TestElement: virtual public VisualImage, public DragElement {
public:
    TestElement(): VisualImage("KartaH5.bmp"){
    }

    void paint(Canvas &canvas) {
        /*if(isDragging()) {
          MemoryCanvas mc(canvas,_width,_height);
          canvas.drawBitmap(0,0,bmp);
          mc.drawAlpha(canvas,180);
        }
        else */canvas.drawBitmap(0,0,bmp);
    }


};

#endif // TESTELEMENT_H_INCLUDED
