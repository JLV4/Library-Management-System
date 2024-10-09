/**------------------------------------------
    Program 1: Library Management System Project
    Description: This program serves a library management system which includes but is not limited to: the deletion, addition, searching, and display of books within the library. 
    Year: Sophomore
    Course: CS 251, Fall 2023.
    System: VS Code on MacOS 13.51 Ventura
    Author: Justin Vaughn
 ---------------------------------------------**/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

//Initial declaration for all the functions used directly in main()
void printMenu();
string statStr(string num);
void addEntry(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3);
void removeEntry(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3);
void outputLibrary(string fileName, vector<string> vct1, vector<string> vct2, vector<string> vct3);
void searchLibrary(vector<string> vct1, vector<string> vct2, vector<string> vct3);
void printInvalidEntries(vector<string> vct1, vector<string> vct2, vector<string> vct3);
void displayEntries(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3);
void loadLibrary(string fileName, vector<string> &vct1, vector<string> &vct2, vector<string> &vct3);
void clearLibrary(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3);
void checkoutOutStatus (vector<string> vct);

// Main Function
int main()
{
   //container declarations
    vector<string> titles;
    vector<string> ISBNs;
    vector<string> statuses;
    string command;


    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {
        printMenu();
        cout << endl << "Enter a command (case does not matter): \n";
        getline(cin, command);

        //block of code that interprets the user input and performs what is desired
        if (command == "A" || command == "a") {
          addEntry(titles, ISBNs, statuses);
        }
        else if (command == "C" || command == "c") {
          clearLibrary(titles, ISBNs, statuses);
        }
        else if (command == "D" || command == "d") {
          if (titles.size() != 0) {
            displayEntries(titles, ISBNs, statuses);
          }
          else {
            cout << "Your Current Library" << endl;
            cout << "--------------------" << endl;
            cout << "The library has no books\n";
          }
        }
        else if (command == "I" || command == "i") {
          printInvalidEntries(titles, ISBNs, statuses);
        }
        else if (command == "L" || command == "l") {
          string fileName;
          cout << "What database to read from? \n";
          getline(cin, fileName);
          loadLibrary(fileName, titles, ISBNs, statuses);
        }
        else if (command == "O" || command == "o") {
          string outputFile;
          getline(cin, outputFile);
          outputLibrary(outputFile, titles, ISBNs, statuses);
        }
        else if (command == "P" || command == "p") {
          checkoutOutStatus(statuses);
        }
        else if (command == "R" || command == "r") {
          removeEntry(titles, ISBNs, statuses);
        } 
        else if (command == "S" || command == "s") {
          searchLibrary(titles, ISBNs, statuses);
        }
        else if ((command == "x" || command == "X")){
          continue;
        }
        else {
          cout << "Unknown command\n";
        }
        cout << endl;
    } while (!(command == "x" || command == "X"));

    return 0;
}

//This function prints the menu out to the user
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

//This helper function return a string based on the checkout status of a given book in the library
string statStr(string num) {
  string currentStatus;
  switch (stoi(num)) {
    case 0:
      currentStatus = "In Library";
      break;
    case 1:
      currentStatus = "Checked Out";
      break;
    case 2:
      currentStatus = "On Loan";
      break;
    case 3:
      currentStatus = "Unknown State";
      break;
    default:
      currentStatus = "Invalid State";
  }
  return currentStatus;
}

//This function's purpose is to add an entry into library via appending to the three vectors representing the library's info
void addEntry(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  string title;
  string ISBN;
  cout << "What is the book title? \n";
  getline(cin, title);
  if (title.find(",") == string::npos) {
    cout << "What is the 13-digit ISBN (with hyphens)? \n";
    getline(cin, ISBN);
    vct1.push_back(title);
    vct2.push_back(ISBN);
    vct3.push_back("0");
    cout << "The Following Entry Was Added\n-----------------------------" << endl;
    cout << vct1.at(vct1.size() - 1) << " --- " << vct2.at(vct2.size() - 1) << " --- " << statStr(vct3.at(vct3.size() - 1)) << endl;
  }
  else {
    cout << "The book title cannot contain commas." << endl;
  }
}

