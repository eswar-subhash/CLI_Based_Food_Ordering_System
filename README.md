# 🍔 Online Food Ordering System

A **C-based console application** that simulates a complete **online food ordering platform**, developed by **Rishik, Jagadish, Eswar, and Ritesh** from **LIET**.

This project allows users to browse a digital food menu, place and manage orders, and for admins to manage the menu and view sales reports — all with persistent data storage.

---

## 🧠 Project Overview

The **Online Food Ordering System** provides two roles:
- 👤 **User** – can register, log in, view the menu, add items to the cart, place orders, rate food, and check order history.
- 🔑 **Admin** – can log in with a secure password to manage menu items and track total sales.

The system uses **file handling in C** to save and load user data, orders, and the menu between sessions.

---

## ⚙️ Features

### 👨‍🍳 For Users
- Register and login system  
- View categorized food menu with prices, stock, and ratings  
- Add and remove items from the cart  
- Checkout and generate a bill  
- View order history  
- Rate food items  

### 🛠️ For Admin
- Secure login with admin password (`Rishik@Admin`)
- Add, update, and remove food items  
- View total sales report  

### 💾 Data Persistence
All user details, menu data, and orders are **saved to binary files**:
- `users.dat`
- `menu.dat`
- `orders.dat`

This ensures data is retained even after the program is closed.

---

## 🧩 Project Structure

├── online_food_ordering.c # Main source code
├── users.dat # Stored user details
├── menu.dat # Stored menu items
├── orders.dat # Stored order records
└── README.md # Project documentation

yaml
Copy code

---

## 🖥️ How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/<your-username>/online-food-ordering-system.git
   cd online-food-ordering-system
Compile the program

bash
Copy code
gcc online_food_ordering.c -o food_ordering
Run the program

bash
Copy code
./food_ordering
Choose your role

1 → Register as a new user

2 → Login as an existing user

3 → Admin login (Password: Rishik@Admin)

4 → Exit

🧾 Example Menu Output
yaml
Copy code
---- MENU ----
101. Burger (Fast Food) - ₹120.00 | Stock: 15 | Rating: 4.5
102. Pizza (Italian) - ₹250.00 | Stock: 10 | Rating: 4.7
103. Fries (Snacks) - ₹90.00 | Stock: 20 | Rating: 4.2
🛍️ Example Cart and Checkout
sql
Copy code
-- CART --
Burger x2 - ₹240.00
Fries x1 - ₹90.00
Total Cart Value: ₹330.00

-- BILL RECEIPT --
Burger x2 - ₹240.00
Fries x1 - ₹90.00
Total Amount: ₹330.00
Order placed successfully!
👨‍💻 Contributors
Name	Role	College
Rishik	Admin Module, File Handling	LIET
Jagadish	User Interface, Cart System	LIET
Eswar	Order & Rating System	LIET
Ritesh	Menu Management & Testing	LIET

🧠 Future Improvements
Add delivery tracking simulation

Enable online payment simulation

Implement multi-admin support

Add search and filter options for menu items

🏁 Conclusion
This project demonstrates practical use of:

File handling in C

Structs and arrays for data management

Modular programming and role-based access

Persistent storage for real-world simulation

It’s a great foundational project for beginners learning C programming and file-based systems.

⭐ If you found this project helpful, give it a star on GitHub!
📩 Suggestions and contributions are always welcome
