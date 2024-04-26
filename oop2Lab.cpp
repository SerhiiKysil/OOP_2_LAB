#include <iostream>
#include <string>
#include <list>
#include <array>

using namespace std;

const int HASH_TABLE_SIZE = 10;

struct ClientInfo {
    string car_number;
    string owner_name;
    string contact_details;
};

class HashTable {
private:
    array<list<ClientInfo>, HASH_TABLE_SIZE> table;

    int hashFunction(string car_number) {
        size_t sum = 0;
        for (size_t i = 0; i < car_number.length(); i++) {
            sum += static_cast<int>(car_number[i]); 
        }
        return sum % HASH_TABLE_SIZE;
    }

public:
    void insert(string car_number, string owner_name, string contact_details) {
        int index = hashFunction(car_number);
        ClientInfo clientInfo = {car_number, owner_name, contact_details};
        table[index].push_back(clientInfo);
    }

    ClientInfo* search(string car_number) {
        int index = hashFunction(car_number);
        for (auto &client : table[index]) {
            if (client.car_number == car_number) {
                return &client;
            }
        }
        return nullptr;
    }

    bool remove(string car_number) {
        int index = hashFunction(car_number);
        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->car_number == car_number) {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            cout << "Num " << i << ": ";
            for (auto &client : table[i]) {
                cout << "[" << client.car_number << " - " << client.owner_name << " - " << client.contact_details << "] ";
            }
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    ht.insert("BC6666BB", "Barna Andrew", "0950459747");
    ht.insert("BT2110AM", "Kysil Serhii", "0956230356");
    ht.insert("BT2119AM", "Kysil Serhii", "0956230356");
    ht.insert("BT2510AM", "Kysil Serhii", "0956230356");
    ht.display();

    if (auto client = ht.search("BC6666BB")) {
        cout << "Client found: " << client->owner_name << endl;
    }

    if (ht.remove("BC6666BB")) {
        cout << "Client removed." << endl;
    }

    ht.display();

    return 0;
}
