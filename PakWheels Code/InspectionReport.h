#pragma once
#include <iostream>
#include <string>
using namespace std;

class InspectionReport {
    protected:
        bool passed;
        string notes;
        static int totalInspections;
    public:
        InspectionReport();
        InspectionReport(bool p, string n);
        InspectionReport(const InspectionReport& o);
        virtual ~InspectionReport();

        virtual void print() const = 0;
        virtual string generateSummary() const = 0;

        void set(bool p, string n);
        bool hasPassed() const;
        static int getTotal();
        bool operator==(const InspectionReport& o) const;
};

class StandardReport : public InspectionReport {
    private:
        int exterior;
        int interior;
        int engine;
        int electrical;
    public:
        StandardReport();
        StandardReport(int e, int i, int en, int el, string n);
        StandardReport(const StandardReport& o);

        using InspectionReport::set;
        void set(int e, int i, int en, int el, string n);
        void print() const override;
        string generateSummary() const override;
        int getExterior() const;
        int getInterior() const;
        int getEngine() const;
        int getElectrical() const;
};