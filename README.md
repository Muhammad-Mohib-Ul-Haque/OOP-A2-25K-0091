# PakWheels Car Marketplace System

## About Me

Hi, I'm Muhammad Mohib Ul Haque, a first-year student at FAST-NUCES Karachi studying Bachelor of Artificial Intelligence. I enjoy building things from scratch and understanding how systems work under the hood. This is one of my projects where I got to apply object-oriented programming concepts to something real and familiar.

- **Email:** mohibulhaque109@gmail.com
- **University:** FAST National University of Computer and Emerging Sciences, Karachi
- **Program:** Bachelor of Artificial Intelligence, BAI-2A

---

A C++ project that simulates how PakWheels works — car listings, user accounts, inspection reports, messaging, and admin controls. Built as an assignment in Object Oriednted Programming (OOP) CS1004 at FAST-NUCES Karachi, Spring 2026.

---

## Website Overview

PakWheels (www.pakwheels.com) is Pakistan's largest online car marketplace. It lets sellers list cars, buyers browse and shortlist them, and admins manage the platform. This project replicates those exact features using OOP in C++.

The homepage lets users search by brand, model, city, and price range. In the code, this maps to the `searchBrand()`, `searchModel()`, and `filterPrice()` functions inside `PakWheelsSystem`.

---

## Car Listings — Vehicle, Car, Bike, ElectricCar

Every car on PakWheels has a brand, model, year, price, mileage, and a verified badge if it has been inspected.

In the code, `Vehicle` is an abstract base class. `Car`, `Bike`, and `ElectricCar` all extend it and each override `displayDetails()` to print their own format. `ElectricCar` also extends `Car`, making it multi-level inheritance.

```cpp
class ElectricCar : public Car {
    int rangeKm;
    double batteryKwh;
public:
    ElectricCar(int id, string b, string m, int y, double p,
                int km, int range, double battery)
        : Car(id, b, m, y, p, km, 4, "Electric"),
          rangeKm(range), batteryKwh(battery) {}
};
```

The fuelType is hardcoded to `"Electric"` in the constructor so an EV can never be accidentally given a fuel type.

---

## Inspection Reports — InspectionReport, StandardReport

PakWheels has a paid CarSure inspection service. Inspected cars get a badge showing scores for engine, interior, exterior, and electrical condition.

`InspectionReport` is abstract with two pure virtual functions. `StandardReport` is the concrete class that stores the four scores and decides pass or fail.

```cpp
StandardReport(int e, int i, int en, int el, string n)
    : InspectionReport(false, n),
      exterior(e), interior(i), engine(en), electrical(el) {
    passed = (e >= 6 && i >= 6 && en >= 6 && el >= 6);
    totalInspections++;
}
```

If any score is below 6, the inspection fails. The report is composed inside `Vehicle` — it gets deleted when the car is deleted.

---

## User Accounts — User, Buyer, Seller, Admin

PakWheels has three account types: buyers who browse, sellers who list cars, and admins who manage the platform.

`User` is abstract with a pure virtual `performRole()`. Each subclass overrides it differently.

```cpp
void Buyer::performRole() const {
    cout << name << " browsing PakWheels under PKR " << budget << "\n";
}
void Seller::performRole() const {
    cout << name << " managing " << listCount << " listing(s).\n";
}
void Admin::performRole() const {
    cout << "Admin " << name << " [" << level << "] - Approved:"
         << approved << " Removed:" << removed << "\n";
}
```

`PakWheelsSystem` stores `User*` pointers and calls `performRole()` on them — the right version runs automatically at runtime through polymorphism.

---

## Saved Cars — Favorite, Buyer

PakWheels lets buyers shortlist cars using a heart icon. The saved price is recorded so the buyer can be alerted if the price goes up.

```cpp
bool Favorite::priceRisen(double current) const {
    return current > savedPrice * 1.05;
}
```

If the current price is more than 5% above what it was when saved, `priceRisen()` returns true. The `Favorite` array is composed inside `Buyer` — it is personal to the account and deleted with it.

---

## Buyer-Seller Messaging — Message, Buyer

PakWheels has a built-in chat so buyers can contact sellers directly from a listing page.

```cpp
void PakWheelsSystem::sendMessage(int fromId, int toId,
                                   string content, string ts) {
    Message m(msgCount + 1, content, fromId, toId, ts);
    msgCount++;
    msgLog[msgCount - 1] = m;
    User* u = findUser(toId);
    if (u != nullptr && u->getType() == 'B') {
        Buyer* buyer = (Buyer*)u;
        buyer->receiveMsg(m);
    }
}
```

The message is logged in `PakWheelsSystem` and also delivered into the buyer's inbox. `PakWheelsSystem` is a friend of `Buyer` so it can call `receiveMsg()` directly.

---

## Seller Reviews — Review, Seller

Buyers can leave star ratings and comments on a seller's profile after a transaction.

```cpp
double Seller::avgRating() const {
    if (reviewCount == 0) return 0;
    double s = 0;
    for (int i = 0; i < reviewCount; i++)
        s += reviews[i].getRating();
    return s / reviewCount;
}
```

The average is computed on the fly every time instead of storing it separately, which avoids the data ever going out of sync. Reviews are aggregated by `Seller` — they come from buyers externally and are not owned by the seller.

---

## Admin Controls — Admin, PakWheelsSystem

Admins approve listings, remove fraudulent ads, and ban users. Only a SuperAdmin can ban.

```cpp
void Admin::banUser(User& u) {
    if (canBan) {
        u.deactivate();
        cout << "[Admin] Banned: " << u.getName() << "\n";
    } else {
        cout << "No permission to ban.\n";
    }
}
```

`canBan` is set to true only when the admin level is `"SuperAdmin"`. This mirrors real role-based access control. `approveCar()` is also overloaded — one version takes just the vehicle, the other also takes a note string.

---

## Search and Filter — PakWheelsSystem

PakWheels lets users filter cars by brand, model, price, mileage, and year.

```cpp
void PakWheelsSystem::filterPrice(double p) const {
    totalSearches++;
    cout << "\nUnder PKR " << p << "\n";
    for (int i = 0; i < vCount; i++)
        if (inventory[i]->underPrice(p))
            inventory[i]->displayDetails();
}
```

Every search call increments `totalSearches`, a static member that tracks platform-wide analytics. All filter functions are `const` because they only read data.

---

## How to Compile & Run

No external libraries needed. Standard C++11 only.

**Linux / Mac:**
```bash
g++ -o pakwheels main.cpp PakWheelsSystem.cpp Vehicle.cpp User.cpp InspectionReport.cpp
./pakwheels
```

**Windows (MinGW):**
```bash
g++ -o pakwheels.exe main.cpp PakWheelsSystem.cpp Vehicle.cpp User.cpp InspectionReport.cpp
pakwheels.exe
```

Make sure all five `.cpp` files are included. Forgetting `InspectionReport.cpp` will cause a linker error.

---

## Course Info

- **Course:** Object Oriented Programming — CS1004
- **Instructor:** Mr. Talha Shahid
- **University:** FAST-NUCES, Karachi Campus
- **Semester:** Spring 2026
- **Reference:** [www.pakwheels.com](https://www.pakwheels.com)
