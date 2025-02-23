#include <iostream>
#include <random>
#include <vector>

#define HALF_POSSIBLE_VALUE 5

template <typename T> class SkiplistTemplate {
private:
  struct DataNode {
    T data;
    DataNode *next;
  };
  struct CacheNode {
    CacheNode *next;
    CacheNode *nextLevel;
    DataNode *dataNode;
  };
  enum class SearchMode { SEARCH, DELETE, ADD };

private:
  std::mt19937 gen;                        // Mersenne Twister 随机数引擎
  std::uniform_int_distribution<int> dist; // 均匀分布
  // idx[i] store i level
  std::vector<CacheNode *> idx;
  DataNode *datas;

private:
  // The function will use two mode:
  // 1. if path is zero, it will return as soon as possible
  // 2. if path is filled, then it will search to the lowest level
  //    and path will be filled with the node that should be updated in the [i]
  //    level. Notice the caller should init it's size.
  // 3. the path[i] is mapping to idx[i - 1]. Because path[0] stores data level.
  bool searchInner(const T &target, SearchMode searchMode,
                   std::vector<void *> *path = 0) {
    int curCacheLevel = idx.size() - 1;
    CacheNode *pre = nullptr;
    CacheNode *cur = nullptr;
    bool ifEqual = false;

    while (curCacheLevel >= 0) {
      pre = idx[curCacheLevel];
      cur = pre->next;
      while (cur != nullptr && cur->dataNode->data < target) {
        pre = cur;
        cur = cur->next;
      }

      // find element and not in add/erase mode, just return
      ifEqual = cur != nullptr && cur->dataNode->data == target;
      if (ifEqual && searchMode == SearchMode::SEARCH) {
        return true;
      }

      // in add/erase mode, find to lowest level
      if (ifEqual && searchMode == SearchMode::DELETE) {
        (*path)[curCacheLevel + 1] = pre;
      }
      if (searchMode == SearchMode::ADD) {
        (*path)[curCacheLevel + 1] = pre;
      }
      curCacheLevel--;
    }

    // search data level if necessary
    DataNode *preDataNode;
    DataNode *curDataNode;
    // no cache exist
    if (pre == nullptr || pre->dataNode == nullptr) {
      preDataNode = datas;
    } else {
      preDataNode = pre->dataNode;
    }
    curDataNode = preDataNode->next;

    while (curDataNode != nullptr && curDataNode->data < target) {
      preDataNode = curDataNode;
      curDataNode = curDataNode->next;
    }

    ifEqual = curDataNode != nullptr && curDataNode->data == target;
    if (searchMode == SearchMode::SEARCH && ifEqual) {
      return true;
    }
    if (searchMode == SearchMode::DELETE && ifEqual) {
      (*path)[0] = preDataNode;
      return true;
    }
    if (searchMode == SearchMode::ADD) {
      (*path)[0] = preDataNode;
    }
    return ifEqual;
  }

public:
  SkiplistTemplate()
      : dist(0, 10),
        gen(std::random_device{}()), datas{new DataNode{T{}, nullptr}} {}

  bool search(const T &target) {
    return searchInner(target, SearchMode::SEARCH);
  }

  void add(const T &target) {
    std::vector<void *> path;
    path.resize(idx.size() + 1);
    searchInner(target, SearchMode::ADD, &path);

    // update data level
    DataNode *dataNode = (DataNode *)path[0];
    DataNode *newDataNode = new DataNode{target, dataNode->next};
    dataNode->next = newDataNode;

    // update cache level
    int random = dist(gen);
    int curPathIdx = 1;
    CacheNode *preLevelCacheNode = nullptr;

    while (random < HALF_POSSIBLE_VALUE) {
      CacheNode *newCacheNode =
          new CacheNode{nullptr, preLevelCacheNode, newDataNode};

      // update exist level
      if (curPathIdx < path.size()) {
        CacheNode *curCacheNode = (CacheNode *)path[curPathIdx];
        newCacheNode->next = curCacheNode->next;
        curCacheNode->next = newCacheNode;
      }
      // add new level
      else {
        CacheNode *head = new CacheNode{nullptr, nullptr, nullptr};
        head->next = newCacheNode;
        idx.push_back(head);
      }

      curPathIdx++;
      preLevelCacheNode = newCacheNode;
      random = dist(gen);
    }
  }

  bool erase(const T &target) {
    std::vector<void *> path;
    path.resize(idx.size() + 1);
    bool res = searchInner(target, SearchMode::DELETE, &path);
    if (!res) {
      return res;
    }

    // update data level
    DataNode *preDataNode = (DataNode *)path[0];
    DataNode *targetNode = preDataNode->next;
    preDataNode->next = targetNode->next;
    delete targetNode;

    // update cache level
    for (int i = 1; i < path.size() && path[i] != nullptr; i++) {
      CacheNode *preCacheNode = (CacheNode *)path[i];
      CacheNode *targetCacheNode = preCacheNode->next;
      preCacheNode->next = targetCacheNode->next;
      delete targetCacheNode;
    }

    return res;
  }

  void printSkiplist() {
    std::cout << "---------------------\n";
    std::cout << "Skiplist Structure:\n";

    for (int level = idx.size() - 1; level >= 0; --level) {
      CacheNode *cur = idx[level]->next;
      std::cout << "Level " << level << ": ";
      while (cur) {
        std::cout << cur->dataNode->data << " -> ";
        cur = cur->next;
      }
      std::cout << "NULL\n";
    }

    std::cout << "Data Level: ";
    DataNode *cur = datas->next;
    while (cur != nullptr) {
      std::cout << cur->data << " -> ";
      cur = cur->next;
    }
    std::cout << "NULL\n";
    std::cout << "---------------------\n";
  }
};
using Skiplist = SkiplistTemplate<int>;

#include <string>
int main() {
  std::vector<std::string> operations = {
      "Skiplist", "add",   "add",    "add",    "add",
      "search",   "erase", "search", "search", "search"};
  std::vector<std::vector<int>> values = {{},  {0}, {5}, {2}, {1},
                                          {0}, {5}, {2}, {3}, {2}};

  Skiplist *obj = nullptr;

  for (size_t i = 0; i < operations.size(); ++i) {
    if (operations[i] == "Skiplist") {
      obj = new Skiplist();
    } else if (operations[i] == "add") {
      obj->add(values[i][0]);
      std::printf("add %d\n", values[i][0]);
    } else if (operations[i] == "search") {
      std::printf("search :%d ret %d\n", values[i][0],
                  obj->search(values[i][0]));
    } else if (operations[i] == "erase") {
      std::printf("erase :%d ret %d\n", values[i][0], obj->erase(values[i][0]));
    }
    obj->printSkiplist();
  }
  return 0;
}