#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <exception>
#include <vector>

#include "headers/templates.hpp"
#include "headers/tickets.hpp"
#include "headers/people.hpp"
#include "headers/places.hpp"
#include "headers/vehicles.hpp"



// Locomotive constructors
Locomotive::Locomotive(){
    driver = nullptr;
    max_dist = -1;
    speed = -1;
    max_pull = -1;
}

Locomotive::Locomotive(int md, int s, int p){
    driver = nullptr;
    max_dist = md;
    speed = s;
    max_pull = p;
}

// returns true if there is a driver assigned
bool Locomotive::has_driver(){
    if(driver!=nullptr){
        return true;
    }
    else{
        return false;
    }
}

// assignment for driver
void Locomotive::assign_driver(Driver* d){
    if(driver != nullptr)
        throw assignment_exception();
    driver = d;
    driver->assign(this);
}

void Locomotive::remove_driver(){
    driver->remove_assignment();
    driver=nullptr;
}

int Locomotive::get_md(){ return max_dist;}
int Locomotive::get_speed(){ return speed;}
int Locomotive::get_pull(){ return max_pull;}

void Locomotive::print(){
    if(this->has_driver()){
        std::cout << "Driver: " << driver->get_name() << " " << driver->get_surname() << std::endl;
    }
    else{
        std::cout << "No driver" << std::endl;
    }
    std::cout << "Max distance: " << max_dist << std::endl;
    std::cout << "Speed: " << speed << std::endl;
    std::cout << "Max pull: " << max_pull << std::endl;
}

bool Locomotive::operator==(const Locomotive& x){
    if(max_dist!=x.max_dist)
        return false;
    if(max_pull!=x.max_pull)
        return false;
    if(speed!=x.speed)
        return false;
    return true;
}

bool Locomotive::operator!=(const Locomotive& x){
    if(*this==x)
        return false;
    return true;
}
// RailCar constructor
RailCar::RailCar(int p){
    if(p<0)
        throw less_than_zero();
    places = p;
    next = nullptr;
}

void RailCar::add_passenger(Passenger x){
    p_list.push_back(x);
}

void RailCar::add_passenger(string n, string s){
    p_list.push_back(Passenger(n,s));
}

void RailCar::remove_passenger(string n, string s){
    Passenger tmp = Passenger(n,s);
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        if(it->get_name() == n and it->get_surname() == s){
            p_list.erase(it);
            break;
        }
    }
}

void RailCar::remove_all_passengers(){
    p_list.clear();
}

RailCar RailCar::operator+(const Passenger &x){
    RailCar result = *this;
    result.add_passenger(x);
    return result;
}

RailCar& RailCar::operator+=(const Passenger &x){
    this->add_passenger(x);
    return *this;
}

void RailCar::print_passangers(){
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        it->print();
    }
}

// Train constructor
Train::Train(int i, string t){
    cond = nullptr;
    id = i;
    type = t;
    head = nullptr;
}

Train::~Train(){
    RailCar* tmp = head;
    while(tmp){
        tmp = tmp->next;
        delete tmp;
    }
    loco.remove_driver();
    remove_cond();
}

// Train printing function
void Train::print(){
    std::cout << type << std::endl;
    loco.print();
    t.print();
    if(check_cond())
        cond->print();
    else
        std::cout<<"No conductor" <<std::endl;
    RailCar* tmp = head;
    int c = 1;
    while(tmp){
        std::cout << "Car no " << c++ <<std::endl;
        tmp->print_passangers();
        tmp = tmp->next;
    }
}

// checks if there exists a locomotive
bool Train::check_loco(){
    if(loco == Locomotive())
       return false;
    return true;
}
// checks if there is a driver assigned
bool Train::check_driver(){
    if(loco.has_driver())
        return true;
    return false;
}

// check if there is a conductor
bool Train::check_cond(){
    if(cond == nullptr)
        return false;
    else
        return true;
}

// checks if the locomotive has enough pull for the number of attached cars
bool Train::check_pull(){
    if(this->check_loco()){
        if(this->count_cars() <= loco.get_pull())
            return true;
    }
    return false;
}

// evokes all the other check functions for the train
bool Train::check(){
    if(check_loco() && check_pull() && check_cond() && check_driver())
        return true;
    else
        return false;
}

// sets the ticket for the train
void Train::set_ticket(Ticket ti){
    t = ti;
}

// sets ticked by arguments
void Train::set_ticket(int c, float p, float dp){
    t = Ticket(c,p,dp);
}

Ticket Train::get_ticket(){return t;}

// adds a RailCar to the end of the linked list
void Train::add_car(RailCar x){
    if(!head){
        head = new RailCar(x);
    }
    else{
        RailCar* tmp = head;
        while(tmp->next){
            tmp = tmp->next;
        }
        tmp->next = new RailCar(x);
    }
}

void Train::add_car(int p){
    this->add_car(RailCar(p));
}

// removes a railcar from linked list
void Train::remove_car(int i){
    RailCar* tmp = head;
    RailCar* prev = head;
    if(i == 0){
        tmp = head->next;
        delete head;
        head = tmp;
    }
    else{
        for(int c=0;c<i;c++){
            prev = tmp;
            tmp = tmp->next;
            if(tmp->next == nullptr)
                break;
        }
        if(tmp!=nullptr){
            prev->next = tmp->next;
            delete tmp;
        }
    }
}

