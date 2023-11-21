#include <iostream>
#include <fstream> // Бібліотека для запису та зчитування файлу
#include <vector> // Бібліотека для використання ліста
#include <string>
#include <algorithm> // Бібліотека для сортування ліста
#include <iomanip> // Для setw
#include <Windows.h> //Sleep



using namespace std;

int id = 1; //Глобальний ід





// Функція таблички меню
void funcMenutext()
{
	cout << "\nSupermarket menu:" << endl;
	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;

	cout << left << setw(24) << "| 1. Show all products"
		<< setw(20) << "| 2. Add a product"
		<< setw(21) << "| 3. Delete product"
		<< setw(13) << "| 4. Search"
		<< setw(14) << "| 5. Selling"
		<< setw(14) << "| 6. Sorting"
		<< setw(19) << "| 0. Finish work |" << endl;

	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;
}





// Функція шапки таблички
void headStorage()
{
	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;

	cout << left << setw(9) << "id"
		<< setw(23) << "Name"
		<< setw(20) << "Group"
		<< setw(18) << "Price"
		<< setw(19) << "Quantity" << endl;

	fill_n(ostream_iterator<char>(cout), 124, '-');
	cout << endl;
}





// Клас Product представляє окремий товар у супермаркеті
class Product
{
private:
	int id;             // Унікальний ідентифікатор продукту
	string name;        // Назва продукту
	string category;    // Категорія продукту
	double price;       // Ціна продукту
	int quantity;       // Кількість продукту у супермаркеті
public:
	Product() : id(0), name(""), category(""), price(0.0), quantity(0) {}

	Product(int id, const string& name, const string& category, double price, int quantity)
		: id(id), name(name), category(category), price(price), quantity(quantity) {}

	// Сетери і гетери для доступу до властивостей продукту

	void setID(int newID) { id = newID; }
	int getID() const { return id; }

	void setName(const string& newName) { name = newName; }
	string getName() const { return name; }

	void setCategory(const string& newCategory) { category = newCategory; }
	string getCategory() const { return category; }

	void setPrice(double newPrice) { price = newPrice; }
	double getPrice() const { return price; }

	void setQuantity(int newQuantity) { quantity = newQuantity; }
	int getQuantity() const { return quantity; }
};





// Клас Supermarket відповідає за управління товарами у супермаркеті
class Supermarket
{
private:
	vector<Product> products;  // Список продуктів у супермаркеті
public:
	Supermarket() {}

	int getLastProductID() const
	{
		if (products.empty()) {
			return 0;
		}
		return products.back().getID();
	}

	bool isEmpty() const
	{
		return products.empty();
	} 

	// Додавання продукту до асортименту супермаркету
	void addProduct(const Product& product)
	{
		int lastID = products.empty() ? 0 : products.back().getID();
		products.push_back(product); //Стандартна функція додавання у список вектор
	}

	// Збереження даних про продукти у файлі
	void saveToFile(const string& filename)
	{
		ofstream file(filename);
		if (file.is_open())
		{
			for (const Product& product : products)
			{
				// Записуємо дані про продукт у файл.
				file << product.getID() << endl;
				file << product.getName() << endl;
				file << product.getCategory() << endl;
				file << product.getPrice() << endl;
				file << product.getQuantity() << endl;
			}
			file.close();
			cout << "The data is saved to a file " << filename << endl;
		}
		else
		{
			cout << "Unable to open file " << filename << " for recording" << endl;
		}
	}

	// Завантаження даних про продукти з файлу
	void loadFromFile(const string& filename)
	{
		ifstream file(filename);
		if (file.is_open()) {
			products.clear();
			int id, quantity;
			double price;
			string name, category;
			while (file >> id >> name >> category >> price >> quantity)
			{
				Product product(id, name, category, price, quantity);
				products.push_back(product);
			}
			file.close();
			cout << "Data is loaded from a file " << filename << endl;
		}
		else
		{
			cout << "Unable to open file " << filename << " for reading" << endl;
		}
	}

	// Виведення на екран інформації про всі товари у супермаркеті
	void displayAllProducts()
	{
		for (const Product& product : products)
		{
			cout << left << setw(9) << product.getID()
				<< setw(23) << product.getName()
				<< setw(20) << product.getCategory()
				<< setw(18) << product.getPrice()
				<< setw(19) << product.getQuantity() << endl;
		}
	}

	// Пошук продуктів певної категорії
	void displayProductsByCategory(const string& category)
	{
		cout << "Products in the category: " << category << endl;
		headStorage();
		for (const Product& product : products)
		{
			if (product.getCategory() == category)
			{
				cout << left << setw(9) << product.getID()
					<< setw(23) << product.getName()
					<< setw(20) << product.getCategory()
					<< setw(18) << product.getPrice()
					<< setw(19) << product.getQuantity() << endl;
			}
		}
	}

	// Пошук продукту за назвою
	void searchProductByName(const string& name)
	{
		cout << "Product search by name: " << name << endl;
		headStorage();
		bool found = false;
		for (const Product& product : products)
		{
			if (product.getName() == name)
			{
				cout << left << setw(9) << product.getID()
					<< setw(23) << product.getName()
					<< setw(20) << product.getCategory()
					<< setw(18) << product.getPrice()
					<< setw(19) << product.getQuantity() << endl;
				found = true;
			}
		}
		if (!found)
		{
			cout << "Product not found" << endl;
		}
	}

