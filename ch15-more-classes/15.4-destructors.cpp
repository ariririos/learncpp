#include <iostream>
#include <string>

class DataStore {
public:
    void add(std::string_view) {}
};

class NetworkData {
private:
    std::string m_server_name {};
    DataStore m_data_queue {};
public:
    NetworkData(std::string_view server_name)
        : m_server_name { server_name }
    {}

    ~NetworkData() {
        send_data();
    }

    void add_data(std::string_view data) {
        m_data_queue.add(data);
    }

    void send_data() {
        // connect to server, send all data, clear data
    }

};

class Simple {
private:
    int m_id {};
public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple(" << m_id << ")\n";
    }
    ~Simple() {
        std::cout << "Destructing Simple(" << get_id() << ")\n"; // calling member functions is fine since the object isn't destroyed until *after* this function has run
    }

    int get_id() const { return m_id; }
};

int main() {
    NetworkData n { "some_ip_address" };

    n.add_data("somedata1");
    n.add_data("somedata2");
    
    n.send_data(); // if explicitly calling send_data() is required before shutting down to actually send the data to the server, it should be in a destructor, especially since we could have conditionals here that exit the program early

    Simple simple1 { 1 };
    {
        Simple simple2 { 2 };
    } // simple2 dies here

    // remember that static variables (incl. globals and static locals) are constructed at program start and destroyed at program shutdown

    // adding ~NetworkData() obviates the need to call n.send_data() above

    // implicit destructors that do nothing are created if none is provided

    // if std::exit() is called or an unhandled exception occurs without stack unwinding, destructors *will not* run
    return 0;
} // simple1 dies here