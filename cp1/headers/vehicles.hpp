#ifndef vehicles_hpp
#define vehicles_hpp

using std::string;
using std::vector;

struct less_than_zero: public std::exception{
    char* what() const throw(){
        return (char*)"Value can't be less than zero";
    }
};

struct train_not_exists: public std::exception{
    char* what() const throw(){
        return (char*)"Train of that id doesn't exist";
    }
};

struct bad_train: public std::exception{
    char* what() const throw(){
        return (char*)"Train doesn't have correct parameters";
    }
};

struct empty_metro_exception: public std::exception{
    char* what() const throw(){
        return (char*)"Can't empty metro to the station that doesn't contain it";
    }
};

class Locomotive{
private:
    Driver *driver;
    int max_dist;
    int speed;
    int max_pull;
public:
    Locomotive();   
    Locomotive(int md, int s, int p);
    int get_md();
    int get_speed();
    int get_pull();
    bool has_driver();
    void assign_driver(Driver*);
    void remove_driver();
    void print();  
    bool operator==(const Locomotive&);
    bool operator!=(const Locomotive&);
};


class RailCar{
private:
    int places;
    RailCar *next;
    vector<Passenger> p_list;
public:
    RailCar(int p); //done

    void add_passenger(Passenger);  //done
    void add_passenger(string name, string surname);    //done
    void remove_passenger(string name, string surname); //done
    void remove_all_passengers();   //done
    RailCar operator+(const Passenger&);    //done
    RailCar& operator+=(const Passenger&);  //done
    void print_passangers();    //done
    friend class Train;
    friend class Conductor;
};

class Train{
protected:
    int id;
    string type;
    Locomotive loco;
    RailCar *head;
    Conductor* cond;
    Ticket t;
public:
    Train(int id,string type);
    ~Train();
    bool check_loco(); 
    bool check_driver();
    bool check_cond();
    bool check_pull();
    
    void print();
    void set_ticket(Ticket t);
    void set_ticket(int c, float p, float dp);
    Ticket get_ticket();
    
    void add_car(RailCar);
    void add_car(int p);
    void remove_car(int id);
    int count_cars();
    RailCar* operator[](int i);
    void add_loco(Locomotive);
    void remove_loco();
    void add_conductor(Conductor*);
    void remove_cond();
    void add_driver(Driver*);
    void remove_driver();
    
    virtual bool check();
    friend class RailStation;
    friend class Conductor;
};

class HSTrain: public Train{
private:
    int minspeed;
public:
    HSTrain(int id, int minspeed);
    void modify(int i, int ms);
    bool check_speed();
    bool check();
};

class LDTrain: public Train{
private:
    int dist;
public:
    LDTrain(int id,int dist);
    void modify(int i, int d);
    bool check_dist();
    bool check();
};

class SDTrain: public Train{
private:
    int max_dist;
    int max_speed;
public:
    SDTrain(int id, int md, int ms);
    void modify(int i, int md, int ms);
    bool check_dist();
    bool check_speed();
    bool check();   
};

class MetroStation;
class Metro{
private:
    Ticket ticket;
    int places;
    vector<Passenger> p_list;
    Conductor* cond;
    MetroStation * station;
public:
    Metro();
    Metro(int p);
    ~Metro();
    
    Ticket get_ticket(){return ticket;}
    void print();
    void add_passenger(Passenger);                      // adds passenger by given object
    void add_passenger(string name, string surname);    // adds passenger by name
    void remove_passenger(string name, string surname); // removes specified passenger
    void remove_all_passengers();                       // removes all passengers from list
    void set_ticket(Ticket);                            // sets the ticket
    void set_ticket(int code, float price, float dp);   // sets values of ticket
    // overloaded operators for ease of use
    Metro operator+(const Passenger&);
    Metro& operator+=(const Passenger&);            
    void empty_to_station();                            // removes all passengers and puts them on station
    void add_conductor(Conductor*);                     // adds conductor and assigns it
    void remove_conductor();                            // removes conductor assignment
    friend class Conductor;
    friend class MetroStation;
};
#endif /* vehicles_hpp */
