#ifndef THREAD_SAFE_LIST_H_
#define THREAD_SAFE_LIST_H_

#include <algorithm>
#include <list>
#include <memory>
#include <mutex>
#include <queue>

template <typename T>
class ThreadSafeList {
private:
    std::list<T*> list;
    mutable std::mutex mtx;

public:
    void push_back(T* value) {
        std::lock_guard<std::mutex> lock(mtx);
        list.push_back(value);
    }

    void pop_front() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!list.empty()) {
            delete list.front();
            list.pop_front();
        }
    }

    void remove(T* value) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = std::find(list.begin(), list.end(), value);
        if (it != list.end()) {
            delete *it;
            list.erase(it);
        }
    }

    template <typename Func>
    void for_each(Func func) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& item: list) {
            func(*item);
        }
    }

    template <typename Func, typename Arg>
    void for_each_with_arg(Func func, Arg arg) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto& item: list) {
            func(*item, arg);
        }
    }

    ~ThreadSafeList() {
        for (auto item: list) {
            delete item;
        }
    }
};

#endif