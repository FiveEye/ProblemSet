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

class Helper : public Generator<int> {
public:
    vector<int>& v1;
    vector<int>& v2;
    int i, j;
    Helper(vector<int>& _v1, vector<int>& _v2) : v1(_v1), v2(_v2) {}
    bool next(int &x) {
        PRG_BEG
        i = j = 0;
        while(i < v1.size() || j < v2.size()) {
            if(i < v1.size()) {
                x = v1[i++];
                YIELD();
            }
            if(j < v2.size()) {
                x = v2[j++];
                YIELD();
            }
        }
        PRG_END
    }
};

class ZigzagIterator {
public:
    IteratorHelper<int> iter;
    ZigzagIterator(vector<int>& v1, vector<int>& v2) : iter(make_shared<Helper>(v1, v2)){
        
    }

    int next() {
        return iter.next();
    }

    bool hasNext() {
        return iter.hasNext();
    }
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */
