#include "stdafx.h"
#include "LockGuard.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>

std::mutex io_mutex;
std::mutex cv_mutex;
std::mutex signal_mutex;
std::condition_variable cv;
bool signal = false;
int data = 0;

bool signal_status() { return signal; }

void thrd_func(int tid) {
	custom_lock::lock_guard<std::mutex> lck(io_mutex);		//Lock io output to prevent overlaping messages

	std::cout << "Sleeping for 1 sec: Thread " << tid << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void CV_thrd(int tid) {
	std::unique_lock<std::mutex> lck(cv_mutex);

	std::cout << "Thread " << tid << " Starting" << std::endl;

	while(true)  {	
		std::cout << "Thread " << tid << " waiting" << std::endl;
		cv.wait(lck, [] {return signal; });
		std::cout << "Data:" << data << std::endl;
		data++;
		std::cout << "Thread " << tid << " Sleeping for 1 sec" <<std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		cv.notify_one();
	}

	
}



/*int main() {
	int temp;
	const int numThreads = 3;

	std::thread T[numThreads];
	std::thread T2[numThreads];

	std::cout << "Starting base threading example" << std::endl;


	for (int i = 0; i < numThreads; i++)
		T[i] = std::thread(thrd_func, i);

	for (int i = 0; i < numThreads; i++)
		T[i].join();

	std::cout << "Threads have all joined" << std::endl;

	for (int i = 0; i < numThreads; i++)
		T2[i] = std::thread(CV_thrd, i);

	signal = true;

	std::cout << "seting singal true" << std::endl;

	cv.notify_one();

	for (int i = 0; i < numThreads; i++)
		T2[i].join();

	std::cout << "Threads have all joined" << std::endl;

	std::cin >> temp;
}*/
	
