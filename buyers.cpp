#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User
{
private:
	string username;
	string password;

public:
	User(const string& uname, const string& pwd) : username(uname), password(pwd) {}

	bool authenticate(const string& uname, const string& pwd) const
	{
		return (username == uname && password == pwd);
	}

	const string& getUsername() const
	{
		return username;
	}
};

class UserManager
{
private:
	const string usersFile = "users.txt";

public:
	bool addUser(const string& uname, const string& pwd)
	{
		ifstream file(usersFile);
		string existingUsername;
		while (file >> existingUsername) {
			if (existingUsername == uname) {
				file.close();
				return false;
			}
		}
		file.close();

		ofstream outFile(usersFile, ios::app);
		if (outFile.is_open()) {
			outFile << uname << " " << pwd << endl;
			outFile.close();
			return true;
		}
		return false;
	}

	User* findUser(const string& uname, const string& pwd) {
		ifstream file(usersFile);
		string username, password;
		while (file >> username >> password) {
			if (username == uname && password == pwd) {
				file.close();
				return new User(username, password);
			}
		}
		file.close();
		return nullptr;
	}
};

class admin {
private:
	string username;
	string password;

public:
	admin(const string& uname, const string& pwd) : username(uname), password(pwd) {}

	bool authenticate(const string& uname, const string& pwd) const {
		return (username == uname && password == pwd);
	}

	const string& getUsername() const {
		return username;
	}


};

class adminManager {
private:
	const string adminFile = "admins.txt";

public:
	bool addadmin(const string& uname, const string& pwd) {
		ifstream file(adminFile);
		string existingUsername;
		while (file >> existingUsername) {
			if (existingUsername == uname) {
				file.close();
				return false;
			}
		}
		file.close();

		ofstream outFile(adminFile, ios::app);
		if (outFile.is_open()) {
			outFile << uname << " " << pwd << endl;
			outFile.close();
			return true;
		}
		return false;
	}

	admin* findadmin(const string& uname, const string& pwd) {
		ifstream file(adminFile);
		string username, password;
		while (file >> username >> password) {
			if (username == uname && password == pwd) {
				file.close();
				return new admin(username, password);
			}
		}
		file.close();
		return nullptr;
	}
};

class Product {
private:
	int id;
	string name;
	float price;
	int quantity;

public:
	Product(int pid, const string& pname, float pprice, int pquantity)
		: id(pid), name(pname), price(pprice), quantity(pquantity) {}

	int getId() const {
		return id;
	}

	const string& getName() const {
		return name;
	}

	float getPrice() const {
		return price;
	}

	int getQuantity() const {
		return quantity;
	}

	void display() const {
		cout << "ID: " << id << ", Name: " << name << ", Price: $" << price << ", Quantity: " << quantity << endl;
	}
};

class ProductManager {
private:
	const string productsFile = "products.txt";

public:
	void addProduct(int pid, const string& pname, float pprice, int pquantity) {
		ofstream outFile(productsFile, ios::app);
		if (outFile.is_open()) {
			outFile << pid << " " << pname << " " << pprice << " " << pquantity << endl;
			outFile.close();
		}
	}

	Product* findProduct(const string& pname) {
		ifstream file(productsFile);
		int id;
		string name;
		float price;
		int quantity;
		while (file >> id >> name >> price >> quantity) {
			if (name == pname) {
				file.close();
				return new Product(id, name, price, quantity);
			}
		}
		file.close();
		return nullptr;
	}

	void displayAllProducts() {
		ifstream file(productsFile);
		int id;
		string name;
		float price;
		int quantity;
		while (file >> id >> name >> price >> quantity) {
			Product product(id, name, price, quantity);
			product.display();
		}
		file.close();
	}
	void removeProduct(int productId) {
		ifstream inFile(productsFile);
		ofstream outFile("temp.txt");

		int id;
		string name;
		float price;
		int quantity;
		bool found = false;

		while (inFile >> id >> name >> price >> quantity) {
			if (id == productId) {
				found = true;
				continue;
			}
			outFile << id << " " << name << " " << price << " " << quantity << endl;
		}

		inFile.close();
		outFile.close();

		if (found) {
			remove(productsFile.c_str());
			rename("temp.txt", productsFile.c_str());
			cout << "Product removed successfully!" << endl;
		}
		else {
			cout << "Product not found." << endl;
		}
	}

