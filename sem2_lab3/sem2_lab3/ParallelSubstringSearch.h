#pragma once
#include "ITextProcessor.h"
#include <thread>
#include <vector>

class ParallelSubstringSearch : public ITextProcessor {
public:
    std::wstring process(const std::wstring& text, const std::wstring& pattern) override {
        size_t length = text.length();
        size_t numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        std::vector<bool> results(numThreads, false);

        for (size_t i = 0; i < numThreads; ++i) {
            threads.emplace_back([&, i] {
                size_t start = i * length / numThreads;
                size_t end = (i + 1) * length / numThreads;
                if (text.substr(start, end - start).find(pattern) != std::wstring::npos) {
                    results[i] = true;
                }
                });
        }

        for (auto& t : threads) {
            t.join();
        }

        for (const auto& res : results) {
            if (res) {
                return L"Substring found";
            }
        }

        return L"Substring not found";
    }
};

