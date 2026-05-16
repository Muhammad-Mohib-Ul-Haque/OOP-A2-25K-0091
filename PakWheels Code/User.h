#pragma once
#include <iostream>
#include <string>
using namespace std;

class Vehicle;

class Review {
    private:
        int rating;
        string comment;
        string buyerName;
        string date;
        bool verified;
    public:
        Review();
        Review(int r, string c, string bn, string d);
        Review(const Review& o);
        int getRating() const;
        bool isVerified() const;
        bool isPositive() const;
        void show() const;
};

class Favorite {
    private:
        int vehicleId;
        string brand;
        string model;
        string note;
        double savedPrice;
    public:
        Favorite();
        Favorite(int id, string b, string m, string n, double p);
        int getId() const;
        double getSavedPrice() const;
        bool priceRisen(double current) const;
        void updateNote(string n);
        void show() const;
};

class Message {
    private:    
        int msgId;
        int fromId;
        int toId;
        string content;
        string timestamp;
        bool read;
    public:
        Message();
        Message(int id, string c, int f, int t, string ts);
        Message(const Message& o);
        void markRead();
        int getToId() const;
        int getFromId() const;
        bool isUnread() const;
        bool involves(int id) const;
        void show() const;
};

class User {
    protected:
        int userId;
        string name;
        string email;
        string phone;
        char type;
        bool active;
        static int totalUsers;
        const string country;
    public:
        User();
        User(int id, string n, string e, string ph, char t);
        virtual ~User();

        virtual void performRole() const = 0;
        virtual void showProfile() const;

        int getId() const;
        string getName() const;
        char getType() const;
        bool isActive() const;
        void deactivate();
        static int getTotalUsers();
        bool operator==(const User& o) const;
};

class Buyer : public User {
    private:
        Favorite favs[10];
        Message inbox[20];
        int favCount;
        int msgCount;
        double budget;
        const int maxFavs;
    public:
        Buyer(int id, string n, string e, string ph, double b);
        void addFavorite(int vid, string b, string m, string note, double p);
        void removeFavorite(int vid);
        void receiveMsg(const Message& m);
        void viewInbox() const;
        void viewFavorites() const;
        void performRole() const override;
        void showProfile() const override;
        double getBudget() const;
        void setBudget(double b);
        friend class PakWheelsSystem;
};

class Seller : public User {
    private:
        int listings[10];
        Review reviews[20];
        int listCount;
        int reviewCount;
        double revenue;
        const int maxListings;
    public:
        Seller(int id, string n, string e, string ph);
        void listCar(int vid);
        bool delistCar(int vid);
        void addReview(const Review& r);
        void addRevenue(double a);
        double avgRating() const;
        int getListCount() const;
        void showReviews() const;
        void performRole() const override;
        void showProfile() const override;
        friend void auditRevenue(const Seller& s);
};

class Admin : public User {
    private:
        string level;
        string department;
        int approved;
        int removed;
        bool canBan;
        static int totalAdmins;
    public:
        Admin(int id, string n, string e, string ph, string lvl);
        ~Admin();
        void approveCar(Vehicle& v);
        void removeCar(Vehicle& v);
        void banUser(User& u);
        void approveCar(Vehicle& v, string note);
        void performRole() const override;
        void showProfile() const override;
        int getApproved() const;
        int getRemoved() const;
        static int getTotalAdmins();
};

void auditRevenue(const Seller& s);