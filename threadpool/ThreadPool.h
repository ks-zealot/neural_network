#pragma once
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
 public:
  void Start();
  void Stop();
  void queueJob(std::function<void()>& job);

 private:
  std::vector<std::thread> threads;
  void ThreadLoop();
  std::queue<std::function<void()>> jobs;
  std::mutex queue_mutex;
  std::condition_variable mutex_condition;
  bool bShouldTerminate = false;
};
