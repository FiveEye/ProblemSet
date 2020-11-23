#define PRG_BEG \
switch(state) { \
case 0:;

#define PRG_END \
case -1:; \
default: { return false; } }

#define YIELD() \
do { state = __LINE__; return true; case __LINE__:; } while(0)

#define YIELD_ALL(iter,output) \
do { while((iter)->next((output))) { YIELD(); } } while(0) 

#define RETURN() \
do { state = -1; return false; } while(0)

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
    shared_ptr<Generator<T>> getPtr() { return this->shared_from_this(); }
};

template<typename T>
class IteratorHelper : public std::enable_shared_from_this<IteratorHelper<T>> {
public:
    shared_ptr<Generator<T>> gen;
    T output;
    bool pending;
    IteratorHelper(Generator<T> &_gen) : gen(_gen.getPtr()),  pending(false) {}
    IteratorHelper(shared_ptr<Generator<T>> _gen) : gen(_gen),  pending(false) {}
    T next() {
        if(!pending) hasNext();
        if(pending) {
            pending = false;
        } else {
            // Error, Iterator is done.
        }
        return output;
    }
    bool hasNext() {
        if(pending) return pending;
        return pending = gen->next(output);
    }
    shared_ptr<IteratorHelper<T>> getPtr() { return this->shared_from_this(); }
};

class Helper : public Generator<char> {
public:
    string s;
    int i, j, c;
    char pc;
    Helper(string &_s) : s(_s) {
    }
    bool next(char &x) {
        PRG_BEG
        j = 0;
        c = 0;
        pc = 0;
        for(i = 0; i < s.size(); ++i) {
            c = s[i];
            if('0' <= c && c <= '9') {
                j = j * 10 + c - '0';
            } else {
                if(pc == 0) {
                    pc = c;
                    continue;
                }
                for(;j > 0; --j) {
                    x = pc;
                    YIELD();
                }
                pc = c;
            }
        }
        for(;j > 0; --j) {
            x = pc;
            YIELD();
        }
        x = ' ';
        PRG_END
    }
};

class StringIterator {
public:
    IteratorHelper<char> iter;
    StringIterator(string compressedString) : iter(make_shared<Helper>(compressedString)){

    }
    
    char next() {
        return iter.next();
    }
    
    bool hasNext() {
        return iter.hasNext();
    }
};

/**
 * Your StringIterator object will be instantiated and called as such:
 * StringIterator* obj = new StringIterator(compressedString);
 * char param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
