#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

int i = 0;
int* value = &i;

class cl {
public:
	cl() = default;
	void increase() {
		++var;
	}

	int get() {
		return var;
	}

private:
	int var;
};

cl* c1 = new cl();

void worker_thread(void) {
	i++;
	std::cout << "[+] Starting worker_thread...\n";
	return;
}

void Main(void) {
	
	std::thread thr(worker_thread);
	std::cout << "[+] This expression appears before the detach().\n";
	thr.detach();
	std::cout << "processed value: " << i << std::endl;
	delete c1;
	return;
}