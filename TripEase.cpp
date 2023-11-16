#include <iostream>
#include <string>
#include <unordered_map>
#include <ctime>
#include <iomanip>

using namespace std;

// Structures
struct User {
    int id;
    string name;
    int age;
    char gender;
    string phoneNumber;
    float billAmount = 0.0;
};

struct BookingDate {
    int day;
    int month;
    int year;
};

struct Node {
    User data;
    Node* next;
};

struct Hotel {
    string name;
    int pricePerRoom;
    int availableRooms;
};

struct Cab {
    string route;
    int price;
    int availableCabs;
};

// Global variables
unordered_map<string, Cab> cabRoutes;
Node* head = NULL;
BookingDate globalBookingDate;

// Function declarations
void initializeCabRoutes();
void welcomeMessage();
BookingDate promptForBookingDate();
Node* registerUser(Node* head);
void hotelBooking(Node* head);
void cabBooking(Node* head);
void billGeneration(Node* head);
Node* findUser(Node* head, int id);
void displayHotels(Hotel hotels[]);
Hotel* selectHotel(Hotel hotels[]);
void exitMessage();

int main() {
    int choice;

    welcomeMessage();
    initializeCabRoutes();
    globalBookingDate = promptForBookingDate();

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. User Registration\n";
        cout << "2. Hotel Booking\n";
        cout << "3. Cab Booking\n";
        cout << "4. Bill Generation\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: head = registerUser(head); break;
            case 2: hotelBooking(head); break;
            case 3: cabBooking(head); break;
            case 4: billGeneration(head); break;
            case 5: exitMessage(); return 0;
            default: cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}

void welcomeMessage() {
    cout << "*************************************\n";
    cout << "*         Welcome to TripEase       *\n";
    cout << "*************************************\n";
}

BookingDate promptForBookingDate() {
    BookingDate date;
    cout << "Please enter your booking date (dd mm yyyy): ";
    cin >> date.day >> date.month >> date.year;
    return date;
}

void initializeCabRoutes() {
    cabRoutes["Hotel to India Gate"] = {"Hotel to India Gate", 300, 5, };
    cabRoutes["Hotel to Lotus Temple"] = {"Hotel to Lotus Temple", 350, 7, };
    cabRoutes["Hotel to Akshardham Temple"] = {"Hotel to Akshardham Temple", 200, 6, };
    cabRoutes["Hotel to CyberCity"] = {"Hotel to CyberCity", 500, 4,};
    cabRoutes["Hotel to Hauz Khas"] = {"Hotel to Hauz Khas", 450, 3,};
    cabRoutes["Hotel to Qutub Minar"] = {"Hotel to Qutub Minar", 370, 6,};
    cabRoutes["Hotel to Taj Mahal"] = {"Hotel to Taj Mahal", 3000, 5,};
    cabRoutes["Hotel to Mathura-Vrindavan"] = {"Hotel to Mathura-Vrindavan", 2800, 4,};
    cabRoutes["Hotel to Humayun's Tomb"] = {"Hotel to Humayun's Tomb", 250, 3,};
    cabRoutes["Hotel to Lodhi Garden"] = {"Hotel to Lodhi Garden", 225, 7,};
    cabRoutes["Hotel to Agarasen ki Baowli"] = {"Hotel to Agarasen ki Baowli", 235, 5,};
    cabRoutes["Hotel to Bennett University"] = {"Hotel to Bennett University", 940, 6,};
}

Node* registerUser(Node* head) {
    User newUser;
    static int userID = 1;

    cout << "\nUser Registration:\n";
    cout << "--------------------\n";
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newUser.name);
    cout << "Enter Age: ";
    cin >> newUser.age;
    cout << "Enter Gender (M/F): ";
    cin >> newUser.gender;
    cout << "Enter Phone Number: ";
    cin >> newUser.phoneNumber;

    newUser.id = userID++;

    Node* newNode = new Node;
    newNode->data = newUser;
    newNode->next = NULL;

    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    cout << "\nUser registered successfully!\n";
    cout << "Your User ID is: " << newNode->data.id << "\n";
    return head;
}

