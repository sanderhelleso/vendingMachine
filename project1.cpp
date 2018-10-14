/*
 *  Title: project1.cpp
 *
 *  Abstract: 
 *  - This program simulates an imaginary vending machine on the CSUMB 
 *    campus. A user can buy a bottle of water ($1.50), a bottle of coffee ($2.00),
 *    a chip ($1.00), and a chocolate bar ($2.50) from the machine. The user can 
 *    select several item(s) if the items are available from the machine. Furthermore,
 *    the user can de-select item(s) that are already selected. After finishing the selection
 *    of item(s), the user can pay for the items with either a debit card (Valid PIN: 7777)
 *    or cash. A user can try to pay the item(s) only one time and if the user fails to pay
 *    due to the incorrect PIN or insufficient cash amount, the machine will de-select all
 *    sections the user chose. Note that an administrator of the machine can refill the 
 *    machine or reset it to the initial status.
 * 
 *  - The program is written to scale, and in all functions except refill (cap up to 4), the program
 *    will be able to handle any amount of items.
 *   
 *  Author: Sander Hellesoe
 *  ID: 7337
 *  Date: 09/30/2018
 */

#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <sstream>
#include <limits>
#include <iterator>
#include <tuple>
#include <vector>

using namespace std;


//////////////////////////// HELPER FUNCTIONS HEADS ////////////////////////////


void clearCin(); // clear cin
string displayError(string message); // display error in red
string displaySuccess(string message); // display success action in green
string prettyPrintDouble(double value); // print out doubles nicely formated



///////////////////////////////////////////////////////////////////////////////







//////////////////////////// MACHINE ITEM STRUCTURE ///////////////////////////

struct item 
{
    string name;
    double price;
    int quantity;
    int sold;
} water, regularCoffe, sunChip, chocolateBar; // base machine items


/////////////////////////////////////////////////////////////////////////////







///////////////////////////// VENDING MACHINE  ////////////////////////////


class VendingMachine 
{
    
    public:
        
        // helper functions
        void fillUpItems();
        bool checkQuantity(int index, int quantity);
        bool continueSelection();
        double getTotalPrice();
        bool payDebit();
        bool payCash();
        void resetSelectedItems();
        
        // core functions
        const string display();
        bool setNumber(int vmNumber);
        bool setName(string vmName);
        void status();
        bool refill(int amount1, int amount2, int amount3, int amount4);
        void displayMenu();
        bool selectItem();
        bool payment();
        void displayReceipt();
        void deselect();
        void reset();
        
        // constructors
        VendingMachine();
        VendingMachine(int number, string name);
    
    private:
        
        // member fields
        int number;
        string name;
        const int TAX = 10; // tax is set to 10% of total price
        list<item> items; // all items of machine
        vector<tuple<item, int>> selectedItems; // items selected by user for purcase
};


//////////////////////////////////////////////////////////////////////////////







//////////////////////////////// CONSTRUCTORS //////////////////////////////


// default constructor
VendingMachine::VendingMachine()
: number(0), name("UNKNOWN")
{
    
    fillUpItems();     // fill up machine with items
}

// constructor with number and name
VendingMachine::VendingMachine(int vmNumber, string vmName) 
: number(vmNumber), name(vmName)
{
    fillUpItems();
}

/////////////////////////////////////////////////////////////////////////







///////////////////////////// CLASS FUNCTIONS //////////////////////////


// fill up machine with items
void VendingMachine::fillUpItems() 
{
    // machine items
    water = {"Water", 1.50, 0, 0};
    regularCoffe = {"Regular Coffee", 2.0, 0, 0};
    sunChip = {"Sun Chip", 1.0, 0, 0};
    chocolateBar = {"Chocolate Bar", 2.50, 0, 0};
    
    // add items to list
    items.push_back(water);
    items.push_back(regularCoffe);
    items.push_back(sunChip);
    items.push_back(chocolateBar);
}

// display vending machine information
const string VendingMachine::display() 
{
    return "Number: " + to_string(number) + ", Name: " + name + "\n";
}

// set the number for a vending machine
bool VendingMachine::setNumber(int vmNumber) 
{
    number = vmNumber;
    return true;
}

// set the name for a vending machine
bool VendingMachine::setName(string vmName) 
{
    name = vmName;
    return true;
}

