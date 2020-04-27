#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include "Godzina.h"
#include "BTS_linia.h"

using namespace std;

class BTS_przystanek
{
private:
    string m_nazwa;
    double m_gps_n;
    double m_gps_e;
    string m_typ;
    string m_nz;
    string m_strefa;
    map<int, string> m_linie;
    map<vector<int>, string> m_rozklad;
public:
    BTS_przystanek(const string& nazwa, double gps_n, double gps_e, const string& typ, const string& nz, const string& strefa, map<int, string> linie, map<vector<int>, string> rozklad);
    string get_nazwa() const;
    double get_gps_e() const;
    double get_gps_n() const;
    string get_typ() const;
    string get_nz() const;
    string get_strefa() const;
    map<int, string> get_linie() const;
    map<vector<int>, string> get_rozklad() const;
    void set_nazwa(const string& name);
    void set_gps_e(double gps_e);
    void set_gps_n(double gps_n);
    void set_typ(const string& typ);
    void set_nz(const string& nz);
    void set_strefa(const string& strefa);
    void add_linia(int linia, string kierunki);
    void del_linia(int linia);
    void add_roklad(int godzina, int minuta, int linia, string kierunek);
    void print_rozklad(void);
    void print_przystnek(void);
    void print_linie(void);
    void set_rozklad(map<vector<int>, string> rozklad);
   // bool operator<(const BTS_przystanek g);
};