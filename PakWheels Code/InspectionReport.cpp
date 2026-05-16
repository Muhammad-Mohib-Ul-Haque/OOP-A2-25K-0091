#include "InspectionReport.h"

int InspectionReport::totalInspections = 0;

InspectionReport::InspectionReport() : passed(false), notes("Pending") {
}

InspectionReport::InspectionReport(bool p, string n) : passed(p), notes(n) {
}

InspectionReport::InspectionReport(const InspectionReport& o) : passed(o.passed), notes(o.notes) {
}

InspectionReport::~InspectionReport() {
}

void InspectionReport::set(bool p, string n) {
    passed = p;
    notes = n;
}

bool InspectionReport::hasPassed() const {
    return passed;
}

int InspectionReport::getTotal() {
    return totalInspections;
}

bool InspectionReport::operator==(const InspectionReport& o) const {
    if (passed == o.passed) {
        return true;
    }
    return false;
}

StandardReport::StandardReport() : InspectionReport(false, "Pending"), exterior(0), interior(0), engine(0), electrical(0) {
}

StandardReport::StandardReport(int e, int i, int en, int el, string n) : InspectionReport(false, n), exterior(e), interior(i), engine(en), electrical(el) {
    if (e >= 6 && i >= 6 && en >= 6 && el >= 6) {
        passed = true;
    } 
    else {
        passed = false;
    }
    totalInspections++;
}

StandardReport::StandardReport(const StandardReport& o) : InspectionReport(o.passed, o.notes),exterior(o.exterior),interior(o.interior),engine(o.engine),electrical(o.electrical){
    totalInspections++;
}

void StandardReport::set(int e, int i, int en, int el, string n) {
    exterior = e;
    interior = i;
    engine = en;
    electrical = el;
    notes = n;
    if (e >= 6 && i >= 6 && en >= 6 && el >= 6) {
        passed = true;
    } 
    else{
        passed = false;
    }
    totalInspections++;
}

void StandardReport::print() const {
    if (exterior == 0 && interior == 0 && engine == 0 && electrical == 0) {
        cout << "  " << notes;
    } 
    else {
        cout<<"  Exterior:"<<exterior<<" Interior:"<<interior<<" Engine:"<<engine<<" Electrical:"<< electrical<<" | "<< notes;
    }
    if (passed == true){
        cout << " [PASS]";
    } 
    else{
        cout << " [FAIL]";
    }
    cout << "\n";
}

string StandardReport::generateSummary() const {
    if (passed == true) {
        return "PASS - " + notes;
    }
    return "FAIL - " + notes;
}

int StandardReport::getExterior()const{
    return exterior;
}

int StandardReport::getInterior()const {
    return interior;
}

int StandardReport::getEngine()const{
    return engine;
}

int StandardReport::getElectrical() const{
    return electrical;
}