// display the current status of vending machine
void VendingMachine::status() 
{
    
    // get item information
    string sold = "Sold:";
    string remaining = "Remaining:";
    double totalEarning = 0.0;
    for (item const &item : items) 
    {
        sold += " " + item.name + ": " + to_string(item.sold) + " /";
        remaining += " " + item.name + ": " + to_string(item.quantity) + " /";
        totalEarning += (item.sold * item.price);
    }
    
    // remove last "/" from strings
    sold.pop_back();
    remaining.pop_back();
    
    // display machine status
    cout << display() << sold + "\n" + remaining + "\nTotal Earnings: " << displaySuccess("$" + prettyPrintDouble(totalEarning + (totalEarning / TAX))) << endl;
}

// refill vending machine items
bool VendingMachine::refill(int amount1, int amount2, int amount3, int amount4) 
{
    // add amounts to array
    int refillAmount[4] = {amount1, amount2, amount3, amount4};
    int index = 0;
    for (item &item : items) {
        item.quantity += refillAmount[index];
        index++;
    }
    
    return true;
}

// display vending machine items available, price and selection number
void VendingMachine::displayMenu() 
{
    string menu = "===== Vending Machine Menu =====\n";
    
    // for every item available, store string data
    int index = 1;
    for (item const &item : items) 
    {
        
        string itemMenu = to_string(index) + ". " + item.name;
        for (int i = 0; i < (17 - item.name.length()); i++) 
        {
            itemMenu += ".";
        }
        
        // add item price
        itemMenu += "$" + prettyPrintDouble(item.price) + "\n";
        menu += itemMenu;
        index++;
    }
    
    // display finished menu
    cout << menu;
}

// allow user to select item(s) to buy from the vending machine
bool VendingMachine::selectItem() 
{   
    const string ERROR_MESSAGE = displayError("Invalid Option. Options available: (1 - " + to_string(items.size()) + ").");
    const string PROMPT = "Select Item: ";
    cout << PROMPT;

    int option = 0;
    bool correctOption = false;
    
    // continue to prompt until an correct option is selected
    while (!correctOption) 
    {
        // check for number input
        while(!(cin >> option) && !correctOption)
        {   
            clearCin();
            cerr << displayError(ERROR_MESSAGE);
            cout << PROMPT;
        }
        
        // check for correct number option (range of unique items in machine)
        for (int i = 1; i < items.size() + 1; i++) {
            if (option == i) {
                correctOption = true;
            }
        }
        
        if (!correctOption)
        {   
            cerr << displayError(ERROR_MESSAGE);
            cout << PROMPT;
        }
    }
    
    // prompt user for amount to buy
    cout << "How many do you want to buy? ";
    
    // get amount of item user wants to buy
    int amount = 0;
    
    while (!(cin >> amount && amount > 0))
    {   
        clearCin();
        cerr << displayError("Invalid Option. Please select your amount.") << "\nSelect amount: ";
    }
    
    // validate selection amount
    checkQuantity(option - 1, amount);
    
    // propmt user to continue
    if (continueSelection()) {
        cout << endl;
        selectItem();
    }
    
    return true;
}

// check if item has sufficent quantity to purcase
bool VendingMachine::checkQuantity(int index, int quantity) 
{
    
    int count = 0;
    for (item &item : items)
    {
        
        // selected item
        if (count == index) 
        {
            
            // info about item and quanitiy to be displayed to user
            string info = "You selected " + item.name + " (" + to_string(quantity) + ")";
            
            // check for sufficent quantity
            if (item.quantity < quantity) 
            {
                info += " - Sorry. We don’t have enough " + item.name + "s.";
                cerr << displayError(info) << endl;
                return false;
            }
            
            // decrement quantity of item temporaly
            item.quantity -= quantity;

            // add item and quantity to "selected items"
            cout << info << endl;
            selectedItems.emplace_back(item, quantity);
            return true;
        }
        
        count++;
    }
    
    return false;
}

// prompt the user to continue or quit vending machine item selection
bool VendingMachine::continueSelection() 
{
    clearCin();
    
    char option = {0};
    bool correctOption = false;
    
    // prompt user for option until correct
    while (!correctOption) 
    {
        cout << "Continue? (Y/N) ";
        string input;
        getline(cin, input);
        
        // options allowed Y or N, reprompt and display error message if false
        if (input.length() == 1 && (toupper(input[0]) == 'Y' ||  toupper(input[0]) == 'N')) 
        {
            option = toupper(input[0]);
            correctOption = true;
        }
        
        else {
            cerr << displayError("Invalid option. Options available: (Y/N).") << endl;
        }
    }
    
    // quit selection
    if (option == 'N')
    {
        return false;
    }
    
    // continue selection
    return true;
}

