#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_COURIERS = 100;

struct Date {
    int day;
    int month;
    int year;
};

bool validateDate(const Date& date, const Date& today) {
    if (date.year < 2024) {
        cout << "Error: Year should be 2024 or later.\n";
        return false;
    }
    if (date.month < 1 || date.month > 12) {
        cout << "Error: Invalid month. Please enter a valid month (1-12).\n";
        return false;
    }
    if (date.day < 1 || date.day > 31) {
        cout << "Error: Invalid day. Please enter a valid day (1-31).\n";
        return false;
    }

    if (date.month == 2) {
        bool leapYear = (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0);
        int maxDays = leapYear ? 29 : 28;
        if (date.day > maxDays) {
            cout << "Error: Invalid day for February in the given year.\n";
            return false;
        }
    } else if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        if (date.day > 30) {
            cout << "Error: Invalid day. This month has only 30 days.\n";
            return false;
        }
    }
    
    // Date comparison logic
    if (date.year < today.year ||
        (date.year == today.year && date.month < today.month) ||
        (date.year == today.year && date.month == today.month && date.day < today.day)) {
        cout << "Error: Delivery date cannot be before today's date.\n";
        return false;
    }

    return true;  // Valid date
}

class Courier {
protected:
    static int id_counter;
    int id;
    string recipientName;
    string status;
    double weight;
    double distance;
    double cost;
    Date deliveryDate;

public:
    Courier(const string& name, double weightVal, double distanceVal, double costVal, const Date& date)
        : recipientName(name), weight(weightVal), distance(distanceVal), cost(costVal), deliveryDate(date), status("Collected") {
        id = ++id_counter;
    }

    virtual void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    virtual void displayDetails() const {
        cout << "\nID: " << id << ", Recipient: " << recipientName
             << ", Status: " << status
             << ", Weight: " << weight << " kg"
             << ", Distance: " << distance << " km"
             << ", Cost: $" << cost
             << ", Delivery Date: " << deliveryDate.day << "/" << deliveryDate.month << "/" << deliveryDate.year << "\n";
    }

    int getId() const {
        return id;
    }
};

int Courier::id_counter = 0;

class ExpressCourier : public Courier {
private:
    double expressCharge;

public:
    ExpressCourier(const string& name, double weightVal, double distanceVal, double costVal, const Date& date)
        : Courier(name, weightVal, distanceVal, costVal, date) {
        expressCharge = 15.0;
        cost += expressCharge;
    }

    void displayDetails() const override {
        cout << "[Express Delivery] ID: " << id << ", Recipient: " << recipientName
             << ", Status: " << status
             << ", Weight: " << weight << " kg"
             << ", Distance: " << distance << " km"
             << ", Cost: $" << cost << " (includes express charge of $" << expressCharge << ")"
             << ", Delivery Date: " << deliveryDate.day << "/" << deliveryDate.month << "/" << deliveryDate.year << "\n";
    }
};

class CourierManagement {
private:
    Courier* couriers[MAX_COURIERS];
    ExpressCourier* expressCouriers[MAX_COURIERS];
    int courierCount = 0;
    int expressCourierCount = 0;

    double calculateCost(double weight, double distance) {
        return weight * 0.5 + distance * 0.2;
    }

public:
    void addCourier(const string& name, double weight, double distance, const Date& deliveryDate) {
        if (courierCount < MAX_COURIERS) {
            double cost = calculateCost(weight, distance);
            couriers[courierCount++] = new Courier(name, weight, distance, cost, deliveryDate);
            cout << "Courier added successfully!\n";
        } else {
            cout << "Cannot add more couriers. Limit reached.\n";
        }
    }

    void addExpressCourier(const string& name, double weight, double distance, const Date& deliveryDate) {
        if (expressCourierCount < MAX_COURIERS) {
            double cost = calculateCost(weight, distance);
            expressCouriers[expressCourierCount++] = new ExpressCourier(name, weight, distance, cost, deliveryDate);
            cout << "Express Courier added successfully!\n";
        } else {
            cout << "Cannot add more express couriers. Limit reached.\n";
        }
    }

    void listCouriers() const {
        if (courierCount == 0 && expressCourierCount == 0) {
            cout << "No couriers found.\n";
        } else {
            cout << "\n--- List of Couriers ---\n";
            for (int i = 0; i < courierCount; ++i) {
                couriers[i]->displayDetails();
            }
            for (int i = 0; i < expressCourierCount; ++i) {
                expressCouriers[i]->displayDetails();
            }
        }
    }

