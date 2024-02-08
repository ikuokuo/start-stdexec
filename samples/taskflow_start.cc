#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <taskflow/taskflow.hpp>
#include <taskflow/algorithm/pipeline.hpp>

int main(int argc, char const *argv[]) {
  (void)(argc);
  (void)(argv);

  fmt::print("Hello, {}!\n", "taskflow");
  spdlog::info("Hello, {}!", "taskflow");

  auto thread_num = std::thread::hardware_concurrency();

  tf::Executor executor(thread_num);
  tf::Taskflow taskflow;

  auto [A, B, C, D] = taskflow.emplace(  // create four tasks
    [] () { std::cout << "TaskA\n"; },
    [] () { std::cout << "TaskB\n"; },
    [] () { std::cout << "TaskC\n"; },
    [] () { std::cout << "TaskD\n"; });

  A.precede(B, C);  // A runs before B and C
  D.succeed(B, C);  // D runs after  B and C

  executor.run(taskflow).wait();

  return 0;
}
