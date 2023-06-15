#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <syncstream>
#include <thread>


static int id = 0;
class ThreadSafeCounter
{
public:
    //ThreadSafeCounter() = default;
    ThreadSafeCounter() {
        ++id;
        std::cout << "Default Object Created: " << id << std::endl;
    }

    ThreadSafeCounter(int i) {
        ++id;
        std::cout << "Argument Object Created: " << id << std::endl;
        std::unique_lock lock(mutex_);
        this->value_ = i;
    }

    // Multiple threads/readers can read the counter's value at the same time.
    unsigned int get() const
    {
        std::shared_lock lock(mutex_);
        return value_;
    }


    // Only one thread/writer can increment/write the counter's value.
    void increment()
    {
        std::unique_lock lock(mutex_);
        ++value_;
    }

    // Only one thread/writer can reset/write the counter's value.
    void reset()
    {
        std::unique_lock lock(mutex_);
        value_ = 0;
    }

private:
    mutable std::shared_mutex mutex_;
    unsigned int value_{};
};

void Main()
{
    ThreadSafeCounter counter(100);
    int test = 90;

    // I didn't know you could do this kind of cool stuff to defined inline-functions.
    auto increment_and_print = [&counter, &test](const std::string arg)
    {
        for (int i{}; i != 3; ++i)
        {
            counter.increment();
            std::osyncstream(std::cout)
                << std::this_thread::get_id() << ' ' << counter.get() << arg << '\n';
        }
    };

    std::thread thread1(increment_and_print, "Hello World.");
    std::thread thread2(increment_and_print, "I'm ready.");

    increment_and_print("Final.");

    thread1.join();
    thread2.join();
}