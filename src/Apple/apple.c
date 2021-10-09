#define UNICODE
#include<Windows.h>
#include<tchar.h>
#include<stdlib.h>
#include<time.h>
#include"source.h"

DWORD WINAPI inject(LPVOID args) {
    HWND hwnd = FindWindowW(NULL, L"Minesweeper");
    HDC hdc = GetDC(hwnd);
    const int total_time = 218 * 1000;
    const int total_frame = 6472;
    const clock_t start_time = clock();
    for (int i = 0; i < 6472; i++) {
        while (clock() - start_time < (i * (double)(total_time) / total_frame)) { Sleep(1); }
        memcpy((BYTE*)0x01005340, frames[i], 832);
        InvalidateRect(hwnd, 0, FALSE);
    }
    ReleaseDC(hwnd, hdc);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpvRevered) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hinstDll);
        CreateThread(NULL, 0, inject, NULL, 0, NULL);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