	// Видалення продукту за ID
	void deleteProductByID(int id)
	{
		for (auto it = products.begin(); it != products.end(); ++it)
		{
			if (it->getID() == id)
			{
				products.erase(it);
				cout << "Product with ID " << id << " deleted" << endl;
				return;
			}
		}
		cout << "Product with ID " << id << " not found" << endl;
	}

	// Продаж продукту за ID та кількість.
	void sellProduct(int id, int quantity)
	{
		for (Product& product : products)
		{
			if (product.getID() == id)
			{
				if (product.getQuantity() >= quantity)
				{
					product.setQuantity(product.getQuantity() - quantity);
					cout << "The sale is successful. The total cost: " << (product.getPrice() * quantity) << endl;
				}
				else
				{
					cout << "Insufficient quantity in stock" << endl;
				}
				return;
			}
		}
		cout << "Product with ID " << id << " not found" << endl;
	}

	// Сортування за ID.
	void sortProductsByID() {
		sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
			return a.getID() < b.getID();
			});
		cout << "Products are sorted by ID" << endl;
	}

	// Сортування за назвою.
	void sortProductsByName() {
		sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
			return a.getName() < b.getName();
			});
		cout << "Products are sorted by name" << endl;
	}

	// Сортування за ціною.
	void sortProductsByPrice()
	{
		sort(products.begin(), products.end(), [](const Product& a, const Product& b)
			{
				return a.getPrice() < b.getPrice();
			});
		cout << "Products are sorted by price" << endl;
	}
};





void main()
{
	Supermarket supermarket;

	string filename = "supermarket_data.txt";

	supermarket.loadFromFile(filename);

	if (!supermarket.isEmpty()) 
	{
		id = supermarket.getLastProductID() + 1;
	}

	int numMenu = 0;

	do
	{
		funcMenutext();
		cout << "Enter number menu: ";
		cin >> numMenu;
		cin.ignore();



		if (numMenu > 7)
		{
			system("cls");
			funcMenutext();
			cout << "Enter number menu: ";
			cin >> numMenu;
			cin.ignore();
		}



		if (numMenu == 1)
		{
			system("cls");
			cout << "Oll Products" << endl << endl;
			headStorage();
			supermarket.displayAllProducts();
			fill_n(ostream_iterator<char>(cout), 124, '-');
			cout << endl;
		}



		if (numMenu == 2)
		{
			system("cls");

			int quantity;
			double price;
			string name, category;
			cout << "Enter the name of the product: ";
			cin >> name;
			cin.ignore();
			cout << "Enter the product category: ";
			cin >> category;
			cin.ignore();
			cout << "Enter the price of the product: ";
			cin >> price;
			cin.ignore();
			cout << "Enter the product quantity: ";
			cin >> quantity;
			cin.ignore();
			Product product(id, name, category, price, quantity);
			id++;
			supermarket.addProduct(product);
			supermarket.saveToFile(filename);

			system("cls");
			cout << "\nA new product has been added!" << endl;
			Sleep(2000);
			system("cls");
		}



		if (numMenu == 3)
		{
			int id;
			cout << "Enter the product ID to remove: ";
			cin >> id;
			cin.ignore();
			supermarket.deleteProductByID(id);
			supermarket.saveToFile(filename);
		}



		if (numMenu == 4)
		{
			system("cls");
			cout << "1. Find product by name" << endl;
			cout << "2. Find products by category" << endl;
			int numberFind;
			cout << "Enter search criteria: ";
			cin >> numberFind;
			cin.ignore();

			switch (numberFind)
			{
			case 1:
			{
				string name;
				cout << "Enter the name of the product: ";
				cin >> name;
				cin.ignore();
				supermarket.searchProductByName(name);
				break;
			}
			case 2:
			{
				string category;
				cout << "Enter a category: ";
				cin >> category;
				cin.ignore();
				supermarket.displayProductsByCategory(category);
				break;
			}
			default:
				break;
			}
		}



		if (numMenu == 5)
		{
			int id, quantity;
			cout << "Enter the Product ID to sell: ";
			cin >> id;
			cin.ignore();
			cout << "Enter the quantity to sell: ";
			cin >> quantity;
			cin.ignore();
			system("cls");
			supermarket.sellProduct(id, quantity);
		}



		if (numMenu == 6)
		{
			system("cls");
			cout << "1. Sorting goods by Price" << endl;
			cout << "2. Sorting goods by Name" << endl;
			cout << "3. Sorting goods by ID" << endl;
			cout << "Another number: Exit to the initial menu" << endl;
			int numberSort;
			cout << "Enter number menu: ";
			cin >> numberSort;
			cin.ignore();

			switch (numberSort)
			{
			case 1:
			{
				supermarket.sortProductsByPrice();
				supermarket.saveToFile(filename);
				system("cls");
				cout << "\nProduct are sorted by Price!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			case 2:
			{
				supermarket.sortProductsByName();
				supermarket.saveToFile(filename);
				system("cls");
				cout << "\nProduct are sorted by Name!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			case 3:
			{
				supermarket.sortProductsByID();
				supermarket.saveToFile(filename);
				system("cls");
				cout << "\nProduct are sorted by ID!" << endl;
				Sleep(2000);
				system("cls");
				break;
			}
			default:
				break;
			}
		}
	} while (numMenu != 0);
}