//This helper function's purpose is to search through the vectors representing the library and delete the book if it's found while also printing the deleted book to the terminal
void deleteBook(string deleteItem, vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  bool found = false;
  cout << "The Following Entry Was Removed From The Library" << endl;
  cout << "------------------------------------------------" << endl;
  for (int i = vct1.size() - 1; i >= 0; i--) {
    if ((deleteItem == vct2.at(i)) || (deleteItem == vct1.at(i))) {
      cout << vct1.at(i) << " --- " << vct2.at(i) << " --- " << statStr(vct3.at(i)) << endl;
      vct1.erase(vct1.begin() + i);
      vct2.erase(vct2.begin() + i);
      vct3.erase(vct3.begin() + i);
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "No matching entry found in the library." << endl;
  }
}

//This helper function loops through the vectors of ISBNs and book titles and in order to find the book the user wants to and then outputs that book to the terminal
void searchForBook(string searchItem, vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  bool found = false;
  cout << "The Following Are Your Search Results" << endl;
  cout << "-------------------------------------" << endl;
  for (int i = vct1.size() - 1; i >= 0; i--) {
    if (searchItem == vct2.at(i) || searchItem == vct1.at(i)) {
      cout << vct1.at(i) << " --- " << vct2.at(i) << " --- " << statStr(vct3.at(i)) << endl;
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "No matching entry found in the library." << endl;
  }
}

//This function uses the delete book helper function to remove a library entry of the user's choices. It accepts either a ISBN or title and tells the user if their choice is invlaid or not
void removeEntry(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  string deleteItem;
  string choice;
  cout << "Would you like remove by (1) name or (2) ISBN." << endl;
  cout << "Enter the numeric choice: " << endl;
  getline(cin, choice);
  if (choice == "1") {
    cout << "Enter the book name: " << endl;
    getline(cin, deleteItem);
    deleteBook(deleteItem, vct1, vct2, vct3);
  }
  else if (choice == "2") {
    cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
    getline(cin, deleteItem);
    deleteBook(deleteItem, vct1, vct2, vct3);
  }
  else {
    cout << "Invalid remove by choice option." << endl;
  }
}

//This function displays the library's contents to the user bu utilizing the three vectors declared earlier
void displayEntries(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  cout << "Your Current Library\n--------------------" << endl;
  for (int i = 0; i < vct1.size(); i++) {
    cout << vct1.at(i) << " --- " << vct2.at(i) << " --- " << statStr(vct3.at(i)) << endl;
  }
}

//This function prompts the user for a search terms and uses the searchForBook() helper function. It may either be an ISBN or the book's title used as the input
void searchLibrary(vector<string> vct1, vector<string> vct2, vector<string> vct3) {
  string searchTerm;
  string choice;
  cout << "Would you like to search by (1) name or (2) ISBN." << endl;
  cout << "Enter the numeric choice: " << endl;
  getline(cin, choice);
  if (choice == "1") {
    cout << "Enter the book name: " << endl;
    getline(cin, searchTerm);
    searchForBook(searchTerm, vct1, vct2, vct3);
  }
  else if (choice == "2") {
    cout << "Enter the book 13-digit ISBN (with dashes): " << endl;
    getline(cin, searchTerm);
    searchForBook(searchTerm, vct1, vct2, vct3);
  }
  else {
      cout << "Invalid search by choice option." << endl;
  }
}

//This function clears the library by erasing all contents in the three vectors and reporting back to the user
void clearLibrary(vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  vct1.clear();
  vct2.clear();
  vct3.clear();
  cout << "Your library is now empty." << endl;
}

//This function is a helper function utilized by the loadlibrary() function. It's purpose is to assist with processing each line in a given file in order to seperate the info as needed for placement into one of 3 vectors
void processLine(string textLine, vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  string title = textLine;
  string ISBN = "000-0-00-000000-0";
  string status = "0";
  string newISBN;
  unsigned int count = 0;
  unsigned int idx1;
  unsigned int idx2;
  //block of code loops/searches through textLine string in order to find commas and make sub-strings where appropiate
  while (textLine.find(",") != string::npos) {
    if (count == 0) {
      idx1 = textLine.find(",");
      textLine.at(idx1) = '0';
      title = textLine.substr(0, idx1);
      ISBN = textLine.substr(idx1 + 1, textLine.size() - (idx1 + 1));
      count++;
    }
    else if (count == 1) {
      idx2 = textLine.find(",");
      ISBN = textLine.substr(idx1 + 1, (idx2 - idx1) - 1);
      textLine.at(idx2) = '0';
      status = textLine.at(textLine.size() - 1);
    }
  }
//loop for getting rid of unnecessary spaces
  for (auto chr : ISBN) {
    if (!isspace(chr)) {
      newISBN += chr;
    }
  }
  vct1.push_back(title);
  vct2.push_back(newISBN);
  vct3.push_back(status);
}

//This function loads the library by reading the file and uses the processLine helper function. 
void loadLibrary(string fileName, vector<string> &vct1, vector<string> &vct2, vector<string> &vct3) {
  string textLine;
  ifstream myFile;
  int count = 0;
  myFile.open(fileName);
  //this block of code checks of the file opened successfully and if so and then calls the processLIne() function
  if (myFile.is_open()) {
    while (!myFile.eof()) {
      getline(myFile, textLine);
      processLine(textLine, vct1, vct2, vct3);
      count++;
    }
    cout << "Read in " << count << " lines from the file.\n";
  }
  else {
    cout << "Could not find the database file" << endl;
  }
  myFile.close();
}

//This helper function returns an int that represents the count of each status (i.e -> "In Library", "Checked out", etc.)
int eachStatusCount (string matchNum, vector<string> vct) {
  int count = 0;
  for (auto num : vct) {
    if (matchNum == num) {
      count++;
    }
  }
  return count;
}

//This helper function specfically returns the number of invalid state books within the library
int invalidCount (vector<string> vct) {
  int otherCount = 0;
  for (auto str_num : vct) {
    if (stoi(str_num) > 3) {
      otherCount++;
    }
  }
  return otherCount;
}

//By using the previously mentioned helper functions (invalidCount() and eachStatusCount()), this function outputs the checkout status of all the library's books to the user
void checkoutOutStatus (vector<string> vct) {
  cout << "Your current Library's Stats\n----------------------------" << endl;
  cout << "Total Books: " << vct.size() << endl;
  cout << "  In Library: " << eachStatusCount("0", vct) << endl;
  cout << "  Checked Out: " << eachStatusCount("1", vct) << endl;
  cout << "  On Loan: " << eachStatusCount("2", vct) << endl;
  cout << "  Unknown: " << eachStatusCount("3", vct) << endl;
  cout << "  Other: " << invalidCount(vct) << endl;
}

//This helper function uses an algortitm to determine wheter or not the ISBN of a book is valid or invalid. It returns an int representing the check digit value
int checkDigitAlgoritm (int idx, vector<string> vct) {
  string partOfISBN = (vct.at(idx)).substr(0, vct.at(idx).size() - 1);
  bool val = true;
  string chr2;
  int checkDigitVal = 0;
  for (char chr : partOfISBN) {
    chr2 = "";
    chr2 += chr;
    if (isdigit(chr)) {
      if (val) {
        checkDigitVal += stoi(chr2);
        val = false;
      }
      else {
        checkDigitVal += ((stoi(chr2)) * 3);
        val = true;
      }
    }
  }
  if (checkDigitVal == 0) {
    return 0;
  }
  else {
    checkDigitVal %= 10;
    return (10 - checkDigitVal);
  }
}

//This prints the invalid entries in the library out to the user by using the checkDigitAlgorthim() mentioned previosuly as well as checking the checkout status of the books in the library
void printInvalidEntries (vector<string> vct1, vector<string> vct2, vector<string> vct3) {
  string matchVal;
  int count = 0;
  int checkDigit;
  cout << "The Following Library Entries Have Invalid Data\n";
  cout << "-----------------------------------------------\n";
  for (int i = 0; i < vct1.size(); i++) {
    matchVal = (vct2.at(i)).at(vct2.at(i).size() - 1);
    checkDigit = checkDigitAlgoritm(i, vct2);
    if ((stoi(vct3.at(i)) > 3) || (checkDigit != stoi(matchVal))) {
      cout << vct1.at(i) << " --- " << vct2.at(i) << " --- " << statStr(vct3.at(i)) << endl;
      count++;
    }
  }
  if (vct1.size() == 0) {
      cout << "The library has no books." << endl;
  }
  else if (count == 0) {
      cout << "The library has no invalid entries." << endl;
  }
}

//This function creates a new file and outputs the book titles, ISBNs, and checkout statuses on each line in a formatted fashion
void outputLibrary(string fileName, vector<string> vct1, vector<string> vct2, vector<string> vct3) {
  ofstream newFile;
  newFile.open(fileName);
  //loops for writing each line to the file
  for (int i = 0; i < vct1.size(); i++) {
    newFile << vct1.at(i) << ", " << vct2.at(i) << ", " << vct3.at(i) << endl;
  }
  newFile.close();
} 
