#include <iostream>
#include <string>
using namespace std;
class Plan {
protected:
    string customerName;
    string phoneNumber;
    int billMonth;
public:
    Plan(string name, string phone, int month)
        {
        customerName = name;
        phoneNumber = phone;
        billMonth = month;
        }
    virtual double calculateBill() = 0;
    virtual int inputCalls() {
        string callDuration;
        int totalMinutes = 0;
        cout << "Enter calls duration like that (hh:mm:ss) , (choose 'end' to stop): " << endl;
        while (true) {
            cout << "Call duration: ";
            cin >> callDuration;
            if (callDuration == "end")
                break;
            int hours, minutes, seconds;
            sscanf(callDuration.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);
            int totalCallMinutes = hours * 60 + minutes;
            if (seconds > 0) {
                totalCallMinutes += 1;
            }
            totalMinutes += totalCallMinutes;
        }
        return totalMinutes;
    }
    virtual void printAccountDetails() const {
        static const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun","Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        cout << "Customer Name: " << customerName << endl
                  << "Phone Number: " << phoneNumber << endl
                  << "Bill Month: " << months[billMonth - 1] << endl;
    }
    virtual ~Plan() {}
};
class PackagePlan : public Plan {
private:
    int allowedMins;
    double monthlyCost;
    double outRate;
    int outPackMins;
public:
    PackagePlan(string name, string phone, int month, int allowed, double cost, double rate)
        : Plan(name, phone, month), allowedMins(allowed), monthlyCost(cost), outRate(rate), outPackMins(0) {}
    double calculateBill() override {
        double extraCost = outPackMins * outRate;
        double totalBill = monthlyCost + extraCost;
        cout << "Monthly Cost: " << monthlyCost << endl
                  << "Out of Package Minutes: " << outPackMins << endl
                  << "Out of Package Rate: " << outRate << " per minute" << endl
                  << "Extra Cost: " << extraCost << endl
                  << "Total Bill: " << totalBill << endl;
        return totalBill;
    }
    int inputCalls() override {
        int totalMinutes = Plan::inputCalls();
        if (totalMinutes > allowedMins) {
            outPackMins = totalMinutes - allowedMins;
        }
        else {
            outPackMins = 0;
        }
        return totalMinutes;
    }
    void printAccountDetails() const override {
        Plan::printAccountDetails();
        cout << "Allowed Minutes: " << allowedMins << endl
                  << "Monthly Cost: " << monthlyCost << endl
                  << "Out of Package Rate: " << outRate << " per minute" << endl;
    }
};
class RatePlan : public Plan {
private:
    double callRate;
    int minutesConsumed;
public:
    RatePlan(string name, string phone, int month, double callRate)
        : Plan(name, phone, month), callRate(callRate), minutesConsumed(0) {}
    double calculateBill() override {
        double totalBill = minutesConsumed * callRate;
        cout << "Minutes Consumed: " << minutesConsumed << endl
                  << "Call Rate: " << callRate << " per minute" << endl
                  << "Total Bill: " << totalBill << endl;
        return totalBill;
    }
    int inputCalls() override {
        minutesConsumed = Plan::inputCalls();
        return minutesConsumed;
    }
    void printAccountDetails() const override {
        Plan::printAccountDetails();
        cout << "Call Rate: " << callRate << " per minute" << endl;
    }
};
int main() {
    Plan* plans[5];
    for (int i = 0; i < 5; ++i) {
        int planType;
        cout << "Choose plan type (0 for Package Plan, 1 for Rate Plan): ";
        cin >> planType;
        string customerName, phoneNumber;
        int billMonth;
        cout << "Enter Customer Name: ";
        cin >> customerName;
        cout << "Enter Phone Number: ";
        cin >> phoneNumber;
        cout << "Enter Bill Month (1-12): ";
        cin >> billMonth;
        if (planType == 0) {
            int allowedMins;
            double monthlyCost, outRate;
            cout << "Enter Allowed Minutes: ";
            cin >> allowedMins;
            cout << "Enter Monthly Cost: ";
            cin >> monthlyCost;
            cout << "Enter Out of Package Rate: ";
            cin >> outRate;
            plans[i] = new PackagePlan(customerName, phoneNumber, billMonth, allowedMins, monthlyCost, outRate);
        }
        else {
            double callRate;
            cout << "Enter Call Rate: ";
            cin >> callRate;
            plans[i] = new RatePlan(customerName, phoneNumber, billMonth, callRate);
        }
    }
    for (int i = 0; i < 5; ++i) {
        plans[i]->inputCalls();
        plans[i]->printAccountDetails();
        plans[i]->calculateBill();
        delete plans[i];
    }
    return 0;
}

