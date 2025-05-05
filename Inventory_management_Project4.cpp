
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

class Product{
    public:
    int id;
    string name;
    double price;
    int quantity;
    string location;

    Product(int i, string n, double p ,  int q, string loc )
    :id(i), name(n), price(p), quantity(q), location(loc){}
  
    void displayProduct() const {
        cout << "ID: " << id << ", Name: " << ", Price: $" << price << ", Quantity: " << quantity << ", Location " << location << endl;
    }

bool operator< (const Product& other) const {
    return name < other.name;
}
string toString() const {
    return to_string(id) + "," + name + ","+ to_string(price)+ to_string(quantity) +","+ location;
}
static Product fromString(const string& data){
    stringstream ss(data);
    string segment;
    vector<string> parts;
    while (getline(ss, segment, ',')) {
        parts.push_back(segment);
    }
    if(parts.size() == 5) {
        return Product(stoi(parts[0]), parts[1], stod(parts[2]), stoi(parts[3]), parts[4]);
    }
    return Product(-1, "Error", 0.0, 0, "");
}
};
vector<Product> inventory;
const string FILENAME = "inventory.txt";

void saveInventory() {
    ofstream outfile(FILENAME);
    if(outfile.is_open()){
        for(const auto& product : inventory) {
            outfile << product.toString() << endl;
        }
        outfile.close();
        cout << "Inventory saved to " << FILENAME << endl;
    }else{
        cerr << "Unable to open file for saving. " << endl;
    }
}
void loadInventory() {
    ifstream infile(FILENAME);
    string line;
    if(infile.is_open()) {
        while(getline(infile, line)) {
            Product product = Product ::fromString(line);
            if(product.id != -1){
                inventory.push_back(product);
            }
        }
        infile.close();
        cout<< "Inventory loaded from " << FILENAME << endl;
    }else{
        cerr << "Unable to open file for loading. Staring with an empty inventory." << endl;
    }
}

void addProduct(int id, string name, double price, int quantity, string location) {
   inventory.emplace_back(id, name, price, quantity, location);
   cout << "Product added succesfully! " << endl;
}
Product* findProductById(int id){
    for (auto& product : inventory) {
        if(product.id == id) return &product;
    }
    return nullptr;
}
void updateStock(int id, int newQuantity) {
    Product* product = findProductById(id);
    if(product) {
        product ->quantity = newQuantity;
        cout << "Stock update for" << product->name << endl;
    }else{
        cout << "Prodcut not fount!" << endl;
    }
}
   
void processOrder(int id, int quantity) {
    Product* product = findProductById(id);
    if(product) {
        if(product ->quantity >= quantity) {
            product->quantity -= quantity;
            cout << "Order palced for " << product ->name << endl;
        }else{
            cout << "Insufficient stock!" <<endl;
        }
        }else{
            cout << "Product not found!" << endl;
        }
    }
    
void searchProductByName(const string& name) {
   bool found = false;
   for(const auto& product : inventory) {
    if(product.name == name){
        product.displayProduct();
        found = true;
    }
   }if(!found) {
    cout << "Product not found!" << endl;
   }
}
   

void checkStockLevels() {
    for(const auto& product : inventory) {
        if(product.quantity < 5) {
            cout << "Low stock alert for " << product.name<<  "!" << endl;
        }
    }
}
void sortInventory(){
    sort(inventory.begin(), inventory.end());
    cout << "Inventory sorted by name." << endl;
}

void generateReport() {
   cout << "Inventory Report: " << endl;
   for(const auto& product : inventory) {
    product.displayProduct();
   }
}
 
void menu() {
    int choice;
    while(true) {
        cout << "\n1. Add Product\n2. Search Product\n3. Process Order\n4. Update Stock\n5. Check Alerts\n6. Generate Report\n7. Sort Inventory (by Name)\n8. Save Inventory\n9. Exit\n";
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
            string name;
            cout << "Enter product name: ";
            cin >> name;
            searchProductByName(name);
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
    }else if (choice == 7 ){
        sortInventory();
    }else if (choice == 8) {
        saveInventory();
    }else if (choice == 9) {
        break;
    }else{
        cout<< "Invalid choice. Try again." << endl;
    }
  }
}
int main() {
    loadInventory();
    menu();
    saveInventory();
    return 0;
}