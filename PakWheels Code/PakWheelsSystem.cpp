#include "PakWheelsSystem.h"

int PakWheelsSystem::totalSearches = 0;

PakWheelsSystem::PakWheelsSystem() : vCount(0), uCount(0), msgCount(0), name("PakWheels") {
    for (int i = 0; i < 50; i++) {
        inventory[i] = nullptr;
    }
}

PakWheelsSystem::~PakWheelsSystem() {
    for (int i = 0; i < vCount; i++) {
        delete inventory[i];
    }
}

void PakWheelsSystem::registerUser(User* u) {
    if (uCount < 30) {
        users[uCount] = u;
        uCount++;
    }
}

void PakWheelsSystem::addCar(const Car& c) {
    if (vCount < 50) {
        inventory[vCount] = new Car(c);
        vCount++;
    }
}

void PakWheelsSystem::addBike(const Bike& b) {
    if (vCount < 50) {
        inventory[vCount] = new Bike(b);
        vCount++;
    }
}

void PakWheelsSystem::addEV(const ElectricCar& e) {
    if (vCount < 50) {
        inventory[vCount] = new ElectricCar(e);
        vCount++;
    }
}

Vehicle* PakWheelsSystem::findVehicle(int id) {
    for (int i = 0; i < vCount; i++) {
        if (inventory[i] != nullptr && inventory[i]->getId() == id && inventory[i]->isActive()) {
            return inventory[i];
        }
    }
    return nullptr;
}

User* PakWheelsSystem::findUser(int id) {
    for (int i = 0; i < uCount; i++) {
        if (users[i]->getId() == id) {
            return users[i];
        }
    }
    return nullptr;
}

bool PakWheelsSystem::updatePrice(int vid, double p) {
    Vehicle* v = findVehicle(vid);
    if (v != nullptr) {
        v->setPrice(p);
        return true;
    }
    return false;
}

void PakWheelsSystem::searchBrand(string b) const {
    totalSearches++;
    cout << "\nBrand: " << b << "\n";
    for (int i = 0; i < vCount; i++) {
        if (inventory[i]->matchBrand(b)) {
            inventory[i]->displayDetails();
        }
    }
}

void PakWheelsSystem::searchModel(string m) const {
    totalSearches++;
    cout << "\nModel: " << m << "\n";
    for (int i = 0; i < vCount; i++) {
        if (inventory[i]->matchModel(m)) {
            inventory[i]->displayDetails();
        }
    }
}

void PakWheelsSystem::filterPrice(double p) const {
    totalSearches++;
    cout << "\nUnder PKR " << p << "\n";
    for (int i = 0; i < vCount; i++) {
        if (inventory[i]->underPrice(p)) {
            inventory[i]->displayDetails();
        }
    }
}

void PakWheelsSystem::filterMileage(int km) const {
    totalSearches++;
    cout << "\nUnder " << km << "km\n";
    for (int i = 0; i < vCount; i++) {
        if (inventory[i]->underMileage(km)) {
            inventory[i]->displayDetails();
        }
    }
}

void PakWheelsSystem::filterYear(int y) const {
    totalSearches++;
    cout << "\nFrom " << y << " onwards\n";
    for (int i = 0; i < vCount; i++) {
        if (inventory[i]->fromYear(y)) {
            inventory[i]->displayDetails();
        }
    }
}

void PakWheelsSystem::sendMessage(int fromId, int toId, string content, string ts) {
    Message m(msgCount + 1, content, fromId, toId, ts);
    msgCount++;
    msgLog[msgCount - 1] = m;
    
    User* u = findUser(toId);
    if (u != nullptr && u->getType() == 'B') {
        Buyer* buyer = (Buyer*)u;
        buyer->receiveMsg(m);
    }
    
    cout << "Msg sent: #" << fromId << " -> #" << toId << "\n";
}

void PakWheelsSystem::showStats() const {
    cout << "\n" << name << " Stats\n";
    cout << "Users: " << User::getTotalUsers() << "\n";
    cout << "Listings: " << Vehicle::getTotal() << "\n";
    cout << "Inspections: " << InspectionReport::getTotal() << "\n";
    cout << "Searches: " << totalSearches << "\n";
    cout << "Admins: " << Admin::getTotalAdmins() << "\n";
}

int PakWheelsSystem::getSearches() {
    return totalSearches;
}

void compareVehicles(const PakWheelsSystem& pw, int id1, int id2) {
    Vehicle* a = nullptr;
    Vehicle* b = nullptr;
    
    for (int i = 0; i < pw.vCount; i++) {
        if (pw.inventory[i]->getId() == id1) {
            a = pw.inventory[i];
        }
        if (pw.inventory[i]->getId() == id2) {
            b = pw.inventory[i];
        }
    }
    
    if (a == nullptr || b == nullptr) {
        cout << "Vehicle not found.\n";
        return;
    }

    cout << "\nVehicle Comparison\n";
    a->displayDetails();
    b->displayDetails();
    
    if ((*a) == (*b)) {
        cout << "  Same listing? : Yes\n";
    } else {
        cout << "  Same listing? : No\n";
    }
    
    if ((*a) < (*b)) {
        cout << "  Cheaper       : Vehicle #" << id1 << "\n";
    } else {
        cout << "  Cheaper       : Vehicle #" << id2 << "\n";
    }
    
    cout << "  Combined price: PKR " << ((*a) + (*b)) << "\n";
}

void listAllVehicles(const PakWheelsSystem& pw) {
    cout << "\nFull Inventory (Admin View)\n";
    for (int i = 0; i < pw.vCount; i++) {
        if (pw.inventory[i] != nullptr) {
            pw.inventory[i]->displayDetails();
        }
    }
}