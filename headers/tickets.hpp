#ifndef tickets_hpp
#define tickets_hpp

struct out_of_range: public std::exception{
    char* what() const throw(){
        return (char*)"Percentage out of range [0,1]";
    }
};

class Ticket{
private:
    int code;
    float price;
    float discount_percent;
public:
    Ticket();
    Ticket(int c, float p);
    Ticket(int c, float p, float dp);
    
    bool operator==(const Ticket);
    bool operator!=(const Ticket);
    void print();
    int get_code();
    float get_price();
    float get_discount();
    float get_dprice();
};



#endif /* tickets_hpp */
