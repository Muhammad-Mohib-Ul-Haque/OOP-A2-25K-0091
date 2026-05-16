#include "PakWheelsSystem.h"

int main() {
    PakWheelsSystem pw;
    Seller* s1 = new Seller(1,"Ahmed Khan","ahmed@email.com", "0301-1111111");
    Seller* s2 = new Seller(2,"Bilal Raza","bilal@email.com", "0391-2222222");
    Buyer* b1 = new Buyer (3,"Sara Malik","sara@email.com", "0341-3333333", 5500000);
    Buyer* b2 = new Buyer (4, "Usman Tariq","usman@email.com","0383-4444444", 12000000);
    Admin* a1 = new Admin (5,"Superuser", "admin@pw.com","0300-0070160", "SuperAdmin");

    pw.registerUser(s1);
    pw.registerUser(s2);
    pw.registerUser(b1);
    pw.registerUser(b2);
    pw.registerUser(a1);

    cout <<"User Roles\n";
    s1->performRole();
    s2->performRole();
    b1->performRole();
    b2->performRole();
    a1->performRole();

    Car v1(101, "Toyota",  "Corolla",   2020, 4800000,  45000, 4, "Petrol");
    Car v2(102, "Honda",   "Civic",     2021, 6200000,  22000, 4, "Petrol");
    Car v3(103, "Suzuki",  "Alto",      2019, 2100000,  80000, 4, "Petrol");
    Car v4(104, "Toyota",  "Fortuner",  2022, 9500000,  15000, 4, "Diesel");
    Car v5(105, "KIA",     "Sportage",  2023, 8750000,   5000, 4, "Petrol");

    ElectricCar e1(301, "Tesla",  "Model 3", 2023, 15000000, 12000, 500, 75.5);
    ElectricCar e2(302, "BYD",    "Atto 3",  2024, 11500000,  3000, 420, 60.0);

    v1.addReport(8, 9, 8, 7, "Clean engine, minor scratches");
    v2.addReport(9, 9, 9, 8, "Well maintained, single owner");
    v3.addReport(6, 7, 5, 6, "Engine okay, body rust present");
    v4.addReport(9, 8, 9, 9, "Excellent condition, low mileage");
    v5.addReport(10, 9, 10, 9, "Brand new condition");
    e1.addReport(10, 10, 10, 10, "Battery perfect, no degradation");
    e2.addReport(9, 10, 9, 10, "Minor software update needed");

    pw.addCar(v1);
    pw.addCar(v2);
    pw.addCar(v3);
    pw.addCar(v4);
    pw.addCar(v5);
    pw.addEV(e1);
    pw.addEV(e2);

    cout << "\nInventory Listing\n";
    listAllVehicles(pw);

    cout << "\nOperator Testing\n";
    Vehicle* ptr1 = pw.findVehicle(101);
    Vehicle* ptr2 = pw.findVehicle(102);
    Vehicle* ptr3 = pw.findVehicle(103);
    Vehicle* ptr4 = pw.findVehicle(104);

    if (ptr1 && ptr2) {
        if ((*ptr1) < (*ptr2)){
            cout << ptr1->getBrand() << " is cheaper than " << ptr2->getBrand() << endl;
        }
        cout << "Combined price (101 + 102): " << ((*ptr1) + (*ptr2)) << endl;
    }

    if (ptr3 && ptr4) {
        if ((*ptr3) < (*ptr4)){
            cout << ptr3->getBrand() << " " << ptr3->getModel()<< " is cheaper than "<< ptr4->getBrand() << " " << ptr4->getModel() << endl;
        }
        cout << "Combined price (103 + 104): " << ((*ptr3) + (*ptr4)) << endl;
    }

    cout << "\nAbstraction Summaries\n";
    cout << "ID 101: " << v1.getReportSummary() << endl;
    cout << "ID 102: " << v2.getReportSummary() << endl;
    cout << "ID 103: " << v3.getReportSummary() << endl;
    cout << "ID 104: " << v4.getReportSummary() << endl;
    cout << "ID 105: " << v5.getReportSummary() << endl;
    cout << "ID 301: " << e1.getReportSummary() << endl;
    cout << "ID 302: " << e2.getReportSummary() << endl;

    
    cout << "\nAffordability Check (Sara: 5,500,000)\n";
    Vehicle* cheap1 = pw.findVehicle(101);  
    Vehicle* cheap2 = pw.findVehicle(103);  
    Vehicle* overBudget = pw.findVehicle(102); 
    if (cheap1 && b1->getBudget() >= cheap1->getPrice())
        cout << "Sara can afford: " << cheap1->getBrand() << " " << cheap1->getModel() << endl;
    if (cheap2 && b1->getBudget() >= cheap2->getPrice())
        cout << "Sara can afford: " << cheap2->getBrand() << " " << cheap2->getModel() << endl;
    if (overBudget && b1->getBudget() < overBudget->getPrice())
        cout << "Sara cannot afford: " << overBudget->getBrand() << " " << overBudget->getModel() << endl;

    cout << "\nAffordability Check (Usman: 12,000,000)\n";
    Vehicle* ev1ptr = pw.findVehicle(301);
    Vehicle* ev2ptr = pw.findVehicle(302);
    if (ev1ptr && b2->getBudget() < ev1ptr->getPrice())
        cout << "Usman cannot afford: " << ev1ptr->getBrand() << " " << ev1ptr->getModel() << endl;
    if (ev2ptr && b2->getBudget() >= ev2ptr->getPrice())
        cout << "Usman can afford: " << ev2ptr->getBrand() << " " << ev2ptr->getModel() << endl;

    return 0;
}