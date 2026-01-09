#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>


int main() {

    std::cout << "------------------------------ CLI Process Lister ----------------------------\n";

    // 1. DEFINE VARIABLES
    HANDLE hThreadSnap;
    THREADENTRY32 te32;

    te32.dwSize = sizeof(THREADENTRY32);


    // 2. TAKE THE SNAPSHOT
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);


    // 3. CHECKING FOR ERRORS
    if (hThreadSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error: Snap Process has an invalid handle value." << std::endl;

        return -1;
    }


    // 4. GET THE FIRST PROCESS
    if (!Thread32First(hThreadSnap, &te32))
    {
        std::cout << "Error: The process list was not found." << std::endl;
        CloseHandle(hThreadSnap);

        return -1;
    }


    // 5. LOOP THROUGH THE REST
        std::cout << "------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(50) << "THREAD NAME" << std::setw(15) << "PID" << std::endl;
        std::cout << "------------------------------------------------------------------------------\n";

        do {
            if (te32.th32OwnerProcessID) {
                std::wcout << std::left
                    << std::setw(50) << te32.th32OwnerProcessID
                    << std::setw(15) << te32.th32ThreadID
                    << std::endl;
            }
        } while (Thread32Next(hThreadSnap, &te32));
        


    // 6. CLEAN UP
    CloseHandle(hThreadSnap);
    std::cout << "------------------------------------------------------------------------------\n\n";
    std::cout << "SCANNING COMPLETE.\n\n\n";


    system("pause");
    return 0;
}