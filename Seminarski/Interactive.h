#ifndef INTERACTIVE_H_INCLUDED
#define INTERACTIVE_H_INCLUDED

#include <vector>
#include "utils.h"

using namespace std;

class MouseInteractive;
vector<MouseInteractive*> mouseInteractives;

class MouseInteractive {
public:
    MouseInteractive() {
        mouseInteractives.push_back(this);
    }
    ~MouseInteractive() {
        izbaci(mouseInteractives,this);
    }

    virtual void mouseDown(int buttons, int shifts, int x, int y) {}
    virtual void mouseUp(int buttons, int shifts, int x, int y) {}
    virtual void mouseDblClick(int buttons, int shifts, int x, int y) {}
    virtual void mouseMove(int buttons, int shifts, int x, int y) {}
};

class KeyboardInteractive;
vector<KeyboardInteractive*> keyboardInteractives;

class KeyboardInteractive {
public:
    KeyboardInteractive() {
        keyboardInteractives.push_back(this);
    }
    ~KeyboardInteractive() {
        izbaci(keyboardInteractives,this);
    }
    virtual void keyUp(int key, int shifts) {}
    virtual void keyDown(int key, int shifts) {}
};

#endif // INTERACTIVE_H_INCLUDED
