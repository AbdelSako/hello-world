#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string& url, int sec)
{
    // simulate a long page fetch
    std::cout << "[+] Sleeping...\n";
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    std::string result = "fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    std::cout << url << " just got the lock\n";
    std::this_thread::sleep_for(std::chrono::seconds(sec));
    g_pages[url] = result;
    std::cout << url << " exiting func.\n";
}

void Main()
{
    std::thread t1(save_page, "http://foo",3);
    std::thread t2(save_page, "http://bar", 3);
    t1.join();
    t2.join();

    // safe to access g_pages without lock now, as the threads are joined
    for (const auto& pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}