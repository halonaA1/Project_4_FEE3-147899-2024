
#include <iostream>
#include <string>
#include <unordered_map>
#include <mutex>
using namespace std;

class Product{
    public:
    int id;
    string name;
    double price;
    int quantity;
    string location;
    mutex lock;

    Product(int i, string n, double p ,  int q, string loc ) {
        id = i;
        name = n;
        price = p;
        quantity = q;
        location = loc;
    }
    void displayProduct() {
        cout << "ID: " << id << "Name: " << ", Price: $" << price << ", Quantity: " << quantity << ", Location " << location << endl;
    }
};
unordered_map<int, Product*> inventory;
int productCount = 0;

void addProduct(int id, string name, double price, int quantity, string location) {
    if(inventory.find(id) !=inventory.end()) {
    cout << "Product with this ID already exist!\n";
    return;
}
if(price < 0 || quantity < 0) {
    cout << "Invalid input! Price and quantity must be non-negative.\n";
    return;
}
inventory[id] = new Product(id, name, price, quantity, location);
cout << "Product added succesfully!\n";
}
void updateStock(int id, int newQuantity) {
    if(inventory.find(id) == inventory.end()){
        cout <<"Product not found!\n";
        return;
    }
    if(newQuantity < 0) {
        cout << "Invalid quantity!\n";
        return;
    }
    inventory[id] ->lock.lock();
    inventory[id] ->quantity = newQuantity;
    inventory[id] ->lock.unlock();
    cout << "Stock update for " << inventory[id] ->name << endl;
}
void processOrder(int id, int quantity) {
        if (inventory.find(id) == inventory.end()) {
            cout << "Product not found!\n";
            return;
        }
        inventory[id] ->lock.lock();
            if(inventory[id] ->quantity >= quantity) {
                inventory[id] ->quantity -= quantity;
                cout <<"Order placed for " << inventory[id] ->name << endl;
            }else{
                cout << "Insufficient stock!\n";
            }
            inventory[id] ->lock.unlock();
        }
    
void searchProductById(int id) {
    if(inventory.find(id) == inventory.end()) {
       cout << "Product not found!\n";
            return;
        }
        inventory[id] ->displayProduct();
    }
   

void checkStockLevels() {
    for(auto &pair  : inventory) {
        if(pair.second ->quantity < 5) {
            cout << "Low stock alert for " << pair.second ->name<<  "!\n";
        }
    }
}
void generateReport(int pageSize = 5) {
    int page = 1;
    int count = 0;

    cout << "Inventory Report (page " << page << "):\n";
    for(auto &pair  : inventory) {
        pair.second ->displayProduct();
        count++;

        if(count % pageSize == 0) {
            cout << "Press Enter to continue to the next page...\n";
            cin.ignore();
            cin.get();
            page++;
            cout << "Inventory Report (Page " << page << "):\n";
        }
    }
}
 
void menu() {
    int choice;
    while(true) {
        cout << "\n1. Add Product\n2. Search Product\n3. Process Order\n4. Update Stock\n5. Check Alerts\n6. Generate Report\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        if(choice == 1) {
            int id, quantity;
            double price;
            string name, location;
            cout << "Enter Id, Name, Price, Quantity, Location: ";
            cin >> id >> name >> price >> quantity >> location;
            addProduct(id, name, price, quantity, location);
        }else if (choice == 2) {
            int id;
            cout << "Enter product ID: ";
            cin >> id;
            searchProductById(id);
        }else if(choice == 3) {
            int id, qty;
            cout << "Enter product ID and quantity: ";
            cin >> id >> qty;
            processOrder(id, qty);
        } else if(choice == 4) {
            int id, qty;
            cout << "Enter product ID and new quantity: ";
            cin >> id >> qty;
            updateStock(id, qty);
        } else if (choice == 5) {
            checkStockLevels();
    }else if(choice == 6) {
        generateReport();
    }else {
        break;
    }
    }
}
int main() {
    menu();
    return 0;
}