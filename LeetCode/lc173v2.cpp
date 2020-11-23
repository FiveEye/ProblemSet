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

#define YIELD_ALL(iter,output) while(iter->next(output)) YIELD();

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
    TreeNode * root;
    shared_ptr<Helper> iter;
    Helper(TreeNode * _root) : root(_root) {}
    bool next(int &output) {
        PRG_BEG
        if(root == NULL) RETURN();
        if(root->left == NULL && root->right == NULL) {
            output = root->val;
            YIELD();
            RETURN();
        }
        iter = make_shared<Helper>(root->left);
        YIELD_ALL(iter,output);
        output = root->val;
        YIELD();
        iter = make_shared<Helper>(root->right);
        YIELD_ALL(iter,output);
        PRG_END
    }
};


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class BSTIterator {
public:
    IteratorHelper<int> iter;
    BSTIterator(TreeNode* root) : iter(make_shared<Helper>(root)) {
        
    }
    
    /** @return the next smallest number */
    int next() {
        return iter.next();
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return iter.hasNext();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
