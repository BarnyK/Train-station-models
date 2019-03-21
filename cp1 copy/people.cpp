#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>

#include "headers/tickets.hpp"
#include "headers/people.hpp"
#include "headers/vehicles.hpp"
using std::string;

// People constructors
People::People(){;}
People::People(string n, string s, string t){
    name = n;
    surname = s;
    type = t;
}

// Functions that return variables
string People::get_name(){return name;}
string People::get_surname(){return surname;}
string People::get_type(){return type;}

// Printing function for people
void People::print(){
    std::cout << "Name: " << name << std::endl;
    std::cout << "Surname: " << surname << std::endl;
}

// Constructors for Pasengers
Passenger::Passenger(string n, string s):People(n,s,"Passenger"){money=0;}

Passenger::Passenger(string n, string s, bool d):People(n,s,"Passenger"),discount{d}{
    money=0;
}

Passenger::Passenger(string n, string s, float m):People(n,s,"Passenger"),money{m}{
    discount=false;
}

Passenger::Passenger(string n, string s, Ticket ti):People(n,s,"Passenger"),t{ti}{
    money=0;
    discount = false;
}
Passenger::Passenger(string n, string s, bool d, float m, Ticket ti):People(n,s,"Passenger"),t{ti},discount{d},money{m}{}

// Passenger printing
void Passenger::print(){
    std::cout << name << " " << surname << " " << std::endl;
}

// Get functions for passenger
float Passenger::get_money(){return money;}
Ticket Passenger::get_ticket(){return t;}

// Operations on money variable
void Passenger::add_money(float x){
    if(money+x>=0){
        money+=x;
    }
    else{
        throw less_than_zero();
    }
}

void Passenger::set_money(float x){
    if(x>=0){
        money = x;
    }
    else{
        throw less_than_zero();
    }
}

void Passenger::subtract_money(float x){
    if(money-x>=0){
        money-=x;
    }
    else{
        throw less_than_zero();
    }
}

void Passenger::buy_ticket(Ticket ti){
    if(discount){
        if(money - ti.get_dprice() < 0){
            throw money_exception();
        }
        else{
            money-=ti.get_dprice();
            t = ti;
        }
    }
    else{
        if(money - ti.get_price() < 0){
            throw money_exception();
        }
        else{
            money-=ti.get_price();
            t = ti;
        }
    }
}

// Conductor constructors
Conductor::Conductor(){
    train = nullptr;
    metro = nullptr;
}
Conductor::Conductor(string n, string s):People(n,s,"Conductor"){
    train = nullptr;
    metro = nullptr;
}

// Assignment function for Metro
void Conductor::assign(Metro* x){
    if(metro==nullptr && train==nullptr)
        metro = x;
    else{
        throw assignment_exception();
    }
}

// Assignment function for Train
void Conductor::assign(Train* x){
    if(metro==nullptr && train==nullptr)
        train = x;
    else{
        throw assignment_exception();
    }
}

// Removes assignments that might exist
void Conductor::remove_assignment(){
    train = nullptr;
    metro = nullptr;
}

// Function makes the conductor check passengers in the train for tickets
// If an individual doesn't have a proper ticket he is removed from the train
void Conductor::check_tickets(){
    if(train!=nullptr){
        RailCar* tmp = train->head;
        while(tmp){
            string removal[tmp->places][2];
            int i =0;
            int removed=0;
            for(std::vector<Passenger>::iterator it = tmp->p_list.begin(); it != tmp->p_list.end(); it++){
                if(it->get_ticket() != train->t){
                    removal[i][0] = it->get_name();
                    removal[i][1] = it->get_surname();
                    removed++;
                }
            }
            for(i=0;i<removed;i++)
                tmp->remove_passenger(removal[i][0], removal[i][1]);
            tmp = tmp->next;
        }
    }
    else if(metro!=nullptr){
        string removal[metro->places][2];
        int i =0;
        int removed=0;
        for(std::vector<Passenger>::iterator it = metro->p_list.begin(); it != metro->p_list.end(); it++){
            if(it->get_ticket() != metro->ticket){
                removal[i][0] = it->get_name();
                removal[i][1] = it->get_surname();
                removed++;
            }
        }
        for(i=0;i<removed;i++)
            metro->remove_passenger(removal[i][0], removal[i][1]);
    }
}

// Driver constructors
Driver::Driver():People(){};
Driver::Driver(string n, string s):People(n,s,"Driver"){
    loco = nullptr;
}

// Assignment function
void Driver::assign(Locomotive* x){
    if(loco==nullptr)
        loco = x;
    else
        throw assignment_exception();
}
void Driver::remove_assignment(){
    loco = nullptr;
}
