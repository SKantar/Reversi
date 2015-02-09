#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <string>

#define WM_TESTVC WM_USER+400

using namespace std;

/*  Make the class name into a global variable  */
char szClassName[ ] = "ApplicationClassName";
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

enum { fsNormal=0, fsItalic=1, fsUnderline=2, fsStrikeOut=4, fsBold=8 };
enum { mbLeft=1, mbMiddle=2, mbRight=4 };
enum { ssShift=1, ssCtrl=2, ssAlt=4 };
enum { taLeft=1, taRight=2, taHCenter=3, taTop=4, taBottom=8, taVCenter=12, taCenter=15 };


class MouseInteractive;
class KeyboardInteractive;
class BasicGame;


class Application {
private:
     HWND hwnd;
     HDC hdc;
     COLORREF _backgroundColor;
     MouseInteractive* _capturedMouse;
     KeyboardInteractive* _hasFocus;
     BasicGame* _game;
public:

     Application() {
         hwnd=0;
         hdc=0;
         _backgroundColor=GetSysColor(COLOR_APPWORKSPACE);
         _capturedMouse=NULL;
         _hasFocus=NULL;
         _game=NULL;
     }

     ~Application() {
         if(hwnd) KillTimer(hwnd,1);
     }

     HWND getHWND() {
         return hwnd;
     }
     HDC getHDC() {
         return hdc;
     }

     void setGame(BasicGame* game) {
         _game=game;
     }

     BasicGame* getCurrentGame() {
         return _game;
     }

     void initialize(HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow) {

        WNDCLASSEX wincl;        /* Data structure for the windowclass */

        /* The Window structure */
        wincl.hInstance = hThisInstance;
        wincl.lpszClassName = szClassName;
        wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
        wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
        wincl.cbSize = sizeof (WNDCLASSEX);

        /* Use default icon and mouse-pointer */
        wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL;                 /* No menu */
        wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
        wincl.cbWndExtra = 0;                      /* structure or the window instance */
        /* Use Windows's default colour as the background of the window */
        wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

        /* Register the window class, and if it fails quit the program */
        if (!RegisterClassEx (&wincl))
           return ;

        /* The class is registered, let's create the program*/
        hwnd = CreateWindowEx (
              0,                   /* Extended possibilites for variation */
              szClassName,         /* Classname */
              "Application",       /* Title Text */
              WS_OVERLAPPEDWINDOW, /* default window */
              CW_USEDEFAULT,       /* Windows decides the position */
              CW_USEDEFAULT,       /* where the window ends up on the screen */
              544,                 /* The programs width */
              375,                 /* and height in pixels */
              HWND_DESKTOP,        /* The window is a child-window to desktop */
              NULL,                /* No menu */
              hThisInstance,       /* Program Instance handler */
              NULL                 /* No Window Creation data */
        );
        hdc=GetDC(hwnd);
        /* Make the window visible on the screen */
        ShowWindow (hwnd, nCmdShow);
        SetTimer(hwnd, 1, 40, (TIMERPROC) NULL);
    }

    void run() {
        MSG messages;
        /* Run the message loop. It will run until GetMessage() returns 0 */
        while (GetMessage (&messages, NULL, 0, 0))
        {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }

    }

    void setTitle(const string& title) {
        SetWindowText(hwnd,title.c_str());
    }

    string getTitle() {
        char buffer[1000];
        GetWindowText(hwnd,buffer,1000);
        return string(buffer);
    }

    void setPosition(int left, int top) {
        int l,r,t,b;
        getBounds(l,t,r,b);
        setBounds(left,top,r,b);
    }

    void setDimensions(int width, int height) {
        int l,r,t,b;
        getBounds(l,t,r,b);
        setBounds(l,t,l+width<0?0:width,t+height<0?0:height);
    }

    void getDimensions(int& width, int &height) {
        RECT r=getBoundsRect();
        width=r.right-r.left;
        height=r.bottom-r.top;
    }

    int getWidth() {
        int width, height;
        getDimensions(width,height);
        return width;
    }
    int getHeight() {
        int width, height;
        getDimensions(width,height);
        return height;
    }

    void getBounds(int &left, int &top, int &right, int &bottom) {
        RECT r=getBoundsRect();
        left=r.left;
        top=r.top;
        right=r.right;
        bottom=r.bottom;
    }

    RECT getBoundsRect() {
        RECT r;
        GetClientRect(hwnd, &r);
        return r;
    }

    void setBounds(int left,int top, int right, int bottom) {
        SetWindowPos(hwnd, NULL, left, top, right, bottom, SWP_NOZORDER);
    }

    void setBackgroundColor(COLORREF color) {
        _backgroundColor=color;
    }
    COLORREF getBackgroundColor() {
        return _backgroundColor;
    }

    void paint();

    void mouseMove(int buttons, int shifts, int x, int y) ;
    void mouseUp(int buttons, int shifts, int x, int y) ;
    void mouseDown(int buttons, int shifts, int x, int y) ;
    void mouseDblClick(int buttons, int shifts, int x, int y) ;

    void keyUp(int key, int shifts);
    void keyDown(int key, int shifts);

    void processTimers();

    void repaint() {
       InvalidateRect(hwnd,NULL,true);
    }

    MouseInteractive* capturedMouse() {
        return _capturedMouse;
    }
    KeyboardInteractive* hasFocus() {
        return _hasFocus;
    }

    friend class BasicGame;
};

Application application;

#include "Canvas.h"
#include "VisualElement.h"
#include "Interactive.h"
#include "BasicGame.h"
#include "Timer.h"



