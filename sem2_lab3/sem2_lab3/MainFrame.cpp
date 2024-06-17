#include "MainFrame.h"
#include <CommCtrl.h>
#include <sstream>
#include <thread>

MainFrame::MainFrame(HINSTANCE hInstance) : hInstance(hInstance), hwndMain(nullptr), hwndInputText(nullptr), hwndSubstring(nullptr), hwndResult(nullptr), hwndSearchButton(nullptr), hwndCountButton(nullptr) {}

void MainFrame::Show() {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("MainFrame");
    RegisterClass(&wc);

    hwndMain = CreateWindow(wc.lpszClassName, TEXT("Text Processor"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance, this);
    ShowWindow(hwndMain, SW_SHOWNORMAL);
    UpdateWindow(hwndMain);
}

LRESULT CALLBACK MainFrame::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    MainFrame* pThis = nullptr;
    if (uMsg == WM_NCCREATE) {
        pThis = static_cast<MainFrame*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
        pThis->hwndMain = hwnd;
    }
    else {
        pThis = reinterpret_cast<MainFrame*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }

    if (pThis) {
        switch (uMsg) {
        case WM_CREATE:
            pThis->InitializeComponents(hwnd);
            return 0;
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                pThis->OnSearchSubstring();
            }
            else if (LOWORD(wParam) == 2) {
                pThis->OnCountWordFrequency();
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void MainFrame::InitializeComponents(HWND hwnd) {
    hwndInputText = CreateWindow(TEXT("EDIT"), nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 10, 760, 200, hwnd, nullptr, hInstance, nullptr);
    hwndSubstring = CreateWindow(TEXT("EDIT"), nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 220, 200, 20, hwnd, nullptr, hInstance, nullptr);
    hwndSearchButton = CreateWindow(TEXT("BUTTON"), TEXT("Search Substring"), WS_CHILD | WS_VISIBLE, 220, 220, 150, 30, hwnd, (HMENU)1, hInstance, nullptr);
    hwndCountButton = CreateWindow(TEXT("BUTTON"), TEXT("Count Word Frequency"), WS_CHILD | WS_VISIBLE, 380, 220, 150, 30, hwnd, (HMENU)2, hInstance, nullptr);
    hwndResult = CreateWindow(TEXT("EDIT"), nullptr, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 10, 260, 760, 300, hwnd, nullptr, hInstance, nullptr);
}

void MainFrame::OnSearchSubstring() {
    int length = GetWindowTextLength(hwndInputText);
    std::vector<TCHAR> buffer(length + 1);
    GetWindowText(hwndInputText, buffer.data(), length + 1);
    std::wstring inputText(buffer.begin(), buffer.end());

    length = GetWindowTextLength(hwndSubstring);
    buffer.resize(length + 1);
    GetWindowText(hwndSubstring, buffer.data(), length + 1);
    std::wstring substring(buffer.begin(), buffer.end());

    auto processor = ProcessorFactory::createProcessor(false, "substring");
    std::wstring result = processor->process(inputText, substring);

    SetWindowText(hwndResult, result.c_str());
}
void MainFrame::OnCountWordFrequency() {
    int length = GetWindowTextLength(hwndInputText);
    std::vector<TCHAR> buffer(length + 1);
    GetWindowText(hwndInputText, buffer.data(), length + 1);
    std::wstring inputText(buffer.begin(), buffer.end());

    auto processor = ProcessorFactory::createProcessor(false, "word_frequency");
    std::wstring result = processor->process(inputText);

    SetWindowText(hwndResult, result.c_str());
}
