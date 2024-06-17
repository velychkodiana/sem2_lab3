#pragma once
#include "ITextProcessor.h"
#include <map>
#include <sstream>

class SequentialWordFrequencyCounter : public ITextProcessor {
public:
    std::wstring process(const std::wstring& text, const std::wstring& pattern = L"") override {
        std::wistringstream iss(text);
        std::map<std::wstring, int> wordCount;
        std::wstring word;
        while (iss >> word) {
            ++wordCount[word];
        }

        std::wstringstream result;
        for (const auto& [word, count] : wordCount) {
            result << word << L": " << count << L"\n";
        }

        return result.str();
    }
};
