#ifndef BASICGAME_H_INCLUDED
#define BASICGAME_H_INCLUDED

#include "visualText.h"

class Player {
protected:
   string _name;
   int _score;
public:
   Player(const string &name) {
       _name=name;
   }
   int getScore() {
       return _score;
   }
   const string& getName() const {
       return _name;
   }
};

class BasicGame {
protected:
    virtual void testVictoryCondition() {}
    virtual void endGame(const Player* won) {
        string txt;
        if(won) txt=won->getName()+" has won the game!";
        else txt="draw game";
        endGameText=new VisualText(txt,taCenter);
        endGameText->setDimension(300,50);
        endGameText->setPosition((application.getWidth()-endGameText->getWidth())/2,(application.getHeight()-endGameText->getHeight())/2);
        endGameText->setAlpha(180);
        _active=false;
    }
    vector<Player*> players;
    VisualText* endGameText;
    bool _active;
public:
    BasicGame() {
        if(application._game) free(application._game);
        application._game=this;
        endGameText=NULL;
        _active=false;
    }
    virtual void startGame() {
        if(endGameText) free(endGameText);
        _active=true;
    }
    void nextMove() {
        PostMessage(application.getHWND(),WM_TESTVC,0,0);
    }
    bool isActive() {
        return _active;
    }
    friend  LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

};


#endif // BASICGAME_H_INCLUDED
