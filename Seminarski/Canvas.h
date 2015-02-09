#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED

#include "Application.h"
#include "Utils.h"
//#include "gdiplus/gdiplus.h"




class Font {
private:
    HDC _hdc;
    HFONT font;
    int _size;
    double _angle;
    int _orientation;
    int _style; //normal=0; italic=1; underline=2; strikeOut=4; bold=8;
    COLORREF _color;
    string _name;

    void update() {
            // vise o ovome na: http://msdn.microsoft.com/en-us/library/dd183499(VS.85).aspx
            if(_hdc==NULL) return;
            SetBkMode ( _hdc, TRANSPARENT );
            int height = -MulDiv(_size, GetDeviceCaps(_hdc, LOGPIXELSY), 72);
            if(font!=NULL) DeleteObject(font);
            font = CreateFont(height, 0, int(_angle*10), _orientation,
                           (_style&fsBold)>0 ? FW_BOLD : FW_NORMAL,  //weight
                           (_style&fsItalic)>0,                     //italic
                           (_style&fsUnderline)>0,                  //underline
                           (_style&fsStrikeOut)>0,                  //strikeout
                           EASTEUROPE_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                           DEFAULT_PITCH | FF_SWISS, _name.c_str());

            SelectObject(_hdc, font);
    }

public:
    Font() {
        _hdc=NULL;
        font=NULL;
        reset();
    }
    ~Font() {
        DeleteObject(font);
    }
    void reset() {
        _size=0;
        _angle=0;
        _orientation=0;
        _style=0;
        _color=GetSysColor(COLOR_WINDOWTEXT);
        update();
    }
    void setDC(HDC hdc) {
        _hdc=hdc;
        update();
    }
    void setName(const string& name) {
        _name=name;
        update();
    }
    const string& getName() { return _name; }

    void setColor(COLORREF color) {
        _color=color;
        SetTextColor( _hdc, color);
    }
    COLORREF getColor() {
        return _color;
    }

    void setSize(int size) {
        _size=size;
        update();
    }
    int getSize() { return _size; }

    void setAngle(double angle) {
        _angle=angle;
        update();
    }
    double getAngle() {
        return _angle;
    }

    void setStyle(int style) {
        _style=style;
        update();
    }
    int getStyle() { return _style; }
    void setItalic(bool on=true) {
        _style=setBit(_style,fsItalic,on);
        update();
    }
    bool isItalic() { return (_style&fsItalic)>0; }
    void setBold(bool on=true) {
        _style=setBit(_style,fsBold,on);
        update();
    }
    bool isBold() { return (_style&fsBold)>0; }
    void setUnderline(bool on=true) {
        _style=setBit(_style,fsUnderline,on);
        update();
    }
    bool isUnderline() { return (_style&fsUnderline)>0; }
    void setStrikeOut(bool on=true) {
        _style=setBit(_style,fsStrikeOut,on);
        update();
    }
    bool isStrikeOut() { return (_style&fsStrikeOut)>0; }
};

class Pen {
private:
    HDC    _hdc;
    HPEN   _hPen;
    COLORREF _color;
    int _style; //PS_SOLID ,PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME
    int _width;
    void update() {
        if(_hdc==NULL) return;
        if(_hPen) DeleteObject (_hPen);
        _hPen = CreatePen (_style, _width, _color);
        SelectObject (_hdc, _hPen);
    }
public:
    Pen() {
        _hdc=NULL;
        _hPen=NULL;
        reset();
    }
    ~Pen ()
    {
        if(_hPen) DeleteObject (_hPen);
    }
    void reset() {
        _width=1;
        _style=PS_SOLID;
        _color=RGB(0,0,0);
        update();
    }
    void setDC(HDC hdc) {
        _hdc=hdc;
        update();
    }
    void setColor(COLORREF color) {
        _color=color;
        update();
    }
    void setNoColor() {
        setStyle(PS_NULL);
    }
    COLORREF getColor() {
        return _color;
    }
    void setWidth(int width) {
        _width=width;
    }
    int getWidth() {
        return _width;
    }
    void setStyle(int style) {
        _style=style;
    }
    int getStyle() {
        return _style;
    }

};

class Brush {
private:
    HDC      _hdc;
    HBRUSH   _hBrush;
    COLORREF _color;
    bool _hasColor;
    void update() {
        if(_hdc==NULL) return;
        if(_hBrush) DeleteObject (_hBrush);
        LOGBRUSH t;
        t.lbStyle=_hasColor?BS_SOLID:BS_NULL;
        t.lbColor = _color;
        _hBrush = CreateBrushIndirect(&t);
        SelectObject (_hdc, _hBrush);
    }
public:
    Brush() {
        _hdc=NULL;
        _hBrush=NULL;
        reset();
    }
    ~Brush ()
    {
        if(_hBrush) DeleteObject (_hBrush);
    }
    void reset() {
        _color=GetSysColor(COLOR_WINDOW);
        update();
    }
    void setDC(HDC hdc) {
        _hdc=hdc;
        update();
    }
    void setColor(COLORREF color) {
        _color=color;
        _hasColor=true;
        update();
    }
    void setNoColor() {
        _hasColor=false;
        update();
    }
    COLORREF getColor() {
        return _color;
    }
};

