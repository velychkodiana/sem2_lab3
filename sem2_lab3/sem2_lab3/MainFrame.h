#pragma once

#include <Windows.h>
#include <string>
#include "ProcessorFactory.h"
#include "Benchmark.h"

class MainFrame {
public:
    MainFrame(HINSTANCE hInstance);
    void Show();
private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void InitializeComponents(HWND hwnd);
    void OnSearchSubstring();
    void OnCountWordFrequency();

    HINSTANCE hInstance;
    HWND hwndMain;
    HWND hwndInputText;
    HWND hwndSubstring;
    HWND hwndResult;
    HWND hwndSearchButton;
    HWND hwndCountButton;
};
