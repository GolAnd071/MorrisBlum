#include <chrono>
#include <thread>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <cmath>
#include <vector>
#include <atomic>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <random>

std::atomic<int> a{ 0 };
std::atomic<int> b{ 0 };
std::atomic<int> c{ 0 };

int main()
{
	using namespace std::chrono_literals;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(1, 100);

	std::thread th([&]()
		{
			while (true) {
				auto start = std::chrono::high_resolution_clock::now();

				int prob = dist(gen);

				if (prob == 1)
					++c;
				if (prob <= 10)
					++b;
				if (prob <= 50)
					++a;

				std::this_thread::sleep_for(1ms);

				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double, std::milli> elapsed = end - start;
				std::cout << "Waited " << elapsed.count() << " ms\n";
			}
		});

	while (true) {
		a = a / 2;
		b = b / 2;
		c = c / 2;

		std::cout << a << ' ' << b << ' ' << c << '\n';

		std::this_thread::sleep_for(1000ms);
	}
}