	int decreaseProductQuantity(int productId, int quantityToDecrease) {
		ifstream inFile(productsFile);
		ofstream outFile("temp.txt");

		int id;
		string name;
		float price;
		int quantity;
		bool found = false;

		while (inFile >> id >> name >> price >> quantity) {
			if (id == productId) {
				found = true;
				if (quantity == 0) {
					inFile.close();
					outFile.close();
					return 0; // Quantity is already zero
				}
				else if (quantity - quantityToDecrease < 0) {


					inFile.close();
					outFile.close();
					return 2;
				}
				else {
					quantity -= quantityToDecrease;

				}
			}
			outFile << id << " " << name << " " << price << " " << quantity << endl;
		}

		inFile.close();
		outFile.close();
		if (found) {
			remove(productsFile.c_str());
			rename("temp.txt", productsFile.c_str());
			return 1; // Quantity decreased successfully
		}
		else {
			return -1; // Product not found
		}
	}

	int addProductQuantity(int productId, int quantityToAdd) {
		ifstream inFile(productsFile);
		ofstream outFile("temp.txt");

		int id;
		string name;
		float price;
		int quantity;
		bool found = false;

		while (inFile >> id >> name >> price >> quantity) {
			if (id == productId) {
				found = true;
				quantity += quantityToAdd;
			}
			outFile << id << " " << name << " " << price << " " << quantity << endl;
		}

		inFile.close();
		outFile.close();

		if (found) {
			remove(productsFile.c_str());
			rename("temp.txt", productsFile.c_str());
			return 1; // Quantity increased successfully
		}
		else {
			return -1; // Product not found
		}
	}
	bool getProductDetails(int productId, string& productName, float& productPrice) {
		ifstream inFile(productsFile);
		int id;
		string name;
		float price;
		int quantity;

		while (inFile >> id >> name >> price >> quantity) {
			if (id == productId) {
				inFile.close();
				productName = name;
				productPrice = price;
				return true; // Product found
			}
		}

		inFile.close();
		return false; // Product ID not found
	}
};


class Review {
private:
	string userName;
	string reviewText;

public:
	Review(const string& uname, const string& review) : userName(uname), reviewText(review) {}

	const string& getUserName() const {
		return userName;
	}

	const string& getReviewText() const {
		return reviewText;
	}
};


class ReviewManager {
private:
	const string reviewsFile = "reviews.txt";

public:
	void writeReview(string& uname, string& reviewText) {
		ofstream outFile(reviewsFile, ios::app);
		if (outFile.is_open()) {
			outFile << uname << " : " << reviewText << endl;
			outFile.close();
		}
	}

	void readReviews() const {
		ifstream file(reviewsFile);
		string username, review;
		cout << "Reviews:" << endl;
		while (file >> review) {
			Review r(username, review);
			/*cout << "User: " << r.getUserName() << ", Review: " << r.getReviewText() << endl;*/

			cout << review << " ";
		}
		file.close();
	}

	//void readReviews() const {
	//    ifstream file(reviewsFile);
	//    string line;

	//    cout << "Reviews:" << endl;
	//    while (getline(file, line)) {
	//        istringstream iss(line);
	//        string username, reviewText;

	//        // Read username and review text separately
	//        if (iss >> username >> ws && getline(iss, reviewText)) {
	//            Review r(username, reviewText);
	//            cout << "User: " << r.getUserName() << ", Review: " << r.getReviewText() << endl;
	//        }
	//    }
	//    file.close();
	//}

};



