#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

static const int items = 10;
static string Menu[items] = { "Mamee", "Lays", "Dorito", "Twister", "Snek Ku", "Apollo Layer Cakes", "Super Rings", "Cheetos", "Pringles", "JACKnJILL" };
static double Price[items] = { 5, 10, 10, 3, 2, 1, 2, 12, 8, 4 };
static const int RItems = 100;
static string Rec[RItems];
static double RecPrice[RItems]; 

void DisMenu();
void DisReceipt(double total);
void DisplayReceiptFile(); 

int main()
{
	double total = 0;
	int count = 0;
	int selection, quantity;

	while (true) {
		DisMenu();
		cout << "Enter selection (0 to quit): ";
		cin >> selection;

		if (selection == 0) {
			break;
		}
		else if (selection >= 1 && selection <= items) {
			cout << "Enter the quantity for the item you wish to purchase: ";
			cin >> quantity;

			if (count < RItems) {
				total += (quantity * Price[selection - 1]);
				Rec[count] = Menu[selection - 1];
				RecPrice[count] = (quantity * Price[selection - 1]);
				count++;
			}
			else {
				cout << "Maximum receipt items reached.\n";
				break;
			}
		}
		else {
			cout << "\nInvalid selection, please enter a number between 0 and " << items << ".\n";
		}
	}

	cout << "\nTotal Charges:\n";
	DisReceipt(total);
	DisplayReceiptFile(); 

	return 0;
}

void DisMenu() {
	cout << "\n======= Menu =======\n";
	for (int num = 0; num < items; num++) {
		cout << num + 1 << ". " << Menu[num] << "   RM" << Price[num] << endl;
	}
	cout << "====================\n";
}

void DisReceipt(double total) {

	for (int i = 0; i < RItems && !Rec[i].empty(); i++) { //display on console
		cout << i + 1 << ". " << Rec[i] << "   RM" << RecPrice[i] << endl;
	}
	cout << "====================\n";
	cout << "Total Price: RM" << total << endl;

	cout << "\nPlease enter the amount of money you wish to insert: RM";
	double Dmoney, AddMoney, Changes = 0;
	cin >> Dmoney;

	while (true) {
		if (Dmoney < total) {
			cout << "Please enter more money to cover for the total price: RM";
			cin >> AddMoney;
			Dmoney += AddMoney;
		}
		else if (Dmoney >= total) {
			Changes = Dmoney - total;
			break;
		}
		else
			cout << "\nInvalid input. Please enter a number.\n";
	}

	ofstream dataFile("Receipt.dat"); //writes in Receipt.dat
	dataFile << fixed << setprecision(2);

	for (int i = 0; i < RItems && !Rec[i].empty(); i++) {
		dataFile << i + 1 << ". " << Rec[i] << "   RM" << RecPrice[i] << endl;
	}
	dataFile << "=====================================\n";
	dataFile << "Total Price: RM" << total << endl << "Cash: RM" << Dmoney << endl << "Changes: RM" << Changes;
	dataFile.close();
}

void DisplayReceiptFile() {
	ifstream dataFile("Receipt.dat");

	if (!dataFile) {
		cout << "Unable to open 'Receipt.dat'.\n";
		return;
	}

	cout << "\n======= Displaying Receipt.dat =======\n";
	string line;
	while (getline(dataFile, line)) {
		cout << line << endl;
	}
	cout << "=====================================\n";

	dataFile.close();
}
