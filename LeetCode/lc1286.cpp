#include <cstdlib>
#include <ctime>
#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include <tuple>
#include <typeinfo>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class Generator : public std::enable_shared_from_this<Generator<T>> {
public:
    int state;
    Generator() : state(0) {}
    virtual bool next(T& output) = 0;
    bool operator()(T& output) {
        return next(output);
    }
};

#define PRG_BEG \
switch(state) { \
case 0:;

#define PRG_END \
case -1:; \
default: { return false; } }

#define YIELD() \
do { state = __LINE__; return true; case __LINE__:; } while(0)

#define RETURN() \
do { state = -1; return false; } while(0)

#define RESET() \
do { state = 0; } while(0)

class Helper : public Generator<string> {
public:
    string& s;
    int n, i;
    Helper * iter;
    Helper(string& _s, int _n, int _i) : s(_s), n(_n), i(_i), iter(NULL) {}
    ~Helper() { delete iter; }
    void reset(int _n, int _i) {
        RESET();
        n = _n;
        i = _i;
    }
    bool next(string &output) {
        PRG_BEG
        if(i >= s.size() || s.size() - i < n) {
            RETURN();
        }
        for(; i < s.size(); ++i) {
            if(n == 1) {
                output.push_back(s[i]);
                YIELD();
                continue;
            }
            if(iter == NULL) {
                iter = new Helper(s, n - 1, i + 1);
            } else {
                iter->reset(n - 1, i + 1);
            }
            while(iter->next(output)) {
                output.push_back(s[i]);
                YIELD();
            }
        }
        PRG_END
    }
};

class CombinationIterator {
public:
    Helper helper;
    string s;
    bool isNew;
    
    CombinationIterator(string characters, int combinationLength) : 
        helper(characters, combinationLength, 0), isNew(false) { }
    
    string next() {
        if(!isNew) hasNext();
        isNew = false;
        return string(s.rbegin(),s.rend());
    }
    
    bool hasNext() {
        if(isNew) return true;
        s.clear();
        return isNew = helper(s);
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
