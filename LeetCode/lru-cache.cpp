#include <functional>
#include <queue>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

#define MP(a,b) make_pair(a,b)
typedef pair<int, int> PII;
class LRUCache{
private:
  queue<PII> pq;
  unordered_map<int, PII> kv;
  int now;
  int cap = 0;
public:
  LRUCache(int capacity) {
    while(!pq.empty()) pq.pop();
    kv.clear();
    now = 0;
    cap = capacity;
  }
    
  int get(int key) {
    auto ret = kv.find(key);
    if(ret != kv.end()) {
      ret->second.second = ++now;
      pq.push(MP(now, key));
      return ret->second.first;
    }
    return -1;
  }

  void set(int key, int value) {
    auto top = pq.front();
    while(!pq.empty()) {
      top = pq.front();
      auto t = kv.find(top.second);
      if(top.first == t->second.second) break;
      pq.pop();
    }
    
    auto t = kv.find(key);
    if(t == kv.end() && cap <= 0) {
      kv.erase(top.second);
      pq.pop();
    }
    if(t == kv.end()) --cap;
    ++now;
    kv[key] = MP(value, now);
    pq.push(MP(now, key));

  }
};