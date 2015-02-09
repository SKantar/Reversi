#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer;
vector<Timer*> timers;

class Timer {
protected:
    int _skip;
    int _counter;
    int _skipped;
    void processTimerEvent() {
          if(_skipped>=_skip) {
              _skipped=0;
              step(_counter++);
          } else _skipped++;
    }
public:
    Timer(int skip=0): _skip(skip), _counter(0), _skipped(0) {
        timers.push_back(this);
    }
    ~Timer() {
        izbaci(timers,this);
    }
    virtual void step(int counter) {
    }
    friend class Application;

};



#endif // TIMER_H_INCLUDED