void adminMenu() {
	int choice;
	while (true) {
		cout << "\nAdmin Menu:" << endl;
		cout << "1. Add Product" << endl;
		cout << "2. Remove Product" << endl;
		cout << "3. Add Quantity of Product" << endl;
		cout << "4. Display All Products" << endl;
		cout << "5. Read Reviews" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		ProductManager pm;
		ReviewManager rm;

		if (choice == 1) {

			int pid;
			string pname;
			float pprice;
			int pquantity;

			cout << "\nEnter product's id : ";
			cin >> pid;
			cout << "Enter product's name : ";
			cin >> pname;
			cout << "Enter product's price : ";
			cin >> pprice;
			cout << "Enter product's quantity : ";
			cin >> pquantity;
			pm.addProduct(pid, pname, pprice, pquantity);
			cout << "Product added successfully.\n";
		}
		else if (choice == 2) {

			int pid;
			cout << "\nEnter product's id : ";
			cin >> pid;
			pm.removeProduct(pid);
			cout << "product removed successfully.";
		}
		else if (choice == 3) {

			int pid;
			int pquantity;
			cout << "\nEnter product's id : ";
			cin >> pid;
			cout << "Enter quantity you want to add to product's previous quantity : ";
			cin >> pquantity;
			int i = pm.addProductQuantity(pid, pquantity);
			if (i == 1) {
				cout << "\nProduct quantity increased successfully.";
			}
			else {
				cout << "\nProduct not found.";
			}
		}
		else if (choice == 4) {

			pm.displayAllProducts();
		}
		else if (choice == 5) {
			cout << endl;
			rm.readReviews();
			cout << endl;
		}
		else if (choice == 6) {
			cout << "Exiting Admin Panel..." << endl;
			return;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}


void userMenu(string username) {
	int choice;
	while (true) {
		cout << "\nUser Menu:" << endl;
		cout << "1. Write Review" << endl;
		cout << "2. Display Products" << endl;
		cout << "3. Buy Products" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		ReviewManager rm;
		ProductManager pm;

		if (choice == 1) {

			string review;
			cout << "Write your review : ";
			cin.ignore();
			cin.clear();
			getline(cin, review);
			cin.ignore();
			cin.clear();
			rm.writeReview(username, review);
			cout << "\nThe review has been submitted successfully.";

		}
		else if (choice == 2) {
			pm.displayAllProducts();
		}
		else if (choice == 3) {

			int pid;
			int pquantity;
			string cardno;
			string pin;
			string cvv;
			cout << "\nEnter product's id you want to buy : ";
			cin >> pid;
			cout << "Enter in how much quantity you want the product : ";
			cin >> pquantity;
			cout << "Enter you Card Number : ";
			cin >> cardno;
			cout << "Enter you Card CVV : ";
			cin >> cvv;
			cout << "Enter you Card pin : ";
			cin >> pin;

			int i = pm.decreaseProductQuantity(pid, pquantity);
			if (i == 0 || i == 2) {
				cout << "\nProduct is not available in that much quantity.";
			}
			else if (i == 1) {
				cout << "\nYour purchase is successfull.";
				string pname; float pprice, tprice;
				pm.getProductDetails(pid, pname, pprice);
				cout << "\nBill : \n";
				cout << "User Name : " << username << endl;
				cout << "Purchase through card : " << cardno << endl;
				cout << "Product name : " << pname << endl;
				cout << "Price of single product : " << pprice << " $" << endl;
				cout << "Product quantity : " << pquantity << endl;
				tprice = pprice * pquantity;
				cout << "Total price/Amount paid : " << tprice << " $" << endl;
			}
			else {
				cout << "\nProduct not found.";
			}
		}
		else if (choice == 4) {
			cout << "Exiting User Panel..." << endl;
			return;
		}
		else
		{
			cout << "Invalid choice. Please try again." << endl;
		}
	}
}

int main() {
	int choice;
	while (true) {
		cout << "\nMain Menu:" << endl;
		cout << "1. Admin Login" << endl;
		cout << "2. User Login" << endl;
		cout << "3. User Sign Up" << endl;
		cout << "4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		adminManager am;
		UserManager um;
		if (choice == 1) {

			string enteredUsername, enteredPassword;
			cout << "Enter username: ";
			cin >> enteredUsername;
			cout << "Enter password: ";
			cin >> enteredPassword;

			admin* loggedInUser = am.findadmin(enteredUsername, enteredPassword);
			if (loggedInUser != nullptr) {
				cout << "Login successful! Welcome, " << loggedInUser->getUsername() << "!" << endl;
				delete loggedInUser;
				adminMenu();
			}
			else {
				cout << "Invalid username or password. Login failed." << endl;
			}
		}
		else if (choice == 2) {
			string enteredUsername, enteredPassword;
			cout << "Enter username: ";
			cin >> enteredUsername;
			cout << "Enter password: ";
			cin >> enteredPassword;

			User* loggedInUser = um.findUser(enteredUsername, enteredPassword);
			if (loggedInUser != nullptr) {
				cout << "Login successful! Welcome, " << loggedInUser->getUsername() << "!" << endl;
				delete loggedInUser;
				userMenu(enteredUsername);
			}
			else {
				cout << "Invalid username or password. Login failed." << endl;
			}
		}
		else if (choice == 3) {
			string newUsername;
			string newPassword;
			cout << "Enter new user name : ";
			cin >> newUsername;
			cout << "Enter your password : ";
			cin >> newPassword;
			bool userAdded = um.addUser(newUsername, newPassword);
			if (userAdded) {
				cout << "User added successfully!" << endl;
			}
			else {
				cout << "Failed to add user. User already exists." << endl;
			}

		}
		else if (choice == 4) {
			cout << "Exiting Program..." << endl;
			return 0;
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}
	return 0;
}


