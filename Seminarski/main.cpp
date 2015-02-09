#define WINVER 0x500
#include <windows.h>
#include <iostream>
#include "Application.h"
#include "Dragndrop.h"
#include "Board.h"
#include "Reversi.h"
#include <vector>
//#include "MS_IKSOKS.h"
using namespace std;
int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    application.initialize(hThisInstance, hPrevInstance, lpszArgument, nCmdShow);

    application.setTitle("Reversi");
    application.setBackgroundColor(RGB(20,100,50));
    application.setDimensions(770,800);
   /* vector <ReversiFigura> f;
        for(int i = 0; i < MAXN; i++)
            for(int j = 0; j < MAXM; j++)
            if(i == 3 && j == 4) f.push_back(new ReversiFigura(1,i,j));
            else if(i == 4 && j == 3) f.push_back(new ReversiFigura(1,i,j));
            else if(i == 3 && j == 3) f.push_back(new ReversiFigura(2,i,j));
            else if(i == 4 && j == 4) f.push_back(new ReversiFigura(2,i,j));
            else f.push_back(new ReversiFigura(0,i,j));*/

    Reversi reversi;
    ReversiFigura f1(0, 0, 0);
    ReversiFigura f2(0, 0, 1);
    ReversiFigura f3(0, 0, 2);
    ReversiFigura f4(0, 0, 3);
    ReversiFigura f5(0, 0, 4);
    ReversiFigura f6(0, 0, 5);
    ReversiFigura f7(0, 0, 6);
    ReversiFigura f8(0, 0, 7);

    ReversiFigura f9(0, 1, 0);
    ReversiFigura f10(0, 1, 1);
    ReversiFigura f11(0, 1, 2);
    ReversiFigura f12(0, 1, 3);
    ReversiFigura f13(0, 1, 4);
    ReversiFigura f14(0, 1, 5);
    ReversiFigura f15(0, 1, 6);
    ReversiFigura f16(0, 1, 7);

    ReversiFigura f17(0, 2, 0);
    ReversiFigura f18(0, 2, 1);
    ReversiFigura f19(0, 2, 2);
    ReversiFigura f20(0, 2, 3);
    ReversiFigura f21(0, 2, 4);
    ReversiFigura f22(0, 2, 5);
    ReversiFigura f23(0, 2, 6);
    ReversiFigura f24(0, 2, 7);

    ReversiFigura f25(0, 3, 0);
    ReversiFigura f26(0, 3, 1);
    ReversiFigura f27(0, 3, 2);
    ReversiFigura f28(1, 3, 3);
    ReversiFigura f29(2, 3, 4);
    ReversiFigura f30(0, 3, 5);
    ReversiFigura f31(0, 3, 6);
    ReversiFigura f32(0, 3, 7);

    ReversiFigura f33(0, 4, 0);
    ReversiFigura f34(0, 4, 1);
    ReversiFigura f35(0, 4, 2);
    ReversiFigura f36(2, 4, 3);
    ReversiFigura f37(1, 4, 4);
    ReversiFigura f38(0, 4, 5);
    ReversiFigura f39(0, 4, 6);
    ReversiFigura f40(0, 4, 7);

    ReversiFigura f41(0, 5, 0);
    ReversiFigura f42(0, 5, 1);
    ReversiFigura f43(0, 5, 2);
    ReversiFigura f44(0, 5, 3);
    ReversiFigura f45(0, 5, 4);
    ReversiFigura f46(0, 5, 5);
    ReversiFigura f47(0, 5, 6);
    ReversiFigura f48(0, 5, 7);

    ReversiFigura f49(0, 6, 0);
    ReversiFigura f50(0, 6, 1);
    ReversiFigura f51(0, 6, 2);
    ReversiFigura f52(0, 6, 3);
    ReversiFigura f53(0, 6, 4);
    ReversiFigura f54(0, 6, 5);
    ReversiFigura f55(0, 6, 6);
    ReversiFigura f56(0, 6, 7);

    ReversiFigura f57(0, 7, 0);
    ReversiFigura f58(0, 7, 1);
    ReversiFigura f59(0, 7, 2);
    ReversiFigura f60(0, 7, 3);
    ReversiFigura f61(0, 7, 4);
    ReversiFigura f62(0, 7, 5);
    ReversiFigura f63(0, 7, 6);
    ReversiFigura f64(0, 7, 7);

    //ReversiFigura c1(1, -1, 0);
    //ReversiFigura c2(2,  8, 0);

    /*
    IksOksFigura f1(false, 100,100);
    IksOksFigura f12(true, 100,100);
    IksOksFigura f13(false, 100,100);
    IksOksFigura f4(true, 100,100);
    IksOksFigura f2(false, 100,100);
    IksOksFigura f3(true, 100,100);
    IksOksFigura f5(false, 100,100);
    IksOksFigura f6(true, 100,100);
    IksOksFigura f7(false, 100,100);
    */

    application.run();
    return 0;
}


