#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <iomanip>


int main() {

    std::cout << "------------------------- CLI Process Lister -----------------------\n";

    // 1. DEFINE VARIABLES
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    pe32.dwSize = sizeof(PROCESSENTRY32);


    // 2. TAKE THE SNAPSHOT
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);


    // 3. CHECKING FOR ERRORS
    if (hProcessSnap == INVALID_HANDLE_VALUE)
    {
        std::cout << "Error: Snap Process has an invalid handle value." << std::endl;

        return -1;
    }


    // 4. GET THE FIRST PROCESS
    if (!Process32First(hProcessSnap, &pe32)) 
    {
        std::cout << "Error: The process list was not found." << std::endl;
        CloseHandle(hProcessSnap);

        return -1;
    }


    // 5. LOOP THROUGH THE REST
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(35) << "PROCESS NAME" << "PID" << std::endl;
    std::cout << "--------------------------------------------------------------------\n";

    do {
        std::wcout << std::left
            << std::setw(35) << pe32.szExeFile
            << std::setw(15) << pe32.th32ProcessID
            << std::endl;
    } while (Process32Next(hProcessSnap, &pe32));


    // 6. CLEAN UP
    CloseHandle(hProcessSnap);
    std::cout << "--------------------------------------------------------------------\n";
    std::cout << "Scanning complete.\n";
    std::cout << "--------------------------------------------------------------------\n";

    system("pause");
    return 0;
}