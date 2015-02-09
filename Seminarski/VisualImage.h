#ifndef VISUALIMAGE_H_INCLUDED
#define VISUALIMAGE_H_INCLUDED

#include "VisualElement.h"
#include "Canvas.h"

class VisualImage : virtual public VisualElement {
protected:
   Bitmap bmp;

public:
   VisualImage(string fileName="") {
      if(fileName!="") load(fileName);
   }
   void load(string fileName) {
      bmp.load(fileName);
      setDimension(bmp.getWidth(),bmp.getHeight());
   }
   void paint(Canvas& canvas) {
        VisualElement::paint(canvas);
        canvas.drawBitmap(0,0,bmp);
   }


};

#endif // VISUALIMAGE_H_INCLUDED
