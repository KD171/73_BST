#include "Godzina.h"


Godzina::Godzina(time_t godzina = 0, time_t minuta = 0) : m_godzina{ godzina }, m_minuta{ minuta }
{
    m_minuta = minuta % 60;
    m_godzina = (godzina + minuta / 60) % 24;

}

Godzina::Godzina(const string& godzina)
{
    string hh;
    string mm = "0";
    int i;
    time_t h1, m1;
    for (i = 0; i < size(godzina); i++) {
        if (godzina[i] == ':') {
            break;
        }
        else {
            hh += godzina[i];
        }
    }
    i++;
    for (i; i < size(godzina); i++) {
        mm += godzina[i];
    }
    stringstream m(mm);
    m >> m1;
    m_minuta = m1 % 60;
    m1 = m1 / 60;
    stringstream h(hh);
    h >> h1;
    m_godzina = (h1 + m1) % 24;
}

time_t Godzina::get_h(void)
{
    return m_godzina;
}

time_t Godzina::get_m(void)
{
    return m_minuta;
}

time_t Godzina::to_minuty()
{
    return m_godzina * 60 + m_minuta;
}

void Godzina::print()
{
    cout << setfill('0') << setw(2) << m_godzina << ":" << setfill('0') << setw(2) << m_minuta << endl;
}

void Godzina::print_bez_linii()
{
    cout << setfill('0') << setw(2) << m_godzina << ":" << setfill('0') << setw(2) << m_minuta;
}

Godzina::~Godzina()
{
}

bool Godzina::operator==(Godzina const& g)
{
    if (m_godzina == g.m_godzina) {
        return (m_minuta == g.m_minuta);
    }
    else
        return false;
}

bool Godzina::operator<(const Godzina& g)
{
    return (60 * m_godzina + m_minuta) < (60 * g.m_godzina + m_minuta);
}


