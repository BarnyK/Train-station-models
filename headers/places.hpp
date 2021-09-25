#ifndef places_hpp
#define places_hpp

#define MAX_TRAINS 5

using std::string;
using std::vector;

struct station_no_free_space: public std::exception{
    char* what() const throw(){
        return (char*)"There is no empty space for the train on specified station";
    }
};

struct train_id_exception: public std::exception{
    char* what() const throw(){
        return (char*)"Can't add trains with the same id onto 1 station";
    }
};
struct dest_not_exists: public std::exception{
    char* what() const throw(){
        return (char*)"Given destination is null";
    }
};
struct metro_positions_exception: public std::exception{
    char* what() const throw(){
        return (char*)"No such metro position, function take either 0 or 1 as arugment";
    }
};
struct metro_not_exists: public std::exception{
    char* what() const throw(){
        return (char*)"Specified metro doesn't exist";
    }
};
struct position_taken: public std::exception{
    char* what() const throw(){
        return (char*)"Metro position taken";
    }
};


class RailStation;
class MetroStation;
class Station{
protected:
    int id;
    string name;
    string type;
    Station *next;
    Station *prev;
    vector<Passenger> p_list;
public:
    Station();
    Station(int id, string name, string type);
    string get_name(){return name;}
    void change_name(string name);                      // changes name
    void add_passenger(Passenger);                      // adds Passenger from object
    void add_passenger(string name, string surname);    // adds Passenger by creating a new one
    void remove_passenger(string name, string surname); // removes Passenger by name and surname
    void remove_all_passengers();                       // removes all passenger from the train
    friend class Line<Station>;
    friend class Line<RailStation>;
    friend class Line<MetroStation>;
};

class MetroStation: public Station{
private:
    Metro* first;
    Metro* second;
public:
    MetroStation(int id,string name);
    ~MetroStation();
    
    bool isFree(int pos);                   // returns true if the pos is free
    void add_metro(int pos, Metro*);        // adds metro from pointer
    void add_metro(int pos, int places);    // adds metro by creating new one
    void remove_metro(int pos);             // removes metro
    void move_metro(int pos);               // moves metro to the next station
    void print_passengers();                // prints list of passengers on the station
    // dunctions for moving passengers from metro to station and other way
    void pass_from_s_to_m(int pos, string name, string surname);
    void pass_from_m_to_s(int pos, string name, string surname);
    Metro* operator[](int i);               // returns metro from position 0 or 1
    friend class Metro;
    friend class Line<MetroStation>;
};

class RailStation: public Station{
private:
    Train* trains[MAX_TRAINS];  // macro defined MAX_TRAINS
public:
    RailStation(int id, string name);
    void print();
    void add_train(Train*);     // adds pointer to train to array
    void remove_train(int id);  // removes pointer to train
    void erase_train(int d);    // removes the train completely
    int find_train(int id);     // returns position of train with id in array
    int first_free_space();     // return first free space in array of trains
    void pass_from_t_to_s(int id, string name, string surname); // takes a passenger from train and puts it at station
    void pass_from_s_to_t(int id, string name, string surname); // takes a passenger from station and puts it in trian
    void move_train(int i, RailStation* dest);  // moves train to the other station
    Train* operator[](int i);
    friend class Train;
    friend class Line<RailStation>;
};


#endif /* places_hpp */
