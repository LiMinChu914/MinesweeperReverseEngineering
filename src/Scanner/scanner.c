#define UNICODE
#include<Windows.h>
#include<tchar.h>

#define MASK        ((BYTE)0x1F)

#define WIDTH       16
#define HEIGHT      16

HWND hwnd = NULL;

HDC* src = (HDC*)0x01005A20;
BYTE(*base)[32] = (BYTE(*)[32])0x01005340;

void(__stdcall* sub_1002646)(int, int) = (void(__stdcall*)(int, int))0x01002646;

void (*sub_10037E1)() = (void (*)())0x010037E1;

// mouse button up
void _sub_10037E1() {
    InvalidateRect(hwnd, 0, FALSE);
    sub_10037E1();
}

int mineCount(int x, int y) {
    static int dx[] = { -1,0,1,-1,1,-1,0,1 };
    static int dy[] = { -1,-1,-1,0,0,1,1,1 };
    int count = 0;
    for (int i = 0; i < 8; i++)
        if (base[y + dy[i]][x + dx[i]] & 0x80)
            count++;
    return count;
}

void __stdcall _sub_1002646(int x, int y) {
    HDC hdc = GetDC(hwnd);
    int block_type = 0;
    if (base[y][x] & 0x80) {
        if ((base[y][x] & 0x0F) == 0x0E)
            block_type = 0xC;
        else
            block_type = 0xA;
    }
    else if ((base[y][x] & 0x0F) == 0x0E)
        block_type = 0xB;
    else
        block_type = mineCount(x, y);
    BitBlt(hdc, (x - 1) * WIDTH + 12, (y - 1) * HEIGHT + 55, WIDTH, HEIGHT, src[block_type], 0, 0, SRCCOPY);
    ReleaseDC(hwnd, hdc);
}

void redirection_sub_10037E1() {
    HANDLE cProcess = GetCurrentProcess();
    LPVOID call_sub_10037E1 = (LPVOID)(0x0100200A - 4);
    DWORD offset = (DWORD)_sub_10037E1 - (DWORD)0x0100200A;
    WriteProcessMemory(cProcess, call_sub_10037E1, &offset, 4, NULL);
    CloseHandle(cProcess);
}

void redirection_sub_1002646() {
    HANDLE cProcess = GetCurrentProcess();
    LPVOID call_sub_1002646 = (LPVOID)(0x01003389 - 4);
    DWORD offset = (DWORD)_sub_1002646 - (DWORD)0x01003389;
    WriteProcessMemory(cProcess, call_sub_1002646, &offset, 4, NULL);
    CloseHandle(cProcess);
}

void redirection(LPVOID address, LPVOID function) {
    HANDLE cProcess = GetCurrentProcess();
    LPVOID call_address = (LPVOID)((DWORD)address - 4);
    DWORD offset = (DWORD)function - (DWORD)address;
    WriteProcessMemory(cProcess, call_address, &offset, 4, NULL);
    CloseHandle(cProcess);
}

BOOL WINAPI DllMain(HINSTANCE hinstDll, DWORD dwReason, LPVOID lpvRevered) {
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        hwnd = FindWindow(NULL, L"Minesweeper");
        redirection((LPVOID)0x0100200A, _sub_10037E1);
        redirection((LPVOID)0x01003389, _sub_1002646);
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
