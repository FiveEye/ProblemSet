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

template<typename T>
class Iterator : public std::enable_shared_from_this<Iterator<T>> {
public:
    shared_ptr<Generator<T>> gen;
    T output;
    bool pending;
    Iterator(Generator<T> &_gen) : gen(_gen.getPtr()),  pending(false) {}
    Iterator(Generator<T> *_gen) : gen(_gen->getPtr()),  pending(false) {}
    Iterator(shared_ptr<Generator<T>> _gen) : gen(_gen),  pending(false) {}
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
    shared_ptr<Iterator<T>> getPtr() { return this->shared_from_this(); }
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

class Helper : public Generator<int> {
public:
    vector<NestedInteger> list;
    int i;
    shared_ptr<Helper> iter;
    Helper(vector<NestedInteger> &nestedList) : list(nestedList) {}
    Helper(NestedInteger &i) {
        list.clear();
        list.push_back(i);
    }
    bool next(int& output) {
        PRG_BEG
        for(i = 0; i < list.size(); ++i) {
            if(list[i].isInteger()) {
                output = list[i].getInteger();
                YIELD();
                continue;
            }
            iter = make_shared<Helper>(list[i].getList());
            while(iter->next(output)) YIELD();
        }
        PRG_END
    }
};

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    Iterator<int> iter;
    NestedIterator(vector<NestedInteger> &nestedList) : iter(make_shared<Helper>(nestedList)) {
    }
    
    int next() {
        return iter.next();
    }
    
    bool hasNext() {
        return iter.hasNext();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
