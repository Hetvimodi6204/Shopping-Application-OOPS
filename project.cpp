#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;
class Item
{
public:
    string category;
    string model;
    double price;
    int rating;

    Item(string cat, string mod, double pr, int rt) : category(cat), model(mod), price(pr), rating(rt) {}

    // Overloading the stream output operator to print Item details
    friend ostream &operator<<(ostream &os, const Item &item)
    {
        os << item.category << "\t" << item.model << "\tPrice: " << item.price << "\tRating: " << item.rating;
        return os;
    }
};

class Customer
{
private:
    string name;
    string email;
    string phone;
    string address;
    string postalCode;
    string state;
    string city;
    vector<pair<Item, int>> selected_items;

public:
    Customer()
    {
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your phone number: ";
        cin >> phone;
        cout << "Enter your address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter your postal code: ";
        cin >> postalCode;
        cout << "Enter your state: ";
        cin >> state;
        cout << "Enter your city: ";
        cin >> city;
    }

    string getName() const
    {
        return name;
    }

    void addToCart(Item item, int quantity)
    {
        selected_items.emplace_back(item, quantity);
    }

    void removeFromCart(int index, int quantity)
    {
        if (index < selected_items.size())
        {
            if (selected_items[index].second > quantity)
            {
                selected_items[index].second -= quantity;
                cout << "Removed " << quantity << " items from the cart successfully." << endl;
            }
            else
            {
                selected_items.erase(selected_items.begin() + index);
                cout << "Item removed from the cart successfully." << endl;
            }
        }
        else
        {
            cout << "Invalid index. No item removed from the cart." << endl;
        }
    }

    void printCart()
    {
        auto current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << "Items in the cart - " << ctime(&current_time);
        if (selected_items.empty())
        {
            cout << "No items in the cart." << endl;
        }
        else
        {
            for (int i = 0; i < selected_items.size(); i++)
            {
                cout << i + 1 << ". " << selected_items[i].first << " (Quantity: " << selected_items[i].second << ")" << endl;
            }
        }
        cout << setw(50) << setfill('-') << '-' << endl;
    }

    void printBill()
    {
        auto current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
        auto delivery_time = chrono::system_clock::to_time_t(chrono::system_clock::now() + chrono::hours(24 * 7)); // 7 days from now

        double total_amount = 0;
        cout << "Category\tItem\tQuantity\tCost - " << ctime(&current_time);
        for (auto &selected_item : selected_items)
        {
            Item item = selected_item.first;
            int quantity = selected_item.second;
            double temp = quantity * item.price;
            total_amount += temp;
            cout << item.category << "\t\t" << item.model << "\t" << quantity << "\t\t" << temp << endl;
        }
        cout << setw(50) << setfill('-') << '-' << endl;
        cout << "Total amount:\t\t\t\t" << total_amount << endl;
        cout << "Expected Day of Delivery:\t" << ctime(&delivery_time);
        cout << setw(50) << setfill('-') << '-' << endl;
        cout << "THANK YOU, " << name << ", AND HAPPY ONLINE SHOPPING" << endl;
    }
     void saveToLogFile() {
        ofstream outFile("purchase_details.txt", ios::app); // Open file in append mode
        if (outFile.is_open()) {
            outFile << "Customer Name: " << name << "\n";
            outFile << "Email: " << email << "\n";
            outFile << "Phone: " << phone << "\n";
            outFile << "Address: " << address << "\n";
            outFile << "Postal Code: " << postalCode << "\n";
            outFile << "State: " << state << "\n";
            outFile << "City: " << city << "\n";
            outFile << "Items Purchased:\n";
            for (const auto &selected_item : selected_items) {
                outFile << selected_item.first.category << "\t" << selected_item.first.model << "\tQuantity: " << selected_item.second << "\n";
            }
            outFile << "------------------------\n";
            outFile.close();
        } else {
            cout << "Unable to open file for logging purchase details." << endl;
        }
    }
};

class Shop
{
public:
    virtual void show() {};
    virtual void select(Customer *customer) {};
    virtual void filterItemsByRating(double minRating) {};
};

class Mobile : public Shop
{
private:
    vector<Item> mobile_items;

public:
    Mobile()
    {
        mobile_items.emplace_back(Item("Mobile", "Samsung", 15000, 4));
        mobile_items.emplace_back(Item("Mobile", "Redmi", 12000, 3));
        mobile_items.emplace_back(Item("Mobile", "Apple", 100000, 5));
        mobile_items.emplace_back(Item("Mobile", "OnePlus", 35000, 4));
        mobile_items.emplace_back(Item("Mobile", "Google", 60000, 5));
        mobile_items.emplace_back(Item("Mobile", "Huawei", 28000, 3));
        mobile_items.emplace_back(Item("Mobile", "Moto", 25000, 4));
        mobile_items.emplace_back(Item("Mobile", "Sony", 32000, 4));
        mobile_items.emplace_back(Item("Mobile", "Nokia", 18000, 3));
        mobile_items.emplace_back(Item("Mobile", "Xiaomi", 20000, 4));
        mobile_items.emplace_back(Item("Mobile", "Realme", 17000, 3));
        mobile_items.emplace_back(Item("Mobile", "Oppo", 22000, 4));
        mobile_items.emplace_back(Item("Mobile", "Vivo", 19000, 3));
    }

