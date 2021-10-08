#define UNICODE
#include <windows.h>  
#include <stdio.h>
#include <tchar.h>  

BOOL InjectDll(DWORD dwPID, LPCTSTR szDllPath) {
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    HMODULE hMod = NULL;
    LPVOID pRemoteBuf = NULL;
    DWORD dwBufSize = (DWORD)(_tcslen(szDllPath) + 1) * sizeof(TCHAR);
    LPTHREAD_START_ROUTINE pThreadProc;

    if (!(hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPID))) {
        _tprintf(L"OpenProcess(%d) failed!!! [%d]\n", dwPID, GetLastError());
        return FALSE;
    }

    pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);

    WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)szDllPath, dwBufSize, NULL);

    hMod = GetModuleHandle(L"kernel32.dll");
    pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryW");

    hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);

    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
    CloseHandle(hProcess);

    return TRUE;
}

int _tmain(int argc, TCHAR* argv[]) {
    if (argc != 3) {
        _tprintf(L"USAGE : %s dll_path pid\n", argv[0]);
        return 1;
    }

    if (InjectDll((DWORD)_tstol(argv[2]), argv[1]))
        _tprintf(L"InjectDll(\"%s\") success!!!\n", argv[1]);
    else
        _tprintf(L"InjectDll(\"%s\") failed!!!\n", argv[1]);

    return 0;
}