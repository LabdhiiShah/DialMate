#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class contact {
private:
  string name;
  string phone;

public:
  contact() {}
  contact(string n, string p) {
    name = n;
    phone = p;
  }
  string getName() const { return name; }
  string getPhone() const { return phone; }
  void setName(string n) { name = n; }
  void setPhone(string p) { phone = p; }
  void displayContacts() const { cout << name << "\n " << phone << endl; }
};
class log {
private:
  vector<contact> contacts;
  int choice;

public:
  void menu();
  void addContact();
  void displayContact();
  void searchContact();
  void editContact();
  void deleteContact();
  void saveContact();
  void loadContact();
  void exitSystem();
};

void log::menu() {
  loadContact();
  while (true) {
    cout << "1.Add Contact\n2.Display Contact\n3.Search\n4.Edit "
            "Contact\n5.Delete "
            "Contact\n6.Exit"
         << endl;
    cout << "Choose an Option: ";
    cin >> choice;

    switch (choice) {
    case 1: {
      addContact();
      break;
    }
    case 2: {
      displayContact();
      break;
    }
    case 3: {
      searchContact();
      break;
    }
    case 4: {
      editContact();
      break;
    }
    case 5: {
      deleteContact();
      break;
    }
    case 6: {
      exitSystem();
      break;
    }
    default: {
      cout << "Invalid Choice!!" << endl;
      break;
    }
    }
  }
}

// perfecttttttttt
void log::addContact() {
  // system("cls");
  string name, phone;
  cout << "Enter Name: ";
  cin.ignore();
  getline(cin, name);

  string lower_name = name;
  transform(lower_name.begin(), lower_name.end(), lower_name.begin(),
            ::tolower);

  auto it = find_if(contacts.begin(), contacts.end(), [&](const contact &c) {
    string contactName = c.getName();
    transform(contactName.begin(), contactName.end(), contactName.begin(),
              ::tolower);
    return contactName == lower_name;
  });

  if (it != contacts.end()) {
    cout << "A Contact with the same name exists!!\n";
    return;
  }

  cout << "Enter Number: ";
  cin >> phone;
  if (phone.length() == 10) {
    contacts.push_back(contact(name, phone));
    cout << "Contact added Successfullyyy!!\n";
  } else {
    cout << "Invalid Length of phone number\n";
  }
}

void log::displayContact() {
  if (contacts.empty()) {
    cout << "No Contacts found!!" << endl;
    return;
  }

  sort(contacts.begin(), contacts.end(),
       [](const contact &a, const contact &b) {
         return a.getName() < b.getName(); // Sorts alphabetically
       });
  // system("cls");
  cout << "\n=========== CONTACT LIST ===========\n";
  for (const auto &c : contacts) {
    c.displayContacts();
  }
}

void log ::searchContact() {
  if (contacts.empty()) {
    cout << "No Contacts Found!!" << endl;
    return;
  }
  // system("cls");
  string query;
  cout << "Enter Name or Phone Number to Search: ";
  cin.ignore();
  getline(cin, query);

  transform(query.begin(), query.end(), query.begin(), ::tolower);

  bool found = false;

  for (const auto &c : contacts) {
    string contactName = c.getName();
    string contactPhone = c.getPhone();

    transform(contactName.begin(), contactName.end(), contactName.begin(),
              ::tolower);

    if (c.getName().find(query) != string::npos ||
        c.getPhone().find(query) != string::npos) {
      c.displayContacts();
      found = true;
    }
  }
  if (!found) {
    cout << "No Contacts Found!!" << endl;
  }
}

// hogayaaaaaaaa sara kuch
void log::editContact() {
  if (contacts.empty()) {
    cout << "No contacts to edit!\n";
    return;
  }
  string name, newName;
  cout << "Enter the name of the contact to edit: ";
  cin.ignore();
  getline(cin, name);

  string lowerName = name;
  transform(lowerName.begin(), lowerName.end(), lowerName.begin(),
            ::tolower); // convert to lowercase

  auto it = find_if(contacts.begin(), contacts.end(), [&](const contact &c) {
    string contactName = c.getName(); // finds entered name
    transform(contactName.begin(), contactName.end(),
              contactName.begin(), // converts into lowercase
              ::tolower);
    return contactName == lowerName;
  });

  if (it == contacts.end()) {
    cout << "Contact not found!\n";
    return;
  }

  int choice;
  cout << "1.Edit Name\n2.Edit Phone no.\nEnter your Choice: ";
  cin >> choice;

  if (choice == 1) {

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);
    string lowerNewName = newName;
    transform(lowerNewName.begin(), lowerNewName.end(), lowerNewName.begin(),
              ::tolower);

    auto duplicate =
        find_if(contacts.begin(), contacts.end(), [&](const contact &c) {
          string contactName = c.getName();
          transform(contactName.begin(), contactName.end(), contactName.begin(),
                    ::tolower);
          return contactName == lowerNewName;
        });
    // if (duplicate != contacts.end())  -> value not found
    // if (duplicate == contacts.end())  -> value found

    if (duplicate != contacts.end()) {
      cout << "A Contact with the same name exists!!\n";
      return;
    } else {
      it->setName(newName);
      cout << "Name Updated Successfullyy\n";
      return;
    }
  } else if (choice == 2) {
    string newPhone;
    cout << "Enter new phone number: ";
    cin >> newPhone;
    if (newPhone.length() == 10) {
      it->setPhone(newPhone);
      cout << "Phone number updated successfully!\n";
    } else {
      cout << "Invalid Length of Phone no.!!";
    }
  } else {
    cout << "Invalid choice!\n";
  }
}

// doneeeeeeeee
void log::deleteContact() {
  if (contacts.empty()) {
    cout << "No contacts available to delete!\n";
    return;
  }

  string name;
  cout << "Enter the name to be deleted: ";
  cin.ignore();
  getline(cin, name);

  transform(name.begin(), name.end(), name.begin(),
            ::tolower); // Converts entered name to lowercase

  auto it = find_if(contacts.begin(), contacts.end(),
                    [&](const contact &c) { // finds if entered name is present
                                            // in the contact list
                      string contactName = c.getName();

                      transform(contactName.begin(), contactName.end(),
                                contactName.begin(), ::tolower);
                      return contactName == name;
                    });

  if (it != contacts.end()) // If contact found
  {
    contacts.erase(it); // Remove the contact
    cout << "Contact deleted successfully!\n";
  } else {
    cout << "Contact not found!\n";
  }
}

void log::saveContact() {
  ofstream file("contacts.txt"); // Open the file in write mode
  if (!file) {
    cout << "Error while Saving Contacts!\n";
    return;
  }

  for (const auto &c : contacts) {
    file << c.getName() << "," << c.getPhone()
         << endl; // Writes the content in file
  }
  file.close();
  cout << "Contact Saved Successfully!!\n";
}

void log ::loadContact() {
  ifstream file("contacts.txt"); // Reads the data from file
  if (!file) {
    cout << "No Saved Contacts Found!!\n";
    return;
  }

  string name, phone;
  while (getline(file, name, ',') &&
         getline(file, phone)) { // Reads content from file and save in vector
    contacts.push_back(contact(name, phone));
  }
  file.close();
}

void log::exitSystem() {
  //system("cls");
  exit(0);
}

int main() {
  log obj1;
  obj1.menu();
  return 0;
}

//*case insensitive[]
//*repeated contact names []
//*no. of 10 digits []
//*ascending order[]
//*favourites
//*search[]
//*sub no.s
