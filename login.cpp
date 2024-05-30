#include <iostream>
#include <fstream>

using namespace std;

class login
{
protected:
    string email;
    string username;
    string password;

public:
    void checklogin()
    {
        int flag = 0;
        string tempusername, temppassword, tempemail;
        bool loopend = false;
        ifstream fin;
        fin.open("signin.txt", ios::in);

        if (!fin)
        {
            cout << "file not opened" << endl;
            exit(1);
        }

        else
        {
            while (loopend == false)
            {
                while (fin >> tempemail >> tempusername >> temppassword)
                {
                    if (username == tempusername && temppassword == password)
                    {

                        cout << "login successful!" << endl;
                        flag = 1;
                        loopend = true;
                    }
                }
                if (flag == 0)
                {
                    cout << "login failed!" << endl;
                    fin.clear();
                    fin.seekg(ios_base::beg);
                    enter_credentials();
                }
                        }
            fin.close();
        }
    }
    void enter_credentials()
    {
        cout << "enter username" << endl;
        cin >> username;
        cout << "enter password" << endl;
        cin >> password;
    }
};
int main()
{
    login l1;
    l1.enter_credentials();
    l1.checklogin();
}