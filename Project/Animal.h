//
// Created by phoenix559 on 10/30/26.
//

#ifndef CSCI115_ANIMAL_H
#define CSCI115_ANIMAL_H
#include <utility>
#include <climits>



class Animal {
protected:
    int cost_of_edges [5][5] = {};
    char type = 'A';
    std::pair<int,int> position = {-1,-1}; // position is (r,c), not (x,y)
    virtual void set_cost_of_edges() = 0;
    int terrain_index(char terrain);
public:
    Animal() = default;
    Animal(char arg_type, int r = -1, int c = -1);
    virtual ~Animal();
    std::pair <int,int> get_position () const;
    void update_location (int r, int c);
    char get_type () const;
    int get_cost_of_edge(char from, char to); 
    virtual void display () = 0;
};

class Monkey : public Animal {
protected:
    virtual void set_cost_of_edges () override;
public:
    Monkey();
    Monkey(int r, int c);
    ~Monkey();
    virtual void display() override;
};

class Bird : public Animal {
protected:
    virtual void set_cost_of_edges () override;
public:
    Bird();
    Bird(int r, int c);
    ~Bird();
    virtual void display() override;
};

class Frog:public Animal {
protected:
    virtual void set_cost_of_edges () override;
public:
    Frog();
    Frog(int r, int c);
    ~Frog();
    virtual void display() override;
    
};

class Fish:public Animal {
protected:
    virtual void set_cost_of_edges () override;
public:
    Fish();
    Fish(int r, int c);
    ~Fish();
    virtual void display() override;
    
};

#endif //CSCI115_ANIMAL_H