void Application::paint() {
    PAINTSTRUCT psPaint;
    HDC hdc = BeginPaint( hwnd, &psPaint );


    RECT rect;
    GetClientRect(hwnd, &rect);

    MemoryCanvas c(hdc,rect.right,rect.bottom);

    COLORREF backColor=0xFE000000+ application.getBackgroundColor();
    c.brush.setColor(backColor);
    c.pen.setColor(backColor);
    Rectangle(c,0,0,rect.right,rect.bottom);

    //VisualElement* v;

    for(vector<VisualElement*>::iterator it=visualElements.begin(); it!=visualElements.end(); it++) {
       c.reset();
       c.setClipRect((*it)->getRect());
       (*it)->paint(c);
    }

    //BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);
    //BitBlt(hdc, 0, 0, rect.right, rect.bottom, c.getDC(), 0, 0, SRCCOPY);
    c.draw(hdc);
    //c.drawAlphaToDC(hdc,50);

    EndPaint (hwnd, &psPaint);

    //DeleteObject (hBitmap);
    //DeleteDC (hdcMem);
}

void Application::mouseMove(int buttons, int shifts, int x, int y) {
    if(_capturedMouse) {
        _capturedMouse->mouseMove(buttons,shifts,x,y);
        return;
    }
    VisualElement *v=findVisualAtXY(x,y);
    MouseInteractive *m=cast(MouseInteractive,*v);
    if (m) m->mouseMove(buttons,shifts,x,y);
}

void Application::mouseUp(int buttons, int shifts, int x, int y) {
    if(_capturedMouse) {
        _capturedMouse->mouseUp(buttons,shifts,x,y);
        _capturedMouse=NULL;
        return;
    }
    VisualElement *v=findVisualAtXY(x,y);
    MouseInteractive *m=cast(MouseInteractive,*v);
    if (m) m->mouseUp(buttons,shifts,x,y);
}

void Application::mouseDown(int buttons, int shifts, int x, int y) {
    VisualElement *v=findVisualAtXY(x,y);
    MouseInteractive *m=cast(MouseInteractive,*v);
    if (m!=NULL) {
        _capturedMouse=m;
        m->mouseDown(buttons,shifts,x,y);
    }
}

void Application::mouseDblClick(int buttons, int shifts, int x, int y) {
    VisualElement *v=findVisualAtXY(x,y);
    MouseInteractive *m=cast(MouseInteractive,*v);
    if (m) m->mouseDblClick(buttons,shifts,x,y);
}

void Application::keyUp(int key, int shifts) {
    for(vector<KeyboardInteractive*>::iterator it=keyboardInteractives.begin(); it!=keyboardInteractives.end(); it++)
        (*it)->keyUp(key,shifts);

}
void Application::keyDown(int key, int shifts) {
    for(vector<KeyboardInteractive*>::iterator it=keyboardInteractives.begin(); it!=keyboardInteractives.end(); it++)
        (*it)->keyDown(key,shifts);

}

void Application::processTimers() {
    for(vector<Timer*>::iterator it=timers.begin(); it!=timers.end(); it++)
        (*it)->processTimerEvent();
}


int getButtons(int wParam, int def=0) {
    int r=0;
    if( wParam & MK_LBUTTON) r+=mbLeft;
    if( wParam & MK_MBUTTON) r+=mbMiddle;
    if( wParam & MK_RBUTTON) r+=mbRight;
    if(r==0) return def;
    return r;
}

int getShifts(int wParam) {
    int r=0;
    if( wParam & MK_CONTROL) r+=ssCtrl;
    if( wParam & MK_SHIFT) r+=ssShift;
    if( wParam & MK_ALT) r+=ssAlt;
    return r;
}

int getShifts() {
    const int pressed=0x8000;
    int r=0;
    if(GetKeyState(VK_SHIFT) & pressed) r+=ssShift;
    if(GetKeyState(VK_CONTROL) & pressed) r+=ssCtrl;
    if(GetKeyState(VK_MENU) & pressed) r+=ssAlt;
    return r;
}


BasicGame* currentGame() {
    return application.getCurrentGame();
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:{
        HMENU hMenubar = CreateMenu();
        HMENU hFile = CreateMenu();
        HMENU hOptions = CreateMenu();
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFile, "File");
        AppendMenu(hMenubar, MF_POPUP, NULL, "Edit");
        AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hOptions, "Options");

        AppendMenu(hFile, MF_STRING, NULL, "Exit");

        SetMenu(hwnd, hMenubar);
        break;
        }
        case WM_ERASEBKGND:
             break;

        case WM_TIMER:
             application.processTimers();
             break;

        case WM_TESTVC: {
             BasicGame* game=application.getCurrentGame();
             if(game) game->testVictoryCondition();
             break;
        }
        case WM_PAINT:
            application.paint();
            break;

        case WM_KEYUP:
            application.keyUp(wParam,getShifts());
            break;

        case WM_KEYDOWN:
            application.keyDown(wParam,getShifts());
            break;

        case WM_RBUTTONUP:
            application.mouseUp(getButtons(wParam,mbRight),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;
        case WM_LBUTTONUP:
            application.mouseUp(getButtons(wParam,mbLeft),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;
        case WM_MBUTTONUP:
            application.mouseUp(getButtons(wParam,mbMiddle),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;

        case WM_RBUTTONDOWN:
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
            application.mouseDown(getButtons(wParam),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;

        case WM_RBUTTONDBLCLK:
        case WM_LBUTTONDBLCLK:
        case WM_MBUTTONDBLCLK:
            application.mouseDblClick(getButtons(wParam),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;

        case WM_MOUSEMOVE:
            application.mouseMove(getButtons(wParam),getShifts(wParam),GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}





#endif // APPLICATION_H_INCLUDED
