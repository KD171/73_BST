#include "BTS_linia.h"

BTS_linia::BTS_linia(int numer = 0, const string& rodzaj = "", const string& strefa = "") : m_numer{ numer }, m_rodzaj{ rodzaj }, m_strefa{ strefa }
{
}

BTS_linia::BTS_linia(int numer, const string& rodzaj, const string& strefa, vector<string> trasa) : m_numer{ numer }, m_rodzaj{ rodzaj }, m_strefa{ strefa }, m_trasa{ trasa }
{
}

BTS_linia::BTS_linia(int numer, const string& rodzaj, const string& strefa, vector<string> trasa, vector<Godzina> odjazdy, vector<Godzina> odjazdy2, vector<time_t> czas) : m_numer{ numer }, m_rodzaj{ rodzaj }, m_strefa{ strefa }, m_trasa{ trasa }, m_odjazdy_1{ odjazdy }, m_odjazdy_2{ odjazdy2 }, m_czas{ czas }
{
    time_t adt = 0;
    for (int i = 0; i < size(trasa); i++) {
        adt = adt + czas[i];
        vector<Godzina> vec;
        for (int j = 0; j < size(odjazdy); j++) {

            Godzina czwarta(odjazdy[j].get_h(), adt + odjazdy[j].get_m());
            vec.push_back(czwarta);
        }
        sort(vec.begin(), vec.end(),
            [](Godzina& a, const Godzina& b) {
                return a < b;
            });
        m_rozklad_1.push_back(vec);
    }
    czas.erase(czas.begin());
    czas.push_back(0);
    adt = 0;
    for (int i = size(trasa) - 1; i > -1; i--) {
        vector<Godzina> vec;
        adt = adt + czas[i];
        for (int j = 0; j < size(odjazdy2); j++) {
            Godzina czwarta(odjazdy2[j].get_h(), adt + odjazdy2[j].get_m());
            vec.push_back(czwarta);
        }
        sort(vec.begin(), vec.end(),
            [](Godzina& a, const Godzina& b) {
                return a < b;
            });
        m_rozklad_2.push_back(vec);
    }
}

int BTS_linia::get_numer()
{
    return m_numer;
}

string BTS_linia::get_rodzaj()
{
    return m_rodzaj;
}

string BTS_linia::get_strefa()
{
    return m_strefa;
}

void BTS_linia::set_numer(int numer)
{
    m_numer = numer;
}

void BTS_linia::set_rodzaj(const string& rodzaj)
{
    m_rodzaj = rodzaj;
}

void BTS_linia::set_strefa(const string& strefa)
{
    m_strefa = strefa;
}

void BTS_linia::print_linia()
{
    cout << "Linia " << m_numer << " jest to linia ";
    if (m_rodzaj == "BUS") {
        cout << "autobusowa ";
    }
    else {
        cout << "tramwajowa ";
    }
    cout << m_strefa << endl;
}
void BTS_linia::print_trasa(void)
{
    for (int i = 0; i < size(m_trasa); i++) {
        cout << i + 1 << ". " << m_trasa[i] << endl;
    }
}
void BTS_linia::add_trasa(vector<string> trasa)
{
    m_trasa = trasa;
}

void BTS_linia::edit_czas(vector<time_t> czas)
{
    m_czas = czas;
    time_t adt = 0;
    vector<vector<Godzina>> rozklad_1, rozklad_2;
    for (int i = 0; i < size(m_trasa); i++) {
        adt = adt + czas[i];
        vector<Godzina> vec;
        for (int j = 0; j < size(m_odjazdy_1); j++) {

            Godzina czwarta(m_odjazdy_1[j].get_h(), adt + m_odjazdy_1[j].get_m());
            vec.push_back(czwarta);
        }
        sort(vec.begin(), vec.end(),
            [](Godzina& a, const Godzina& b) {
                return a < b;
            });
        rozklad_1.push_back(vec);
    }
    m_rozklad_1 = rozklad_1;
    czas.erase(czas.begin());
    czas.push_back(0);
    adt = 0;
    for (int i = size(m_trasa) - 1; i > -1; i--) {
        vector<Godzina> vec;
        adt = adt + czas[i];
        for (int j = 0; j < size(m_odjazdy_2); j++) {
            Godzina czwarta(m_odjazdy_2[j].get_h(), adt + m_odjazdy_2[j].get_m());
            vec.push_back(czwarta);
        }
        sort(vec.begin(), vec.end(),
            [](Godzina& a, const Godzina& b) {
                return a < b;
            });
        rozklad_2.push_back(vec);
    }
    m_rozklad_2 = rozklad_2;
}

