#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For formatting output
#include <limits>  // For clearing input buffer

// Struct to represent an item in the inventory
struct Item {
    std::string name;
    double price;
    int quantity;
};

// Function to display the main menu
void displayMenu() {
    std::cout << "\n=== Ergonomic Office Supplies Store ===\n";
    std::cout << "1. View Inventory\n";
    std::cout << "2. Place an Order\n";
    std::cout << "3. Exit\n";
    std::cout << "Please choose an option (1-3): ";
}

// Function to display the inventory
void displayInventory(const std::vector<Item>& inventory) {
    std::cout << "\n=== Inventory ===\n";
    std::cout << std::left << std::setw(20) << "Item" << std::setw(10) << "Price" << "Quantity\n";
    std::cout << std::string(40, '-') << "\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << std::left << std::setw(20) << inventory[i].name
                  << "P" << std::fixed << std::setprecision(2) << inventory[i].price
                  << std::setw(10) << inventory[i].quantity << "\n";
    }
}

// Function to handle placing an order
void placeOrder(std::vector<Item>& inventory) {
    displayInventory(inventory);
    std::cout << "\nEnter the number of the item you want to order (1-" << inventory.size() << "): ";
    int choice;
    std::cin >> choice;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
        return;
    }

    if (choice < 1 || choice > static_cast<int>(inventory.size())) {
        std::cout << "Invalid choice. Please try again.\n";
        return;
    }

    Item& selectedItem = inventory[choice - 1];
    std::cout << "You selected: " << selectedItem.name << "\n";
    std::cout << "Enter quantity: ";
    int qty;
    std::cin >> qty;

    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number.\n";
        return;
    }

    if (qty <= 0) {
        std::cout << "Invalid quantity. Please enter a positive number.\n";
        return;
    }

    if (qty > selectedItem.quantity) {
        std::cout << "Sorry, only " << selectedItem.quantity << " available. Order not placed.\n";
        return;
    }

    double totalCost = qty * selectedItem.price;
    std::cout << "Total cost: P" << std::fixed << std::setprecision(2) << totalCost << "\n";
    std::cout << "Confirm order? (y/n): ";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        selectedItem.quantity -= qty;
        std::cout << "Order placed successfully! Remaining quantity: " << selectedItem.quantity << "\n";
    } else {
        std::cout << "Order cancelled.\n";
    }
}

int main() {
    // Initialize inventory with items, prices, and quantities
    std::vector<Item> inventory = {
        {"X11 Mouse", 25.00, 10},
        {"Wooden Wrist Rest", 15.00, 15},
        {"Monitor Arm", 50.00, 5},
        {"Ergo Chair", 200.00, 3}
    };

    int option;
    do {
        displayMenu();
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 3.\n";
            continue;
        }

        switch (option) {
            case 1:
                displayInventory(inventory);
                break;
            case 2:
                placeOrder(inventory);
                break;
            case 3:
                std::cout << "Thank you for visiting Ergonomic Office Supplies Store!\n";
                break;
            default:
                std::cout << "Invalid option. Please choose 1-3.\n";
        }
    } while (option != 3);

    return 0;
}
