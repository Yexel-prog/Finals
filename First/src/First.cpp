#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

struct TravelPlan {
    string destination;
    int days;
    double budget;
    vector<string> touristSpots;
};

vector<TravelPlan> plans;
vector<pair<string, vector<string>>> destinations = {
    {"Brunei", {"Omar Ali Saifuddien Mosque", "Kampong Ayer", "Ulu Temburong National Park"}},
    {"Cambodia", {"Angkor Wat", "Phnom Penh", "Koh Rong"}},
    {"East Timor", {"Dili", "Atauro Island", "Jaco Island"}},
    {"Indonesia", {"Bali", "Borobudur", "Komodo National Park"}},
    {"Laos", {"Luang Prabang", "Kuang Si Falls", "Vang Vieng"}},
    {"Malaysia", {"Petronas Twin Towers", "Batu Caves", "Langkawi"}},
    {"Myanmar", {"Bagan", "Shwedagon Pagoda", "Inle Lake"}},
    {"Philippines", {"Boracay", "Palawan", "Chocolate Hills"}},
    {"Singapore", {"Marina Bay Sands", "Gardens by the Bay", "Sentosa Island"}},
    {"Thailand", {"Bangkok", "Phuket", "Chiang Mai"}},
    {"Vietnam", {"Ha Long Bay", "Hanoi", "Ho Chi Minh City"}}
};

unordered_map<string, double> exchangeRates = {
    {"Brunei", 0.022564}, // Brunei Dollar (BND)
    {"Cambodia", 68.00}, // Cambodian Riel (KHR)
    {"East Timor", 0.017078}, // US Dollar (USD)
    {"Indonesia", 267.045316}, // Indonesian Rupiah (IDR)
    {"Laos", 184.00}, // Lao Kip (LAK)
    {"Malaysia", 0.074119}, // Malaysian Ringgit (MYR)
    {"Myanmar", 35.00}, // Myanmar Kyat (MMK)
    {"Philippines", 1.00}, // Philippine Peso (PHP)
    {"Singapore", 0.022564}, // Singapore Dollar (SGD)
    {"Thailand", 0.575065}, // Thai Baht (THB)
    {"Vietnam", 410.00} // Vietnamese Dong (VND)
};

void addPlan() {
    TravelPlan plan;
    cout << "Available destinations in Southeast Asia:\n";
    for (const auto &dest : destinations) {
        cout << "- " << dest.first << "\n";
    }
    cout << "Enter destination: ";
    cin >> plan.destination;
    cout << "Enter number of days: ";
    cin >> plan.days;
    cout << "Enter budget in PHP: ";
    cin >> plan.budget;

    if (exchangeRates.find(plan.destination) != exchangeRates.end()) {
        plan.budget *= exchangeRates[plan.destination];
        cout << "Budget converted to local currency: " << plan.budget << "\n";
    } else {
        cout << "Destination not found in exchange rates list.\n";
    }

    string visitType;
    cout << "Are you visiting for tourist attractions or just visiting? (Enter 'tourist' or 'just visiting'): ";
    cin >> visitType;

    if (visitType == "tourist") {
        for (const auto &dest : destinations) {
            if (dest.first == plan.destination) {
                cout << "Available tourist spots in " << plan.destination << ":\n";
                for (size_t i = 0; i < dest.second.size(); ++i) {
                    cout << i + 1 << ". " << dest.second[i] << "\n";
                }
                int choice;
                cout << "Enter the number of the tourist spot you plan to visit (enter 0 to finish): ";
                while (cin >> choice && choice != 0) {
                    if (choice > 0 && choice <= dest.second.size()) {
                        plan.touristSpots.push_back(dest.second[choice - 1]);
                    } else {
                        cout << "Invalid choice. Please try again.\n";
                    }
                    cout << "Enter the number of the tourist spot you plan to visit (enter 0 to finish): ";
                }
                break;
            }
        }
    }

    plans.push_back(plan);
    cout << "Plan added successfully!\n";
}

void updatePlan() {
    string destination;
    cout << "Enter destination to update: ";
    cin >> destination;
    for (auto &plan : plans) {
        if (plan.destination == destination) {
            cout << "Enter new number of days: ";
            cin >> plan.days;
            cout << "Enter new budget in PHP: ";
            cin >> plan.budget;
            if (exchangeRates.find(plan.destination) != exchangeRates.end()) {
                plan.budget *= exchangeRates[plan.destination];
                cout << "Budget converted to local currency: " << plan.budget << "\n";
            }
            cout << "Plan updated successfully!\n";
            return;
        }
    }
    cout << "Plan not found!\n";
}

void deletePlan() {
    string destination;
    cout << "Enter destination to delete: ";
    cin >> destination;
    for (auto it = plans.begin(); it != plans.end(); ++it) {
        if (it->destination == destination) {
            plans.erase(it);
            cout << "Plan deleted successfully!\n";
            return;
        }
    }
    cout << "Plan not found!\n";
}

void searchPlan() {
    string destination;
    cout << "Enter destination to search: ";
    cin >> destination;
    for (const auto &plan : plans) {
        if (plan.destination == destination) {
            cout << "Destination: " << plan.destination << "\n";
            cout << "Days: " << plan.days << "\n";
            cout << "Budget: " << plan.budget << "\n";
            cout << "Tourist Spots:\n";
            for (const auto &spot : plan.touristSpots) {
                cout << "- " << spot << "\n";
            }
            return;
        }
    }
    cout << "Plan not found!\n";
}

void suggestSpending() {
    string destination;
    cout << "Enter destination for spending suggestion: ";
    cin >> destination;
    for (const auto &plan : plans) {
        if (plan.destination == destination) {
            double remainingBudget = plan.budget;
            double dailyBudget = plan.budget / plan.days;

            cout << "For " << plan.destination << ", here is your suggested spending per day in local currency:\n";
            for (int i = 1; i <= plan.days; ++i) {
                double hotel = dailyBudget * 0.4; // 40% for hotel
                double food = dailyBudget * 0.3; // 30% for food
                double transport = dailyBudget * 0.2; // 20% for transportation
                double shopping = dailyBudget * 0.1; // 10% for shopping

                if (i == plan.days) { // Allocate remaining budget on the last day
                    hotel += remainingBudget * 0.4;
                    food += remainingBudget * 0.3;
                    transport += remainingBudget * 0.2;
                    shopping += remainingBudget * 0.1;
                }

                remainingBudget -= dailyBudget;

                cout << "Day " << i << ":\n";
                cout << "  Hotel: " << hotel << "\n";
                cout << "  Food: " << food << "\n";
                cout << "  Transportation: " << transport << "\n";
                cout << "  Shopping: " << shopping << "\n";
            }
            return;
        }
    }
    cout << "Plan not found!\n";
}

int main() {
    int choice;
    do {
        cout << "\nTravel Planner Menu:\n";
        cout << "1. Add Plan\n";
        cout << "2. Update Plan\n";
        cout << "3. Delete Plan\n";
        cout << "4. Search Plan\n";
        cout << "5. Suggest Spending\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addPlan(); break;
            case 2: updatePlan(); break;
            case 3: deletePlan(); break;
            case 4: searchPlan(); break;
            case 5: suggestSpending(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 6);
    return 0;
}
