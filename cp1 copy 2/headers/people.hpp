#ifndef people_hpp
#define people_hpp

using std::string;

struct money_exception: public std::exception{
    char* what() const throw(){
        return (char*)"Value of money parameter can't be less than 0";
    }
};

struct assignment_exception: public std::exception{
    char* what() const throw(){
        return (char*)"Can't assign to 2 different vehicles";
    }
};

struct conductor_not_assigned: public std::exception{
    char* what() const throw(){
        return (char*)"Conductor can't check tickets if he is not assigned";
    }
};
struct duplicate_exception: public std::exception{
    char* what() const throw(){
        return (char*)"Can't add duplicate passenger to the list";
    }
};
struct no_such_passanger: public std::exception{
    char* what() const throw(){
        return (char*)"There is no passanger of given name in the list";
    }
};

class People{
protected:
    string name;
    string surname;
    string type;
public:
    People();
    People(string n, string s, string t);
    string get_name();
    string get_surname();
    string get_type();
    void print();
};

class Passenger: public People{
private:
    bool discount;
    float money;
    Ticket t;
public:
    Passenger(string n, string s);
    Passenger(string n, string s, bool d);
    Passenger(string n, string s, float m);
    Passenger(string n, string s, Ticket t);
    Passenger(string n, string s, bool d, float m, Ticket ti);
    void print();
    float get_money();
    Ticket get_ticket();
    void add_money(float);
    void set_money(float x);
    void subtract_money(float x);
    void buy_ticket(Ticket);       
};


class Train;
class Metro;
class Conductor: public People{
private:
    Train *train;
    Metro *metro;
public:
    Conductor();
    Conductor(string n, string s);
    
    void assign(Metro*);        // assigns metro
    void assign(Train*);        // assigns train
    void remove_assignment();   // removes assignment from either metro or train
    void check_tickets();       // checks tickets on train/metro
    
    friend class Train;
};


class Locomotive;
class Driver: public People{
private:
    Locomotive* loco;
public:
    Driver();
    Driver(string n, string s);
    
    void assign(Locomotive*);   // adds assignment to locomotive
    void remove_assignment();   // removes assignment to locomotive
    
    friend class Train;
    friend class Metro;
};

#endif /* people_hpp */
