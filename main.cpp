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


using std::string;

void metro_tests(){
    // Creates a metroline(linked list of metro stations)
    Line<MetroStation> metroline;
    
    // Creates 4 stations of given names
    metroline.add("Kabaty");
    metroline.add("Natolin");
    metroline.add("Imielin");
    metroline.print();
    
    // Creates metro with 20 places
    Metro* m1 = new Metro(20);
    
    // Adds conductor to the metro
    Conductor* c = new Conductor("Jan","Kowalski");
    m1->add_conductor(c);
    
    // Sets ticket for metro
    m1->set_ticket(1111,3.40,0.5);
    
    // Passenger creation without ticket and adding him to metro
    Passenger p = Passenger("Adam", "Kowalski", true, 100, Ticket());
    m1->add_passenger(p);
    m1->print();
    
    // Testing the check tickets function, passanger will be removed because he doesn't have correct ticket
    c->check_tickets();
    m1->print();
    p.buy_ticket(m1->get_ticket()); // buys a ticket
    m1->add_passenger(p);   //gets on metro
    c->check_tickets(); // doesn't get kicked because he has a ticket
    m1->print();
    
    //addition passangers
    m1->operator+=(Passenger("B","K"));
    m1->add_passenger("E","M");
    metroline[1]->add_passenger("B", "G");
    // adding metro onto the first station to the first position(out of 2)
    metroline[0]->add_metro(0,m1);
    m1->print();
    
    // moving metro across stations, moves to Natolin
    metroline[0]->move_metro(0);
    m1->print();
    
    // testing the function to move passanger from station to metro
    metroline[1]->print_passengers();
    m1->print();
    metroline[1]->pass_from_s_to_m(0, "B", "G");
    metroline[1]->print_passengers();
    m1->print();
    
    metroline[1]->move_metro(0);
    m1->print();
    
    // testing the function to move passanger from metro to station
    metroline[2]->pass_from_m_to_s(0, "Adam", "Kowalski");
    m1->print();
    metroline[2]->print_passengers();
    
    // end of the line, all passengers are moved to station
    metroline[2]->move_metro(0);
    metroline[2]->print_passengers();
}

void train_tests(){
    // Creating rail line linked list and adding 3 stations
    Line<RailStation> railline;
    railline.add("Warszawa");
    railline.add("Krakow");
    railline.add("Gdansk");
    railline.print();
    
    // Creating new High Speed Train, initialized with id and minimal locomotive speed
    // Adding the components of train
    HSTrain* hst = new HSTrain(54,40);
    Driver* dri = new Driver("Jan","Kowalski");
    Conductor* cond = new Conductor("Adam", "Kowalski");
    hst->add_loco(Locomotive(200, 30, 3));
    hst->set_ticket(234432,50.f,0.6);
    hst->add_driver(dri);
    hst->add_conductor(cond);
    hst->add_car(5);
    hst->add_car(5);
    
    // Passenger initialization
    Passenger p1 = Passenger("B", "G", 1, 200, Ticket());
    Passenger p2 = Passenger("E", "M", 0, 40, Ticket());
    RailCar* x = hst->operator[](0);
    x->add_passenger(p1);
    x = hst->operator[](1);
    x->add_passenger(p2);
    hst->print();
    
    // Conductor checking tickets, both removed because they don't have tickets
    cond->check_tickets();
    hst->print();
    
    // Example of exception while trying to buy a ticket with not enough money
    try {
        p2.buy_ticket(hst->get_ticket());
    } catch (std::exception& e) {
        std::cout <<'\n'<< e.what() << std::endl;
    }
    std::cout << "He needs " <<(hst->get_ticket()).get_price() - p2.get_money() <<'\n'<< std::endl;
    p2.add_money(10);                   // adding money so he can get the ticket
    p2.buy_ticket(hst->get_ticket());
    p1.buy_ticket(hst->get_ticket());
    x->add_passenger(p1);
    x->add_passenger(p2);
    hst->print();
    
    railline[0]->add_train(hst);
    railline[0]->print();
    
    // Exception for trying to move train when the locomotive doesn't have enough parameters for the train
    try {
        railline[0]->move_train(54, railline[1]);
    } catch (std::exception& e) {
        std::cout <<'\n'<< e.what() << std::endl;
    }
    // Need to remove locomotive and assign driver again
    hst->remove_loco();
    hst->add_loco(Locomotive(200,60,4));
    hst->add_driver(dri);
    railline[0]->move_train(54, railline[1]);
    railline[0]->print();
    railline[1]->print();
}
int main() {
    std::cout << "\nMetro tests: " << std::endl;
    metro_tests();
    std::cout << "\nTrain tests: " << std::endl;
    train_tests();
}
