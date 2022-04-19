/*
*Zach Behrensmeyer
* CS210 Grocery Tracker Assignment
* This application will take user input in C++ then send it to be handled by python code.
* It will call python code to Display a list of grocery items and the count sold
* It will call python code to Display a single given item and its count sold
* It will call python code to Display a histogram of data
* It makes use of preprovided code by SNHU to call python
*/

//Necessary includes
#include <Python.h>
#include <iostream>
#include <iomanip>
#define NOMINMAX
#include <algorithm>
#include <Windows.h>
#include <fstream>

using namespace std;

// *** PROVIDED CODE START *** \\

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("ShoppingLogic");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"ShoppingLogic");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"ShoppingLogic");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

// *** PROVIDED CODE END *** \\

//This method handles menu logic, it also handles the logic to display users desired output
void DisplayMenu() {

	//Value for what the user wants to do
	int mainSelection = 0;

	while (mainSelection != 4) {

		string itemName;
		string fileLine;
		int result;
		ifstream outputFile;
		int itemQuantity = 0;
		
		//Main menu to display user options
		cout << "PLEASE SELECT AN OPTION:" << endl;
		cout << "1: Display a list of all items sold and quantities" << endl;
		cout << "2: Display the number of times an item was sold" << endl;
		cout << "3: Display a histogram with all the sales data for the day" << endl;
		cout << "4: Exit" << endl;
		cout << "Please Enter a number: 1, 2, 3, or 4." << endl;

		cin >> mainSelection;

		//Will display different logic based on user input
		switch (mainSelection) {
			//display list of all items sold and count
		case 1:

			//Clear the console window
			system("CLS");			

			//Call Python method to display list of all items sold and count
			CallProcedure("DisplayListOfItems");			
			break;

			//Display single item sold
		case 2:

			system("CLS");

			//Prompt for item name to send to python
			cout << "Enter the name of the item you want to see: " << endl;
			cin >> itemName;						
			cout << endl;

			// Display result from python
			result = callIntFunc("GetNumberSoldOfSingleItem", itemName);

			if (result != 0) {
				cout << result << " " << itemName << " sold." << endl;
			}
			else {
				cout << "Item not found,  NOTE *** Words must be capitalized" << endl;
			}			

			cout << endl;

			break;

			//Display histrogram of sales data
		case 3:															
			system("CLS");           

			//Writes histogram data to frequency.dat file as per request on this assignment
			CallProcedure("WriteGroceryDataToFile");           

			//Open the file we just wrote to in Python
			outputFile.open("frequency.dat");

			//assign line data to variables
			outputFile >> itemName;
			outputFile >> itemQuantity;
			
			while (!outputFile.fail()) {
								
				//General formatting, makes it easier to read the histogram
				//Color does not need changed, it reads well in my terminal
				cout << setw(12) << left << itemName << setw(10);			
				
				//For the count of the grocery item print a pound symbol
				for (int i = 0; i < itemQuantity; i++) {
					
					//Right justify for easier reading
					cout << right << "#";
				}

				cout << endl;

				//Sets up variables for next iteration of the while loop.
				outputFile >> itemName;
				outputFile >> itemQuantity;
			}
			cout << endl;
			
			//Close input file
			outputFile.close();			
			break;

			//Quit
		case 4:
			mainSelection = 4;
			break;
		default:
			// If user does not enter a valid menu option, they are sent back to the menu
			cin.clear();
			cin.ignore(numeric_limits <streamsize>::max(), '\n');
			cout << endl << "Please enter 1, 2, 3, or 4: " << endl;
			break;
		}
	}
}

//Main method calls for mainmenu to be displayed
int main()
{
	//Displays menu and takes user input for actions desired by user
	DisplayMenu();

	return 0;
}