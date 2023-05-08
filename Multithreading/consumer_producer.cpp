#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

void producer_func(std::queue<int>& queue, std::mutex& mutex, std::condition_variable& condition) {
    // prepare a random number generator
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution dist(0, 100);

    for (int i = 0; i < 20; ++i) {
        {
            // acquire a lock on a mutex to avoid data race with consumer thread
            std::unique_lock lock{mutex};
            queue.emplace(dist(gen));
        }
        // notify condition variable that consumer thread can proceed
        condition.notify_one();
    }
}

void consumer_func(std::queue<int>& queue, std::mutex& mutex, std::condition_variable& condition) {
    int value{};
    for (int i = 0; i < 20; ++i) {
        {
            // acquire a lock to avoid data races with producer thread
            std::unique_lock lock{mutex};
            // go to sleep until the queue has any elements in it
            condition.wait(lock, [&queue] { return !queue.empty(); });
            // this happens only when consumer wakes up and acquires a lock through condition variable
            value = queue.front();
            queue.pop();
        }
        std::cout << value << ' ';
    }
}

int main() {
    std::queue<int> queue;
    std::mutex mutex;
    std::condition_variable condition;
    std::thread producer{producer_func, std::ref(queue), std::ref(mutex), std::ref(condition)};
    std::thread consumer{consumer_func, std::ref(queue), std::ref(mutex), std::ref(condition)};
    producer.join();
    consumer.join();
}
