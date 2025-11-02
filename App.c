/*By Rishik, Jagadish, Eswar, Ritesh From LIET*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USERS 100
#define MAX_ITEMS 50
#define MAX_CART 10
#define ADMIN_PASSWORD "Eswar@Admin"
typedef struct {
    int id;
    char name[50];
    char category[20];
    float price;
    int stock;
    float rating;
    int rating_count;
} FoodItem;
typedef struct {
    char username[50];
    char phone[15];
    char email[50];
    char password[20];
} User;
typedef struct {
    int itemID;
    char name[50];
    int quantity;
    float price;
    float total;
} CartItem;
typedef struct {
    char username[50];
    int orderID;
    CartItem items[MAX_CART];
    int itemCount;
    float totalAmount;
} Order;
User users[MAX_USERS];
FoodItem menu[MAX_ITEMS];
Order orders[MAX_USERS];
int userCount = 0, orderCount = 0, foodCount = 0;
CartItem cart[MAX_CART];
int cartCount = 0;
void saveData();
void loadData();
void saveUsers();
void loadUsers();
void saveMenu();
void loadMenu();
void saveOrders();
void loadOrders();
void registerUser();
int loginUser();
void adminMenu();
void userMenu(char username[]);
void viewMenu();
void addToCart();
void viewCart();
void removeFromCart();
void checkout(char username[]);
void viewOrderHistory(char username[]);
void adminManageMenu();
void adminViewSales();
void rateFood();
void addItemToMenu();
void updateItemInMenu();
void removeItemFromMenu();
int main() {
    loadData();
    int choice;
    while (1) {
        printf("\n==== ONLINE FOOD ORDERING SYSTEM ====\n");
        printf("1. Register\n2. Login\n3. Admin Login\n4. Exit\n");
        printf("Enter your choice: ");scanf("%d", &choice);
        getchar();
        if (choice == 1) {
            registerUser();
        } else if (choice == 2) {
            int userIndex = loginUser();
            if (userIndex != -1) {
                userMenu(users[userIndex].username);
            }
        } else if (choice == 3) {
            char adminPass[20];
            printf("Enter Admin Password: ");scanf("%s", adminPass);
            if (strcmp(adminPass, ADMIN_PASSWORD) == 0) {
                adminMenu();
            } else {
                printf("Incorrect password!\n");
            }
        } else if (choice == 4) {
            saveData();  // Save data before exiting
            printf("Thank you for using the system. Goodbye!\n");
            exit(0);
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }
}
void saveData() {
    saveUsers();
    saveMenu();
    saveOrders();
}

void loadData() {
    loadUsers();
    loadMenu();
    loadOrders();
}

// Save and Load Users
void saveUsers() {
    FILE *file = fopen("users.dat", "wb");
    if (!file) {
        perror("Error opening users.dat");
        return;
    }
    fwrite(&userCount, sizeof(int), 1, file);
    fwrite(users, sizeof(User), userCount, file);
    fflush(file);
    fclose(file);
}

void loadUsers() {
    FILE *file = fopen("users.dat", "rb");
    if (!file) return; // File may not exist yet, so don't show an error.
    fread(&userCount, sizeof(int), 1, file);
    fread(users, sizeof(User), userCount, file);
    fclose(file);
}

// Save and Load Menu
void saveMenu() {
    FILE *file = fopen("menu.dat", "wb");
    if (!file) {
        perror("Error opening menu.dat");
        return;
    }
    fwrite(&foodCount, sizeof(int), 1, file);
    fwrite(menu, sizeof(FoodItem), foodCount, file);
    fflush(file);
    fclose(file);
}

void loadMenu() {
    FILE *file = fopen("menu.dat", "rb");
    if (!file) return; // File may not exist yet
    fread(&foodCount, sizeof(int), 1, file);
    fread(menu, sizeof(FoodItem), foodCount, file);
    fclose(file);
}

// Save and Load Orders
void saveOrders() {
    FILE *file = fopen("orders.dat", "wb");
    if (!file) {
        perror("Error opening orders.dat");
        return;
    }
    fwrite(&orderCount, sizeof(int), 1, file);
    fwrite(orders, sizeof(Order), orderCount, file);
    fflush(file);
    fclose(file);
}
void loadOrders() {
    FILE *file = fopen("orders.dat", "rb");
    if (!file) return;
    fread(&orderCount, sizeof(int), 1, file);
    fread(orders, sizeof(Order), orderCount, file);
    fclose(file);
}
void registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached!\n");
        return;
    }
    printf("Enter username: ");scanf("%s", users[userCount].username);
    printf("Enter phone number: ");scanf("%s", users[userCount].phone);
    printf("Enter email: ");scanf("%s", users[userCount].email);
    printf("Enter password: ");scanf("%s", users[userCount].password);
    userCount++;
    printf("Registration successful!\n");
}
int loginUser() {
    char username[50], password[20];
    printf("Enter username: ");scanf("%s", username);
    printf("Enter password: ");scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return i;
        }
    }
    printf("Invalid credentials!\n");
    return -1;
}
void userMenu(char username[]) {
    int choice;
    while (1) {
        printf("\nUser Menu\n");
        printf("1. View Menu\n2. Add to Cart\n3. View Cart\n4. Remove from Cart\n5. Checkout\n6. View Order History\n7. Rate Food\n8. Logout\n");
        printf("Enter your choice: ");scanf("%d", &choice);
        getchar();
        if (choice == 1) viewMenu();
        else if (choice == 2) addToCart();
        else if (choice == 3) viewCart();
        else if (choice == 4) removeFromCart();
        else if (choice == 5) checkout(username);
        else if (choice == 6) viewOrderHistory(username);
        else if (choice == 7) rateFood();
        else if (choice == 8) return;
        else printf("Invalid choice! Try again.\n");
    }
}
void viewMenu() {
    printf("\n---- MENU ----\n");
    for (int i = 0; i < foodCount; i++) {
        printf("%d. %s (%s) - ₹%.2f | Stock: %d | Rating: %.1f\n",
               menu[i].id, menu[i].name, menu[i].category, menu[i].price, menu[i].stock, menu[i].rating);
    }
}
void addToCart() {
    int id, qty;
    viewMenu();
    printf("Enter Item ID to add: ");scanf("%d", &id);
    printf("Enter quantity: ");scanf("%d", &qty);
    for (int i = 0; i < foodCount; i++) {
        if (menu[i].id == id) {
            if (menu[i].stock >= qty) {
                cart[cartCount].itemID = id;
                strcpy(cart[cartCount].name, menu[i].name);
                cart[cartCount].quantity = qty;
                cart[cartCount].price = menu[i].price;
                cart[cartCount].total = menu[i].price * qty;
                menu[i].stock -= qty;
                cartCount++;
                printf("Added to cart!\n");
            } else {
                printf("Not enough stock available.\n");
            }
            return;
        }
    }
    printf("Invalid Item ID.\n");
}
void viewCart() {
    printf("\n-- CART --\n");
    if (cartCount == 0) {
        printf("Cart is empty.\n");
        return;
    }
    float total = 0;
    for (int i = 0; i < cartCount; i++) {
        printf("%s x%d - ₹%.2f\n", cart[i].name, cart[i].quantity, cart[i].total);
        total += cart[i].total;
    }
    printf("Total Cart Value: ₹%.2f\n", total);
}
void removeFromCart() {
    int id;
    viewCart();
    if (cartCount == 0) return;
    printf("Enter Item ID to remove: ");scanf("%d", &id);
    for (int i = 0; i < cartCount; i++) {
        if (cart[i].itemID == id) {
            menu[cart[i].itemID - 101].stock += cart[i].quantity; // Restore stock
            for (int j = i; j < cartCount - 1; j++) {
                cart[j] = cart[j + 1];
            }
            cartCount--;
            printf("Removed from cart!\n");
            return;
        }
    }
    printf("Item not found in cart.\n");
}
void checkout(char username[]) {
    if (cartCount == 0) {
        printf("Cart is empty!\n");
        return;
    }
    printf("\n-- BILL RECEIPT --\n");
    float total = 0;
    for (int i = 0; i < cartCount; i++) {
        printf("%s x%d - ₹%.2f\n", cart[i].name, cart[i].quantity, cart[i].total);
        total += cart[i].total;
    }
    printf("Total Amount: ₹%.2f\n", total);
    orders[orderCount].orderID = orderCount + 1;
    strcpy(orders[orderCount].username, username);
    orders[orderCount].totalAmount = total;
    orders[orderCount].itemCount = cartCount;
    for (int i = 0; i < cartCount; i++) {
        orders[orderCount].items[i] = cart[i];
    }
    orderCount++; 
    cartCount = 0; 
    printf("Order placed successfully!\n");
}
void viewOrderHistory(char username[]) {
    printf("\n-- ORDER HISTORY --\n");
    int found = 0;
    for (int i = 0; i < orderCount; i++) {
        if (strcmp(orders[i].username, username) == 0) {
            printf("Order ID: %d | Total Amount: ₹%.2f\n", orders[i].orderID, orders[i].totalAmount);
            for (int j = 0; j < orders[i].itemCount; j++) {
                printf("  %s x%d - ₹%.2f\n", orders[i].items[j].name, orders[i].items[j].quantity, orders[i].items[j].total);
            }
            found = 1;
        }
    }
    if (!found) {
        printf("No orders found!\n");
    }
}
void adminMenu() {
    int choice;
    while (1) {
        printf("\nAdmin Menu\n");
        printf("1. Manage Menu\n2. View Sales Report\n3. Logout\n");
        printf("Enter your choice: ");
scanf("%d", &choice);
        if (choice == 1) adminManageMenu();
        else if (choice == 2) adminViewSales();
        else if (choice == 3) return;
        else printf("Invalid choice! Try again.\n");
    }
}
void adminManageMenu() {
    int choice;
    while (1) {
        printf("\nManage Menu\n");
        printf("1. Add Item\n2. Update Item\n3. Remove Item\n4. Back\n");
        printf("Enter your choice: ");
scanf("%d", &choice);
        if (choice == 1) addItemToMenu();
        else if (choice == 2) updateItemInMenu();
        else if (choice == 3) removeItemFromMenu();
        else if (choice == 4) return;
        else printf("Invalid choice! Try again.\n");
    }
}
void addItemToMenu() {
    if (foodCount >= MAX_ITEMS) {
        printf("Menu is full!\n");
        return;
    }
    FoodItem newItem;
    printf("Enter Item ID: ");scanf("%d", &newItem.id);
    getchar();
    printf("Enter Item Name: ");
    fgets(newItem.name, 50, stdin);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';
    printf("Enter Item Category: ");scanf("%s", newItem.category);
    printf("Enter Price: ");scanf("%f", &newItem.price);
    printf("Enter Stock: ");scanf("%d", &newItem.stock);
    newItem.rating = 0.0;
    newItem.rating_count = 0;
    menu[foodCount++] = newItem;
    printf("Item added successfully!\n");
}
void updateItemInMenu() {
    int id;
    printf("Enter Item ID to update: ");scanf("%d", &id);
    for (int i = 0; i < foodCount; i++) {
        if (menu[i].id == id) {
            printf("Enter new Item Name: ");
            getchar(); 
            fgets(menu[i].name, 50, stdin);
            menu[i].name[strcspn(menu[i].name, "\n")] = '\0'; 
            printf("Enter new Item Category: ");
            scanf("%s", menu[i].category);
            printf("Enter new Price: ");
            scanf("%f", &menu[i].price);
            printf("Enter new Stock: ");
            scanf("%d", &menu[i].stock);
            printf("Item updated successfully!\n");
            return;
        }
    }
    printf("Item not found!\n");
}
void removeItemFromMenu() {
    int id;
    printf("Enter Item ID to remove: ");scanf("%d", &id);
    for (int i = 0; i < foodCount; i++) {
        if (menu[i].id == id) {
            for (int j = i; j < foodCount - 1; j++) {
                menu[j] = menu[j + 1];
            }
            foodCount--;
            printf("Item removed successfully!\n");
            return;
        }
    }
    printf("Item not found!\n");
}
void adminViewSales() {
    float totalSales = 0;
    for (int i = 0; i < orderCount; i++) {
        totalSales += orders[i].totalAmount;
    }
    printf("Total Sales: ₹%.2f\n", totalSales);
}
void rateFood() {
    int id, rating;
    viewMenu();
    printf("Enter Item ID to rate: ");scanf("%d", &id);
    printf("Enter rating (1-5): ");scanf("%d", &rating);

    for (int i = 0; i < foodCount; i++) {
        if (menu[i].id == id) {
            menu[i].rating = ((menu[i].rating * menu[i].rating_count) + rating) / (menu[i].rating_count + 1);
            menu[i].rating_count++;
            printf("Rating updated!\n");
            return;
        }
    }
    printf("Invalid Item ID.\n");
}
