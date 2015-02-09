#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

template<class T>
bool izbaci(vector<T*>& v, T* t) {
    if(remove(v.begin(), v.end(), t)!=v.end()) {
        v.pop_back();
        return true;
    }
    return false;
}

template<class T>
void obrisi(vector<T*>& v) {
    T* el;
    while(v.size()>0){
        el = v.back();
        v.pop_back();
        delete el;
    }
}

template<class T>
bool pomeriNaKraj(vector<T*>& v, T* t) {
    if (!izbaci(v,t)) return false;
    v.push_back(t);
    return true;
}

template<class T>
bool pomeriNaPocetak(vector<T*>& v, T* t) {
    if (!izbaci(v,t)) return false;
    v.insert(v.begin(),t);
    return true;
}

template<typename T>
string toString(T t) {
    ostringstream o;
    o<<t;
    return o.str();
}

template<typename T>
T fromString(string& s) {
    istringstream i(s);
    T t;
    i>>t;
    return t;
}


#define is_a(T,O) (dynamic_cast<T *>(&O)!=0)
#define cast(T,O) (dynamic_cast<T *>(&O))

bool pointInRect(int x, int y, RECT r) {
    return x>=r.left && x<=r.right && y>=r.top && y<=r.bottom;
}

int setBit(int where, int bit, bool on) {
    if(on) return where | bit;
    else return where & ~bit;
}

RECT rect(LONG left, LONG top, LONG right, LONG bottom ) {
    RECT r;
    r.left=left;
    r.right=right;
    r.top=top;
    r.bottom=bottom;
    return r;
}

#endif // UTILS_H_INCLUDED
