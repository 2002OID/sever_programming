#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>
#include <atomic>
const auto max_threads = 64;
//volatile int sum;
std::atomic <int> sum;	//atomic 자료구조 실험
std::mutex mylock;


void thread_func(int num_threads) {
	for (auto i = 0; i < 50000000 / num_threads; ++i) {
		sum += 2;
	}
}
int main() {
	std::vector<std::thread> threads;
	for (auto i = 1; i <= max_threads; i *= 2) {
		sum = 0;
		threads.clear();
		auto start = std::chrono::high_resolution_clock::now();
		for (auto j = 0; j < i; ++j) threads.push_back(std::thread{ thread_func, i });

		for (auto& tmp : threads) tmp.join();
		
		auto duration = std::chrono::high_resolution_clock::now() - start;
		std::cout << i << " threads, sum = " << sum;
		std::cout << " duration = " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() << " milliseconds\n";
	}
}