#include <iostream>
#include <conio.h>

int main()
{
    std::string password;
    char ch;

    std::cout << "Enter password: ";

    // Read each character without displaying it on the console
    while ((ch = _getch()) != '\r')
    { // '\r' represents the Enter key
        if (ch == '\b')
        { // '\b' represents the Backspace key
            if (!password.empty())
            {
                password.pop_back();
                std::cout << "\b \b"; // Clear the previous character from the console
            }
        }
        else
        {
            password.push_back(ch);
            std::cout << '*'; // Display asterisk instead of the actual character
        }
    }

    std::cout << std::endl
              << "Password entered: " << password << std::endl;

    return 0;
}