void hotelBooking(Node* head) {
    cout << "\nHotel Booking:\n";
    cout << "----------------\n";
    int userId;
    cout << "Enter User ID: ";
    cin >> userId;

    Node* user = findUser(head, userId);
    if (!user) {
        cout << "User not found. Please register first.\n";
        return;
    }

    cout << "Select City (1. Delhi, 2. Mumbai, 3. Chennai, 4. Kolkata): ";
    int choice;
    cin >> choice;

    Hotel hotels[3];
    switch (choice) {
        case 1:
            hotels[0] = {"Delhi Taj ", 5000, 10};
            hotels[1] = {"Delhi Oberoi Amarvilas", 6000, 8};
            hotels[2] = {"Delhi JW Marriot", 4500, 7};
            break;
        case 2:
            hotels[0] = {"Mumbai Taj ", 5500, 9};
            hotels[1] = {"Mumbai Oberoi Amarvilas", 6500, 8};
            hotels[2] = {"Mumbai JW Marriot", 4900, 7};
            break;
        case 3:
            hotels[0] = {"Chennai Taj ", 5200, 10};
            hotels[1] = {"Chennai Oberoi Amarvilas", 6200, 6};
            hotels[2] = {"Chennai JW Marriot", 4600, 8};
            break;
        case 4:
            hotels[0] = {"Kolkata Taj ", 5300, 7};
            hotels[1] = {"Kolkata Oberoi Amarvilas", 6300, 6};
            hotels[2] = {"Kolkata JW Marriot", 4700, 9};
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }

    displayHotels(hotels);

    Hotel* selectedHotel = selectHotel(hotels);
    if (!selectedHotel) {
        cout << "Invalid choice!\n";
        return;
    }

    cout << "Enter number of rooms to book: ";
    int numOfRooms;
    cin >> numOfRooms;

    if (numOfRooms > selectedHotel->availableRooms) {
        cout << "Not enough rooms available!\n";
        return;
    }

    user->data.billAmount += numOfRooms * selectedHotel->pricePerRoom;
    cout << "\nHotel booked successfully!\n";
    cout << "You booked " << numOfRooms << " rooms in " << selectedHotel->name << "\n";
}

void displayHotels(Hotel hotels[]) {
    cout << "\nAvailable Hotels:\n";
    cout << "--------------------\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". " << hotels[i].name << " - Price per room: " << hotels[i].pricePerRoom << " - Available rooms: " << hotels[i].availableRooms << "\n";
    }
}

Hotel* selectHotel(Hotel hotels[]) {
    cout << "\nSelect hotel by entering its number: ";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= 3) {
        return &hotels[choice - 1];
    }
    return NULL;
}

void cabBooking(Node* head) {
    cout << "\nCab Booking:\n";
    cout << "--------------\n";

    int userId;
    cout << "Enter User ID: ";
    cin >> userId;

    Node* user = findUser(head, userId);
    if (!user) {
        cout << "User not found. Please register first.\n";
        return;
    }

    cout << "\nAvailable Cab Routes:\n";
    cout << "----------------------\n";
    int i = 1;
    for (auto& route : cabRoutes) {
        cout << i++ << ". " << route.first << " - Price: " << route.second.price << "\n";
    }

    cout << "\nSelect Cab-Route by entering its number: ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > cabRoutes.size()) {
        cout << "Invalid choice!\n";
        return;
    }

    i = 1;
    Cab* selectedCab = NULL;
    for (auto& route : cabRoutes) {
        if (i++ == choice) {
            selectedCab = &route.second;
            break;
        }
    }

    if (selectedCab->availableCabs <= 0) {
        cout << "Sorry, no cabs available for this route!\n";
        return;
    }

    selectedCab->availableCabs--;
    user->data.billAmount += selectedCab->price;
    cout << "\nCab booked successfully for route: " << selectedCab->route << "\n";
}

void billGeneration(Node* head) {
    int userId;
    const float TAX_RATE = 0.10;
    const float SERVICE_CHARGE_RATE = 0.05;
    
    cout << "\nBill Generation:\n";
    cout << "-----------------\n";
    cout << "Enter User ID: ";
    cin >> userId;

    Node* user = findUser(head, userId);
    if (!user) {
        cout << "User not found.\n";
        return;
    }

    cout << "\n-------------------BILL-------------------\n";
    cout << "-------------User Details-----------------\n";
    cout << "Name: " << user->data.name << "\n";
    cout << "Age: " << user->data.age << "\n";
    cout << "Gender: " << user->data.gender << "\n";
    cout << "Phone Number: " << user->data.phoneNumber << "\n";
    cout << "Booking Date: " << globalBookingDate.day << "-" << globalBookingDate.month << "-" << globalBookingDate.year << "\n";

    cout << "\n-------------Billing Details--------------\n";
    float baseAmount = user->data.billAmount;
    float taxAmount = baseAmount * TAX_RATE;
    float serviceCharge = baseAmount * SERVICE_CHARGE_RATE;
    float totalAmount = baseAmount + taxAmount + serviceCharge;

    cout << fixed << setprecision(2);  // Display amount in a fixed decimal format with 2 decimal places
    cout << "Base Amount: Rs. " << baseAmount << "\n";
    cout << "Tax (" << TAX_RATE * 100 << "%): Rs. " << taxAmount << "\n";
    cout << "Service Charge (" << SERVICE_CHARGE_RATE * 100 << "%): Rs. " << serviceCharge << "\n";
    cout << "-----------------------------------------\n";
    cout << "Net Payable Amount: Rs. " << totalAmount << "\n";
    cout << "-----------------------------------------\n";
    cout << "Thank you for using our services!\n";
}

Node* findUser(Node* head, int id) {
    Node* temp = head;
    while (temp) {
        if (temp->data.id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void exitMessage() {
    cout << "Thank you for using the Travel Management System. Have a safe journey!\n";
}
