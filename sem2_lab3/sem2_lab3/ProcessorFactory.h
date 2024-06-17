#pragma once
#include "ITextProcessor.h"
#include "SequentialSubstringSearch.h"
#include "ParallelSubstringSearch.h"
#include "SequentialWordFrequencyCounter.h"
#include "ParallelWordFrequencyCounter.h"

class ProcessorFactory {
public:
    static std::unique_ptr<ITextProcessor> createProcessor(bool parallel, const std::string& type) {
        if (type == "substring") {
            return parallel ? std::make_unique<ParallelSubstringSearch>() : std::make_unique<SequentialSubstringSearch>();
        }
        else if (type == "word_frequency") {
            return parallel ? std::make_unique<ParallelWordFrequencyCounter>() : std::make_unique<SequentialWordFrequencyCounter>();
        }
        throw std::invalid_argument("Unknown processor type");
    }
};