// prompt user for payment option
bool VendingMachine::payment() 
{
    const string ERROR_MESSAGE = "Invalid Option. Options available: (1 - 2).\n";
    const string PROMPT = "Please pay the following amount (10% Tax included): " + displaySuccess("$" + prettyPrintDouble(getTotalPrice())) + "Payment Option – Debit(1) / Cash(2): ";
    
    // if user have not selected any items
    if (selectedItems.size() == 0) 
    {   
        cerr << displayError("Could not continue payment. No items have been selected.");
        return false;
    }
    
    // display available payment options
    cout << PROMPT;
    int option = 0;
    bool correctOption = false;
    
    // continue to prompt until an correct option is selected
    while (!correctOption) 
    {
        // check for number input
        while(!(cin >> option) && !correctOption)
        {
            clearCin();
            cerr << displayError(ERROR_MESSAGE);
            cout << PROMPT;
        }
        
        // check for correct number option (1 - 2)
        if (option == 1 || option == 2) 
        {
            correctOption = true;
        }
        
        else 
        {   clearCin();
            cerr << displayError(ERROR_MESSAGE);
            cout << PROMPT;
        }
    }
    
    // user will pay with debit or cash depending on option selected
    switch (option) {
        
        // debit payment
        case 1:
            // payment failed
            if (!payDebit()) {
                resetSelectedItems();
                return false;
            }
            
            // payment succesfull
            return true;
        
        // cash payment 
        case 2:
            // payment failed
            if (!payCash()) {
                resetSelectedItems();
                return false;
            }
            
            // payment succesfull
            return true;
    }
}

// clear selected items and reset quantity
void VendingMachine::resetSelectedItems() 
{
    
    // update vending machine item status
    for (item &item : items) 
    {
        for (int i = 0; i < selectedItems.size(); i++) 
        {
            if (item.name == get<0>(selectedItems[i]).name) 
            {
                item.quantity += get<1>(selectedItems[i]);
            }
        }
    }
    
    // clear selected items
    selectedItems.clear();
}


/*-------------------------------------------------------
                        <pay debit>
                    

allow user to pay with debit. Since all PINs are 4 digits,
there are multiple input checks to handle the validation.
eg: 07777 should NOT work and terminate the payment process

---------------------------------------------------------*/

bool VendingMachine::payDebit() 
{
    clearCin();
    
    // ask user to enter PIN
    cout << "Enter PIN: ";
    
    // accept input as string to solve problem
    // with wrong input format (07777, 007777 etc)
    string pin; 
    cin >> pin;
    
    // check for valid pin
    if (pin == "7777") 
    {   
        cout << displaySuccess("Valid") << endl;
        return true; // correct pin entered
    }
    
    // wrong pin or input entered
    return false;
}

// get total price to pay
double VendingMachine::getTotalPrice() {
    
    double totalPrice = 0.0;
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        
        // item values
        item item = get<0>(selectedItems[i]);
        int quantity = get<1>(selectedItems[i]);
        
        // update total price
        totalPrice += item.price * quantity;
    }
    
    return totalPrice + (totalPrice / TAX);
}

// allow user to pay with cash
bool VendingMachine::payCash() 
{

    // get total price to pay
    double totalPrice = getTotalPrice();
    
    // ask user to enter money amount
    cout << "Enter Money Amount: ";
    
    // get dollar sign required for cash payment
    char dollarSign;
    cin >> dollarSign; 

    if (dollarSign != '$')
    {   
        clearCin();
        return false;
    }
    

    // get amount after $ sign
    double amount;
    cin >> amount;

    // check for sufficent money amount
    if (amount >= totalPrice) 
    {
        
        // display change
        cout << "Change: " + displaySuccess("$" + prettyPrintDouble(amount - totalPrice)) + "\n";
        return true;
    }
    
    // not enough money or wrong input
    return false;
}

// display receipt of purcase
void VendingMachine::displayReceipt() 
{
    string receipt = "";
    double subTotal = 0.0;
    for (int i = 0; i < selectedItems.size(); i++) 
    {
        
        // item values
        item item = get<0>(selectedItems[i]);
        int quantity = get<1>(selectedItems[i]);
        
        // update total selection data
        subTotal += item.price * quantity;

        // create receipt
        receipt += item.name + ": $" + prettyPrintDouble(item.price) + " X ";
        receipt += to_string(quantity) + " = $" + prettyPrintDouble(item.price * quantity) + "\n";

    }
    
    // display subtotal, tax, and total
    receipt += "Subtotal: $" + prettyPrintDouble(subTotal) + "\n";
    receipt += "Tax (10.0%): $" + prettyPrintDouble(subTotal / TAX) + "\n";
    receipt += "Total: $" + prettyPrintDouble(subTotal + (subTotal / TAX)) + "\n";

    // print receipt
    cout << receipt << endl;
    
    // update vending machine item status
    for (item &item : items) {
        for (int i = 0; i < selectedItems.size(); i++) 
        {
            if (item.name == get<0>(selectedItems[i]).name) 
            {
                item.sold += get<1>(selectedItems[i]);
            }
        }
    }
    
    // clear selected items and prepeare for next customer
    selectedItems.clear();
}

