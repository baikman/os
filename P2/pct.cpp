#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#define MAX 1000000000

using namespace std;

mutex the_mutex;
condition_variable_any condc, condp;
int buffer = 0;

void *producer(void *ptr) {
    int i;
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

void *consumer(void *ptr) {
    int i;
}

int main (int argc, char *argv[]) {
    cout << "hi im working on it trust" << endl;
    return 0;
}