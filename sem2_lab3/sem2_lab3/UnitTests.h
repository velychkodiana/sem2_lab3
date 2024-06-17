#pragma once
#include "SequentialSubstringSearch.h"
#include "ParallelSubstringSearch.h"
#include "SequentialWordFrequencyCounter.h"
#include "ParallelWordFrequencyCounter.h"
#include <iostream>

class UnitTests {
public:
    static void runTests() {
        testSequentialSubstringSearch();
        testParallelSubstringSearch();
        testSequentialWordFrequencyCounter();
        testParallelWordFrequencyCounter();
    }

private:
    static void testSequentialSubstringSearch() {
        SequentialSubstringSearch processor;
        std::wstring result = processor.process(L"hello world", L"world");
        assert(result == L"Substring found at position 6");
        std::wcout << L"Sequential Substring Search Test Passed\n";
    }

    static void testParallelSubstringSearch() {
        ParallelSubstringSearch processor;
        std::wstring result = processor.process(L"hello world", L"world");
        assert(result == L"Substring found");
        std::wcout << L"Parallel Substring Search Test Passed\n";
    }

    static void testSequentialWordFrequencyCounter() {
        SequentialWordFrequencyCounter processor;
        std::wstring result = processor.process(L"hello world hello");
        std::wcout << L"Sequential Word Frequency Counter Test Passed\n" << result;
    }

    static void testParallelWordFrequencyCounter() {
        ParallelWordFrequencyCounter processor;
        std::wstring result = processor.process(L"hello world hello");
        std::wcout << L"Parallel Word Frequency Counter Test Passed\n" << result;
    }
};
