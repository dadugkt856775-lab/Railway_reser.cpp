#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

struct Passenger {
    int ticket;
    string name;
    int seat;
};

int main() {
    map<int, Passenger> reservations;
    set<int> bookedSeats;
    vector<Passenger> passengers;

    int nextTicket = 1001;
    int choice;

    do {
        cout << "\n===== RAILWAY RESERVATION =====";
        cout << "\n1. Book Ticket";
        cout << "\n2. Cancel Ticket";
        cout << "\n3. Display Reservations";
        cout << "\n4. Available Seats";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string name;
            int seat;

            cout << "Enter passenger name: ";
            cin >> name;

            cout << "Enter seat number (1-20): ";
            cin >> seat;

            if (seat < 1 || seat > 20) {
                cout << "Invalid seat number.\n";
            }
            else if (bookedSeats.count(seat)) {
                cout << "Seat already booked.\n";
            }
            else {
                Passenger p{nextTicket++, name, seat};

                reservations[p.ticket] = p;
                bookedSeats.insert(seat);
                passengers.push_back(p);

                cout << "Booking successful!\n";
                cout << "Ticket number: " << p.ticket << endl;
            }
        }
        else if (choice == 2) {
            int ticket;
            cout << "Enter ticket number: ";
            cin >> ticket;

            auto it = reservations.find(ticket);

            if (it != reservations.end()) {
                bookedSeats.erase(it->second.seat);
                reservations.erase(it);

                passengers.erase(
                    remove_if(passengers.begin(), passengers.end(),
                        [ticket](const Passenger &p) {
                            return p.ticket == ticket;
                        }),
                    passengers.end());

                cout << "Ticket cancelled successfully.\n";
            } else {
                cout << "Ticket not found.\n";
            }
        }
        else if (choice == 3) {
            for (const auto &entry : reservations) {
                const Passenger &p = entry.second;

                cout << "Ticket: " << p.ticket
                     << " Name: " << p.name
                     << " Seat: " << p.seat << endl;
            }

            if (reservations.empty())
                cout << "No reservations available.\n";
        }
        else if (choice == 4) {
            cout << "Available seats: ";

            for (int seat = 1; seat <= 20; seat++) {
                if (!bookedSeats.count(seat))
                    cout << seat << " ";
            }

            cout << endl;
        }

    } while (choice != 5);

    return 0;
}