// reset machine to original state, clearing all items but keeping number and name
void VendingMachine::reset() 
{
    for (item &item : items) 
    {
        item.quantity = 0;
        item.sold = 0;
    }
}

// deselect items selected by user
void VendingMachine::deselect() 
{
    
    // display error if user tries to de-select with 0 selected items
    if (selectedItems.size() == 0) {
        cerr << displayError("Could not de-select any items. No items have been selected.");
        return;
    }

    // update vending machine item status
    string deselectInfo = "You de-selected\n";
    for (item &item : items) {
        for (int i = 0; i < selectedItems.size(); i++) 
        {
            
            // check for matching item
            int quantity = get<1>(selectedItems[i]);
            if (item.name == get<0>(selectedItems[i]).name) 
            {
                deselectInfo += "   " + displaySuccess(get<0>(selectedItems[i]).name + " (" + to_string(quantity) + ")");
                item.quantity += quantity;
            }
        }
    }
    
    
    // display de-selected items to user
    cout << deselectInfo << endl;
    selectedItems.clear(); // clear selected items
}


/////////////////////////////////////////////////////////////////////////







///////////////////// Non-class helper fuctions ////////////////////////


// clear cin buffer
void clearCin() 
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// displays error message in red color
string displayError(string message) 
{
    return "\033[1;31m" + message + "\033[0m\n";
}

// display a success action in green color
string displaySuccess(string message) 
{
    return "\033[1;32m" + message + "\033[0m\n";
}

// pretty print double values to 2 decimals
string prettyPrintDouble(double value) 
{
    stringstream stream;
    stream << fixed << setprecision(2) << value;
    return stream.str();
}


/////////////////////////////////////////////////////////////






// main class. Simulates a user using a machine
int main() 
{
    cout << "===== Welcome to CSUMB Vending Machine =====\n";
    
    VendingMachine machine1;
    cout << machine1.display();
    
    VendingMachine machine2(200, "Library"); 
    cout << machine2.display();
    
	cout << "\n===== Updated machine1 Info =====\n";
    machine1.setNumber(100);
    machine1.setName("BIT117");
    cout << machine1.display(); 

    cout << "\n===== machine1 Status (1) =====\n";
    machine1.status(); 
    
    machine1.refill(5, 7, 3, 10); // A machine’s admin can refill the items.
    cout << "\n===== machine1 Status (2) =====\n";
    machine1.status();
    
    cout << endl;
    machine1.displayMenu();
    cout << endl;
    
    machine1.selectItem();
    cout << "\n===== machine1 Payment (1) =====\n";
    
    if (machine1.payment())   // Pay with a debit card or cash.
    {
	    cout << "\n===== Receipt (1) =====\n";
	    machine1.displayReceipt();
	}
	
	else 
	{
	    // Note that if a user entered incorrect payment information,
	    // all selections should be deselected.
	    cout << displayError("Invalid payment. All selections are cancelled.") + "\n";
	}

    cout << "\n===== machine1 Status (3) =====\n";
    machine1.status();
    
    cout << endl;
    machine1.selectItem();
	
	cout << endl;
	machine1.deselect();  // A user can de-select items.
	
	cout << endl;
	machine1.selectItem();
	
	cout << "\n===== machine1 Payment (2) =====\n";
	if(machine1.payment())
	{
	    cout << "\n===== Receipt (2) =====\n";
	    machine1.displayReceipt();
	}
	
	else 
	{
	    cout << displayError("Invalid payment. All selections are cancelled.") + "\n";
	}
	
    cout << "\n===== machine1 Status (4) =====\n";
    machine1.status();

    machine1.reset();  // An admin resets the machine to the initial 
                       // status, except the ID and name of the machine.
    cout << "\n===== machine1 Status (5) =====\n";
    machine1.status();
    
    cout << "\n===== Thank you! =====\n";

    return 0;
}