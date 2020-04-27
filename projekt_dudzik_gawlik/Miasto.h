#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <map>
#include "BTS_linia.h"
#include "BTS_przystanek.h"

using namespace std;

class Miasto
{
private:
	string m_miasto;
	vector<BTS_linia> m_linie;
	vector<BTS_przystanek> m_przystanki;
public:
	Miasto(const string& miasto);
	Miasto(const string& misto, vector<BTS_linia> linie, vector<BTS_przystanek> przystaneki);
	string get_miasto();
	vector<BTS_linia> get_linie();
	vector<BTS_przystanek> get_przystanki();
	void set_miasto(string miasto);
	void add_przystanek(BTS_przystanek przystanek);
	void add_linia(BTS_linia linia);
	void obsluga_miasta(void);
	void add_przystanek_o(void);
	void print_przystanki(void);
	void add_linia(void);
	bool check_przystanek(const string& przystanek);
	bool check_linia(int linia);
	void print_linie(void);
	void edit_przystanek(void);
	int int_przystanek(const string& przystanek);
	int int_linia(int linia);
	void edit_linia(void);
	void print_rozklad_lini(void);
	void print_trasa(void);
	void print_rozklad_przystanku(void);
	void print_linie_na_przystanku(void);
	void add_roklady_do_przystankow(vector<string> trasa, vector<time_t> czasy, vector<Godzina> odjazdy, vector<Godzina> odjazdy2, int nr);
	void del_rozklady_z_przystankow(int linia);
	void del_linia_z_przystanku(int linia);
	void add_linia_do_przystanku(int linia);
	void polaczenie(const string& przystanek1, const string& przystanek2, Godzina czas);
	void polaczenie_lu(void);
	void update_trasa(const string& przystanek_old, const string& przystanek_new);
	void open_file_stop(void);
	void open_file_bus(void);
	void edit_file_linia(int numer);
	double get_number_d(void);
	int get_number(void);
};