vector<string> BTS_linia::get_trasa(void)
{
    return m_trasa;
}

vector<time_t> BTS_linia::get_czas(void)
{
    return m_czas;
}

vector<Godzina> BTS_linia::get_odjazdy_1(void)
{
    return m_odjazdy_1;
}

vector<Godzina> BTS_linia::get_odjazdy_2(void)
{
    return m_odjazdy_2;
}

vector<vector<Godzina>> BTS_linia::get_rozklad_1(void)
{
    return m_rozklad_1;
}

vector<vector<Godzina>> BTS_linia::get_rozklad_2(void)
{
    return m_rozklad_2;
}

void BTS_linia::add_odjazd_1(Godzina nowa)
{
    m_odjazdy_1.push_back(nowa);
    edit_czas(m_czas);
}

void BTS_linia::set_odjazdy_1(vector<Godzina> nowe)
{
    m_odjazdy_1 = nowe;
    edit_czas(m_czas);
}

void BTS_linia::print_odjazdy_1(void)
{
    for (int i = 0; i < size(m_odjazdy_1); i++) {
        m_odjazdy_1[i].print();
    }
}

void BTS_linia::print_rozklad_1(const string& przystanek)
{
    int i;
    vector<int> vec;
    vector<Godzina> rozklad;
    vector<Godzina> rozklad2;
    for (i = 0; i < size(m_trasa); i++) {
        if (przystanek == m_trasa[i]) {
            vec.push_back(i);
        }
    }
    cout << "Przystanek " << przystanek << " Linia " << m_numer << endl;
    for (int t = 0; t < size(vec); t++) {
        rozklad = m_rozklad_1[vec[t]];
        for (i = 0; i < size(rozklad); i++) {
            rozklad2.push_back(rozklad[i]);
        }
    }
    sort(rozklad2.begin(), rozklad2.end(),
        [](Godzina& a, const Godzina& b) {
            return a < b;
        });
    for (i = 0; i < size(rozklad2); i++) {
        rozklad2[i].print();
    }
}

void BTS_linia::add_odjazd_2(Godzina nowa)
{
    m_odjazdy_2.push_back(nowa);
    edit_czas(m_czas);
}

void BTS_linia::set_odjazdy_2(vector<Godzina> nowe)
{
    m_odjazdy_2 = nowe;
    edit_czas(m_czas);
}

void BTS_linia::print_odjazdy_2(void)
{
    for (int i = 0; i < size(m_odjazdy_2); i++) {
        m_odjazdy_2[i].print();
    }
}

void BTS_linia::print_rozklad_2(const string& przystanek)
{
    int i;
    vector<int> vec;
    vector<Godzina> rozklad2;
    for (i = 0; i < size(m_trasa); i++) {
        if (przystanek == m_trasa[i]) {
            vec.push_back(size(m_trasa) - i - 1);
        }
    }
    cout << "Przystanek " << przystanek << " Linia " << m_numer << endl;
    for (int t = 0; t < size(vec); t++) {
        vector<Godzina> rozklad = m_rozklad_2[vec[t]];
        for (i = 0; i < size(rozklad); i++) {
            rozklad2.push_back(rozklad[i]);
        }
    }
    sort(rozklad2.begin(), rozklad2.end(),
        [](Godzina& a, const Godzina& b) {
            return a < b;
        });
    for (i = 0; i < size(rozklad2); i++) {
        rozklad2[i].print();
    }

}

vector<string> BTS_linia::get_petle(void)
{
    vector<string> petle;
    if (size(m_trasa) != 0) {
        petle.push_back(m_trasa[0]);
        petle.push_back(m_trasa[size(m_trasa) - 1]);
    }
    else {
        petle.push_back("#####");
        petle.push_back("#####");
    }
    return petle;

}




