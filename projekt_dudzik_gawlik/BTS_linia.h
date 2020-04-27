#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "BTS_przystanek.h"
#include "Godzina.h"

#ifndef BTS_linia_H
#define BTS_linia_H


using namespace std;

class BTS_linia
{
private:
    int m_numer;       //numer lini
    string m_rodzaj;      //autobusowa czy tramwajowa
    string m_strefa;      //miejski kraków czy aglomeracja Skawina
    vector<string> m_trasa;
    vector<Godzina> m_odjazdy_1; // z przystanku 1
    vector<Godzina> m_odjazdy_2;    //z przystanku ostaniego do pierwszego
    vector<time_t> m_czas;
    vector<vector<Godzina>> m_rozklad_1;    //z 1 do ostatniwgo
    vector<vector<Godzina>> m_rozklad_2;    //z ostaniego do 1
public:
    BTS_linia(int numer, const string& rodzaj, const string& strefa);
    BTS_linia(int numer, const string& rodzaj, const string& strefa, vector<string> trasa);
    BTS_linia(int numer, const string& rodzaj, const string& strefa, vector<string> trasa, vector<Godzina> odjazdy, vector<Godzina> odjazdy2, vector<time_t> czas);
    int get_numer();
    string get_rodzaj();
    string get_strefa();
    void set_numer(int numer);
    void set_rodzaj(const string& rodzaj);
    void set_strefa(const string& strefa);
    void print_linia();
    void print_trasa(void);
    void add_trasa(vector<string> trasa);
    void edit_czas(vector<time_t> czas);
    vector<string> get_trasa(void);
    vector<time_t> get_czas(void);
    vector<Godzina> get_odjazdy_1(void);
    vector<Godzina> get_odjazdy_2(void);
    vector<vector<Godzina>> get_rozklad_1(void);
    vector<vector<Godzina>> get_rozklad_2(void);
    void add_odjazd_1(Godzina nowa);
    void set_odjazdy_1(vector<Godzina> nowe);
    void print_odjazdy_1(void);
    void print_rozklad_1(const string& przystanek);
    void add_odjazd_2(Godzina nowa);
    void set_odjazdy_2(vector<Godzina> nowe);
    void print_odjazdy_2(void);
    void print_rozklad_2(const string& przystanek);
    vector<string> get_petle(void);
};

#endif // !BTS_linia_H