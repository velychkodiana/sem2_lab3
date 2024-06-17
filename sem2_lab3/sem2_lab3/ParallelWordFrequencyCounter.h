#pragma once
#include "ITextProcessor.h"
#include <map>
#include <sstream>
#include <thread>
#include <mutex>
#include <vector>

class ParallelWordFrequencyCounter : public ITextProcessor {
public:
    std::wstring process(const std::wstring& text, const std::wstring& pattern = L"") override {
        size_t length = text.length();
        size_t numThreads = std::thread::hardware_concurrency();
        std::vector<std::thread> threads;
        std::map<std::wstring, int> wordCount;
        std::mutex mtx;

        auto countWords = [&](const std::wstring& segment) {
            std::wistringstream iss(segment);
            std::wstring word;
            std::map<std::wstring, int> localCount;
            while (iss >> word) {
                ++localCount[word];
            }
            std::lock_guard<std::mutex> lock(mtx);
            for (const auto& [word, count] : localCount) {
                wordCount[word] += count;
            }
            };

        size_t segmentSize = length / numThreads;
        for (size_t i = 0; i < numThreads; ++i) {
            size_t start = i * segmentSize;
            size_t end = (i == numThreads - 1) ? length : (i + 1) * segmentSize;
            threads.emplace_back(countWords, text.substr(start, end - start));
        }

        for (auto& t : threads) {
            t.join();
        }

        std::wstringstream result;
        for (const auto& [word, count] : wordCount) {
            result << word << L": " << count << L"\n";
        }

        return result.str();
    }
};

