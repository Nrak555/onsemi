#include "stdafx.h"
#include "Lock.h"
#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex io_mutex;

void thrd_func(int tid) {
	custom_lock::lock_guard<std::mutex> lck(io_mutex);

	std::cout << "Sleeping for 1 sec: Thread " << tid << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
	int temp;
	const int numThreads = 5;

	std::thread T[numThreads];

	for (int i = 0; i < numThreads; i++)
		T[i] = std::thread(thrd_func, i);

	for (int i = 0; i < numThreads; i++)
		T[i].join();

	std::cout << "Threads have all joined" << std::endl;

	std::cin >> temp;
}
	
