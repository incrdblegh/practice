// reminder: get rid of global variables. encapsulate the worker, thread pool, shared state and
// synchronization primitives into a single class. also consider encapsulating the rest of the code in a
// task-generator class.

#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>
#include <vector>

// an atomic bool to check whether new tasks are created
std::atomic<bool> tasks_created{true};
// a mutex to allow for a thread-safe cout
std::mutex cout_mutex;

// a reusable RNG class to encapsulate functionality needed to generate  random numbers 
class RNG {
    std::mt19937 generator{std::random_device()()};
    std::uniform_int_distribution<int> distribution;

  public:
    RNG(int begin, int end) : distribution{begin, end} {}
    int operator()() { return distribution(generator); }
};

// thread-safe std::cout
void print(int value) {
    std::lock_guard lock{cout_mutex};
    std::cout << value << ' ';
}

// task generator
void get_tasks(std::queue<std::function<void()>>& tasks, std::mutex& mutex,
               std::condition_variable& condition) {
    // RNG to assign different values to tasks, will be printed later 
    RNG rng{0, 100};
    // make random number of tasks on each execution of the program 
    const int number_of_tasks = RNG(500, 2000)();
    // notify the threads every n (batch_size) tasks
    constexpr int batch_size = 100;
    std::cout << "Generated " << number_of_tasks << " tasks, now executing...\n";

    for (int i = 0; i < number_of_tasks; ++i) {
        {
            // lock the mutex to prevent data races with worker threads
            std::lock_guard lock(mutex);
            tasks.emplace([value = rng()] { print(value); });
        }
        // notify the threads every n (batch_size) tasks
        // not very efficient, better use an outer loop that loops n batches 
        if (number_of_tasks % batch_size == 0) {
            condition.notify_all();
        }
    }
    // set atomic bool flag to false to indicate that no more new tasks are created
    tasks_created = false;
    // notify all one last time
    condition.notify_all();
}

void worker(std::queue<std::function<void()>>& tasks, std::mutex& mutex, std::condition_variable& condition) {
    while (true) {
        // a buffer to avoid task execution in the critical section 
        std::function<void()> task_buffer;
        {
            // acquire a lock on a mutex to prevent data race with other workers and with task generator
            std::unique_lock lock{mutex};
            // return if there are no more new tasks available, and if new tasks won't be created
            if (tasks.empty() && !tasks_created) {
                return;
            }
            // sleep until get notified and the tasks queue is not empty
            condition.wait(lock, [&tasks] { return !tasks.empty(); });
            // move a task into a buffer to avoid task execution in the critical section
            task_buffer = std::move(tasks.front());
            tasks.pop();
        }
        // execute a task stored in the buffer while out of critical section
        task_buffer();
    }
}

void thread_pool(std::queue<std::function<void()>>& tasks, std::mutex& mutex,
                 std::condition_variable& condition) {
    // make use of the threads on a given machine 
    const auto number_of_threads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;

    // initialize worker threads
    for (int i = 0; i < number_of_threads; ++i) {
        threads.emplace_back(worker, std::ref(tasks), std::ref(mutex), std::ref(condition));
    }
    // join all threads
    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    std::queue<std::function<void()>> tasks;
    std::mutex mutex;
    std::condition_variable condition;
    std::thread task_generator(get_tasks, std::ref(tasks), std::ref(mutex), std::ref(condition));
    thread_pool(tasks, mutex, condition);
    task_generator.join();
}
