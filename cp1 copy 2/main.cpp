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
    HSTrain* hst = new HSTrain(54,40);
    hst->add_loco(Locomotive(200, 30, 3));
    hst->set_ticket(234432,50.f,0.6);
    Driver* dri = new Driver("Jan","Kowalski");
    Conductor* cond = new Conductor("Adam", "Kowalski");
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
        std::cout << e.what() << std::endl;
    }
    p2.add_money(50);                   // adding money so he can get the ticket
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
        std::cout << e.what() << std::endl;
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
    train_tests();
}






//        LDTrain t = LDTrain(0,19);  //id min speed
//        t.set_ticket(Ticket(4,4,0.5));
//        t.add_car(5);
//        t.add_car(5);
//        t.add_car(5);
//        t.add_conductor(Conductor("Barny","Krupowicz"));
//        Locomotive f = Locomotive(5,20,5);
//        Driver* kap = new Driver("Barny","Krupowski");
//        f.assign_driver(kap);
//        t.add_loco(f);
//        bool k = t.check();
//        if(k)
//            std::cout << "True\n";
//        else
//            std::cout << "False\n";
//        Station *x = new Station("metro", "kabaty");
//        x->change_name("natolin");
//        x->add_passenger(Passenger("b","K"));
//        Line<Station> x("asdf");
//        MetroStation *stat1 = new MetroStation("Kabaty");
//        Metro* m = new Metro(5);
//        m->add_passenger("b","k");
//        m->add_conductor(Conductor("b","j"));
//        stat1->add_metro(0, m);
//        stat1->add_metro(0);
//        stat1->remove_metro(0);
//        stat1->add_metro(0);


/*
// Creating rail line
Line<RailStation> railline;

// Creating Station
RailStation* st = new RailStation(1,"Warszawa");
RailStation* sd = new RailStation(2,"Krakow");
railline.add(st);
railline.add(sd);
// Creating high speed train
HSTrain* t1 = new HSTrain(1,20);
Conductor* cond = new Conductor("Adam","Kowalski");
t1->set_ticket(2343,200,0.5);
t1->add_conductor(cond);
t1->add_loco(Locomotive(20,30,5));
t1->add_driver(new Driver("Jan","Kowalski"));
//t1->print();
RailCar x(5);
Passenger a = Passenger("Barny", "Krupowicz");
x.add_passenger(a);
t1->add_car(x);
x.remove_passenger("Barny", "Krupowicz");
x.add_passenger(Passenger("Adam","Kowalski",(float)500));
t1->add_car(x);

st->add_train(t1);

st->print();
sd->print();
st->move_train(1, sd);
std::cout << '\n';
st->print();
sd->print();
railline[1]->move_train(1, railline[0]);
*/
