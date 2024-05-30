#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

class malladmin
{
protected:
    int shopid;
    int numberofshops;
    bool shopowned;

public:
    malladmin() {}

    void initialdetails()
    {
        ofstream fout;
        fout.open("mall.txt");
        // adding 7 shops to mall and setting shopowned to 0
        for (int i = 1; i < 8; i++)
        {
            fout << i << " " << 0 << endl;
        }
        fout.close();
    }

    void displaydetails()
    {
        int ctr = 0, ctr2 = 0;

        ifstream fin;
        fin.open("mall.txt", ios::in);
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            while (fin >> shopid >> shopowned)
            {
                ctr++;
                if (shopowned == 0)
                {
                    ctr2++;
                }
            }
            numberofshops = ctr;
            cout << "number of shops: " << numberofshops << endl;
            cout << "number of shops currently available: " << ctr2 << endl;
            cout << "number of shops occupied:" << numberofshops - ctr2 << endl;
            fin.close();
        }
    }
    void remove_shop(int id)
    {
        ifstream fin;
        ofstream fout;
        int flag = 0;
        fin.open("mall.txt", ios::in);
        fout.open("mall1.txt");
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        if (!fout)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            while (fin >> shopid >> shopowned)
            {

                if (id == shopid && shopowned == 1)
                {
                    shopowned = 0;
                    fout << shopid << " " << shopowned << endl;
                    flag = 1;
                }
                else if (id == shopid && shopowned == 0)
                {
                    cout << "shop already is not owned by anyone!" << endl;
                }
                else
                {
                    fout << shopid << " " << shopowned << endl;
                }
            }
            const char *oldfile = "mall.txt";
            const char *newfile = "mall1.txt";
            if (flag == 0)
            {
                remove(newfile);
            }
            else
            {
                fin.close();
                fout.close();
                remove(oldfile);
                rename(newfile, oldfile);

                cout << "shopowner of shop " << id << " successfully removed!" << endl;
            }
        }
    }
    void add_shopowner(int id)
    {
        ifstream fin;
        ofstream fout;
        int flag = 0;
        fin.open("mall.txt", ios::in);
        fout.open("mall1.txt");
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        if (!fout)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            while (fin >> shopid >> shopowned)
            {

                if (id == shopid)
                {
                    shopowned = 1;
                    fout << shopid << " " << shopowned << endl;
                    flag = 1;
                }
                else
                {
                    fout << shopid << " " << shopowned << endl;
                }
            }
            const char *oldfile = "mall.txt";
            const char *newfile = "mall1.txt";
            if (flag == 0)
            {
                remove(newfile);
            }
            else
            {
                fin.close();
                fout.close();
                remove(oldfile);
                rename(newfile, oldfile);
            }
        }
    }
};

// int malladmin::numberofshops = 0;

int main()
{
    malladmin admin;
    // admin.initialdetails();
    // admin.remove_shop(4);
    admin.add_shopowner(5);
}