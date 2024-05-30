
#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <string.h>
using namespace std;

class shop;
class malladmin
{
protected:
    int shopid;
    static int numberofshops;
    int shopowned;
    int numberofshopsowned;
    friend class seller;

public:
    malladmin() {}
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
    void remove_shopowner(int id)
    {
        ifstream fin;
        ofstream fout;
        int flag = 0;
        fin.open("mall.txt", ios::in);
        fout.open("mall1.txt", ios::app);
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
                rename(newfile, oldfile);
                remove(oldfile);
                cout << "shopowner of shop" << shopid << " successfully removed!";
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
    static int numberofshopsoccupied()
    {
        ifstream fin;
        int tempshopid, ctr = 0;
        bool tempshopowned;

        fin.open("mall.txt");
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            while (fin >> tempshopid >> tempshopowned)
            {
                if (tempshopowned == 1)
                {
                    ctr++;
                }
            }
            fin.close();
        }
        numberofshops = ctr;
        return numberofshops;
    }
    int getshopid()
    {
        return shopid;
    }
    bool getshopowned()
    {
        return shopowned;
    }
};
int malladmin::numberofshops = 0;

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
        fout.open("signin.txt", ios::out | ios::app);
        if (!fout)
        {
            cout << "file not opened!" << endl;
            exit(1);
        }
        else
        {
            if (fout << email << " " << username << " " << password << " " << 'N' << endl)
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

class product
{
protected:
    int id;
    string name;
    string description;
    string type;
    int quantity;
    int price;
    string brand;

public:
    product(int id, string name, string description, string type, int quantity, int price, string brand) : id(id), name(name), description(description), type(type), quantity(quantity), price(price), brand(brand) {}
    product() { id = 0; }
    int getId() { return id; }
    string getName() { return name; }
    string getDescription() { return description; }
    int getQuantity() { return quantity; }
    string getbrand() { return brand; }
    void setid(int x) { id = x; }
    void setname(string x) { name = x; }
    void settype(string x) { type = x; }
    void setdescription(string x) { description = x; }
    void setquantity(int x) { quantity = x; }
    void operator--() { quantity--; }
    string getType() { return type; }
    int getPrice() { return price; }
    void setPrice(int x) { price = x; }
    void setbrand(string x) { brand = x; }
    friend class shop;
    friend bool operator==(product, product);
};

class shop
{
protected:
    string shopid;
    string shopname;
    string shopdescription;
    product *p;
    int productcount;

public:
    shop(string name, string description) : shopname(name), shopdescription(description), productcount(0)
    {
    }
    shop(string shopid) : shopid(shopid), shopname("NULL"), shopdescription("NULL")
    {
    }

    shop()
    {
    }
    string getId() { return shopid; }
    string getName() { return shopname; }
    string getDescription() { return shopdescription; }
    int getproductcount() { return productcount; }
    void setname(string a) { shopname = a; }
    void setdescription(string a) { shopdescription = a; }
    void setshopid(string a) { shopid = a; }

    void addproduct(product *prod)
    {

        fstream fout;
        fout.open("shop" + shopid + ".txt", ios::app);
        if (!fout)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            if (fout << prod->getId() << " " << prod->getName() << " " << prod->getDescription() << " " << prod->getType() << " " << prod->getQuantity() << " " << prod->getPrice() << " " << prod->getbrand() << endl)
            {
                cout << "product successfully added to shop!" << endl;
            }
            fout.close();
        }
    }
    void remove_product(int x)
    {
        ifstream fin;
        ofstream fout;
        string line;
        int ctr = 0;
        fin.open("shop" + shopid + ".txt", ios::in);
        fout.open("temp.txt");

        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            p = new product();
            while (fin >> p->id >> p->name >> p->description >> p->type >> p->quantity >> p->price >> p->brand)
            {
                fin.get();
                if (p->id == x)
                {
                    continue;
                }
                else
                {
                    fout << p->id << " " << p->name << " " << p->description << " " << p->type << " " << p->quantity << " " << p->price << " " << p->brand << " " << endl;
                }
            }
            fin.close();
            fout.close();
            const char *oldfile = ("shop" + shopid + ".txt").c_str();
            const char *newfile = "temp.txt";
            remove(oldfile);
            rename(newfile, oldfile);
        }
    }

    void numberofproductsinshops()
    {
        char ch;
        int ctr = 0;

        ifstream fin;

        fin.open("shop" + shopid + ".txt", ios::in);
        if (!fin)
        {
            cout << "file not opened!" << endl;
            exit(1);
        }
        else
        {

            while (!fin.eof())
            {
                ch = fin.get();
                if (ch == '\n')
                {
                    ctr++;
                }
            }

            cout << " total number of products in shop=" << ctr << endl;
            fin.close();
        }
    }
};
class login
{
protected:
    string email;
    string username;
    string password;

public:
    void checkloginuser()
    {
        int flag = 0;
        char dummyid;
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
                while (fin >> tempemail >> tempusername >> temppassword >> dummyid)
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
    string checklogin_seller()
    {
        int flag = 0;
        string shopid;
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
                while (fin >> tempemail >> tempusername >> temppassword >> shopid)
                {
                    if (username == tempusername && temppassword == password)
                    {

                        cout << "login successful!" << endl;
                        cout << "welcome shop " + shopid << "!!" << endl;
                        flag = 1;
                        loopend = true;
                        return shopid;
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
class seller
{
    signin *Signin;
    login *Login;
    shop *Shop;
    int numberofsellers;

public:
    seller()
    {
        Signin = new signin();
        Login = new login();

        numberofsellers = malladmin::numberofshopsoccupied();
    }
    void signup()
    {
        if (numberofsellers == 7)
        {
            cout << "no shops available!" << endl;
        }
        else
        {
            Signin->set_credentials();
            Signin->save_credentials();
            fstream file2;
            fstream file;
            malladmin *Mall;
            Mall = new malladmin();
            int ctr;
            file2.open("signin.txt", ios::in | ios::out);

            file.open("mall.txt");
            if (!file2 || !file)
            {
                cout << "file not opened!" << endl;
                exit(1);
            }
            else

            {
                while (file >> Mall->shopid >> Mall->shopowned)
                {
                    if (Mall->shopowned == 0)
                    {
                        file2.seekp(-3, ios_base::end);
                        file2 << Mall->shopid << endl;
                        break;
                    }
                }
                file.close();
                file2.close();
                Mall->add_shopowner(Mall->shopid);
                delete[] Mall;
            }
        }
    }

    shop LOGIN()
    {
        Login->enter_credentials();
        Shop = new shop(Login->checklogin_seller());
        return *Shop;
    }

    ~seller()
    {
        delete Signin;
        delete Login;
        delete Shop;
    }
};
int main()
{

    signin s1;
    s1.set_credentials();
    s1.save_credentials();
    login l1;
    l1.enter_credentials();
    l1.checkloginuser();
}