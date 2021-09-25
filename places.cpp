#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>

#include "headers/templates.hpp"
#include "headers/tickets.hpp"
#include "headers/people.hpp"
#include "headers/vehicles.hpp"
#include "headers/places.hpp"


Station::Station(){
    id = -1;
    name = "";
    type = "";
    next = nullptr;
    prev = nullptr;
}

Station::Station(int i,string n, string t){
    id = i;
    name = n;
    type = t;
    next = nullptr;
    prev = nullptr;
}

void Station::change_name(string n){
    name = n;
}

void Station::add_passenger(Passenger x){
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        if(it->get_name() == x.get_name() and it->get_surname() == x.get_surname()){
            throw duplicate_exception();
        }
    }
    p_list.push_back(x);
}

void Station::add_passenger(string n, string s){
    this->add_passenger(Passenger(n,s));
}
void Station::remove_passenger(string n, string s){
    Passenger tmp = Passenger(n,s);
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        if(it->get_name() == n and it->get_surname() == s){
            p_list.erase(it);
            break;
        }
    }
}

void Station::remove_all_passengers(){
    p_list.clear();
}

MetroStation::MetroStation(int i,string n):Station(i,n,"MetroStation"){
    first = nullptr;
    second = nullptr;
}

MetroStation::~MetroStation(){
    delete first;
    delete second;
}

bool MetroStation::isFree(int pos){
    if((pos==0 && first!=nullptr) || (pos==1 && second!=nullptr))
        return false;
    else if(pos!=0 && pos!=1){
        std::cout << "No such position as " << pos << std::endl;
        return false;
    }
    else
        return true;
}

void MetroStation::add_metro(int pos, Metro* m){
    if(pos==0){
        if(isFree(pos)){
            first = m;
            m->station = this;
        }
        else
            std::cout << "Position taken\n";
    }
    else if(pos==1)
        if(isFree(pos)){
            second = m;
            m->station = this;
        }
        else
            std::cout << "Position taken\n";
    else{
        throw metro_positions_exception();
    }
}

void MetroStation::add_metro(int pos, int places){
    this->add_metro(pos, new Metro(places));
}

void MetroStation::remove_metro(int pos){
    if(pos==0)
        first = nullptr;
    if(pos==1)
        second = nullptr;
}

void MetroStation::move_metro(int pos){
    if(pos!=0 && pos != 1)
        throw metro_positions_exception();
    Metro* x;
    MetroStation* dest;
    if(pos==0){
        x = first;
        dest = (MetroStation*)next;
    }
    else{
        x= second;
        dest = (MetroStation*)prev;
    }
    if(x==nullptr)
        throw metro_not_exists();
    // in case it's the last station
    if(dest == nullptr){
        x->empty_to_station();
        delete x;
    }
    else{
        dest->add_metro(pos,x);
    }
    if(pos==0)
        first = nullptr;
    else
        second = nullptr;
}
Metro* MetroStation::operator[](int i){
    if(i==0)
        return first;
    else if(i==1)
        return second;
    else
        throw metro_positions_exception();
}

void MetroStation::print_passengers(){
    std::cout << '\n' <<name << std::endl;
    std::cout << "Passengers:" << std::endl;
    for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
        it->print();
    }
}

// Function that moves passenger from metro to station
void MetroStation::pass_from_m_to_s(int p, string n, string s){
    Metro* x;
    if(p==0){
        x = first;
    }
    else if(p==1){
        x = second;
    }
    else{
        throw metro_positions_exception();
    }
    if(x==nullptr)
        throw metro_not_exists();
    else{
        bool found = false;
        for(std::vector<Passenger>::iterator it = x->p_list.begin(); it != x->p_list.end(); it++){
            if(it->get_name() == n && it->get_surname() == s){
                this->add_passenger(*it);
                x->p_list.erase(it);
                found = true;
                break;
            }
        }
        if(!found)
            throw no_such_passanger();
    }
}

// Function that moves passenger from station to metro
void MetroStation::pass_from_s_to_m(int p, string n, string s){
    Metro* x;
    if(p==0){
        x = first;
    }
    else if(p==1){
        x = second;
    }
    else{
        throw metro_positions_exception();
    }
    if(x==nullptr)
        throw metro_not_exists();
    else{
        bool found = false;
        for(std::vector<Passenger>::iterator it = p_list.begin(); it != p_list.end(); it++){
            if(it->get_name() == n && it->get_surname() == s){
                x->add_passenger(*it);
                p_list.erase(it);
                found = true;
                break;
            }
        }
        if(!found)
            throw no_such_passanger();
    }
}
RailStation::RailStation(int i, string n):Station(i,n,"RailStation"){
    for(int i=0;i<MAX_TRAINS;i++){
        trains[i] = nullptr;
    }
}

void RailStation::add_train(Train *x){
    int fs = first_free_space();
    if(fs==-1)
        throw station_no_free_space();
    if(find_train(x->id)== -1)
        trains[fs] = x;
    else
        throw train_id_exception();
}

int RailStation::find_train(int z){
    for(int i=0;i<MAX_TRAINS;i++){
        if(trains[i]!=nullptr && trains[i]->id == z){
            return i;
        }
    }
    return -1;
}

int RailStation::first_free_space(){
    for(int i=0;i<MAX_TRAINS;i++){
        if(trains[i]==nullptr){
            return i;
        }
    }
    return -1;
}

Train* RailStation::operator[](int i){
    return trains[i];
}

void RailStation::print(){
    std::cout <<'\n' <<name << std::endl;
    for(int i=0;i<MAX_TRAINS;i++){
        if(trains[i]!=nullptr){
            std::cout << "\tTrain " << trains[i]->id  <<std::endl;
            trains[i]->print();
        }
    }
}

void RailStation::remove_train(int d){
    trains[d] = nullptr;
}

// deletes th train object
void RailStation::erase_train(int d){
    delete trains[d];
    trains[d] = nullptr;
}
// moves trains across stations
void RailStation::move_train(int i, RailStation* dest){
    int f = find_train(i);
    if(f != -1){
        if(dest == nullptr)
            throw dest_not_exists();
        if(trains[f]->type == "High Speed"){
            HSTrain* t = (HSTrain*)trains[f];
            if(t->check()){
                dest->add_train(t);
                this->remove_train(f);
            }
            else
                throw bad_train();
        }
        else if(trains[f]->type == "Long Distance"){
            LDTrain* t = (LDTrain*)trains[f];
            if(t->check()){
                dest->add_train(t);
                this->remove_train(i);
            }
            else{
                throw bad_train();
            }
        }
        else if(trains[f]->type == "Short Distance"){
            SDTrain* t = (SDTrain*)trains[f];
            if(t->check()){
                dest->add_train(t);
                this->remove_train(i);
            }
            else
                throw bad_train();
        }
        else{
            Train* t = trains[f];
            if(t->check()){
                dest->add_train(t);
                this->remove_train(i);
            }
            else{
                throw bad_train();
            }
        }
    }
    else{
        throw train_not_exists();
    }
}
