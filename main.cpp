#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>


int main() {

    std::cout << "------------------------------ CLI Process Lister ----------------------------\n";

    // 1. DEFINE VARIABLES
    HANDLE hProcessSnap;
    HANDLE hThreadSnap;
    PROCESSENTRY32 pe32;
    THREADENTRY32 te32;


    pe32.dwSize = sizeof(PROCESSENTRY32);
    te32.dwSize = sizeof(THREADENTRY32);


    // 2. TAKE THE SNAPSHOT
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);


    // 3. CHECKING FOR ERRORS
    if (hProcessSnap == INVALID_HANDLE_VALUE || hThreadSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error: Could not take snap." << std::endl;

        return -1;
    }


    // 4. GET THE FIRST PROCESS
    if (!Process32First(hProcessSnap, &pe32))
    {
        std::cout << "Error: The list was not found." << std::endl;
        CloseHandle(hProcessSnap);
        CloseHandle(hThreadSnap);

        return -1;
    }


    // 5. LOOP THROUGH THE REST
    do {

        std::cout << "------------------------------------------------------------------------------\n";
        std::wcout << std::left << std::setw(21) << "PROCESS NAME" << pe32.szExeFile << std::setw(15) << "\n\tPID" << pe32.th32ProcessID << std::endl;
        std::cout << "------------------------------------------------------------------------------\n";

        if (Thread32First(hThreadSnap, &te32))
        {
            do {
                if (te32.th32OwnerProcessID == pe32.th32ProcessID) {
                    std::cout << "   -> Thread ID: " << te32.th32ThreadID << "\n";
                }

            } while (Thread32Next(hThreadSnap, &te32));
        }
    } while (Process32Next(hProcessSnap, &pe32));



    // 6. CLEAN UP
    CloseHandle(hProcessSnap);
    CloseHandle(hThreadSnap);
    std::cout << "------------------------------------------------------------------------------\n\n";
    std::cout << "SCANNING COMPLETE.\n\n\n";


    system("pause");
    return 0;
}