    void updateCourierStatus(int id, const string& newStatus) {
        for (int i = 0; i < courierCount; ++i) {
            if (couriers[i]->getId() == id) {
                couriers[i]->updateStatus(newStatus);
                cout << "Courier status updated successfully!\n";
                return;
            }
        }
        for (int i = 0; i < expressCourierCount; ++i) {
            if (expressCouriers[i]->getId() == id) {
                expressCouriers[i]->updateStatus(newStatus);
                cout << "Express courier status updated successfully!\n";
                return;
            }
        }
        cout << "Courier not found!\n";
    }

    void deleteCourier(int id) {
        for (int i = 0; i < courierCount; ++i) {
            if (couriers[i]->getId() == id) {
                delete couriers[i];
                couriers[i] = couriers[--courierCount];
                cout << "Courier deleted successfully!\n";
                return;
            }
        }
        for (int i = 0; i < expressCourierCount; ++i) {
            if (expressCouriers[i]->getId() == id) {
                delete expressCouriers[i];
                expressCouriers[i] = expressCouriers[--expressCourierCount];
                cout << "Express courier deleted successfully!\n";
                return;
            }
        }
        cout << "Courier not found!\n";
    }
};

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <day> <month> <year>\n";
        return 1;
    }

    CourierManagement cm;
    int choice;

    Date today;
    today.day = stoi(argv[1]);  
    today.month = stoi(argv[2]); 
    today.year = stoi(argv[3]);   

    do {
        cout << "\n--- Courier Management System ---\n";
        cout << "1. Add Regular Courier\n";
        cout << "2. Add Express Courier\n";
        cout << "3. List Couriers\n";
        cout << "4. Update Courier Status\n";
        cout << "5. Delete Courier\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            double weight, distance;
            Date deliveryDate;

            while (true) {
                cout << "Enter Recipient Name: ";
                cin.ignore();
                getline(cin, name);
                if (name.find_first_of("0123456789") == string::npos) {
                    break;
                }
                cout << "Error: Recipient name cannot contain numbers.\n";
            }

            while (true) {
                cout << "Enter Weight of package (kg): ";
                cin >> weight;
                if (cin.fail() || weight <= 0 || weight > 20) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid weight (under 20 kg).\n";
                } else {
                    break;
                }
            }

            while (true) {
                cout << "Enter Distance (km): ";
                cin >> distance;
                if (cin.fail() || distance <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for distance.\n";
                } else {
                    break;
                }
            }

            cout << "Enter Delivery Date (dd mm yyyy): ";
            cin >> deliveryDate.day >> deliveryDate.month >> deliveryDate.year;

			while(!validateDate(deliveryDate, today)){
				cout << "Enter Delivery Date (dd mm yyyy): ";
				cin >> deliveryDate.day >> deliveryDate.month >> deliveryDate.year;	
			}
			
			cm.addCourier(name, weight, distance, deliveryDate);

            
        } else if (choice == 2) {
            string name;
            double weight, distance;
            Date deliveryDate;

            while (true) {
                cout << "Enter Recipient Name: ";
                cin.ignore();
                getline(cin, name);
                if (name.find_first_of("0123456789") == string::npos) {
                    break;
                }
                cout << "Error: Recipient name cannot contain numbers.\n";
            }

            while (true) {
                cout << "Enter Weight of package (kg): ";
                cin >> weight;
                if (cin.fail() || weight <= 0 || weight > 20) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid weight (under 20 kg).\n";
                } else {
                    break;
                }
            }

            while (true) {
                cout << "Enter Distance (km): ";
                cin >> distance;
                if (cin.fail() || distance <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for distance.\n";
                } else {
                    break;
                }
            }

            cout << "Enter Delivery Date (dd mm yyyy): ";
            cin >> deliveryDate.day >> deliveryDate.month >> deliveryDate.year;

        	while(!validateDate(deliveryDate, today)) {
        		cout << "Enter Delivery Date (dd mm yyyy): ";
        		cin >> deliveryDate.day >> deliveryDate.month >> deliveryDate.year;
            } 
                cm.addExpressCourier(name, weight, distance, deliveryDate);
            
        } else if (choice == 3) {
            cm.listCouriers();
        } else if (choice == 4) {
            int id;
            string status;

            cout << "Enter Courier ID to update: ";
            cin >> id;
            cout << "Enter New Status: ";
            cin.ignore();
            getline(cin, status);
            cm.updateCourierStatus(id, status);
        } else if (choice == 5) {
            int id;
            cout << "Enter Courier ID to delete: ";
            cin >> id;
            cm.deleteCourier(id);
        }
    } while (choice != 6);

    return 0;
}
