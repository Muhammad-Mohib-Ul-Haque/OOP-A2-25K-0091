#pragma once
#include "InspectionReport.h"

class PakWheelsSystem;

class Vehicle {
    protected:
        int vId;
        int year;
        int mileage;
        string brand;
        string model;
        double price;
        bool approved;
        bool deleted;
        StandardReport report;
        static int totalListings;

    public:
        Vehicle();
        Vehicle(int id, string b, string m, int y, double p, int km);
        Vehicle(const Vehicle& o);
        virtual ~Vehicle();

        virtual void displayDetails() const = 0;

        void addReport(int e, int i, int en, int el, string n);
        void addReport(bool passed, string notes);

        void setPrice(double p);
        void approve();
        void remove();

        int getId() const;
        string getBrand() const;
        string getModel() const;
        double getPrice() const;
        int getYear() const;
        int getMileage() const;
        bool isActive() const;
        bool isApproved() const;

        string getReportSummary() const;

        bool matchBrand(string b) const;
        bool matchModel(string m) const;
        bool underPrice(double p) const;
        bool underMileage(int km) const;
        bool fromYear(int y) const;

        static int getTotal();
        bool operator==(const Vehicle& o) const;
        double operator+(const Vehicle& o) const;
        bool operator<(const Vehicle& o) const;

        friend class PakWheelsSystem;
};

class Car : public Vehicle {
    protected:
        int doors;
        string fuelType;
    public:
        Car();
        Car(int id, string b, string m, int y, double p, int km, int d, string ft);
        Car(const Car& o);
        void displayDetails() const override;
        int getDoors() const;
        string getFuelType() const;
};

class Bike : public Vehicle {
    private:
        int cc;
    public:
        Bike();
        Bike(int id, string b, string m, int y, double p, int km, int engineCC);
        void displayDetails() const override;
        int getCC() const;
};

class ElectricCar : public Car {
    private:
        int rangeKm;
        double batteryKwh;
    public:
        ElectricCar();
        ElectricCar(int id, string b, string m, int y, double p, int km, int range, double battery);
        void displayDetails() const override;
        int getRangeKm() const;
        double getBatteryKwh() const;
};