HBITMAP createBitmapMask(HBITMAP source, COLORREF transparentColor) {
       //za transparentnost
       //vise o ovome na: http://www.winprog.org/tutorial/transparency.html

       HDC hdcMem, hdcMem2;
       BITMAP bm;

       GetObject(source, sizeof(BITMAP), &bm);
       HBITMAP _hMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
       hdcMem = CreateCompatibleDC(0);
       hdcMem2 = CreateCompatibleDC(0);

       SelectObject(hdcMem, source);
       SelectObject(hdcMem2, _hMask);

       SetBkColor(hdcMem, transparentColor);
       BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
       BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);
       DeleteDC(hdcMem);
       DeleteDC(hdcMem2);
       return _hMask;
}


class Bitmap {
protected:
    HDC        _hdc;
    HBITMAP    _hBitmap;
    HBITMAP    _hMask;
    COLORREF   _transparentColor;
    bool       _transparent;

    void createBitmapMask() {
       //za transparentnost
       //vise o ovome na: http://www.winprog.org/tutorial/transparency.html

       if (_hMask) ::DeleteObject (_hMask);

       HDC hdcMem, hdcMem2;
       BITMAP bm;

       GetObject(_hBitmap, sizeof(BITMAP), &bm);
       _hMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);
       hdcMem = CreateCompatibleDC(0);
       hdcMem2 = CreateCompatibleDC(0);

       SelectObject(hdcMem, _hBitmap);
       SelectObject(hdcMem2, _hMask);

       if(!_transparentColor) _transparentColor=GetPixel(hdcMem,0,0);

       SetBkColor(hdcMem, _transparentColor);
       BitBlt(hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
       BitBlt(hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);
       DeleteDC(hdcMem);
       DeleteDC(hdcMem2);
    }
public:
    Bitmap(string path="",bool transparent=false) {
       _hBitmap=NULL;
       _hMask=NULL;
       _transparentColor=0;
       _transparent=transparent;
       if(path!="") {
           load(path);
           if(transparent) setTransparent(true);
       }
    }
    ~Bitmap() {
        free();
    }

    void load (string path) {
       free ();
       _hBitmap = (HBITMAP) ::LoadImage (0, path.c_str(),
           IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
       //if (_hBitmap == 0)
       //    throw WinException ("Cannot load bitmap from file", path);
    }

    int getWidth() {
        BITMAP bm;
        GetObject(_hBitmap, sizeof(BITMAP), &bm);
        return bm.bmWidth;
    }

    int getHeight() {
        BITMAP bm;
        GetObject(_hBitmap, sizeof(BITMAP), &bm);
        return bm.bmHeight;
    }

    void setTransparent(bool transparent, COLORREF color=NULL) {
        if(!_hBitmap) return;
        _transparent=transparent;
        if(transparent) {
            _transparentColor=color;
            createBitmapMask();
        }
        else if (_hMask) ::DeleteObject (_hMask);
    }

    void free () {
        if (_hBitmap)
            ::DeleteObject (_hBitmap);
        if (_hMask)
            ::DeleteObject (_hMask);
    }
    void paintTo(HDC hdc, int x, int y) const{
        BITMAP bm;
        HDC hdcMem = CreateCompatibleDC(hdc);

        GetObject(_hBitmap, sizeof(bm), &bm);

        if(_transparent) {
           SelectObject(hdcMem, _hMask);
           BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCAND);
           SelectObject(hdcMem, _hBitmap);
           BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);
        }
        else {
           SelectObject(hdcMem, _hBitmap);
           BitBlt(hdc, x, y, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
        }

        DeleteDC(hdcMem);
    }
};

class Canvas {
protected:
    HWND  _hwnd;
    HDC   _hdc;
    HRGN  _rgn;
    bool  _ownDC;
    int _tx;
    int _ty;

    void setDC(HDC hdc) {
        if(_ownDC) DeleteDC(_hdc);
        _ownDC=false;
        if(hdc==NULL)
            _hdc=application.getHDC(); //GetDC(_hwnd);
        else
            _hdc=hdc;

        font.setDC(_hdc);
        brush.setDC(_hdc);
        pen.setDC(_hdc);
    }

    void setClipRect(int left, int top, int right, int bottom) {
        setClipRect(rect(left,top,right,bottom));
    }
    void setClipRect(RECT r) {
        if(_rgn) DeleteObject(_rgn);
        _rgn = CreateRectRgn(r.left+_tx, r.top+_ty, r.right+_tx, r.bottom+_ty);
        SelectClipRgn(_hdc, _rgn);
        _tx=r.left;
        _ty=r.top;
    }

public:
    Font  font;
    Pen pen;
    Brush brush;

    operator HDC () { return _hdc; }

    Canvas(HDC hdc=NULL) {
        _hwnd=application.getHWND();
        _rgn=NULL;
        setDC(hdc);
        reset();
    }
    ~Canvas() {
        if(_ownDC) DeleteDC(_hdc);
        if(_rgn) DeleteObject(_rgn);
    }
    void reset() {
        _tx=0;
        _ty=0;
        if(_rgn) DeleteObject(_rgn);
        _rgn=NULL;
        brush.reset();
        pen.reset();
        font.reset();
    }

