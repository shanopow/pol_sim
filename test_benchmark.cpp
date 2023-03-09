#include <benchmark/benchmark.h>

// Template benchmark
static void BM_StringCreation(benchmark::State& state) {
  for (auto _ : state)
    std::string empty_string;
}
// Register the function as a benchmark
BENCHMARK(BM_StringCreation);

// Template benchmark
static void BM_StringCopy(benchmark::State& state) {
  std::string x = "hello";
  for (auto _ : state)
    std::string copy(x);
}
// Register the function as a benchmark
BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();

// usage
// g++ test_benchmark.cpp -std=c++11 -isystem benchmark/include   -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
// then run executable with ./mybenchmark