    void show() override
    {
        cout << "Mobile Category" << endl;
        int cnt = 1;
        for (auto &item : mobile_items)
        {
            cout << cnt++ << ". " << item << endl;
        }
        cout << setw(80) << setfill('-') << '-' << endl;
    }

    void select(Customer *customer) override
    {
        cout << "These are the smartphones we have...." << endl;
        int num;
        cout << "Enter the number of the smartphone you want to purchase: ";
        cin >> num;
        if (num < 1 || num > mobile_items.size())
        {
            cout << "Wrong Input" << endl;
            return;
        }
        cout << "Enter quantity: ";
        int quantity;
        cin >> quantity;
        cout << "\n\nPURCHASE SUCCESSFUL!! " << mobile_items[num - 1].model << " IS ADDED TO THE CART\n\n";
        customer->addToCart(mobile_items[num - 1], quantity);
    }

    void filterItemsByRating(double minRating) override
    {
        vector<Item> filteredItems;
        for (const Item &item : mobile_items)
        {
            if (item.rating >= minRating)
            {
                filteredItems.push_back(item);
            }
        }
        mobile_items = filteredItems;
    }
};

class Laptop : public Shop
{
private:
    vector<Item> laptop_items;

public:
    Laptop()
    {
        laptop_items.emplace_back(Item("Laptop", "HP", 40000, 4));
        laptop_items.emplace_back(Item("Laptop", "Lenovo", 35000, 3));
        laptop_items.emplace_back(Item("Laptop", "Macbook", 250000, 5));
        laptop_items.emplace_back(Item("Laptop", "Dell", 45000, 4));
        laptop_items.emplace_back(Item("Laptop", "Asus", 38000, 4));
        laptop_items.emplace_back(Item("Laptop", "Acer", 30000, 3));
        laptop_items.emplace_back(Item("Laptop", "MSI", 60000, 5));
        laptop_items.emplace_back(Item("Laptop", "Samsung", 42000, 4));
        laptop_items.emplace_back(Item("Laptop", "Toshiba", 32000, 3));
        laptop_items.emplace_back(Item("Laptop", "Sony", 48000, 4));
        laptop_items.emplace_back(Item("Laptop", "LG", 37000, 3));
        laptop_items.emplace_back(Item("Laptop", "Fujitsu", 40000, 4));
    }

    void show() override
    {
        cout << "Laptop Category" << endl;
        int cnt = 1;
        for (auto &item : laptop_items)
        {
            cout << cnt++ << ". " << item << endl;
        }
        cout << setw(80) << setfill('-') << '-' << endl;
    }

    void select(Customer *customer) override
    {
        cout << "These are the laptops we have...." << endl;
        int num;
        cout << "Enter the number of the laptop you want to purchase: ";
        cin >> num;
        if (num < 1 || num > laptop_items.size())
        {
            cout << "Wrong Input" << endl;
            return;
        }
        cout << "Enter quantity: ";
        int quantity;
        cin >> quantity;
        cout << "\n\nPURCHASE SUCCESSFUL!! " << laptop_items[num - 1].model << " IS ADDED TO THE CART\n\n";
        customer->addToCart(laptop_items[num - 1], quantity);
    }

    void filterItemsByRating(double minRating) override
    {
        vector<Item> filteredItems;
        for (const Item &item : laptop_items)
        {
            if (item.rating >= minRating)
            {
                filteredItems.push_back(item);
            }
        }
        laptop_items = filteredItems;
    }
};

class Courses : public Shop
{
private:
    vector<Item> course_items;

public:
    Courses()
    {
        course_items.emplace_back(Item("Course", "C", 1000, 4));
        course_items.emplace_back(Item("Course", "C++", 3000, 5));
        course_items.emplace_back(Item("Course", "Java", 4000, 4));
        course_items.emplace_back(Item("Course", "Python", 3500, 5));
        course_items.emplace_back(Item("Course", "Js", 3200, 4));
        course_items.emplace_back(Item("Course", "HTML", 1500, 3));
        course_items.emplace_back(Item("Course", "CSS", 1800, 3));
        course_items.emplace_back(Item("Course", "Ruby", 2800, 4));
        course_items.emplace_back(Item("Course", "PHP", 2500, 4));
        course_items.emplace_back(Item("Course", "Swift", 3500, 5));
        course_items.emplace_back(Item("Course", "SQL", 2000, 4));
        course_items.emplace_back(Item("Course", "ML", 5000, 5));
        course_items.emplace_back(Item("Course", "DSA", 3800, 4));
    }

