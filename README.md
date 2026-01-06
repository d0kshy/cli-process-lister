# CLI Process Lister

This code is a simple CLI utility written in C++, which interacts with the Windows API. The task is to get a list of all system active processes and output their names and PIDs to a table.

### How does it work?

**1. Snapshot:**  
The OS is changing actively: processes are created and dying in milliseconds! Because we need to read the list correctly, we cannot read it "live" from memory. So, we use a function called `CreateToolhelp32Snapshot` from the *tlhelp32.h* library. It creates an instant 'frozen' snapshot of the system's state. We save access to this snapshot in the variable `hProcessSnap` (Handle).

**2. Data Structure:**  
We need a special structure — `PROCESSENTRY32` — to get information about a specific process. That's like a blank form, which is filled by Windows with data (file name, PID). Note that before using it, we need to set the size of this structure (`pe32.dwSize`), so the Windows API understands which structure version is being used. If not, the Windows API will decline the request.

**3. Loop:**  
We can't get the whole list at once, so we use a do-while iterator approach:

- First, call `Process32First`. This function takes data from the first process in the snapshot and writes it down to our structure.

- If the first process is found, we start a do-while loop. Inside the loop, we output data to the screen, then call the function `Process32Next` to rewrite the structure with data from the next process.

**4. Cleaning:**  
In the end, we need to call the `CloseHandle` function. If not, it will cause a memory leak.

# ***And that's it! :)***