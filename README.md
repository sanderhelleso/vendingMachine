# Project 1 for class CST238 Data Structrues - Vending Machine
<br>

## Project Description
In this project, you should develop a program named project1.cpp which include a class called VendingMachine. Note that the class simulates an imaginary vending machine on the CSUMB campus. 
A user can buy a bottle of water ($1.50), a bottle of coffee ($2.00), a chip ($1.00), and a chocolate bar ($2.50) from the machine. The user can select several item(s) if the items are available from the machine. Furthermore, the user can de-select item(s) that are already selected. 
After finishing the selection of item(s), the user can pay for the items with either a debit card (Valid PIN: 7777) or cash. A user can try to pay the item(s) only one time and if the user fails to pay due to the incorrect PIN or insufficient cash amount, the machine will de-select all sections the user chose. 
Note that an administrator of the machine can refill the machine or reset it to the initial status.
Read the following demo program and its sample run very carefully and identify data members and function members of the class to run the demo program.

## Demo Program: The following code presents a demo program that uses the VendingMachine class.

```
1.	int main()
2.	{
3.	    cout << "===== Welcome to CSUMB Vending Machine =====\n";
4.	
5.	    VendingMachine machine1;
6.	    cout << machine1.display();  // Display the ID and name of machine1.
7.	
8.	    VendingMachine machine2 (200, "Library"); 
9.	    cout << machine2.display();
10.	
11.	    cout << "\n===== Updated machine1 Info =====\n";
12.	    machine1.setNumber(100);
13.	    machine1.setName("BIT117");
14.	    cout << machine1.display(); 
15.	
16.	    cout << "\n===== machine1 Status (1) =====\n";
17.	    machine1.status();  // status() function displays current status of the machine.
18.	
19.	    machine1.refill(5, 7, 3, 10); // A machine’s admin can refill the items.
20.	
21.	    cout << "\n===== machine1 Status (2) =====\n";
22.	    machine1.status();
23.	
24.	    cout << endl;
25.	    machine1.displayMenu();
26.	
27.	    cout << endl;
28.	    machine1.selectItem();   // A user can select item(s).
29.	
30.	    cout << "\n===== machine1 Payment (1) =====\n";
31.	    if(machine1.payment() == true)   // Pay with a debit card or cash.
32.	    {
33.	        cout << "\n===== Receipt (1) =====\n";
34.	        machine1.displayReceipt();
35.	    }
36.	    else 
37.	    {
38.	        // Note that if a user entered incorrect payment information,
39.	        // all selections should be deselected.
40.	        cout << "Invalid payment. All selections are cancelled.\n";
41.	    }
42.	
43.	    cout << "\n===== machine1 Status (3) =====\n";
44.	    machine1.status();
45.	
46.	    cout << endl;
47.	    machine1.selectItem();
48.	
49.	    cout << endl;
50.	    machine1.deselect( );  // A user can de-select items.
51.	
52.	    cout << endl;
53.	    machine1.selectItem();
54.	
55.	    cout << "\n===== machine1 Payment (2) =====\n";
56.	    if(machine1.payment())
57.	    {
58.	        cout << "\n===== Receipt (2) =====\n";
59.	        machine1.displayReceipt();
60.	    }
61.	
62.	    cout << "\n===== machine1 Status (4) =====\n";
63.	    machine1.status();
64.	
65.	    machine1.reset();  // An admin resets the machine to the initial 
66.	                       // status, except the ID and name of the machine.
67.	    cout << "\n===== machine1 Status (5) =====\n";
68.	    machine1.status();
69.	
70.	    cout << "\n===== Thank you! =====\n";
71.	
72.	    return 0;
73.	}
```

