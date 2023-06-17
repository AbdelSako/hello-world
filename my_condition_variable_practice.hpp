#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m1, m2;
std::condition_variable cv;
bool ready;
int i = 0;


void worker_thread(void) {
	std::cout << "[+] worker_thread; ID = "
		<< std::this_thread::get_id() << " ";

	i++;
	std::cout << "value = " << i << std::endl;
	ready = true;
	cv.notify_one();
	return;
}

void Main(void) {
	
	std::thread thr(worker_thread);
	thr.detach();
	{
		std::unique_lock lk(m1);
		cv.wait(lk, [] {return ready; });
		ready = false;
	}
	
	
	std::cout << "processed value: " << i << std::endl;
	//thr.join();
	return;
}