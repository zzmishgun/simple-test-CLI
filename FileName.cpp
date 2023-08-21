#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

int main() {
    while (true) {
        std::cout << "MyShell> ";
        std::string input;
        std::getline(std::cin, input);

        if (input == "exit") {
            break; // Exit the loop if the user types "exit"
        }

        // Parse the command and arguments
        std::stringstream ss(input);
        std::string command;
        ss >> command;

        // Convert narrow string to wide string
        std::wstring wideCommand(command.begin(), command.end());

        // Execute the command using CreateProcess
        STARTUPINFOW si = {};
        PROCESS_INFORMATION pi = {};

        if (CreateProcessW(NULL, const_cast<LPWSTR>(wideCommand.c_str()), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
            WaitForSingleObject(pi.hProcess, INFINITE);
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }
        else {
            std::cerr << "Error executing command." << std::endl;
        }
    }

    return 0;
}