## Sample Run of the Demo Program: The following presents a sample result of the demo program.
```
===== Welcome to CSUMB Vending Machine =====
Number: 0, Name: UNKNOWN
Number: 200, Name: Library

===== Updated machine 1 Info =====
Number: 100, Name: BIT117

===== machine1 Status (1) =====
Number: 100, Name: BIT117
Sold: Water: 0 / Regular Coffee: 0 / Sun Chip: 0 / Chocolate Bar: 0
Remaining: Water: 0 / Regular Coffee: 0 / Sun Chip: 0 / Chocolate Bar: 0
Total Earning: $0.00

===== machine1 Status (2) =====
Number: 100, Name: BIT117
Sold: Water: 0 / Regular Coffee: 0 / Sun Chip: 0 / Chocolate Bar: 0
Remaining: Water: 5 / Regular Coffee: 7 / Sun Chip: 3 / Chocolate Bar: 10
Total Earning: $0.00

===== Vending Machine Menu =====
1.	Water............$1.50
2.	Regular Coffee...$2.00
3.	Sun Chip.........$1.00
4.	Chocolate Bar....$2.50

Select Item: 2
How many do you want to buy? 2
You selected Regular Coffee (2)
Continue? (Y/N) Y

Select Item: 1
How many do you want to buy? 1
You selected Water (1)
Continue? (Y/N) N

===== machine1 Payment (1) =====
Payment Option – Debit(1) / Cash(2): 1
Enter PIN: 7777
Valid

===== Receipt (1) =====
Water: $1.50 X 1 = $1.50
Regular Coffee: $2.00 X 2 = $4.00
Subtotal: $5.50
Tax (10.0%): $0.55
Total: $6.05

===== machine1 Status (3) =====
Number: 100, Name: BIT117
Sold: Water: 1 / Regular Coffee: 2 / Sun Chip: 0 / Chocolate Bar: 0
Remaining: Water: 4 / Regular Coffee: 5 / Sun Chip: 3 / Chocolate Bar: 10
Total Earning: $6.05

Select Item: 1
How many do you want to buy? 3
You selected Water (3)
Continue? (Y/N) Y

Select Item: 3
How many do you want to buy? 5
You selected Sun Chip (5) – Sorry. We don’t have enough Sun Chip.
Continue? (Y/N) Y

Select Item: 4
How many do you want to buy? 5
You selected Chocolate Bar (5)
Continue? (Y/N) N

You de-selected 
    Water (3)
    Chocolate Bar (5)

Select Item: 4
How many do you want to buy? 9
You selected Chocolate Bar (9)
Continue? (Y/N) N

===== machine1 Payment (2) =====
Payment Option – Debit(1) / Cash(2): 2
Enter Money Amount: $30.85
Change: $6.10

===== Receipt (2) =====
Chocolate Bar: $2.50 X 9 = $22.50
Subtotal: $22.50
Tax (10.0%): $2.25
Total: $24.75

===== machine1 Status (4) =====
Number: 100, Name: BIT117
Sold: Water: 1 / Regular Coffee: 2 / Sun Chip: 0 / Chocolate Bar: 9
Remaining: Water: 4 / Regular Coffee: 5 / Sun Chip: 3 / Chocolate Bar: 1
Total Earning: $30.80

===== machine1 Status (5) =====
Number: 100, Name: BIT117
Sold: Water: 0 / Regular Coffee: 0 / Sun Chip: 0 / Chocolate Bar: 0
Remaining: Water: 0 / Regular Coffee: 0 / Sun Chip: 0 / Chocolate Bar: 0
Total Earning: $0.00

===== Thank you! =====
```

## When you develop the program, you should consider the following conditions:
<br>
<ul>
    <ol>When a user types the money amount for the cash payment, you can assume that the user always types the correct money amount. For example, the user types the dollar sign ‘$’ and then number such as 30.54. You don’t need to check the validity of the money amount such as $35.345 or $12.45.34.</ol>
    <ol>At the payment() function, if a user provides incorrect payment information such as an incorrect PIN or insufficient money amount, all selections the user chose should be de-selected.</ol>
    <ol>At the payment() function, if a user didn’t select any items before, the function should return false because there’s nothing to pay.</ol>
    <ol>If you have any further questions, please contact the instructor.</ol>
