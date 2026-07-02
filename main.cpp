#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "Ticket.h"

using namespace std;

vector<Ticket> tickets;

void loadTickets()
{
    tickets.clear();

    ifstream file("tickets.txt");

    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        Ticket t;

        getline(ss, t.name, '|');
        getline(ss, t.issue, '|');
        getline(ss, t.time, '|');

        string status;
        getline(ss, status);

        t.resolved = (status == "1");

        tickets.push_back(t);
    }

    file.close();
}

void saveTickets()
{
    ofstream file("tickets.txt");

    for (const auto& t : tickets)
    {
        file
            << t.name << "|"
            << t.issue << "|"
            << t.time << "|"
            << t.resolved
            << endl;
    }

    file.close();
}

void createTicket()
{
    Ticket t;

    cin.ignore();

    cout << "Employee Name: ";
    getline(cin, t.name);

    cout << "Issue: ";
    getline(cin, t.issue);

    cout << "Time: ";
    getline(cin, t.time);

    t.resolved = false;

    tickets.push_back(t);

    saveTickets();

    cout << "\nTicket created.\n\n";
}

void viewTickets()
{
    if (tickets.empty())
    {
        cout << "\nNo tickets.\n\n";
        return;
    }

    cout << "\n====== Tickets ======\n\n";

    for (int i = 0; i < tickets.size(); i++)
    {
        cout << "Ticket #" << i + 1 << endl;
        cout << "Name: " << tickets[i].name << endl;
        cout << "Issue: " << tickets[i].issue << endl;
        cout << "Time: " << tickets[i].time << endl;
        cout << "Status: ";

        if (tickets[i].resolved)
            cout << "Resolved";
        else
            cout << "Open";

        cout << "\n----------------------\n";
    }

    cout << endl;
}

void resolveTicket()
{
    viewTickets();

    if (tickets.empty())
        return;

    int choice;

    cout << "Ticket Number: ";
    cin >> choice;

    if (choice < 1 || choice > tickets.size())
    {
        cout << "Invalid ticket.\n";
        return;
    }

    tickets[choice - 1].resolved = true;

    saveTickets();

    cout << "Ticket resolved.\n\n";
}

int main()
{
    loadTickets();

    int option;

    while (true)
    {
        cout << "==== Ticket Logger ====\n";
        cout << "1. Create Ticket\n";
        cout << "2. View Tickets\n";
        cout << "3. Resolve Ticket\n";
        cout << "4. Exit\n\n";

        cout << "Choice: ";
        cin >> option;

        switch (option)
        {
            case 1:
                createTicket();
                break;

            case 2:
                viewTickets();
                break;

            case 3:
                resolveTicket();
                break;

            case 4:
                return 0;

            default:
                cout << "Invalid option.\n\n";
        }
    }
}
