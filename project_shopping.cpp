#include <iostream>
#include <vector>

using namespace std;

class Product {
private:
    string name;
    string description;
    double price;
    string category;

public:
    Product(string n, string desc, double p, string cat): name(n), description(desc), price(p), category(cat) {}

    string getName() const {
        return name;
    }

    string getDescription() const {
        return description;
    }

    double getPrice() const {
        return price;
    }

    string getCategory() const {
        return category;
    }


    void displayNameAndPrice() const {
        cout << name << " - " << price << " LE" << endl;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Description: " << description << endl;
        cout << "Price: " << price << " LE" << endl;
        cout << "Category: " << category << endl;
    }
};

class ShoppingCart {
private:
    vector<Product> items;

public:
    void addItem(const Product& product) {
        items.push_back(product);
    }

    void display() const {
        cout << "Shopping Cart Contents:" << endl;
        for (const auto& item : items) {
            item.display();
            cout << endl;
        }
    }

    double calculateTotal() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.getPrice();
        }
        return total;
    }

    void checkout() {
        cout << "Checkout completed. Total amount: " << calculateTotal() << " LE" << endl;
    }
};

// Function to search for products by name or category
vector<Product> searchProducts(const vector<Product>& productList, const string& query) {
    vector<Product> results;
    for (const auto& product : productList) {
        if (product.getName() == query || product.getCategory() == query) {
            results.push_back(product);
        }
    }
    return results;
}

int main() {
    vector<Product> products = {        //sample products
        Product("milk", "full cream milk carton 1L", 50, "Dairy"),
        Product("eggs", "white eggs, 20 pcs", 160, "Eggs, Cheese & Cold"),
        Product("yoghurt", "natural creamy yoghurt", 10, "Dairy"),
        Product("water bottle", "natural mineral plastic water bottle", 5, "Beverages")
    };

    ShoppingCart cart;

    // User interaction
    cout << "use the following commands:" << endl;
    cout << "1. View all products" << endl;
    cout << "2. Search for a product or category" << endl;
    cout << "3. View shopping cart" << endl;
    cout << "4. Checkout" << endl;

    int choice;
    do {
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "All Products:" << endl;
                for (size_t i = 0; i < products.size(); ++i) {
                    cout << i + 1 << ". ";
                    products[i].displayNameAndPrice();
                }
                int selection;
                cout << "Enter the number of the product for more options (0 to cancel): ";
                cin >> selection;
                if (selection > 0 && selection <= static_cast<int>(products.size())) {
                    cout << "Selected Product: ";
                    products[selection - 1].display();
                    cout << "1. Add to cart" << endl;
                    int option;
                    cout << "Enter your option: ";
                    cin >> option;
                    switch (option) {
                        case 1:
                            cart.addItem(products[selection - 1]);
                            cout << "Product added to cart." << endl;
                            break;
                        default:
                            cout << "Invalid option." << endl;
                    }
                }
                break;
            }
            case 2: {
                string query;
                cout << "Enter product name or category to search: ";
                cin >> query;
                vector<Product> searchResults = searchProducts(products, query);
                if (searchResults.empty()) {
                    cout << "No products found matching the search criteria." << endl;
                } else {
                    cout << "Search Results:" << endl;
                    for (size_t i = 0; i < searchResults.size(); ++i) {
                        cout << i + 1 << ". ";
                        searchResults[i].displayNameAndPrice();
                    }
                    int selection;
                    cout << "Enter the number of the product for more options (0 to cancel): ";
                    cin >> selection;
                    if (selection > 0 && selection <= static_cast<int>(searchResults.size())) {
                        cout << "Selected Product: ";
                        searchResults[selection - 1].display();
                        cout << "1. Add to cart" << endl;
                        int option;
                        cout << "Enter your option: ";
                        cin >> option;
                        switch (option) {
                            case 1:
                                cart.addItem(searchResults[selection - 1]);
                                cout << "Product added to cart." << endl;
                                break;
                            default:
                                cout << "Invalid option." << endl;
                        }
                    }
                }
                break;
            }
            case 3:
                cart.display();
                break;
            case 4:
                cart.checkout();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
