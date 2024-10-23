#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_COURIERS = 100;  

class Courier {
protected:
    static int id_counter;
    int id;
    string recipientName;
    string status;
    double weight;
    double distance;
    double cost;
    string deliveryDate;

public:
    Courier(const string& name, double weightVal, double distanceVal, double costVal, const string& date) {
        id = ++id_counter;
        recipientName = name;
        weight = weightVal;
        distance = distanceVal;
        cost = costVal;
        deliveryDate = date;
        status = "Collected";
    }

    virtual void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    virtual void displayDetails() const {
        cout << "ID: " << id << ", Recipient: " << recipientName
             << ", Status: " << status
             << ", Weight: " << weight << " kg"
             << ", Distance: " << distance << " km"
             << ", Cost: $" << cost
             << ", Delivery Date: " << deliveryDate << "\n";
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
    ExpressCourier(const string& name, double weightVal, double distanceVal, double costVal, const string& date)
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
             << ", Delivery Date: " << deliveryDate << "\n";
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
    void addCourier(const string& name, double weight, double distance, const string& deliveryDate) {
        if (courierCount < MAX_COURIERS) {
            double cost = calculateCost(weight, distance);
            couriers[courierCount++] = new Courier(name, weight, distance, cost, deliveryDate);
            cout << "Courier added successfully!\n";
        } else {
            cout << "Cannot add more couriers. Limit reached.\n";
        }
    }

    void addExpressCourier(const string& name, double weight, double distance, const string& deliveryDate) {
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

int main() {
    CourierManagement cm;
    int choice;

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
            string name, deliveryDate;
            double weight, distance;

            // Validate name
            while (true) {
                cout << "Enter Recipient Name: ";
                cin.ignore();
                getline(cin, name);
                if (name.find_first_of("0123456789") == string::npos) {
                    break; // Valid name
                }
                cout << "Error: Name cannot contain digits. Please enter again.\n";
            }

            // Validate weight
            while (true) {
                cout << "Enter Weight of package (kg): ";
                cin >> weight;
                if (cin.fail() || weight <= 0) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for weight.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break; // Valid weight
                }
            }

            // Validate distance
            while (true) {
                cout << "Enter Distance (km): ";
                cin >> distance;
                if (cin.fail() || distance <= 0) {
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for distance.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break; // Valid distance
                }
            }

            cout << "Enter Estimated Delivery Date: ";
            cin >> deliveryDate;

            cm.addCourier(name, weight, distance, deliveryDate);
        } 
        else if (choice == 2) {
            string name, deliveryDate;
            double weight, distance;

            while (true) {
                cout << "Enter Recipient Name: ";
                cin.ignore();
                getline(cin, name);
                if (name.find_first_of("0123456789") == string::npos) {
                    break;
                }
                cout << "Error: Name cannot contain digits. Please enter again.\n";
            }

            while (true) {
                cout << "Enter Weight of package (kg): ";
                cin >> weight;
                if (cin.fail() || weight <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for weight.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }

            cout << "Enter Estimated Delivery Date: ";
            cin >> deliveryDate;

            cm.addExpressCourier(name, weight, distance, deliveryDate);
        } 
        else if (choice == 3) {
            cm.listCouriers();
        } 
        else if (choice == 4) {
            int id;
            string status;

            while (true) {
                cout << "Enter Courier ID to update status: ";
                cin >> id;
                if (cin.fail() || id <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for ID.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break; // Valid ID
                }
            }

            cout << "Enter New Status (Shipped/Received): ";
            cin >> status;
            cm.updateCourierStatus(id, status);
        } 
        else if (choice == 5) {
            int id;

            // Validate ID
            while (true) {
                cout << "Enter Courier ID to delete: ";
                cin >> id;
                if (cin.fail() || id <= 0) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Error: Please enter a valid positive number for ID.\n";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }

            cm.deleteCourier(id);
        }
    } while (choice != 6);

    return 0;
}
