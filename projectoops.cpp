#include <iostream>
#include <conio.h>
#include <ctime>
#include <string.h>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
#include <cstdlib>

// 22k-4483 ANAS KHAN

// 22K-4139 UMAR AURANGZEB
// 22-4379 MUHAMMAD AZIF
using namespace std;

class shop;
class user;
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
    static int getnumberofshops() { return numberofshops; }
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
int main();
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
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << "email already in use" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
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
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << "username already in use" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                cout << "sign in successful!" << endl;
                fout.close();
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            }
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
    friend class user;

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
    friend class cart;

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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                cout << "product successfully added to shop!" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
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
            cout << "product removed successfully" << endl;
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

    void viewspecificshop()
    {
        int a, b, i;
        int tempid, temmpquantity, tempprice;
        string tempname, temmpdescription, temmptype, tempbrand;

        bool check = false;

        ifstream fin;

        fin.open("shop" + shopid + ".txt", ios::in);
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            cout << setfill('-') << setw(109) << "" << endl;
            cout << "| " << setw(15) << setfill(' ') << "ID"
                 << " | " << setw(15) << "NAME"
                 << " | " << setw(15) << "DESCRIPTION"
                 << " | " << setw(15) << "TYPE"
                 << " | " << setw(15) << "BRAND"
                 << " | " << setw(15) << "PRICE"

                 << " |" << endl;
            cout << setfill('-') << setw(109) << "" << endl;
            while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
            {

                cout << setfill(' ');
                cout << "| " << setw(15) << tempid
                     << " | " << setw(15) << tempname
                     << " | " << setw(15) << temmpdescription
                     << " | " << setw(15) << temmptype
                     << " | " << setw(15) << tempbrand
                     << " | " << setw(15) << tempprice
                     << " |" << endl;
            }
            cout << setfill('-') << setw(109) << "" << endl;
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
    login(string email, string username, string password) : email(email), username(username), password(password) {}
    login() {}
    int checkloginuser()
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
                    // cout << tempemail << " " << tempusername << " " << temppassword << " " << dummyid << endl;
                    if (username == tempusername && temppassword == password)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                        cout << "login successful!" << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                        Sleep(1000);
                        flag = 1;
                        loopend = true;
                        fin.close();
                        return 1;
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
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                        cout << "login successful!" << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                        cout << "Welcome Shop " + shopid << " Owner!!" << endl;
                        flag = 1;
                        loopend = true;
                        return shopid;
                    }
                }
                if (flag == 0)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << "login failed!" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
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
class cart
{
    int *fileid = new int[20], id, tempid;
    string *name = new string[20], tempname;
    string *description = new string[20], temmpdescription;
    string *type = new string[20], temmptype;
    int *quantity = new int[20], temmpquantity;
    int *price = new int[20], tempprice;
    string *brand = new string[20], tempbrand;
    int quantity1;

