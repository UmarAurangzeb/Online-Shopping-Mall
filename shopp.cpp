#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
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
int main()
{
    product p1(1, "Running Shoes", "Men's Running Shoes", "Shoes", 10, 80, "Brand X");
    product p2(2, "Sneakers", "Women's Sneakers", "Shoes", 15, 50, "Brand Y");
    product p3(3, "Boots", "Winter Boots", "Shoes", 5, 120, "Brand Z");
    product p4(4, "Sandals", "Beach Sandals", "Shoes", 20, 30, "Brand A");

    // Beauty
    product p5(5, "Lipstick", "Red Lipstick", "Beauty", 50, 15, "Brand B");
    product p6(6, "Mascara", "Lengthening Mascara", "Beauty", 30, 20, "Brand C");
    product p7(7, "Moisturizer", "Face Moisturizer", "Beauty", 25, 25, "Brand D");
    product p8(8, "Perfume", "Floral Perfume", "Beauty", 40, 50, "Brand E");

    // Books
    product p9(9, "Novel", "Mystery Novel", "Books", 20, 10, "Brand F");
    product p10(10, "Non-Fiction Book", "Science Book", "Books", 15, 15, "Brand G");
    product p11(11, "Fantasy Book", "Epic Fantasy Book", "Books", 12, 20, "Brand H");
    product p12(12, "Self-Help Book", "Motivational Book", "Books", 18, 12, "Brand I");

    // Movies
    product p13(13, "Action Movie", "Thriller Action Movie", "Movies", 5, 8, "Brand J");
    product p14(14, "Comedy Movie", "Hilarious Comedy Movie", "Movies", 8, 6, "Brand K");
    product p15(15, "Drama Movie", "Emotional Drama Movie", "Movies", 6, 10, "Brand L");
    product p16(16, "Science Fiction Movie", "Mind-bending Sci-Fi Movie", "Movies", 4, 12, "Brand M");

    // shop s1("3");
    // s1.addproduct(&p1);
    // s1.addproduct(&p2);
    // s1.addproduct(&p3);
    // s1.addproduct(&p4);
    // shop s2("4");
    // s2.addproduct(&p5);
    // s2.addproduct(&p6);
    // s2.addproduct(&p7);
    // s2.addproduct(&p8);
    // shop s3("5");
    // s3.addproduct(&p9);
    // s3.addproduct(&p10);
    // s3.addproduct(&p11);
    // s3.addproduct(&p12);
    shop s4("7");
    s4.addproduct(&p13);
    s4.addproduct(&p14);
    s4.addproduct(&p15);
    s4.addproduct(&p16);
}