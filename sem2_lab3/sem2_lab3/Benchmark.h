#pragma once
#include <chrono>

class Benchmark {
public:
    template <typename Func>
    static double measure(Func&& func) {
        auto start = std::chrono::high_resolution_clock::now();
        func();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        return diff.count();
    }
};