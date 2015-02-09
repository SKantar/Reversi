#ifndef DRAGNDROP_H_INCLUDED
#define DRAGNDROP_H_INCLUDED

#include "VisualElement.h"

class DropTarget;

class DragElement : virtual public VisualElement, virtual public MouseInteractive {
private:
    int _startX;
    int _startY;
    int px,py;
    bool _isDragging;
    DropTarget* _target;

protected:
    void dropElementAt(int x, int y);
    DropTarget* findDropTargetAtXY(int x, int y);

public:
    DragElement() {
        px=-1;py=-1;
        _isDragging=false;
        _target=NULL;
    }

    bool isDragging() {
        return _isDragging;
    }

    virtual bool isMovable() {
        return true;
    }

    DropTarget* getTarget() {
        return _target;
    }

    virtual bool acceptTarget(DropTarget *t) {
        return true;
    }

    void paint(Canvas &c) {
        if(_isDragging) {
          MemoryCanvas mc(c,_width,_height);
          VisualElement::paint(mc);
          mc.drawAlpha(c,180);
        }
        else VisualElement::paint(c);
    }

    void mouseDown(int buttons, int shifts, int x, int y) {
        if(!isMovable()) return;
        if(!(buttons & mbLeft)) return;
        _isDragging=true;
        toFront();
        px=x; py=y;
        _startX=_left;
        _startY=_top;
        application.repaint();
    }
    void mouseUp(int buttons, int shifts, int x, int y) {
        if(!_isDragging) return;
        _isDragging=false;
        dropElementAt(x,y);
        application.repaint();
    }
    void mouseMove(int buttons, int shifts, int x, int y) {
        if(!_isDragging) return;
        _left+=x-px;
        _top+=y-py;
        px=x;py=y;
        application.repaint();
    }
    friend class DropTarget;

};

class DropTarget;
vector<DropTarget*> dropTargets;

class DropTarget : virtual public VisualElement {
public:
    vector<DragElement*> elements;
    DropTarget() {
       dropTargets.push_back(this);
    }
    virtual ~DropTarget() {
       izbaci(dropTargets,this);
    }
    virtual void addElement(DragElement *e) {
        if(!e) return;
        DropTarget* oldT=e->getTarget();
        if(oldT==this) return;
        if(oldT) oldT->removeElement(e);
        e->_target=this;
        elements.push_back(e);
        e->setPosition(_left,_top);
    }
    void removeElement(DragElement *e) {
        izbaci(elements,e);
    }
    virtual bool acceptElement(DragElement *e) {
        return true;
    }
    bool isEmpty() {
	    return elements.size()==0;
	}
};

DropTarget* DragElement::findDropTargetAtXY(int x, int y) {
    //VisualElement *v;
    DropTarget *t;
    for(vector<VisualElement*>::reverse_iterator it=visualElements.rbegin(); it!=visualElements.rend(); it++)
        if(*it!=this && (t=cast(DropTarget,**it)) && pointInRect(x,y,(*it)->getRect()))
           return t;
    return NULL;
}


void DragElement::dropElementAt(int x, int y) {
    DropTarget* t=findDropTargetAtXY(x,y);
    if(!acceptTarget(t))
        setPosition(_startX,_startY);
    else if(!t) {
        if(_target) {_target->removeElement(this); _target=NULL;}
        return;
    }
    else if( t->acceptElement(this))
        t->addElement(this);
    else
        setPosition(_startX,_startY);
}


#endif // DRAGNDROP_H_INCLUDED