    static int ctr;
    bool discount = false;
    bool check = false;

public:
    void addtocart()
    {

        int i = 0;
        ifstream fin;

        string ctr1 = "1";

        cout << "Enter product id that you want to add to cart";
        cin >> id;

        for (i = 0; i < 7; i++)
        {
            fin.open("shop" + ctr1 + ".txt", ios::in);
            if (!fin)
            {
                cout << "file not opened" << endl;
            }
            else
            {
                while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
                {

                    if (tempid == id)
                    {
                        cout << "Enter quantity";
                        cin >> quantity1;

                        fileid[ctr] = id;
                        name[ctr] = tempname;
                        description[ctr] = temmpdescription;
                        type[ctr] = temmptype;
                        quantity[ctr] = quantity1;
                        price[ctr] = tempprice;
                        brand[ctr] = tempbrand;
                        ctr++;
                        check = true;
                    }
                }
            }
            if (check == true)
            {
                fin.close();
                check = false;
                break;
            }
            int ctr3 = stoi(ctr1);
            ++ctr3;
            ctr1 = to_string(ctr3);
            fin.close();
        }
        if (i == 7)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Product not found!\n"

                 << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            Sleep(1200);
            addtocart();
        }
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
        cout << "Product added successfully!" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    }
    void removefromcart()
    {
        bool found = false;

        cout << "Enter prodct ID that you want to remove ";
        cin >> id;
        for (int i = 0; i < ctr; i++)
        {
            if (id == fileid[i])
            {
                for (int j = i; j < 20 - 1; j++)
                {
                    fileid[j] = fileid[j + 1];
                    name[j] = name[j + 1];
                    description[j] = description[j + 1];
                    type[j] = type[j + 1];
                    quantity[j] = quantity[j + 1];
                    price[j] = price[j + 1];
                    brand[j] = brand[j + 1];
                    found = true;
                }
            }
        }
        if (found == false)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Product not found" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        else
        {
            ctr--;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
            cout << "Product successfully removed!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
    }

    void displaycart()
    {
        cout << setfill('-') << setw(127) << "" << endl;
        cout << "| " << setw(15) << setfill(' ') << "ID"
             << " | " << setw(15) << "NAME"
             << " | " << setw(15) << "DESCRIPTION"
             << " | " << setw(15) << "TYPE"
             << " | " << setw(15) << "QUANTITY"
             << " | " << setw(15) << "BRAND"
             << " | " << setw(15) << "PRICE"

             << " |" << endl;
        cout << setfill('-') << setw(127) << "" << endl;
        for (int i = 0; i < ctr; i++)
        {

            cout << setfill(' ');
            cout << "| " << setw(15) << fileid[i]
                 << " | " << setw(15) << name[i]
                 << " | " << setw(15) << description[i]
                 << " | " << setw(15) << type[i]
                 << " | " << setw(15) << quantity[i]
                 << " | " << setw(15) << brand[i]
                 << " | " << setw(15) << price[i]
                 << " |" << endl;
        }
        cout << setfill('-') << setw(127) << "" << endl;
    }

    void checkout()
    {
        string coupon;
        string code[4] = {"1234", "HELLO", "SIGH", "WHAT"};
        srand(time(0));
        string rider[4] = {"ALi", "umar", "azif", "asfand"}, answer;
        int random = (rand() % (100 - 20 + 1)) + 20;
        cout << "Do you have a coupon? Press[Y/N]";
        cin >> answer;
        if (answer == "Y" || answer == "y")
        {
            cout << "Enter a discount coupon";
            cin >> coupon;
            for (int i = 0; i < 4; i++)
            {
                if (coupon == code[i])
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                    cout << "Congratulations! You got 20% discount" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                    discount = true;
                    break;
                }
            }
        }
        int totalprice = 0;
        for (int i = 0; i < ctr; i++)
        {
            totalprice += (price[i] * quantity[i]);
        }
        float reducedprice = 0;
        float gst = (float)totalprice * 0.13;
        Sleep(1000);
        system("cls");
        cout << endl;

        cout << setw(179) << "YOUR BILL-----------------------------------------------------------------------------------------\n\n\n";
        cout << setfill('-') << setw(127) << "" << endl;
        cout << "| " << setw(15) << setfill(' ') << "ID"
             << " | " << setw(15) << "NAME"
             << " | " << setw(15) << "DESCRIPTION"
             << " | " << setw(15) << "TYPE"
             << " | " << setw(15) << "QUANTITY"
             << " | " << setw(15) << "BRAND"
             << " | " << setw(15) << "PRICE"

             << " |" << endl;
        cout << setfill('-') << setw(127) << "" << endl;
        for (int i = 0; i < ctr; i++)
        {

            cout << setfill(' ');
            cout << "| " << setw(15) << fileid[i]
                 << " | " << setw(15) << name[i]
                 << " | " << setw(15) << description[i]
                 << " | " << setw(15) << type[i]
                 << " | " << setw(15) << quantity[i]
                 << " | " << setw(15) << brand[i]
                 << " | " << setw(15) << price[i]
                 << " |" << endl;
        }
        cout << setfill('-') << setw(127) << "" << endl
             << endl
             << endl
             << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill(' ');
        cout << "| " << setw(15) << "SUB TOTAL";
        cout << " | " << setw(15) << totalprice
             << " |" << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill(' ');
        cout << "| " << setw(15) << "13% GST";
        cout << " | " << setw(15) << gst
             << " |" << endl;
        if (discount == true)
        {
            cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
            cout << setw(89) << right << setfill(' ') << "" << setfill(' ');
            cout << "| " << setw(15) << "DISCOUNT";
            reducedprice = (float)totalprice * 0.2;
            cout << " | " << setw(15) << reducedprice
                 << " |" << endl;
        }
        else
        {
            cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
            cout << setw(89) << right << setfill(' ') << "" << setfill(' ');
            cout << "| " << setw(15) << "DISCOUNT";
            cout << " | " << setw(15) << "0.00"
                 << " |" << endl;
        }

        cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl
             << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
        cout << setw(89) << right << setfill(' ') << "" << setfill(' ');
        int fulltotal = totalprice + gst - reducedprice;
        cout << "| " << setw(15) << "TOTAL";
        cout << " | " << setw(15) << fulltotal
             << " |" << endl;

        cout << setw(89) << right << setfill(' ') << "" << setfill('-') << setw(38) << "" << endl;
        discount = false;
    }
};
int cart::ctr = 0;

