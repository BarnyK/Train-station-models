#ifndef templates_hpp
#define templates_hpp

struct station_not_exists: std::exception{
    char* what() const throw(){
        return (char*)"Station doesn't exist";
    }
};

// Template for linked list for subclasses of Station
template <class T> class Line{
private:
    T *head;
public:
    Line();
    void print();                           // prints the ids and names of stations in the list
    void add(std::string name);             // adds station to the list
    void add(T* st);
    void modify(int id, std::string name);  // modifies name of a station
    void remove(int id);                    // removes station by id
    void remove(std::string name);          // removes station by name
    int find(std::string name);             // returns the position of the station in the list
    
    T* get(std::string name);               // returns station of given name
    T* operator[](int i);                   // returns station from position in the list
};

template<class T> Line<T>::Line(){
    head = nullptr;
}

template<class T> void Line<T>::add(T* st){
    if(head==nullptr){
        head = st;
    }
    else{
        T* tmp = head;
        while(tmp->next){
            tmp = (T*)tmp->next;
        }
        tmp->next = st;
        tmp->next->prev = tmp;
    }
}


template<class T> T* Line<T>::get(std::string n){
    T* tmp = head;
    while(tmp){
        if(tmp->name == n)
            return tmp;
        tmp = (T*)tmp->next;
    }
    return nullptr;
}


template<class T> T* Line<T>::operator[](int i){
    T* tmp = head;
    for(int c=0;c<i;c++){
        tmp = (T*)tmp->next;
        if(!tmp)
            return nullptr;
    }
    return tmp;
}

template<class T> void Line<T>::print(){
    T* tmp = head;
    std::cout << "\nLine: " << std::endl;
    while(tmp){
        std::cout << tmp->id << ": " << tmp->name << std::endl;
        tmp = (T*)tmp->next;
    }
}
template<class T> void Line<T>::add(std::string name){
    if(head==nullptr){
        head = new T(1,name);
    }
    else{
        T* tmp = head;
        while(tmp->next){
            tmp = (T*)tmp->next;
        }
        tmp->next = new T(tmp->id+1,name);
        tmp->next->prev = tmp;
    }
}

template<class T> void Line<T>::modify(int i, std::string n){
    bool found = false;
    T* tmp = head;
    while(tmp){
        if(tmp->id == i){
            tmp->name = n;
            found = true;
            break;
        }
        tmp = (T*)tmp->next;
    }
    if(!found)
        throw station_not_exists();
}

template<class T> void Line<T>::remove(int i){
    T* tmp = head;
    T* prev = head;
    if(head->id == i){
        tmp = (T*)head->next;
        delete head;
        head = tmp;
    }
    while(tmp){
        if(tmp->id == i){
            prev->next = tmp->next;
            delete tmp;
        }
        prev = tmp;
        tmp = (T*)tmp->next;
    }
}

template<class T> void Line<T>::remove(std::string n){
    bool found = false;
    T* tmp = head;
    T* prev = head;
    if(head->name == n){
        found = true;
        tmp = (T*)head->next;
        delete head;
        head = tmp;
    }
    while(tmp && !found){
        if(tmp->name == n){
            prev->next = tmp->next;
            delete tmp;
        }
        prev = tmp;
        tmp = (T*)tmp->next;
    }
    if(!found)
        throw station_not_exists();
}

template<class T> int Line<T>::find(std::string n){
    T* tmp = head;
    while(tmp){
        if(tmp->name == n){
            return tmp->id;
        }
        tmp = (T*)tmp->next;
    }
    return -1;
}

#endif /* templates_hpp */
