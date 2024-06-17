#pragma once
#include "ITextProcessor.h"

class SequentialSubstringSearch : public ITextProcessor {
public:
    std::wstring process(const std::wstring& text, const std::wstring& pattern) override {
        size_t pos = text.find(pattern);
        if (pos != std::wstring::npos) {
            return L"Substring found at position " + std::to_wstring(pos);
        }
        else {
            return L"Substring not found";
        }
    }
};
