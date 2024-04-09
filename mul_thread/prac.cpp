#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
const auto MAX_THREADS = 64;
std::atomic <int> a_sum;
std::mutex mylock;


void thread_func(const int num_threads) {
	for (auto i = 0; i < 50000000 / num_threads; ++i) {
		a_sum += 2;
	}

}
int main() {
	std::vector<std::thread> threads;
	for (auto i = 1; i <= MAX_THREADS; i *= 2) {
		a_sum = 0;
		threads.clear();
		auto start = std::chrono::high_resolution_clock::now();
		for (auto j = 0; j < i; ++j) threads.push_back(std::thread{ thread_func, i });

		for (auto& tmp : threads) tmp.join();

		auto duration = std::chrono::high_resolution_clock::now() - start;
		std::cout << i << " Threads, Sum = " << a_sum;
		std::cout << " Duration = " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds\n";
	}
}


//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <vector>
//#include <mutex>
//const auto MAX_THREADS = 64;
//volatile int sum;
//std::mutex mylock;
//
//
//void thread_func(int num_threads) {
//	volatile int local_sum = 0;
//	for (auto i = 0; i < 50000000 / num_threads; ++i) {
//		
//		local_sum += 2;
//		
//	}
//	mylock.lock();
//	sum += local_sum;
//	mylock.unlock();
//	
//}
//int main() {
//	std::vector<std::thread> threads;
//	for (auto i = 1; i <= MAX_THREADS; i *= 2) {
//		sum = 0;
//		threads.clear();
//		auto start = std::chrono::high_resolution_clock::now();
//		for (auto j = 0; j < i; ++j) threads.push_back(std::thread{ thread_func, i });
//
//		for (auto& tmp : threads) tmp.join();
//		
//		auto duration = std::chrono::high_resolution_clock::now() - start;
//		std::cout << i << " Threads, Sum = " << sum;
//		std::cout << " Duration = " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds\n";
//	}
//}