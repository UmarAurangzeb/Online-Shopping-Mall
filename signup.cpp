#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

class signin
{
    string email;
    string username;
    string password;

public:
    signin() {}
    signin(string email, string username, string password) : email(email), username(username), password(password) {}
    void check_email()
    {
        char emailfromfile[100];
        string line;
        ifstream fin;
        int i, flag;
        fin.open("signin.txt", ios::in);

        if (!fin)
        {
            cout << "file not opened" << endl;
        }

        else
        {
            while (!fin.eof())
            {
                getline(fin, line);
                for (i = 0; i < line.length(); i++)
                {
                    if (line[i] == ' ')
                        break;
                    else
                    {
                        emailfromfile[i] = line[i];
                    }
                }
                emailfromfile[i] = '\0';
                flag = strcmp(email.c_str(), emailfromfile);
                if (flag == 0)
                {
                    cout << "email already in use" << endl;
                    cout << "enter email:";
                    cin >> email;
                    fin.seekg(ios_base::beg);
                }
            }
            fin.close();
        }
    }
    void check_username()
    {
        char usernamefromfile[100];
        string line;
        ifstream fin;
        int i, flag, ctr, j;
        fin.open("signin.txt", ios::in);

        if (!fin)
        {
            cout << "file not opened" << endl;
        }

        else
        {
            while (!fin.eof())
            {
                ctr = 0;
                j = 0;
                getline(fin, line);
                for (i = 0; i < line.length(); i++)
                {

                    if (line[i] == ' ')
                    {
                        ctr++;
                    }
                    if (ctr == 1 && line[i] != ' ')
                    {
                        usernamefromfile[j++] = line[i];
                    }
                }
                usernamefromfile[j] = '\0';

                flag = strcmp(username.c_str(), usernamefromfile);

                if (flag == 0)
                {
                    cout << "username already in use" << endl;
                    cout << "enter username:";
                    cin >> username;
                    fin.seekg(ios_base::beg);
                }
            }
            fin.close();
        }
    }
    void save_credentials()
    {
        ofstream fout;
        fout.open("signin.txt", ios::app);
        if (!fout)
        {
            cout << "file not opened!" << endl;
            exit(1);
        }
        else
        {
            if (fout << email << " " << username << " " << password << endl)
            {
                cout << "sign in successful!" << endl;
            }
            fout.close();
        }
    }

    void displaycredentials()
    {
        cout << "email:" << email << endl;
        cout << "username:" << username << endl;
        cout << "password:" << password << endl;
    }
    void set_credentials()
    {
        cout << "enter email:" << endl;
        cin >> email;
        check_email();
        cout << "enter username:" << endl;
        cin >> username;
        check_username();
        cout << "enter password:" << endl;
        cin >> password;
    }
};
int main()
{
    signin ob1;
    ob1.set_credentials();
    ob1.save_credentials();
}