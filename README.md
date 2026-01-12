# CLI Process Lister

This code is a simple CLI utility written in **C++**, which interacts with the *Windows API*. The task is to get a list of all system active processes, their threads, and output their names, PIDs, and Thread IDs to the console.

### How does it work?

**1. Snapshot:** The OS is changing actively: processes are created and dying in milliseconds! So do threads. Because we need to read the list correctly, we cannot read it "live" from memory. So, we use a function called `CreateToolhelp32Snapshot` from the *tlhelp32.h* library. It creates an instant 'frozen' snapshot of the system's state. So, we should create a Process Snapshot and Threads Snapshot. Next, we save access to those snapshots in the variable `hProcessSnap` and `hThreadSnap` (Handle). 

**2. Data Structure:** We need a special structure - `PROCESSENTRY32`, `THREADENTRY32` - to get information about a specific process and thread. That's like a blank form, which is filled by Windows with data (file name, PID). Note that before using it, we need to set the size of this structure (`pe32.dwSize`, `te32.dwSize`), so the Windows API understands which structure version is being used. If not, the Windows API will decline the request.

**3. Loop (The Nested Approach):** We can't get the whole list at once, so we use a do-while iterator approach with a nested loop:

- **The Process Loop:** First, call `Process32First`. This function takes data from the first process in the snapshot and writes it to our structure. If found, we output the Process Name and PID.

- **The Thread Loop:** Before moving to the next process, we look through our 'frozen' Thread Snapshot (`Thread32First` and `Thread32Next`). We check every thread to see if it belongs to the current process (by matching `te32.th32OwnerProcessID` to the current `pe32.th32ProcessID`). If it matches, we print the Thread ID.

- **Repeat:** Then we call `Process32Next` to rewrite the structure with data from the next process and repeat the cycle.

**4. Cleaning:** In the end, we need to call the `CloseHandle` function for both snapshots. If not, it will cause a memory leak.

***And that's it!***
