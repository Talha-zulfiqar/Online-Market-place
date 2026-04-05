# Online Market Place

This is a simple console-based Online Market Place written in C++ (Visual Studio project). It demonstrates a small file-backed marketplace with two roles: admin and user. The program uses plain text files in the project folder to store users, admins, products and reviews.

Key features
- Admins can add and remove products, change product quantities, and read user reviews.
- Users can sign up, log in, view products, leave reviews, and "buy" products (quantity is updated and a bill is printed).
- Data is stored in the following text files: `users.txt`, `admins.txt`, `products.txt`, `reviews.txt`.

Files of interest
- `buyers.cpp` — main program and the core implementation (users, admins, product/review managers, menus).
- `products.txt` — the products list; each line is: `id name price quantity`.
- `users.txt` / `admins.txt` — simple space-separated `username password` pairs.
- `reviews.txt` — appended reviews in a readable format.

How it works (brief, from the code)
- On start the program shows a main menu with options: Admin Login, User Login, User Sign Up, Exit.
- Admin flow:
	- Admin credentials are checked against `admins.txt`.
	- Once logged in, the admin can add products (id, name, price, quantity), remove products by id, add quantity to existing products, display all products, or read reviews.
	- Product storage is file-based: adding appends to `products.txt`. Removing or updating writes to a temporary file and replaces `products.txt`.
- User flow:
	- Users can sign up (username & password appended to `users.txt`) and then log in.
	- Logged-in users can write reviews (appended to `reviews.txt`), view products, or "buy" products by entering product id, quantity and payment details (card number/CVV/pin) — note: payment is not processed; the input is only used to display a simple bill.
	- Buying decreases product quantity in `products.txt`. If not enough quantity is available, the program reports it.

Security & safety notes
- Passwords and card details are stored/handled in plain text and are not encrypted — this project is educational and not production-ready.
- There is no input validation, concurrency control, or real payment integration. Files are rewritten for updates, so concurrent runs could corrupt data.

Build and run (Visual Studio)
1. Open `Online Market Place.vcxproj` in Visual Studio (or the `.vcxproj` file in the project root).
2. Build for the Debug x64 configuration.
3. Run the produced executable in `x64\Debug\Online Market Place.exe` or run from Visual Studio.

Run from PowerShell (after building):
```powershell
& 'C:\Users\Lenovo\OneDrive\Desktop\Online Market PLace\x64\Debug\Online Market Place.exe'
```

Quick usage example
1. Start the program.
2. Choose "User Sign Up" and create a user (e.g. `alice` / `password123`).
3. From main menu choose "Admin Login" (use an admin account in `admins.txt` or add one by editing the file) and add a product, e.g. `1 Apple 0.99 10`.
4. Log in as the user and choose "Buy Products". Enter the product id (1) and quantity (2). The program will print a small bill and update `products.txt` quantity.



