#include "User.h"
#include "Vehicle.h"

Review::Review() : rating(5), comment("Great!"), buyerName("Anon"), date("N/A"), verified(false) {
}

Review::Review(int r, string c, string bn, string d) : rating(r), comment(c), buyerName(bn), date(d), verified(true) {
}

Review::Review(const Review& o) : rating(o.rating), comment(o.comment), buyerName(o.buyerName), date(o.date), verified(o.verified) {
}

int Review::getRating() const {
    return rating;
}

bool Review::isVerified() const {
    return verified;
}

bool Review::isPositive() const {
    if (rating >= 4) {
        return true;
    }
    return false;
}

void Review::show() const {
    cout << "  " << buyerName << " [" << date << "] " << rating << "/5 - " << comment << "\n";
}

Favorite::Favorite() : vehicleId(0), brand(""), model(""), note(""), savedPrice(0) {
}

Favorite::Favorite(int id, string b, string m, string n, double p) : vehicleId(id), brand(b), model(m), note(n), savedPrice(p) {
}

int Favorite::getId() const {
    return vehicleId;
}

double Favorite::getSavedPrice() const {
    return savedPrice;
}

bool Favorite::priceRisen(double current) const {
    if (current > savedPrice * 1.05) {
        return true;
    }
    return false;
}

void Favorite::updateNote(string n) {
    note = n;
}

void Favorite::show() const {
    cout << "  [Saved] " << brand << " " << model << " ID:" << vehicleId << " PKR " << savedPrice << " | " << note << "\n";
}

Message::Message() : msgId(0), fromId(0), toId(0), content(""), timestamp(""), read(false) {
}

Message::Message(int id, string c, int f, int t, string ts) : msgId(id), content(c), fromId(f), toId(t), timestamp(ts), read(false) {
}

Message::Message(const Message& o) : msgId(o.msgId), content(o.content), fromId(o.fromId), toId(o.toId), timestamp(o.timestamp), read(o.read) {
}

void Message::markRead() {
    read = true;
}

int Message::getToId() const {
    return toId;
}

int Message::getFromId() const {
    return fromId;
}

bool Message::isUnread() const {
    if (read == false) {
        return true;
    }
    return false;
}

bool Message::involves(int id) const {
    if (fromId == id || toId == id) {
        return true;
    }
    return false;
}

void Message::show() const {
    cout << "  [" << timestamp << "] From#" << fromId << " -> To#" << toId;
    if (read == false) {
        cout << " [UNREAD]";
    }
    cout << ": " << content << "\n";
}

int User::totalUsers = 0;

User::User() : userId(0), name(""), email(""), phone(""), type('U'), active(true), country("Pakistan") {
    totalUsers++;
}

User::User(int id, string n, string e, string ph, char t) : userId(id), name(n), email(e), phone(ph), type(t), active(true), country("Pakistan") {
    totalUsers++;
}

User::~User() {
    totalUsers--;
}

int User::getId() const {
    return userId;
}

string User::getName() const {
    return name;
}

char User::getType() const {
    return type;
}

bool User::isActive() const {
    return active;
}

void User::deactivate() {
    active = false;
}

int User::getTotalUsers() {
    return totalUsers;
}

void User::showProfile() const {
    cout << "[#" << userId << "] " << name << " | " << email << " | " << country << "\n";
}

bool User::operator==(const User& o) const {
    if (userId == o.userId) {
        return true;
    }
    return false;
}

Buyer::Buyer(int id, string n, string e, string ph, double b) : User(id, n, e, ph, 'B'), favCount(0), msgCount(0), budget(b), maxFavs(10) {
}

void Buyer::addFavorite(int vid, string b, string m, string note, double p) {
    if (favCount < maxFavs) {
        favs[favCount] = Favorite(vid, b, m, note, p);
        favCount++;
    } else {
        cout << "Favorites full!\n";
    }
}

void Buyer::removeFavorite(int vid) {
    for (int i = 0; i < favCount; i++) {
        if (favs[i].getId() == vid) {
            for (int j = i; j < favCount - 1; j++) {
                favs[j] = favs[j + 1];
            }
            favCount--;
            cout << "Removed from favorites.\n";
            return;
        }
    }
}

void Buyer::receiveMsg(const Message& m) {
    if (msgCount < 20) {
        inbox[msgCount] = m;
        msgCount++;
    }
}

