#include "Vehicle.h"

int Vehicle::totalListings = 0;

Vehicle::Vehicle() : vId(0), year(0), mileage(0), brand(""), model(""), price(0), approved(false), deleted(false) {
}

Vehicle::Vehicle(int id, string b, string m, int y, double p, int km) : vId(id), brand(b), model(m), year(y), price(p), mileage(km), approved(false), deleted(false) {
    totalListings++;
}

Vehicle::Vehicle(const Vehicle& o) : vId(o.vId), brand(o.brand), model(o.model), year(o.year), price(o.price), mileage(o.mileage), approved(o.approved), deleted(o.deleted), report(o.report) {
    totalListings++;
}

Vehicle::~Vehicle() {
}

void Vehicle::addReport(int e, int i, int en, int el, string n) {
    report.set(e, i, en, el, n);
}

void Vehicle::addReport(bool passed, string notes) {
    report.set(passed, notes);
}

void Vehicle::setPrice(double p) {
    price = p;
}

void Vehicle::approve() {
    approved = true;
}

void Vehicle::remove() {
    deleted = true;
    approved = false;
}

int Vehicle::getId() const {
    return vId;
}

string Vehicle::getBrand() const {
    return brand;
}

string Vehicle::getModel() const {
    return model;
}

double Vehicle::getPrice() const {
    return price;
}

int Vehicle::getYear() const {
    return year;
}

int Vehicle::getMileage() const {
    return mileage;
}

bool Vehicle::isActive() const {
    if (deleted == false) {
        return true;
    }
    return false;
}

bool Vehicle::isApproved() const {
    return approved;
}

string Vehicle::getReportSummary() const {
    return report.generateSummary();
}

bool Vehicle::matchBrand(string b) const {
    if (brand == b && deleted == false) {
        return true;
    }
    return false;
}

bool Vehicle::matchModel(string m) const {
    if (model == m && deleted == false) {
        return true;
    }
    return false;
}

bool Vehicle::underPrice(double p) const {
    if (price <= p && deleted == false) {
        return true;
    }
    return false;
}

bool Vehicle::underMileage(int km) const {
    if (mileage <= km && deleted == false) {
        return true;
    }
    return false;
}

bool Vehicle::fromYear(int y) const {
    if (year >= y && deleted == false) {
        return true;
    }
    return false;
}

int Vehicle::getTotal() {
    return totalListings;
}

bool Vehicle::operator==(const Vehicle& o) const {
    if (vId == o.vId) {
        return true;
    }
    return false;
}

double Vehicle::operator+(const Vehicle& o) const {
    return price + o.price;
}

bool Vehicle::operator<(const Vehicle& o) const {
    if (price < o.price) {
        return true;
    }
    return false;
}

Car::Car() : Vehicle(), doors(4), fuelType("Petrol") {
}

Car::Car(int id, string b, string m, int y, double p, int km, int d, string ft) : Vehicle(id, b, m, y, p, km), doors(d), fuelType(ft) {
}

Car::Car(const Car& o) : Vehicle(o), doors(o.doors), fuelType(o.fuelType) {
}

void Car::displayDetails() const {
    if (deleted == true) {
        return;
    }
    cout << "[Car]  " << brand << " " << model << " (" << year << ") " << doors << "-door " << fuelType << " | PKR " << price << " | " << mileage << "km";
    if (approved == true) {
        cout << " [Verified]";
    } else {
        cout << " [Pending]";
    }
    cout << "\n";
    if (approved == true) {
        report.print();
    }
}

int Car::getDoors() const {
    return doors;
}

string Car::getFuelType() const {
    return fuelType;
}

Bike::Bike() : Vehicle(), cc(125) {
}

Bike::Bike(int id, string b, string m, int y, double p, int km, int engineCC) : Vehicle(id, b, m, y, p, km), cc(engineCC) {
}

void Bike::displayDetails() const {
    if (deleted == true) {
        return;
    }
    cout << "[Bike] " << brand << " " << model << " (" << year << ") " << cc << "cc | PKR " << price << " | " << mileage << "km";
    if (approved == true) {
        cout << " [Verified]";
    } else {
        cout << " [Pending]";
    }
    cout << "\n";
    if (approved == true) {
        report.print();
    }
}

int Bike::getCC() const {
    return cc;
}

ElectricCar::ElectricCar() : Car(), rangeKm(0), batteryKwh(0) {
}

ElectricCar::ElectricCar(int id, string b, string m, int y, double p, int km, int range, double battery) : Car(id, b, m, y, p, km, 4, "Electric"), rangeKm(range), batteryKwh(battery) {
}

void ElectricCar::displayDetails() const {
    if (deleted == true) {
        return;
    }
    cout << "[EV]   " << brand << " " << model << " (" << year << ") " << "Range:" << rangeKm << "km | Battery:" << batteryKwh << "kWh | PKR " << price << " | " << mileage << "km";
    if (approved == true) {
        cout << " [Verified]";
    } else {
        cout << " [Pending]";
    }
    cout << "\n";
    if (approved == true) {
        report.print();
    }
}

int ElectricCar::getRangeKm() const {
    return rangeKm;
}

double ElectricCar::getBatteryKwh() const {
    return batteryKwh;
}