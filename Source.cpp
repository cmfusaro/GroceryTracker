#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;



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
	PyObject* my_module = PyImport_ImportModule("PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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
	pName = PyUnicode_FromString((char*)"PythonCode");
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

// Function to accept user input and validate that it is of type int 
int ValidateInt() {
	int num = 0;
	cin.exceptions(ios::failbit);
	while (true) {
		try {
			cin >> num;
		}
		catch (ios_base::failure except) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Please enter an integer." << endl;
			continue;

		}
		break;
	}
	return num;
}

// Function to accept user input and validate that it is of type string
string ValidateStr() {
	string str = " ";
	cin.exceptions(ios::failbit);
	while (true) {
		try {
			cin >> str;
		}
		catch (ios_base::failure except) {
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Please enter a string." << endl;
			continue;

		}
		break;
	}
	return str;
}



void menu() {
	int value = NULL;
	int selection = 0;
	string userinput = " ";
	cout << "1: List of all items purchased" << endl;
	cout << "2: Calculate how many times a specific item was purchased" << endl;
	cout << "3: Display histogram listing all items purchased" << endl;
	cout << "4: Exit" << endl;
	cout << "Enter your selection as a number 1, 2,3, or 4" << endl;
	// Python procedure call to prepare data for all cases
	// Reads input file and parses data and adds to frequency.dat
	// All cases read from frequecy.dat
	CallProcedure("prepare_sales_data");
	// Get and validate userinput as Integer
	selection = ValidateInt();
	switch (selection) {
	case 1:
		// Call python function to list all items and totals for each
		CallProcedure("list_all_items");
		// Recall Menu
		menu();
		break; // Left in out of convention never reached due to menu recall is blocking
	case 2:
		// Get and validate userinput as String
		userinput = ValidateStr();
		// Call python function to find how many of a specific item are sold
		value = callIntFunc("total_specific_item", userinput);
		cout << "Total sales of " << userinput << ": \n" << endl;
		cout << userinput << "  " << value << endl;;
		cout << endl;
		// Recall Menu
		menu();
		break;
	case 3:
		//
		CallProcedure("display_histogram");
		cout << endl;
		menu();
		break;
	case 4:
		cout << "Goodbye!" << endl;
		// Terminate program
		exit(0);
		break;
	}
}



int main()
{
	menu();
	return 0;
}
