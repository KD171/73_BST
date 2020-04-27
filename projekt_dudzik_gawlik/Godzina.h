#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

#ifndef Godzina_H
#define Godzina_H

class Godzina {
private:
    time_t m_godzina;
    time_t m_minuta;
public:
    Godzina(time_t godzina, time_t minuta);
    Godzina(const string& godzina);
    time_t get_h();
    time_t get_m();
    time_t to_minuty();
    void print();
    void print_bez_linii();
    ~Godzina();
    bool operator==(Godzina const& g);
    bool operator<(const Godzina& g);
};

#endif // !Godzina_H


