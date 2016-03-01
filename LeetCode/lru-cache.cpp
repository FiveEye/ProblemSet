#include <functional>
#include <queue>
#include <vector>
#include <map>
#include <utility>

using namespace std;

#define MP(a,b) make_pair(a,b)

typedef pair<int, int> PII;

class LRUCache{
private:
  priority_queue< PII, vector<PII>, std::greater<PII> > pq;
  map<int, int> tm;
  map<int, int> kv;
  int now;
  int cap = 0;
public:
  LRUCache(int capacity) {
    while(!pq.empty()) pq.pop();
    tm.clear();
    kv.clear();
    now = 0;
    cap = capacity;
  }
    
  int get(int key) {
    auto ret = kv.find(key);   
    if(ret != kv.end()) {
      ++now;
      tm[key] = now;
      pq.push(MP(now, key));
      return ret->second;
    }
    return -1;
  }

  void set(int key, int value) {
    while(!pq.empty()) {
      auto top = pq.top();
      auto t = tm.find(top.second);
      if(top.first == t->second) break;
      pq.pop();
    }
    
    auto t = tm.find(key);
    if(t == tm.end() && cap <= 0) {
      auto top = pq.top();
      tm.erase(top.second);
      kv.erase(top.second);
      pq.pop();
    }
    if(t == tm.end()) --cap;
    ++now;
    kv[key] = value;
    tm[key] = now;
    pq.push(MP(now, key));

  }
};

