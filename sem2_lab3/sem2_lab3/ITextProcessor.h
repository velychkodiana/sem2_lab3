#pragma once
#include <string>

class ITextProcessor {
public:
    virtual std::wstring process(const std::wstring& text, const std::wstring& pattern = L"") = 0;
    virtual ~ITextProcessor() = default;
};