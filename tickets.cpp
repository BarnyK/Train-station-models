#include <iostream>
#include <stdio.h>
#include <string>
#include <exception>
#include <vector>

#include "headers/tickets.hpp"

using std::string;

// Constructors
Ticket::Ticket(){
    code = -1;
    price = -1;
    discount_percent = 0;
}
// When a ticket jas no discount bonus
Ticket::Ticket(int c, float p){
    code = c;
    price = p;
    discount_percent = 0;
}
//
Ticket::Ticket(int c, float p, float dp){
    if(dp > 1)
        throw out_of_range();
    code = c;
    price = p;
    discount_percent = dp;
}

void Ticket::print(){
    std::cout << "Ticket: "<< code << ", " << price <<",  " << discount_percent << std::endl;
}

int Ticket::get_code(){ return code;}
float Ticket::get_price(){ return price;}
float Ticket::get_discount(){ return discount_percent;}
float Ticket::get_dprice(){ return discount_percent*price;}

bool Ticket::operator==(Ticket x){
    if((code == x.code) && (price == x.price) && (discount_percent == x.discount_percent))
        return true;
    return false;
}
bool Ticket::operator!=(Ticket x){
    if(*this == x)
        return false;
    return true;
}