void Buyer::viewInbox() const {
    cout << "\nInbox: " << name << " \n";
    for (int i = 0; i < msgCount; i++) {
        inbox[i].show();
    }
    if (msgCount == 0) {
        cout << "  No messages.\n";
    }
}

void Buyer::viewFavorites() const {
    cout << "\nSaved Cars: " << name << " \n";
    for (int i = 0; i < favCount; i++) {
        favs[i].show();
    }
    if (favCount == 0) {
        cout << "  None saved.\n";
    }
}

void Buyer::performRole() const {
    cout << name << " browsing PakWheels under PKR " << budget << "\n";
}

void Buyer::showProfile() const {
    User::showProfile();
    cout << "  Budget: PKR " << budget << " | Favorites: " << favCount << "\n";
}

double Buyer::getBudget() const {
    return budget;
}

void Buyer::setBudget(double b) {
    budget = b;
}

Seller::Seller(int id, string n, string e, string ph) : User(id, n, e, ph, 'S'), listCount(0), reviewCount(0), revenue(0), maxListings(10) {
}

void Seller::listCar(int vid) {
    if (listCount < maxListings) {
        listings[listCount] = vid;
        listCount++;
    }
}

bool Seller::delistCar(int vid) {
    for (int i = 0; i < listCount; i++) {
        if (listings[i] == vid) {
            for (int j = i; j < listCount - 1; j++) {
                listings[j] = listings[j + 1];
            }
            listCount--;
            return true;
        }
    }
    return false;
}

void Seller::addReview(const Review& r) {
    if (reviewCount < 20) {
        reviews[reviewCount] = r;
        reviewCount++;
    }
}

void Seller::addRevenue(double a) {
    revenue = revenue + a;
}

int Seller::getListCount() const {
    return listCount;
}

double Seller::avgRating() const {
    if (reviewCount == 0) {
        return 0;
    }
    double s = 0;
    for (int i = 0; i < reviewCount; i++) {
        s = s + reviews[i].getRating();
    }
    return s / reviewCount;
}

void Seller::showReviews() const {
    cout << "\nReviews: " << name << " (Avg " << avgRating() << "/5)\n";
    for (int i = 0; i < reviewCount; i++) {
        reviews[i].show();
    }
}

void Seller::performRole() const {
    cout << name << " managing " << listCount << " listing(s).\n";
}

void Seller::showProfile() const {
    User::showProfile();
    cout << "  Listings: " << listCount << " | Avg Rating: " << avgRating() << "/5\n";
}

int Admin::totalAdmins = 0;

Admin::Admin(int id, string n, string e, string ph, string lvl) : User(id, n, e, ph, 'A'), level(lvl), department("Listings"), approved(0), removed(0), canBan(false) {
    if (lvl == "SuperAdmin") {
        canBan = true;
    }
    totalAdmins++;
}

Admin::~Admin() {
    totalAdmins--;
}

void Admin::approveCar(Vehicle& v) {
    v.approve();
    approved++;
    cout << "[Admin] Approved ID " << v.getId() << "\n";
}

void Admin::approveCar(Vehicle& v, string note) {
    v.approve();
    approved++;
    cout << "[Admin] Approved ID " << v.getId() << " | Note: " << note << "\n";
}

void Admin::removeCar(Vehicle& v) {
    v.remove();
    removed++;
    cout << "[Admin] Removed ID " << v.getId() << "\n";
}

void Admin::banUser(User& u) {
    if (canBan == true) {
        u.deactivate();
        cout << "[Admin] Banned: " << u.getName() << "\n";
    } else {
        cout << "No permission to ban.\n";
    }
}

void Admin::performRole() const {
    cout << "Admin " << name << " [" << level << "] - Approved:" << approved << " Removed:" << removed << "\n";
}

void Admin::showProfile() const {
    User::showProfile();
    cout << "  Level:" << level << " | Approved:" << approved << " | Removed:" << removed << "\n";
}

int Admin::getApproved() const {
    return approved;
}

int Admin::getRemoved() const {
    return removed;
}

int Admin::getTotalAdmins() {
    return totalAdmins;
}

void auditRevenue(const Seller& s) {
    cout << "  Audit -> " << s.name << " | Revenue: PKR " << s.revenue << " | Listings: " << s.listCount << "\n";
}