    void show() override
    {
        cout << "Programming Courses Category" << endl;
        int cnt = 1;
        for (auto &item : course_items)
        {
            cout << cnt++ << ". " << item << endl;
        }
        cout << setw(80) << setfill('-') << '-' << endl;
    }

    void select(Customer *customer) override
    {
        cout << "These are the programming courses we have...." << endl;
        int num;
        cout << "Enter the number of the course you want to purchase: ";
        cin >> num;
        if (num < 1 || num > course_items.size())
        {
            cout << "Wrong Input" << endl;
            return;
        }
        cout << "Enter quantity: ";
        int quantity;
        cin >> quantity;
        cout << "\n\nPURCHASE SUCCESSFUL!! " << course_items[num - 1].model << " IS ADDED TO THE CART\n\n";
        customer->addToCart(course_items[num - 1], quantity);
    }

    void filterItemsByRating(double minRating) override
    {
        vector<Item> filteredItems;
        for (const Item &item : course_items)
        {
            if (item.rating >= minRating)
            {
                filteredItems.push_back(item);
            }
        }
        course_items = filteredItems;
    }
};

int main()
{
    cout << "WELCOME TO OUR SHOP. WE ARE DELIGHTED THAT YOU ARE HERE. HOW CAN WE HELP YOU? WE DEAL IN ELECTRONIC GADGETS AND COURSES." << endl;
    Customer *c = new Customer;
    vector<Shop *> shops = {new Mobile(), new Laptop(), new Courses()};

    while (true)
    {
        int mainMenuChoice, menu;
        cout << "Please select an option to proceed further." << endl;
        cout << "1. Menu\n2. Modify Cart\n3. Display Cart\n4. Filter\n5. Checkout \n6. Contact Us\n7. Exit\nEnter your choice: ";
        cin >> mainMenuChoice;

        switch (mainMenuChoice)
        {
        case 1:
        { // Menu
            cout << "Please select your category" << endl;
            cout << "1. Mobile" << endl;
            cout << "2. Laptop" << endl;
            cout << "3. Programming Courses" << endl;
            cin >> menu;

            switch (menu)
            {
            case 1:
            {
                shops[menu - 1]->show();
                shops[menu - 1]->select(c);
                break;
            }
            case 2:
            {
                shops[menu - 1]->show();
                shops[menu - 1]->select(c);
                break;
            }
            case 3:
            {
                shops[menu - 1]->show();
                shops[menu - 1]->select(c);
                break;
            }
            default:
            {
                cout << "Wrong Input. Please select a valid option." << endl;
                break;
            }
            }
            break;
        }
        case 2:
        { // Modify Cart
            c->printCart();
            cout << "Enter the index of the item you want to remove from the cart (or 0 to cancel): ";
            int index;
            cin >> index;
            if (index > 0)
            {
                int quantity;
                cout << "Enter quantity: ";
                cin >> quantity;
                c->removeFromCart(index - 1, quantity);
            }
            break;
        }
        case 3:
        { // Display Cart
            c->printCart();
            break;
        }
        case 4:
        { // Filter
            int filterChoice;
            cout << "Please select a category to filter:" << endl;
            cout << "1. Mobile" << endl;
            cout << "2. Laptop" << endl;
            cout << "3. Programming Courses" << endl;
            cin >> filterChoice;

            switch (filterChoice)
            {
            case 1:
            {
                Mobile mobileShop;
                double minRating;
                cout << "Enter the minimum rating for Mobile items: ";
                cin >> minRating;
                mobileShop.filterItemsByRating(minRating);
                mobileShop.show();
                break;
            }
            case 2:
            {
                Laptop laptopShop;
                double minRating;
                cout << "Enter the minimum rating for Laptop items: ";
                cin >> minRating;
                laptopShop.filterItemsByRating(minRating);
                laptopShop.show();
                break;
            }
            case 3:
            {
                Courses courseShop;
                double minRating;
                cout << "Enter the minimum rating for Programming Courses: ";
                cin >> minRating;
                courseShop.filterItemsByRating(minRating);
                courseShop.show();
                break;
            }
            default:
            {
                cout << "Wrong Input. Please select a valid option." << endl;
                break;
            }
            }
            break;
        }
        case 5:
        { // Checkout
            c->printBill();
            c->saveToLogFile();
            break;
        }
        case 6:
        { // Contact Us
            cout << "Contact Us: " << endl;
            cout << "Email: contact@yourshop.com" << endl;
            cout << "Phone: +123-456-7890" << endl;
            break;
        }
        case 7:
        { // Exit
            delete c;
            for (Shop *shop : shops)
            {
                delete shop;
            }
            return 0;
        }
        default:
        {
            cout << "Wrong Input. Please select a valid option." << endl;
            break;
        }
        }
    }
}