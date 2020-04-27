#include "BTS_przystanek.h"


BTS_przystanek::BTS_przystanek(const string& nazwa = "", double gps_n = 0, double gps_e = 0, const string& typ = "", const string& nz = "", const string& strefa = "", map<int, string> linie = {}, map<vector<int>, string> rozklad = {  }) : m_nazwa{ nazwa }, m_gps_n{ gps_n }, m_gps_e{ gps_e }, m_typ{ typ }, m_nz{ nz }, m_strefa{ strefa }, m_linie{ linie }, m_rozklad{ rozklad }
{
}

string BTS_przystanek::get_nazwa() const
{
	return m_nazwa;
}

double BTS_przystanek::get_gps_e() const
{
	return m_gps_e;
}

double BTS_przystanek::get_gps_n() const
{
	return m_gps_n;
}

string BTS_przystanek::get_typ() const
{
	return m_typ;
}

string BTS_przystanek::get_nz() const
{
	return m_nz;
}

string BTS_przystanek::get_strefa() const
{
	return m_strefa;
}

map<int, string> BTS_przystanek::get_linie() const
{
	return m_linie;
}

map<vector<int>, string> BTS_przystanek::get_rozklad() const
{
	return m_rozklad;
}

void BTS_przystanek::set_nazwa(const string& name)
{
	m_nazwa = name;
}

void BTS_przystanek::set_gps_e(double gps_e)
{
	m_gps_e = gps_e;
}

void BTS_przystanek::set_gps_n(double gps_n)
{
	m_gps_n = gps_n;
}

void BTS_przystanek::set_typ(const string& typ)
{
	if (typ == "BUS" || typ == "TRAM" || typ == "BUS-TRAM") {
		m_typ = typ;
	}
	else { cout << "Aby ustawiæ typ przystanku wpisz BUS TRAM lub BUS-TRAM" << endl; }
}

void BTS_przystanek::set_nz(const string& nz)
{
	if (nz == "TAK" || nz == "NIE") {
		m_nz = nz;
	}
	else { cout << "Aby ustawiæ opcje przystanku wpisz TAK lub NIE\n"; }
}

void BTS_przystanek::set_strefa(const string& strefa)
{
	if (strefa == "Miejski" || strefa == "Aglomeracyjny") {
		m_strefa = strefa;
	}
	else { cout << "Aby ustawiæ opcje przystanku wpisz Miejski lub Aglomeracyjny\n"; }
}

void BTS_przystanek::add_linia(int linia, string kierunki)
{
	if (m_linie.find(linia) == m_linie.end()) {
		m_linie[linia] = kierunki;
	}
	else {
		cout << "Linia ju¿ jest dopisana do tego przystanku\n";
	}
}

void BTS_przystanek::del_linia(int linia)
{
	m_linie.erase(m_linie.find(linia));
}

void BTS_przystanek::add_roklad(int godzina, int minuta, int linia, string kierunek)
{
	vector<int> vec = { godzina,minuta,linia };
	m_rozklad[vec] = kierunek;
}

void BTS_przystanek::print_rozklad(void)
{
	cout << "Rozk³ad dla przystanku " << m_nazwa << endl;
	cout << "Odjazd\tLinia\tKierunek" << endl;
	for (pair<vector<int>, string>element : m_rozklad) {
		vector<int> godz = element.first;
		string kierunek = element.second;
		cout << setfill('0') << setw(2) << godz[0] << ":" << setfill('0') << setw(2) << godz[1] << "\t" << godz[2] << "\t" << kierunek << endl;
	}
}

void BTS_przystanek::print_przystnek(void)
{
	cout << "Przystanek: \"" << m_nazwa << "\" o wspó³¿êdnych GPS: " << m_gps_n << "N," << m_gps_e << "E obs³uguje on: " << m_typ << " i jest on w strefie " << m_strefa << endl;
}

void BTS_przystanek::print_linie(void)
{
	cout << "Przysztanek " << m_nazwa << " obs³uguj¹ linie:" << endl;
	int i = 0;
	for (pair <int, string> element : m_linie) {
		i++;
		int linia = element.first;
		string kieruneki = element.second;
		cout << i << ". " << linia << "\t" << kieruneki << endl;
	}
}

void BTS_przystanek::set_rozklad(map<vector<int>, string> rozklad)
{
	m_rozklad = rozklad;
}
/*
bool BTS_przystanek::operator<(const BTS_przystanek g)
{
	return false;
}
*/