void addnewproduct(shop obj)
{
    int id;
    string name;
    string description;
    string type;
    int quantity;
    int price;
    string brand;
    cout << "Adding new product: " << endl;
    cout << "------------------" << endl;
    cout << "Input product ID: ";
    cin >> id;
    cout << "Input name: ";
    cin >> name;
    cout << "Input description: ";
    cin >> description;
    cout << "Input type: ";
    cin >> type;
    cout << "Input quantity: ";
    cin >> quantity;
    cout << "Input price: ";
    cin >> price;
    cout << "Input brand: ";
    cin >> brand;
    product newproduct(id, name, description, type, quantity, price, brand);
    obj.addproduct(&newproduct);
}
class user
{
    int id, tempid;
    string tempname, name;
    string temmpdescription;
    string temmptype;
    int temmpquantity;
    int tempprice;
    string tempbrand;
    friend class shop;

public:
    user()
    {
    }
    void searchproduct()
    {
        int a, b, i;
        bool check = false;

        ifstream fin;
        string ctr1 = "1";

        cout << "Press 1 to search with product id\nPress 2 to search with product name: ";
        cin >> a;
        while (a != 1 && a != 2)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Wrong input! Enter again: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            cin >> a;
        }

        if (a == 1)
        {
            cout << "Enter product id that you want to search: ";
            cin >> id;
            for (i = 0; i < 7; i++)
            {
                fin.open("shop" + ctr1 + ".txt", ios::in);
                if (!fin)
                {
                    cout << "file not opened" << endl;
                }
                else
                {
                    while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
                    {
                        if (tempid == id)
                        {
                            cout << setfill('-') << setw(109) << "" << endl;
                            cout << "| " << setw(15) << setfill(' ') << "ID"
                                 << " | " << setw(15) << "NAME"
                                 << " | " << setw(15) << "DESCRIPTION"
                                 << " | " << setw(15) << "TYPE"
                                 << " | " << setw(15) << "BRAND"
                                 << " | " << setw(15) << "PRICE"

                                 << " |" << endl;
                            cout << setfill('-') << setw(109) << "" << endl;

                            cout << setfill(' ');
                            cout << "| " << setw(15) << tempid
                                 << " | " << setw(15) << tempname
                                 << " | " << setw(15) << temmpdescription
                                 << " | " << setw(15) << temmptype
                                 << " | " << setw(15) << tempbrand
                                 << " | " << setw(15) << tempprice
                                 << " |" << endl;
                            cout << setfill('-') << setw(109) << "" << endl
                                 << endl
                                 << endl
                                 << endl;

                            check = true;
                        }
                    }
                }
                int ctr3 = stoi(ctr1);
                ++ctr3;
                ctr1 = to_string(ctr3);
                if (check == true)
                {
                    check = false;
                    break;
                }
                fin.close();
            }
        }
        else if (a == 2)
        {
            cout << "Enter product name that you want to search: ";
            cin >> name;
            for (i = 0; i < 7; i++)
            {
                fin.open("shop" + ctr1 + ".txt", ios::in);
                if (!fin)
                {
                    cout << "file not opened" << endl;
                }
                else
                {
                    while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
                    {
                        if (tempname == name)
                        {
                            cout << setfill('-') << setw(109) << "" << endl;
                            cout << "| " << setw(15) << setfill(' ') << "ID"
                                 << " | " << setw(15) << "NAME"
                                 << " | " << setw(15) << "DESCRIPTION"
                                 << " | " << setw(15) << "TYPE"
                                 << " | " << setw(15) << "BRAND"
                                 << " | " << setw(15) << "PRICE"

                                 << " |" << endl;
                            cout << setfill('-') << setw(109) << "" << endl;
                            for (int i = 0; i < 1; i++)
                            {

                                cout << setfill(' ');
                                cout << "| " << setw(15) << tempid
                                     << " | " << setw(15) << tempname
                                     << " | " << setw(15) << temmpdescription
                                     << " | " << setw(15) << temmptype
                                     << " | " << setw(15) << tempbrand
                                     << " | " << setw(15) << tempprice
                                     << " |" << endl;
                                cout << setfill('-') << setw(109) << "" << endl
                                     << endl
                                     << endl
                                     << endl;
                            }
                            check = true;
                        }
                    }
                }
                int ctr3 = stoi(ctr1);
                ++ctr3;
                ctr1 = to_string(ctr3);
                if (check == true)
                {
                    check = false;
                    break;
                }
                fin.close();
            }
        }
        else if (a != 1 && a != 2)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Wrong input! Enter again: " << endl
                 << endl;
            cin >> a;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }

        if (i == 7)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Product not found!" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
    }
    void viewshop()
    {
        int a, b, i;

        bool check = false;
        string shopid;
        ifstream fin;

        cout << "Enter shop id: ";
        cin >> shopid;
        while (shopid != "1" && shopid != "2" && shopid != "3" && shopid != "4" && shopid != "5" && shopid != "6" && shopid != "7")
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Wrong shop id! Enter again: " << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            cin >> shopid;
        }

        fin.open("shop" + shopid + ".txt", ios::in);
        if (!fin)
        {
            cout << "file not opened" << endl;
        }
        else
        {
            cout << setfill('-') << setw(109) << "" << endl;
            cout << "| " << setw(15) << setfill(' ') << "ID"
                 << " | " << setw(15) << "NAME"
                 << " | " << setw(15) << "DESCRIPTION"
                 << " | " << setw(15) << "TYPE"
                 << " | " << setw(15) << "BRAND"
                 << " | " << setw(15) << "PRICE"

                 << " |" << endl;
            cout << setfill('-') << setw(109) << "" << endl;
            while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
            {

                cout << setfill(' ');
                cout << "| " << setw(15) << tempid
                     << " | " << setw(15) << tempname
                     << " | " << setw(15) << temmpdescription
                     << " | " << setw(15) << temmptype
                     << " | " << setw(15) << tempbrand
                     << " | " << setw(15) << tempprice
                     << " |" << endl;
            }
            cout << setfill('-') << setw(109) << "" << endl;
        }
    }
    void viewallproducts()
    {
        int a, b;

        bool check = false;
        string ctr1 = "1";
        ifstream fin;
        cout << setfill('-') << setw(109) << "" << endl;
        cout << "| " << setw(15) << setfill(' ') << "ID"
             << " | " << setw(15) << "NAME"
             << " | " << setw(15) << "DESCRIPTION"
             << " | " << setw(15) << "TYPE"
             << " | " << setw(15) << "BRAND"
             << " | " << setw(15) << "PRICE"

             << " |" << endl;
        cout << setfill('-') << setw(109) << "" << endl;
        for (int i = 0; i < 7; i++)
        {
            fin.open("shop" + ctr1 + ".txt", ios::in);
            if (!fin)
            {
                cout << "file not opened" << endl;
            }
            else
            {

                while (fin >> tempid >> tempname >> temmpdescription >> temmptype >> temmpquantity >> tempprice >> tempbrand)
                {

                    cout << setfill(' ');
                    cout << "| " << setw(15) << tempid
                         << " | " << setw(15) << tempname
                         << " | " << setw(15) << temmpdescription
                         << " | " << setw(15) << temmptype
                         << " | " << setw(15) << tempbrand
                         << " | " << setw(15) << tempprice
                         << " |" << endl;
                }
                cout << setfill('-') << setw(109) << "" << endl;
            }
            int ctr3 = stoi(ctr1);
            ++ctr3;
            ctr1 = to_string(ctr3);
            if (check == true)
            {
                check = false;
                break;
            }
            fin.close();
        }
    }
    void usermenu(cart ob1)

    {
        int c, d, e;
        cout << "Please choose from the following menu\n\n";
        cout << "1) Search a product " << endl;
        cout << "2) Search a specific shop " << endl;
        cout << "3) View all products" << endl;
        cout << "4) View cart" << endl;
        cout << "5) To logout" << endl;
        cin >> c;
        if (c == 1)
        {
            system("cls");
            searchproduct();

            do
            {
                cout << "Press 1 to add to cart: " << endl;
                cout << "Press 2 to go back: " << endl;
                cin >> d;

                if (d == 1)
                {

                    ob1.addtocart();
                }
                else if (d == 2)
                {
                    system("cls");
                    usermenu(ob1);
                }
            } while (d != 2);
        }
        else if (c == 2)
        {
            system("cls");
            viewshop();
            do
            {
                cout << "Press 1 to add to cart: " << endl;
                cout << "Press 2 to go back: " << endl;
                cin >> d;

                if (d == 1)
                {

                    ob1.addtocart();
                }
                else if (d == 2)
                {
                    system("cls");
                    usermenu(ob1);
                }
            } while (d != 2);
        }
        else if (c == 3)
        {
            system("cls");
            viewallproducts();
            do
            {
                cout << "Press 1 to add to cart: " << endl;
                cout << "Press 2 to go back: " << endl;
                cin >> d;

                if (d == 1)
                {

                    ob1.addtocart();
                }
                else if (d == 2)
                {
                    system("cls");
                    usermenu(ob1);
                }
            } while (d != 2);
        }
        else if (c == 4)
        {
            char ch;
            system("cls");
            ob1.displaycart();
            cout << "Press 1 to remove a product from the cart" << endl;
            cout << "Press 2 to go to checkout: " << endl;
            cout << "Press 3 to go back: " << endl;
            cin >> d;
            while (d != 1 && d != 2 && d != 3)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                cout << "Input again: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                cin >> d;
            }

            if (d == 1)
            {
                system("cls");
                ob1.displaycart();
                ob1.removefromcart();
                Sleep(1200);
                system("cls");
                ob1.displaycart();

                cout << "Do you want to remove anythhing else?[Y/N]" << endl;
                cin >> ch;
                while (ch == 'y' || ch == 'Y')
                {

                    ob1.removefromcart();
                    Sleep(1200);
                    system("cls");
                    ob1.displaycart();
                    cout << "Do you want to remove anythhing else?[Y/N]" << endl;
                    cin >> ch;
                }
                system("cls");
                usermenu(ob1);
            }

            else if (d == 2)
            {
                system("cls");
                ob1.checkout();
                cout << "Press 1 to place order:" << endl;
                cout << "Press 2 to go back:" << endl;
                cin >> e;
                while (e != 1 && e != 2)
                {
                    cout << "Input again: ";
                    cin >> e;
                }

                if (e == 1)
                {
                    srand(time(NULL));
                    string rider[4] = {"ALi", "umar", "azif", "asfand"}, answer;
                    int random = (rand() % (100 - 20 + 1)) + 20;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                    cout << "ORDER CONFIRMED!!" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                    cout << "Your order will be delivered in " << random << " minutes." << endl;
                    random = (rand() % (3 - 0 + 1)) + 0;
                    cout << "Your rider is " << rider[random] << endl;
                    cout << "THANK YOU FOR CHOOSING US" << endl;
                    exit(0);
                }
                else if (e == 2)
                {
                    system("cls");
                    usermenu(ob1);
                }
            }
            else if (d == 3)
            {
                system("cls");
                usermenu(ob1);
            }
        }
        else if (c == 5)
        {
            main();
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Invalid input" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            Sleep(500);
            system("cls");
            usermenu(ob1);
        }
    }
};
int main()
{
    system("cls");
    // seller s1;
    // s1.signup();
    //  s1.LOGIN();
    system("color f0");
    string a, a1, a2, b, b1, b2, c;
    a1 = "login";
    a2 = "signup";
    b1 = "admin";
    b2 = "user";
    int x;
    char w;
    string chh = "WELCOME TO OOP ONLINE MALL";
    cout << setw(58);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);

    for (int i = 0; i < chh.length(); i++)

    {
        Sleep(20);
        cout << chh[i];
    }
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
    cout << endl;

    do
    {
        cout << "Please choose from the following menu:" << endl
             << endl;
        cout << "Enter 'Admin' if you are the admin" << endl;
        cout << "Enter 'Seller' if you are a seller" << endl;
        cout << "Enter 'User' if you are a user" << endl;
        cin >> b;
        transform(b.begin(), b.end(), b.begin(), ::tolower);
        system("cls");
        if (b == b1)
        {
            string a;
            system("cls");
            string ch = "WELCOME ADMIN";
            cout << "Input admin username: ";
            cin >> c;
            cout << "Input admin password: ";
            cin >> a;
            if (c == "fast" && a == "1234")
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 250);
                cout << "Login successful" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);
                Sleep(1000);
                system("cls");
                cout << setw(58);
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);

                for (int i = 0; i < ch.length(); i++)

                {
                    Sleep(20);
                    cout << ch[i];
                }

                cout << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

                malladmin ob;
                int id;
                char v, w, y;
                do
                {
                    cout << endl
                         << "Press 1 to display mall details\nPress any other key to go back" << endl;
                    cin >> y;
                    switch (y)
                    {
                    case '1':
                        ob.displaydetails();
                        break;
                    }
                } while (y == '1');
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                cout << endl
                     << "Wrong id or password" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            }
        }
        else if (b == "seller")
        {
            int v, w, p;
            seller ob1;
            shop obj;
            do
            {
                cout << "Press: " << endl
                     << endl;
                cout << "1) to signin/login" << endl;
                cout << "2) to signup" << endl;
                cin >> v;

                string ch = "WELCOME SELLER";
                switch (v)
                {
                case 1:
                    obj = ob1.LOGIN();
                    Sleep(1000);
                    system("cls");
                    cout << setw(70);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);

                    for (int i = 0; i < ch.length(); i++)

                    {
                        Sleep(20);
                        cout << ch[i];
                    }
                    cout << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                    do
                    {
                        cout << "Press: " << endl
                             << endl
                             << "1) to add a new product" << endl
                             << "2) to remove a product" << endl;
                        cout << "3) to view your shop" << endl;
                        cout << "4) to go back" << endl;
                        cin >> x;
                        switch (x)
                        {
                        case 1:
                            addnewproduct(obj);
                            break;

                        case 2:
                            cout << "Input product id that you want to remove : ";
                            cin >> w;
                            obj.remove_product(w);
                            break;
                        case 3:
                            obj.viewspecificshop();
                            break;
                        case 4:
                            main();

                        default:
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                            cout << "Invalid Input" << endl;
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                            break;
                        }

                    } while (x != 4);

                case 2:

                    ob1.signup();
                    if (malladmin::getnumberofshops() < 7)
                    {
                        cout << "Signup successful! Please login again to update a shop " << endl;
                    }
                    Sleep(1000);
                    system("cls");
                    main();
                    break;

                default:
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                    cout << "Invalid Input!" << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                }
            } while (p != 1 || p != 2);
        }
        else if (b == b2)
        {
            cout << "Enter: " << endl
                 << endl;
            cout << "'Login' to sign in into an existing account." << endl;
            cout << "'Signup' to create a new account." << endl;
            cin >> a;
            transform(a.begin(), a.end(), a.begin(), ::tolower);
            string email;
            string username;
            string password;
            if (a == a1)
            {
                login ob;
                int v;
                ob.enter_credentials();
                v = ob.checkloginuser();
                if (v == 1)
                {
                    user ob1;
                    cart ob2;
                    system("cls");
                    string ch = "WELCOME USER";
                    cout << setw(59);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 249);

                    for (int i = 0; i < ch.length(); i++)

                    {
                        Sleep(20);
                        cout << ch[i];
                    }
                    cout << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);

                    ob1.usermenu(ob2);
                }
            }
            else if (a == a2)
            {
                signin s1;
                s1.set_credentials();
                s1.save_credentials();
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
                cout << "Invalid input" << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
            }
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 252);
            cout << "Invalid input" << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
        }
        cout << endl
             << "Go back to homescreen?[Y/N]" << endl;
        cin >> w;
        Sleep(1000);
        system("cls");
    } while (w == 'y' || w == 'Y');
    cout << "Exited the program successfully!" << endl;
    return 0;
}