/*********************************************************
* Summary: This file includes a solution to the producer-
*           consumer problem using threads.
*
* Author: Brandon Aikman
* Created: Sep 2025
* Summary of Modifications:
* 24 Sep 2025 – Initial version.
*
* ©Copyright Cedarville University, its Computer Science faculty, and the
* authors. All rights reserved.
********************************************************/
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#define MAX 12

using namespace std;

mutex the_mutex;
condition_variable_any condc, condp;    // Condition variables for consumer and producer threads
const int N = 7;                        // Size of the buffer
char buff[N];
int in = 0;                             // producer counter
int out = 0;                            // consumer counter
int count = 0;                          // counter

void producer() {
    for (int i = 0; i < MAX; i++) {
        unique_lock<mutex> lock(the_mutex); // Lock the mutex

        while (count == N) {
            condp.wait(lock); // Wait while at the final index
        }

        char c = 'A' + rand() % 26; // Set c to a random capital letter
        buff[in] = c; // Place c in the buffer
        in = (in + 1) % N; // Circular increment
        count++;

        cout << (char)tolower(c) << endl;

        condc.notify_one(); // Notify consumer thread
    }
    return;
}

void consumer() {
    for (int i = 0; i < MAX; i++) {
        unique_lock<mutex> lock(the_mutex); // Lock the mutex

        while (count == 0) {
            condc.wait(lock); // Wait while at the first (zero-indexed) index
        }

        char c = buff[out]; // Grab c from the buffer
        out = (out + 1) % N; // Circular increment
        count--;

        cout << c << endl;

        condp.notify_one(); // Notify producer thread
    }
    return;
}

int main (int argc, char *argv[]) {
    cout << "The Producer-Consumer Problem\nBuffer Size: " << N << "\n[p]roducer / [C]onsumer - " << MAX << " items" << endl;
    thread pro(producer); // Create producer thread
    this_thread::sleep_for(chrono::seconds(1)); // Sleep to allow producer to start
    thread con(consumer); // Create consumer thread
    pro.join();
    con.join();
    cout << "Inter-process communication complete." << endl;
    return 0;
}