#pragma once
#include "Vehicle.h"
#include "User.h"

class PakWheelsSystem {
    private:
        Vehicle* inventory[50];
        User* users[30];
        Message msgLog[100];
        int vCount;
        int uCount;
        int msgCount;
        const string name;
        static int totalSearches;

    public:
        PakWheelsSystem();
        ~PakWheelsSystem();

        void registerUser(User* u);
        void addCar(const Car& c);
        void addBike(const Bike& b);
        void addEV(const ElectricCar& e);

        Vehicle* findVehicle(int id);
        User* findUser(int id);

        bool updatePrice(int vid, double p);

        void searchBrand(string b) const;
        void searchModel(string m) const;
        void filterPrice(double p) const;
        void filterMileage(int km) const;
        void filterYear(int y) const;

        void sendMessage(int fromId, int toId, string content, string ts);
        void showStats() const;

        static int getSearches();

        friend void compareVehicles(const PakWheelsSystem& pw, int id1, int id2);
        friend void listAllVehicles(const PakWheelsSystem& pw);
};

void compareVehicles(const PakWheelsSystem& pw, int id1, int id2);
void listAllVehicles(const PakWheelsSystem& pw);