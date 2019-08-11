#include <iostream>
#include <thread>
#include <mutex>
#include <cstring>

static int public_num = 0;
const int THREAD_NUM = 1000;
const int TIMES = 1000;

std::mutex mutex;

bool is_finish[THREAD_NUM];

void fun(int thread_index) {
    for (int i=0; i<TIMES; ++i) {
        mutex.lock();
        ++public_num;
        mutex.unlock();
    }
    mutex.lock();
    std::cout<< "thread " << thread_index << ":public_num=" << public_num << std::endl;
    mutex.unlock();
    is_finish[thread_index] = true;
}

int main(int argc, char** argv) {
    std::cout.sync_with_stdio(true);
    std::memset(is_finish, false, THREAD_NUM*sizeof(bool));
    for (int i=0; i<THREAD_NUM; ++i) {
        std::thread t(fun, i);
        t.detach();
    }
    while (true) {
        bool result = true;
        for (int i=0; i<THREAD_NUM; ++i) {
            result &= is_finish[i];
        }
        if (result) {
            break;
        }
    }
    std::cout << "main:public_num=" << public_num << std::endl;
    return 0;
}