// returns a number of railcars in array
int Train::count_cars(){
    int count = 0;
    RailCar* tmp = head;
    while(tmp){
        count+=1;
        tmp = tmp->next;
    }
    return count;
}

RailCar* Train::operator[](int i){
    RailCar* tmp = head;
    for(int c=0;c<i;c++){
        if(!tmp)
            break;
        tmp = tmp->next;
    }
    return tmp;
}
// adds a locomotive to the train
void Train::add_loco(Locomotive x){
    loco = x;
}

// removes a locomotive from the train
void Train::remove_loco(){
    loco.remove_driver();
    loco = Locomotive();
}

// adds a conductor to the train
void Train::add_conductor(Conductor* x){
    x->train = this;
    cond = x;
}

// removes conductor
void Train::remove_cond(){
    cond->remove_assignment();
    cond = nullptr;
}

// adds a driver
void Train::add_driver(Driver* x){
    loco.assign_driver(x);
}
void Train::remove_driver(){
    loco.remove_driver();
}

// High speed train constructor
HSTrain::HSTrain(int i, int m):Train(i,"High Speed"){
    minspeed = m;
}

// checks the minimal value of speed
bool HSTrain::check_speed(){
    if(this->check_loco()){
        if(minspeed < loco.get_speed())
            return true;
    }
    return false;
}

// evokes all the check functions
bool HSTrain::check(){
    if(check_speed() && check_driver() && check_cond() && check_pull())
        return true;
    return false;
}

//
void HSTrain::modify(int i, int ms){
    if(ms<0)
        throw less_than_zero();
    id = i;
    
    minspeed = ms;
}

LDTrain::LDTrain(int i, int t):Train(i,"Long Distance"){
    if(t<0)
        throw less_than_zero();
    dist = t;
}

// checks if value of maximal distance on locomotive is higher than distance for train
bool LDTrain::check_dist(){
    if(this->check_loco()){
        if(dist < loco.get_md())
            return true;
    }
    return false;
}

// evokes all other check functions
bool LDTrain::check(){
    if(check_dist() && check_driver() && check_cond() && check_pull())
        return true;
    return false;
}

// function to modify value
void LDTrain::modify(int i, int d){
    if(dist<0)
        throw less_than_zero();
    dist = d;
    id = i;
}

// Short distance train constructor
SDTrain::SDTrain(int i, int md, int ms):Train(i,"Short Distance"){
    max_dist = md;
    max_speed = ms;
}

// checks if the train max distance is higher than locomotives distance
bool SDTrain::check_dist(){
    if(this->check_loco()){
        if(max_dist > loco.get_md())
            return true;
    }
    return false;
}

// checks if the trains max speed is higher than assigned locomotives
bool SDTrain::check_speed(){
    if(this->check_loco()){
        if(max_speed > loco.get_speed())
            return true;
    }
    return false;
}

// calls all the check functions
bool SDTrain::check(){
    if(check_dist() && check_speed() && check_driver() && check_cond() && check_pull())
        return true;
    return false;
}

// modifies the values specific to short distance trains
void SDTrain::modify(int i, int md, int ms){
    if(i!=0)
        id = i;
    max_dist = md;
    max_speed = ms;
}

// Metro constructors
Metro::Metro(){
    places = 0;
    station = nullptr;
}
Metro::Metro(int p){
    places = p;
    station = nullptr;
}
Metro::~Metro(){
    remove_conductor();
    if(station->first == this)
        station->remove_metro(0);
    else if(station->second == this)
        station->remove_metro(1);
    station = nullptr;
}

void Metro::print(){
    std::cout << "\nMetro" << std::endl;
    if(station!=nullptr)
        std::cout << "Station: " << station->get_name() << std::endl;
    if(cond!=nullptr)
        std::cout << "Conductor: " << cond->get_name() << " " << cond->get_surname() << std::endl;
    ticket.print();
    std::cout << "Passengers:" << std::endl;
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        it->print();
    }
}

// functions to manage passangers vector
void Metro::add_passenger(Passenger x){
    p_list.push_back(x);
}
void Metro::add_passenger(string n, string s){
    p_list.push_back(Passenger(n,s));
}
void Metro::remove_passenger(string n, string s){
    Passenger tmp = Passenger(n,s);
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        if(it->get_name() == n and it->get_surname() == s){
            p_list.erase(it);
            break;
        }
    }
}
void Metro::remove_all_passengers(){
    p_list.clear();
}
// Tickets operations
void Metro::set_ticket(Ticket t){
    ticket = t;
}
void Metro::set_ticket(int c, float p, float dp){
    ticket = Ticket(c,p,dp);
}
// overloaded operators for easier addition
Metro Metro::operator+(const Passenger &x){
    Metro result = *this;
    result.add_passenger(x);
    return result;
}

Metro& Metro::operator+=(const Passenger &x){
    this->add_passenger(x);
    return *this;
}

// conductor managment 
void Metro::add_conductor(Conductor* c){
    cond = c;
    c->assign(this);
    
}
void Metro::remove_conductor(){
    cond->remove_assignment();
    cond = nullptr;
}

void Metro::empty_to_station(){
    if(station->first != this && station->second != this){
        station = nullptr;
        throw empty_metro_exception();
    }
    
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        station->add_passenger(*it);
    }
    p_list.clear();
}