     HDC getDC() const {
        return _hdc;
    }
    int getTx() const {
        return _tx;
    }
    int getTy() const {
        return _ty;
    }

   /* void clear() {
        int w=GetDeviceCaps(_hdc,HORZRES);
        int h=GetDeviceCaps(_hdc,VERTRES);

        COLORREF color=GetSysColor(COLOR_WINDOW);
        RECT r=rect(0,0,w,h);
        FillSolidRect(rect, backgroundColor);
    }*/

    void point (int x, int y)
    {
        ::SetPixel (_hdc, x+_tx, y+_ty, pen.getColor());
    }

    void moveTo (int x, int y)
    {
        ::MoveToEx (_hdc, x+_tx, y+_ty, 0);
    }

    void line ( int x1, int y1, int x2, int y2 )
    {
        MoveToEx (_hdc, x1+_tx, y1+_ty, 0);
        LineTo (_hdc, x2+_tx, y2+_ty);
    }

    void rectangle (int left, int top, int right, int bottom)
    {
        // draw rectangle using current pen
        // and fill it using current brush
        ::Rectangle (_hdc, left+_tx, top+_ty, right+_tx, bottom+_ty);
    }

    void roundRect(int left, int top, int right, int bottom, int cornerX, int cornerY)
    {
        // draw rectangle using current pen
        // and fill it using current brush
        ::RoundRect (_hdc, left+_tx, top+_ty, right+_tx, bottom+_ty, cornerX, cornerY);
    }

    void alphaRect(int left, int top, int right, int bottom, int alpha);

    void getTextSize (int & cxChar, int & cyChar)
    {
        TEXTMETRIC tm;
        GetTextMetrics (_hdc, & tm);
        cxChar = tm.tmAveCharWidth;
        cyChar = tm.tmHeight + tm.tmExternalLeading;
    }

    void text (int x, int y, const string& text)
    {
        TextOut ( _hdc, x+_tx, y+_ty, text.data() , text.size() );
    }
    void textInRect(RECT r, const string& text) {
        DrawText(_hdc,text.c_str(),-1,&r,DT_LEFT);
    }
    void drawBitmap(int x, int y, const Bitmap& bitmap) {
        bitmap.paintTo(_hdc,x+_tx,y+_ty);
    }


    friend class Application;

};



class MemoryCanvas: public Canvas {
protected:
    HBITMAP hBitmap;
    int _width;
    int _height;
    void createBitmap(HDC hdc, int width, int height) {
        _hdc = CreateCompatibleDC(hdc);
        SetBkMode ( _hdc, TRANSPARENT );
        hBitmap = CreateCompatibleBitmap (hdc, width, height);
        _width=width; _height=height;
        SelectObject(_hdc, hBitmap);
        setDC(_hdc);
    }
public:
    MemoryCanvas(const Canvas& c, int width, int height, bool transparent=true) : Canvas(NULL) {
        HDC hdc=c.getDC();
        createBitmap(hdc,width,height);
        if(transparent) BitBlt(_hdc, 0, 0, _width, _height, hdc, c.getTx(), c.getTy(), SRCCOPY);
    }
    MemoryCanvas(HDC hdc, int width, int height) : Canvas(NULL){
        createBitmap(hdc,width,height);
        COLORREF backColor=application.getBackgroundColor();
        setDC(_hdc);
        brush.setColor(backColor);
        pen.setColor(backColor);
        Rectangle(_hdc,0,0,width,height);
        reset();
    }

    ~MemoryCanvas() {
        DeleteObject (hBitmap);
        DeleteDC (_hdc);
    }

    void draw(HDC hdc, int left=0, int top=0) {
        BitBlt(hdc, left, top, _width, _height, _hdc, 0, 0, SRCCOPY);
    }
    void draw(Canvas c, int left=0, int top=0) {
        draw(c.getDC(),left+c.getTx(),top+c.getTy());
    }
    void drawAlpha(HDC hdc, int alpha, int left=0, int top=0) {
        BLENDFUNCTION blender;
        blender.BlendOp=AC_SRC_OVER;
        blender.BlendFlags=0;
        blender.SourceConstantAlpha=alpha;
        blender.AlphaFormat=0;
        AlphaBlend(hdc,left,top,_width,_height,_hdc,0,0,_width,_height,blender);
    }
    void drawAlpha(Canvas c, int alpha, int left=0, int top=0) {
        drawAlpha(c.getDC(),alpha,left+c.getTx(),top+c.getTy());
    }


};

void Canvas::alphaRect(int left, int top, int right, int bottom, int alpha) {
       int w=right-left, h=bottom-top;
       MemoryCanvas mc(*this,w,h,false);
       mc.brush.setColor(brush.getColor());
       mc.pen.setNoColor();
       mc.rectangle(0,0,w,h);
       mc.drawAlpha(*this,alpha,left,top);
}



#endif // CANVAS_H_INCLUDED
