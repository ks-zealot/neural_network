#include "threadpool/ThreadPool.h"

#include <functional>
#include <mutex>
#include <thread>
#include "logging/log.h"
#include "logging/log.h"

void ThreadPool::Start() {

  const uint8_t maxThreads = std::thread::hardware_concurrency();
  info ( " start thread pool with {} threads", maxThreads);
  threads.resize(maxThreads);
  for (int i = 0; i < maxThreads; i++) {
    threads.at(i) = std::thread(&ThreadPool::ThreadLoop, this);
  }
}

void ThreadPool::Stop() {
  {
    info("stop thread pool");
    std::unique_lock<std::mutex> lock(queue_mutex);
    bShouldTerminate = true;
  }
  mutex_condition.notify_all();
  for (std::thread& active_thread : threads) {
    active_thread.join();
  }
  threads.clear();
}
void ThreadPool::queueJob(std::function<void()>& job) {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    jobs.push(job);
  }
  mutex_condition.notify_one();
}

void ThreadPool::ThreadLoop() {
  while (true) {
    std::function<void()> job;
    {
      std::unique_lock<std::mutex> lock(queue_mutex);
      mutex_condition.wait(
          lock, [this] { return !jobs.empty() || bShouldTerminate; });
      if (bShouldTerminate) {
        return;
      }
      job = jobs.front();
      jobs.pop();
    }
    job();
  }
}
