#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

class Product {
public:
    int id;
    string name;
    double price;

    Product(int id, string name, double price) {
        this->id = id;
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
public:
    vector<pair<Product, int>> cart;

    void addProduct(const Product& product, int quantity) {
        for (auto& item : cart) {
            if (item.first.id == product.id) {
                item.second += quantity;
                return;
            }
        }
        cart.push_back({product, quantity});
    }

    void viewCart() {
        if (cart.empty()) {
            cout << "Shopping cart is empty!" << endl;
            return;
        }
        cout << "\nShopping Cart:" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "----------------------------------------------------" << endl;
        for (const auto &item : cart) {
            cout << left << setw(10) << item.first.id << setw(20) << item.first.name << setw(10) << item.first.price << setw(10) << item.second << endl;
        }
        cout << "----------------------------------------------------\n";
    }

    vector<pair<Product, int>> checkout() {
        vector<pair<Product, int>> orderedProducts = cart;
        cart.clear();
        return orderedProducts;
    }

    bool isEmpty() {
        return cart.empty();
    }
};

class Order {
public:
    static int nextOrderId;
    int orderId;
    vector<pair<Product, int>> orderedProducts;
    double totalAmount;

    Order(vector<pair<Product, int>> products) {
        orderId = nextOrderId++;
        orderedProducts = products;
        totalAmount = 0;
        for (const auto &item : products) {
            totalAmount += item.first.price * item.second;
        }
    }

    void viewOrder() const {
        cout << "\nOrder ID: " << orderId << endl;
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Order Details:" << endl;
        cout << "----------------------------------------------------" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "----------------------------------------------------" << endl;
        for (const auto &item : orderedProducts) {
            cout << left << setw(10) << item.first.id << setw(20) << item.first.name << setw(10) << item.first.price << setw(10) << item.second << endl;
        }
        cout << "----------------------------------------------------" << endl;
        cout << "You have successfully checked out the products!\n";
    }
};

int Order::nextOrderId = 1;

void displayProducts(const vector<Product>& products) {
    cout << "\nAvailable Products:" << endl;
    cout << "--------------------------------------" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    cout << "--------------------------------------" << endl;
    for (const auto &product : products) {
        cout << left << setw(10) << product.id << setw(20) << product.name << setw(10) << product.price << endl;
    }
    cout << "--------------------------------------" << endl;
}

int getValidIntegerInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Invalid input! Please enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return value;
        }
    }
}

char getValidCharInput(string prompt) {
    char choice;
    while (true) {
        cout << prompt;
        cin >> choice;
        if (cin.fail() || (toupper(choice) != 'Y' && toupper(choice) != 'N')) {
            cout << "Invalid input! Please enter 'Y' or 'N'.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return toupper(choice);
        }
    }
}

int main() {
    vector<Product> products = {
        Product(1, "Paper", 20),
        Product(2, "Pencil", 10),
        Product(3, "Notebook", 50),
        Product(4, "Eraser", 5),
        Product(5, "Pen", 15)
    };

    ShoppingCart cart;
    vector<Order> orders;

    while (true) {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter choice: ";
        int choice = getValidIntegerInput("");

        if (choice == 1) {
            displayProducts(products);
            char addMore;
            do {
                int productId = getValidIntegerInput("Enter the ID of the product you want to add: ");
                int quantity = getValidIntegerInput("Enter the quantity: ");

                bool found = false;
                for (const auto& product : products) {
                    if (product.id == productId) {
                        cart.addProduct(product, quantity);
                        cout << "Product added successfully!" << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Invalid product ID!" << endl;
                }

                addMore = getValidCharInput("Do you want to add another product? (Y/N): ");
            } while (addMore == 'Y');
        }
        else if (choice == 2) {
            cart.viewCart();
            if (!cart.isEmpty()) {
                char checkoutChoice = getValidCharInput("Do you want to check out all the products? (Y/N): ");
                if (checkoutChoice == 'Y') {
                    orders.push_back(Order(cart.checkout()));
                }
            }
        }
        else if (choice == 3) {
            if (orders.empty()) {
                cout << "No orders have been placed yet!" << endl;
            } else {
                for (const auto &order : orders) {
                    order.viewOrder();
                }
            }
        }
        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Please enter a number between 1 and 4.\n";
        }
    }

    return 0;
}
