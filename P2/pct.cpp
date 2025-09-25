#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define MAX 1000000000

using namespace std;

mutex the_mutex;
condition_variable_any condc, condp;
int buffer = 0;

void producer(void *ptr) {
    int i;
    for (i = 1; i <= MAX; i++) {
        the_mutex.lock();
        while (buffer != 0) {
            the_mutex.unlock();
            condp.wait(the_mutex);
            the_mutex.lock();
        }
        buffer = i;
        condc.notify_one();
        the_mutex.unlock();
    }
    return;
}

void consumer(void *ptr) {
    int i;
    for (i = 1; i <= MAX; i++) {
        the_mutex.lock();
        while (buffer == 0) {
            the_mutex.unlock();
            condc.wait(the_mutex);
            the_mutex.lock();
        }
        buffer = 0;
        condp.notify_one();
        the_mutex.unlock();
    }
    return;
}

int main (int argc, char *argv[]) {
    thread pro(producer);
    thread con(consumer);
    pro.join();
    this_thread::sleep_for(chrono::seconds(1));
    con.join();
    return 0;
}