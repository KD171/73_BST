#include "Miasto.h"


Miasto::Miasto(const string& miasto) :m_miasto{ miasto }
{
	obsluga_miasta();
}

Miasto::Miasto(const string& miasto = "", vector<BTS_linia> linie = {}, vector<BTS_przystanek> przystanki = {}) : m_miasto{ miasto }, m_linie{ linie }, m_przystanki{ przystanki }
{
}

string Miasto::get_miasto()
{
	return m_miasto;
}

vector<BTS_linia> Miasto::get_linie()
{
	return m_linie;
}

vector<BTS_przystanek> Miasto::get_przystanki()
{
	return m_przystanki;
}

void Miasto::set_miasto(string miasto)
{
	m_miasto = miasto;
}

void Miasto::add_przystanek(BTS_przystanek przystanek)
{
	m_przystanki.push_back(przystanek);
}

void Miasto::add_linia(BTS_linia linia)
{
	m_linie.push_back(linia);
}

void Miasto::obsluga_miasta(void)
{
	system("cls");
	cout << "wait..." << endl;
	open_file_stop();
	open_file_bus();
	system("cls");
	cout << "Witamy w systemie zarz¹dzania transporu publicznego miasta " << m_miasto << endl;
	string i, j;
	while (1) {
		cout << "Wpisz co chcesz zrobiæ:\n";
		cout << "1\tAby sprawdziæ rozk³ad jazdy\n2\tAby znaleœæ po³¹czenie\n3\tAby edytowaæ linie i przystanki\n99\tZakoñcz\n";
		cin >> i;
		if (i == "1") {
			system("cls");
			cout << "1\tWyœwietl rozk³ad jazdy przystanku\n2\tSprawdŸ rozk³ad lini\n3\tSprawdŸ które linie obs³uguj¹ konkretny przystanek\n4\tSprawdŸ trasê linii\n5\tSprawdŸ dostêpne przystanki\n6\tSprawdŸ dostêpne linie\n";
			cin >> i;
			if (i == "1") {
				print_rozklad_przystanku();
			}
			else if (i == "2") {
				print_rozklad_lini();
			}
			else if (i == "3") {
				print_linie_na_przystanku();
			}
			else if (i == "4") {
				print_trasa();
			}
			else if (i == "5") {
				print_przystanki();
			}
			else if (i == "6") {
				print_linie();
			}
			system("pause");
		}
		else if (i == "2") {
			system("cls");
			polaczenie_lu();
			system("pause");
		}
		else if (i == "3") {
			system("cls");
			cout << "1\tDodaj przystanek\n2\tDodaæ linie\n3\tEdycja przystanku\n4\tEdycja lini\n";
			cin >> i;
			if (i == "1") {
				add_przystanek_o();
			}
			else if (i == "2") {
				add_linia();
			}
			else if (i == "3") {
				edit_przystanek();
			}
			else if (i == "4") {
				edit_linia();
			}
			system("pause");
		}
		else if (i == "99") {
			break;
		}
		system("cls");
	}

}

void Miasto::add_przystanek_o(void)
{
	string nazwa, strefa, nz, typ;
	cout << "Wpisz nazwe przystanku \n";
	cin.ignore();
	getline(cin, nazwa);
	if (check_przystanek(nazwa) == 0) {
		double e1, n1;
		cout << "Wpisz lokacje E\n";
		e1 = get_number_d();
		cout << "Wpisz lokacje N\n";
		n1 = get_number_d();
		cout << "W jakiej strefie jest przystanek? Mijski/Podmiejski\n";
		cin >> strefa;
		cout << "Czy przystanek jest na ¿¹danie?\n";
		cin >> nz;
		cout << "Typ przystanku: BUS BUS-TRAM TRAM\n";
		cin >> typ;
		map<int, string> linie = {};
		map<vector<int>, string> linie_r;
		BTS_przystanek przyst(nazwa, n1, e1, typ, nz, strefa, linie, linie_r);
		fstream file;
		file.open("przystanki.txt", ios::in | ios::out | ios::app);
		if (file.is_open()) {
			file << nazwa << endl;
			file << n1 << endl;
			file << e1 << endl;
			file << nz << endl;
			file << typ << endl;
			file << strefa << endl;
			file.close();
		}
		m_przystanki.push_back(przyst);
	}
	else {
		cout << "Przystanek o podanej nazwie istniej w bazie\nMo¿esz wyedytowaæ ten przystanek\n";
	}
}

void Miasto::print_przystanki(void)
{
	if (size(m_przystanki) > 0) {
		cout << "Przystanki w mieœcie " << m_miasto << endl;
		for (int i = 0; i < size(m_przystanki); i++) {
			cout << i + 1 << ". " << m_przystanki[i].get_nazwa() << endl;
		}
	}
	else {
		cout << "Brak przystanków w mieœcie\n";
	}

}

void Miasto::add_linia(void)
{
	fstream file, file2;
	int nr;
	int j = 1;
	string rodzaj, strefa, przystanek;
	cout << "Podaj numer linii" << endl;
	nr = get_number();
	string name = "linia_" + to_string(nr) + ".txt";
	file2.open("linie.txt", ios::in | ios::out | ios::app);
	file2 << name << endl;
	file2.close();
	if (check_linia(nr) == 0) {
		file.open(name, ios::in | ios::out | ios::app);
		cout << "Czy jest to autobus czy tramwaj? BUS TRAM" << endl;
		cin >> rodzaj;
		cout << "Jest to linia miejska czy strefowa?" << endl;
		cin >> strefa;
		cout << "Dodaj trase linia. Wpisz nazwe przystanków po kolei dostêpnych w bazie. Wpisz \"pêtla\" aby zakoñczyæ.\n";
		if (file.is_open()) {
			file << nr << endl;
			file << rodzaj << endl;
			file << strefa << endl;
		}
		vector<string> trasa = {};
		cin.ignore();
		while (1) {
			cout << j << ". ";
			getline(cin, przystanek);
			if (przystanek == "pêtla") {
				if (size(trasa) != 0) {
					string kierunki = trasa[0] + " <-> " + trasa[size(trasa) - 1];
					if (file.is_open()) {
						file << "pêtla" << endl;
					}
					for (int i = 0; i < size(trasa); i++) {
						przystanek = trasa[i];
						m_przystanki[int_przystanek(przystanek)].add_linia(nr, kierunki);
					}
				}
				break;
			}
			else {
				if (check_przystanek(przystanek)) {
					trasa.push_back(przystanek);
					if (file.is_open()) {
						file << przystanek << endl;
					}
					j++;
				}
				else {
					cout << "nie ma takiego przystanku" << endl;
				}
			}
		}
		if (size(trasa) > 1) {
			vector<time_t> czas = { 0 };
			if (file.is_open()) {
				file << 0 << endl;
			}
			vector<Godzina> odjazdy = {};
			vector<Godzina> odjazdy2 = {};
			cout << "Podaj czas jaki potrzebuje " << rodzaj << " aby dotrzeæ z przystanku do przystanku\n";
			for (int i = 0; i < (size(trasa) - 1); i++) {
				cout << i + 1 << "." << trasa[i] << " - > " << i + 2 << ". " << trasa[i + 1] << "\t";
				time_t czas_przejazdu;
				czas_przejazdu = get_number();
				//cin >> czas_przejazdu;
				if (file.is_open()) {
					file << czas_przejazdu << endl;
				}
				czas.push_back(czas_przejazdu);
			}
			cout << "Dodaj godziny startu o której " << rodzaj << " startuje z pêtli " << trasa[0] << "\nDane wporwadzaj w formacie HH:MM gdzie HH to godzina ':' i MM to minuta\nWpisz 99 aby zakoñczyæ" << endl;
			while (1) {
				string godz;
				cout << "HH:MM\b\b\b\b\b";
				cin >> godz;
				if (file.is_open()) {
					file << godz << endl;
				}
				if (godz[1] == '9' && godz[0] == '9') {

					break;
				}
				Godzina czas(godz);
				odjazdy.push_back(czas);
			}
			cout << "Dodaj godziny startu o której " << rodzaj << " startuje z pêtli " << trasa[size(trasa) - 1] << "\nDane wporwadzaj w formacie HH:MM gdzie HH to godzina ':' i MM to minuta\nWpisz 99 aby zakoñczyæ" << endl;
			while (1) {
				string godz;
				cout << "HH:MM\b\b\b\b\b";
				cin >> godz;
				if (file.is_open()) {
					file << godz << endl;
				}
				if (godz[1] == '9' && godz[0] == '9') {
					break;
				}
				Godzina czas(godz);
				odjazdy2.push_back(czas);
			}
			file.close();
			BTS_linia nowa(nr, rodzaj, strefa, trasa, odjazdy, odjazdy2, czas);
			add_roklady_do_przystankow(trasa, czas, odjazdy, odjazdy2, nr);
			m_linie.push_back(nowa);
		}
		else {
			file.close();
			BTS_linia nowa(nr, rodzaj, strefa);
			m_linie.push_back(nowa);
		}
	}
	else {
		cout << "Linia o podanym numerze ju¿ istnieje\n";
	}

}

bool Miasto::check_przystanek(const string& przystanek)
{
	for (int i = 0; i < size(m_przystanki); i++) {
		if (m_przystanki[i].get_nazwa() == przystanek) {
			return true;
		}
	}
	return false;
}

bool Miasto::check_linia(int linia)
{
	for (int i = 0; i < size(m_linie); i++) {
		if (m_linie[i].get_numer() == linia) {
			return true;
		}
	}
	return false;
}

void Miasto::print_linie(void)
{
	if (size(m_linie) > 0) {
		cout << "Linie obs³uguj¹ce miasto " << m_miasto << endl;
		for (int i = 0; i < size(m_linie); i++) {
			vector<string> trasa = m_linie[i].get_petle();
			cout << i + 1 << ". " << m_linie[i].get_numer() << "\t" << trasa[0] << "  <->  " << trasa[1] << endl;
		}
	}
	else {
		cout << "¯adne linie nie s¹ dostêne w mieœcie\nNajpierw dodaj linie\n";
	}

}

void Miasto::edit_przystanek(void)
{
	cout << "Jaki przystanek chcesz edytowaæ, podaj jego nazwe\n";
	string przystanek, tr;
	cin.ignore();
	getline(cin, przystanek);
	if (check_przystanek(przystanek)) {
		int u;
		int i{};
		int t = int_przystanek(przystanek);
		cout << "Wybierz czêœæ któr¹ chcesz zmieniæ\n1 -> Nazwa\n2 -> Lokacja GPS N\n3 -> Lokacja GPS E\n4 -> Na ¿¹danie\n5 -> Typ obs³ugi\n6 -> Strefa\n7 -> Aby zakoñczyæ edycje\n";
		u = get_number();
		string nazwa, nz, typ, strefa, tofile;
		double gps_n, gps_e;
		switch (u)
		{
		case 1:
			cout << "WprowadŸ now¹ nazwe przystanku\n";
			cin.ignore();
			getline(cin, nazwa);
			tofile = nazwa;
			m_przystanki[t].set_nazwa(nazwa);
			update_trasa(przystanek, nazwa);
			break;
		case 2:
			cout << "WprowadŸ now¹ lokacje GPS N\n";
			cin.ignore();
			gps_n = get_number_d();
			tofile = to_string(gps_n);
			m_przystanki[t].set_gps_n(gps_n);
			break;
		case 3:
			cout << "WprowadŸ now¹ lokacje GPS E\n";
			cin.ignore();
			gps_e = get_number_d();
			tofile = to_string(gps_e);
			m_przystanki[t].set_gps_e(gps_e);
			break;
		case 4:
			cout << "Czy przystanek jest na ¿¹danie?\n";
			cin.ignore();
			cin >> nz;
			tofile = nz;
			m_przystanki[t].set_nz(nz);
			break;
		case 5:
			cout << "WprowadŸ co teraz obs³uguje przystanek BUS, TRAM, BUS-TRAM\n";
			cin.ignore();
			cin >> typ;
			tofile = typ;
			m_przystanki[t].set_typ(typ);
			break;
		case 6:
			cout << "Czy przystanek jest w Stefie Miejskiej czy na Algomeracji?\n";
			cin.ignore();
			cin >> strefa;
			tofile = strefa;
			m_przystanki[t].set_strefa(strefa);
			break;
		default:
			break;
		}
		fstream file, file2;
		file.open("przystanki.txt", ios::in | ios::out | ios::app);
		file2.open("temp.txt", ios::in | ios::out | ios::app);
		while (getline(file, tr)) {
			if (tr == przystanek) {
				i++;
			}
			if (i == u) {
				file2 << tofile << endl;
				i++;
			}
			else {
				file2 << tr << endl;
				if (i > 0) {
					i++;
				}

			}
		}
		file.close();
		file2.close();
		remove("przystanki.txt");
		rename("temp.txt", "przystanki.txt");
	}
	else {
		cout << "Nie ma takiego przystanku w bazie\nNajpierw dodaj przystanek albo spradŸ czy nazwa przystanku zosta³a poprawnie wprowadzona\n";
		print_przystanki();
	}
}

int Miasto::int_przystanek(const string& przystanek)
{
	for (int i = 0; i < size(m_przystanki); i++) {
		if (m_przystanki[i].get_nazwa() == przystanek) {
			return i;
		}
	}
}

int Miasto::int_linia(int linia)
{
	for (int i = 0; i < size(m_linie); i++) {
		if (m_linie[i].get_numer() == linia) {
			return i;
		}
	}
}

void Miasto::edit_linia(void)
{
	cout << "Któr¹ linie chcesz edytowaæ?\n";
	string l;
	int linia;
	cin.ignore();
	linia = get_number();
		if (check_linia(linia)) {
			int u, t, numer, z, j;
			t = int_linia(linia);
			cout << "Wybierz któr¹ czêœæ chcesz wyedytowaæ\n1 -> Numer\n2 -> Rodzaj\n3 -> Strefa\n4 -> Trasa\n5 -> Czasy miêdzy przystankami\n6 -> Odjazdy z pêtli\t";
			u = get_number();
			j = 0;
			string rodzaj, strefa, trasa_s, przystanek;
			vector<string> trasa;
			vector<time_t> czas;
			switch (u) {
			case 1:
				cout << "WprowadŸ nowy numer lini\n";
				cin.ignore();
				numer = get_number();
				if (check_linia(numer)) {
					cout << "Numer linii jest ju¿ u¿ywany, nie wprowadzono zmian\n";
					break;
				}
				else {
					string fname = "linia_" + to_string(linia) + ".txt";
					string tp;
					remove(fname.c_str());
					fstream fil, fil2;
					fil.open("linie.txt", ios::in | ios::out | ios::app);
					fil2.open("temp.txt", ios::in | ios::out | ios::app);
					while (getline(fil, tp)) {
						if (tp == fname) {
							fil2 << "linia_" + to_string(numer) + ".txt" << endl;
						}
						else {
							fil2 << tp << endl;
						}
					}
					fil.close();
					fil2.close();
					remove("linie.txt");
					rename("temp.txt", "linie.txt");
					m_linie[t].set_numer(numer);
					edit_file_linia(numer);
					break;
				}
			case 2:
				cout << "WprowadŸ nowy rodzaj lini\nBUS TRAM \n";
				cin.ignore();
				cin >> rodzaj;
				m_linie[t].set_rodzaj(rodzaj);
				edit_file_linia(linia);
				break;
			case 3:
				cout << "WprowadŸ akutaln¹ strefe \n";
				cin.ignore();
				cin >> strefa;
				m_linie[t].set_strefa(strefa);
				edit_file_linia(linia);
				break;
			case 4:
				cout << "Jeœli chcesz wproadziæ ca³¹ now¹ trase wybierz 1\nJeœli chcesz dodaæ jeden przystanek do aktualnej trasy wybierz 2\nJeœli chcesz usun¹æ przystanek z akualnej trasy wybierz 3\n";
				cin >> z;
				if (z == 1) {
					cout << "Wpisz nazwy przystanków po kolei. Aby zakoñczyæ wpisz pêtla\n";
					cin.ignore();
					j = 1;
					while (1) {
						cout << j << ". ";
						getline(cin, przystanek);
						if (przystanek == "pêtla") {
							if (size(trasa) != 0) {
							}
							break;
						}
						else {
							if (check_przystanek(przystanek)) {
								trasa.push_back(przystanek);
								j++;
							}
							else {
								cout << "nie ma takiego przystanku" << endl;
							}
						}
					}
					if (size(trasa) == 0) {
						cout << "Nie wprowadzono zmian w trasie\n";
						break;
					}
					vector<time_t> czas = { 0 };
					cout << "Podaj czas jaki potrzebuje " << rodzaj << " aby dotrzeæ z przystanku do przystanku\n";
					for (int i = 0; i < (size(trasa) - 1); i++) {
						cout << i + 1 << "." << trasa[i] << " - > " << i + 2 << ". " << trasa[i + 1] << "\t";
						time_t czas_przejazdu;
						czas_przejazdu = get_number();
						czas.push_back(czas_przejazdu);
					}
					del_linia_z_przystanku(linia);
					del_rozklady_z_przystankow(linia);
					m_linie[t].add_trasa(trasa);
					m_linie[t].edit_czas(czas);
					add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
					add_linia_do_przystanku(linia);

				}
				else if (z == 2) {
					if (size(m_linie[t].get_trasa()) == 0) {
						cout << "Najpierw dodaj trasê do linii\n";
						break;
					}
					cout << "Oto aktualna trasa lini " << linia << endl;
					vector<string> trasa_old = m_linie[t].get_trasa();
					m_linie[t].print_trasa();
					int nr;
					cout << "Wpisz numer jaki ma mieæ nowy przystanek\n";
					nr = get_number();
					nr = nr - 1;
					if (nr <= trasa_old.size()) {
						cout << "Wpisz nazwê nowego przystanku\n";
						cin.ignore();
						while (1) {
							getline(cin, przystanek);
							if (check_przystanek(przystanek)) {
								break;
							}
							else {
								cout << "Nie ma takiego przystanku w bazie. Spróbuj ponownie\n";
							}
						}
						cout << nr << "\n" << trasa_old.size() << endl;
						trasa_old.insert(trasa_old.begin() + nr, przystanek);
						time_t t1, t2;
						cout << nr << "\n" << trasa_old.size() << endl;
						vector<time_t> czas = m_linie[t].get_czas();
						if (nr == 0) {
							cout << 1 << endl;
							cout << "WprowadŸ czas jaki potrzebny jest aby pojazd dosta³ siê z przystanku " << trasa_old[nr] << " do przystanku " << trasa_old[nr + 1] << endl;
							t1 = get_number();
							czas.insert(czas.begin() + 1, t1);
						}
						else if ((nr + 1) == trasa_old.size()) {
							cout << 2 << endl;
							cout << "WprowadŸ czas jaki potrzebny jest aby pojazd dosta³ siê z przystanku " << trasa_old[nr - 1] << " do przystanku " << trasa_old[nr] << endl;
							t1 = get_number();
							czas.push_back(t1);
						}
						else {
							cout << 3 << endl;
							cout << "WprowadŸ czas jaki potrzebny jest aby pojazd dosta³ siê z przystanku " << trasa_old[nr - 1] << " do przystanku " << trasa_old[nr] << endl;
							t1 = get_number();
							cout << "WprowadŸ czas jaki potrzebny jest aby pojazd dosta³ siê z przystanku " << trasa_old[nr] << " do przystanku " << trasa_old[nr + 1] << endl;
							t2 = get_number();
							czas.erase(czas.begin() + nr);
							czas.insert(czas.begin() + nr, t1);
							czas.insert(czas.begin() + nr + 1, t2);
						}
						del_linia_z_przystanku(linia);
						del_rozklady_z_przystankow(linia);
						m_linie[t].add_trasa(trasa_old);
						m_linie[t].edit_czas(czas);
						add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
						string kierunki = trasa_old[0] + " <-> " + trasa_old[size(trasa_old) - 1];
						for (int i = 0; i < size(trasa_old); i++) {
							m_przystanki[int_przystanek(trasa_old[i])].add_linia(linia, kierunki);
						}
					}
					else {
						cout << "Za du¿a wartoœæ, spróbuj ponownie.\n";
					}
				}
				else if (z == 3) {
					if (size(m_linie[t].get_trasa()) == 0) {
						cout << "Najpierw dodaj trasê do linii\n";
						break;
					}
					cout << "Oto aktualna trasa lini " << linia << endl;
					m_linie[t].print_trasa();
					int nr;
					cout << "Wpisz numer jaki ma zostaæ usuniêty\n";
					nr = get_number();
					vector<string> trasa = m_linie[t].get_trasa();
					time_t t1;
					vector<time_t> czas = m_linie[t].get_czas();
					if (nr <= trasa.size()) {
						nr = nr - 1;
						if (nr == 0) {
							trasa.erase(trasa.begin() + nr);
							czas.erase(czas.begin() + 1);
						}
						else if ((nr + 1) == trasa.size()) {
							trasa.erase(trasa.end() - 1);
							czas.erase(czas.end() - 1);
						}
						else {
							trasa.erase(trasa.begin() + nr);
							cout << "WprowadŸ czas jaki potrzebny jest aby pojazd dosta³ siê z przystanku " << trasa[nr - 1] << " do przystanku " << trasa[nr] << endl;
							t1 = get_number();
							czas.erase(czas.begin() + nr);
							czas.erase(czas.begin() + nr);
							czas.insert(czas.begin() + nr, t1);
						}
						del_linia_z_przystanku(linia);
						del_rozklady_z_przystankow(linia);
						m_linie[t].add_trasa(trasa);
						m_linie[t].edit_czas(czas);
						add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
						string kierunki = trasa[0] + " <-> " + trasa[size(trasa) - 1];
						for (int i = 0; i < size(trasa); i++) {
							m_przystanki[int_przystanek(trasa[i])].add_linia(linia, kierunki);
						}
					}
					else {
						cout << "Zakres przekroczny. Spróbuj ponownie.\n";
					}
				}
				else {
					cout << "Spróbuj ponownie\n";
				}
				edit_file_linia(linia);
				break;
			case 5:
				if (size(m_linie[t].get_trasa()) == 0) {
					cout << "Najpierw dodaj trasê do linii\n";
					break;
				}
				cout << "Zmieñ czasy przejazdów miêdzy przystankami\n";
				trasa = m_linie[t].get_trasa();
				czas = { 0 };
				time_t cz;
				for (int i = 0; i < size(trasa) - 1; i++) {
					cout << i + 1 << ". " << trasa[i] << " -> " << trasa[i + 1] << "\t";
					cz = get_number();
					czas.push_back(cz);
				}
				del_rozklady_z_przystankow(linia);
				m_linie[t].edit_czas(czas);
				add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
				edit_file_linia(linia);
				break;
			case 6:
				if (size(m_linie[t].get_trasa()) == 0) {
					cout << "Najpierw dodaj trasê do linii\n";
					break;
				}
				int x, y;
				cout << "Dodawanie nowych godzin odjazdów z pêtli\n1 aby dodaæ kilka nowych odjazdów\n2 aby dodaæ ca³kiem nowe godziny odjazdów\n3 aby usun¹æ niektóre godziny odjazdów\n";
				x = get_number();
				cin.ignore();
				vector<string> petle = m_linie[t].get_petle();
				cout << "Z wyjazdy z której pêtli bêd¹ edytowane\n1. " << petle[0] << "\n2. " << petle[1] << endl;
				y = get_number();
				if (x == 1) {
					cout << "Podaj nowe dodatkowe godziny wyjazdów z pêtli ";
					if (y == 1) {
						cout << petle[0] << "\nWpisz 99 aby zakoñczyæ\n";
					}
					else {
						cout << petle[1] << "\nWpisz 99 aby zakoñczyæ\n";
					}
					while (1) {
						string godz;
						cin.ignore();
						cout << "HH:MM\b\b\b\b\b";
						cin >> godz;
						if (godz[1] == '9' && godz[0] == '9') {
							break;
						}
						Godzina nowa(godz);
						if (y == 1) {
							del_rozklady_z_przystankow(linia);
							m_linie[t].add_odjazd_1(nowa);
							add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
						}
						else {
							del_rozklady_z_przystankow(linia);
							m_linie[t].add_odjazd_2(nowa);
							add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
						}
					}
				}
				else if (x == 2) {
					cout << "Podaj ca³kiem nowe godizny odjazdów z pêtli ";
					if (y == 1) {
						cout << petle[0] << "\nWpisz 99 aby zakoñczyæ\n";
					}
					else {
						cout << petle[1] << "\nWpisz 99 aby zakoñczyæ\n";
					}
					vector<Godzina> nowe;
					while (1) {
						string godz;
						cout << "HH:MM\b\b\b\b\b";
						cin >> godz;
						if (godz[1] == '9' && godz[0] == '9') {
							break;
						}
						Godzina nowa(godz);
						nowe.push_back(nowa);
					}
					if (y == 1) {
						del_rozklady_z_przystankow(linia);
						m_linie[t].set_odjazdy_1(nowe);
						add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
					}
					else {
						del_rozklady_z_przystankow(linia);
						m_linie[t].set_odjazdy_2(nowe);
						add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
					}
				}
				else if (x == 3) {
					while (1) {
						cout << "Oto godziny odjazdów z pêtli ";
						vector<Godzina> nowe;
						if (y == 1) {
							cout << petle[0] << endl;
							nowe = m_linie[t].get_odjazdy_1();
							m_linie[t].print_odjazdy_1();
						}
						else {
							cout << petle[1] << endl;
							nowe = m_linie[t].get_odjazdy_2();
							m_linie[t].print_odjazdy_2();
						}

						cout << "Któr¹ godzine chcesz usn¹æ\nWprowadŸ 99 aby zakoñczyæ usuwanie\nhh\b\b";
						string godz;
						cout << "HH:MM\b\b\b\b\b";
						cin >> godz;
						if (godz[1] == '9' && godz[0] == '9') {
							break;
						}
						Godzina usun(godz);
						int i;
						for (i = 0; i < size(nowe); i++) {
							if (usun == nowe[i]) {
								nowe.erase(nowe.begin() + i);
								cout << i << endl;
								if (y == 1) {
									del_rozklady_z_przystankow(linia);
									m_linie[t].set_odjazdy_1(nowe);
									add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);

								}
								else {
									del_rozklady_z_przystankow(linia);
									m_linie[t].set_odjazdy_2(nowe);
									add_roklady_do_przystankow(m_linie[int_linia(linia)].get_trasa(), m_linie[int_linia(linia)].get_czas(), m_linie[int_linia(linia)].get_odjazdy_1(), m_linie[int_linia(linia)].get_odjazdy_2(), linia);
								}
							}
						}
						if (i == size(nowe)) {
							cout << "Nie mogê znaleœæ takiej godziny, sporóbuj ponownie\n";
						}
					}
				}
				else {
					cout << "Ÿle wprowadzony numer";
				}
				edit_file_linia(linia);
			}
		}
		else {
			cout << "Nie ma takiej lini w bazie\nSprawdŸ czy poprawnie wprowadzono poprawnie numer linii\n";
		}
}

void Miasto::print_rozklad_lini(void)
{
	cout << "Dostêpne linie w bazie to:\n";
	print_linie();
	cout << "Wpisz numer linii której chcesz sprawdziæ rozk³ad     \b\b\b";
	int nr, x;
	nr = get_number();
	if (check_linia(nr)) {
		if (size(m_linie[int_linia(nr)].get_trasa()) != 0) {
			cout << "Oto trasa linii\n";
			m_linie[int_linia(nr)].print_trasa();
			cout << "Wpisz pe³n¹ nazwê przystanku dla którego chcesz sprawdziæ rozk³ad dla linii " << nr << endl;
			string przystanek;
			cin.ignore();
			getline(cin, przystanek);
			if (check_przystanek(przystanek)) {
				vector<string> petle = m_linie[int_linia(nr)].get_petle();
				cout << "W któr¹ stornê jedziesz?\n1. " << petle[0] << "\n2. " << petle[1] << endl;
				x = get_number();
				if (x == 1) {
					m_linie[int_linia(nr)].print_rozklad_2(przystanek);
				}
				if (x == 2) {
					m_linie[int_linia(nr)].print_rozklad_1(przystanek);
				}
			}
			else {
				cout << "Nie rozpoznano przystanku\n";
			}
		}
		else {
			cout << "Brak trasy linii w bazie" << endl;
		}
	}
	else {
		cout << "Nie ma takiej linii sprubuj ponownie\n";
	}
}

void Miasto::print_trasa(void)
{
	int linia;
	cout << "Której lini trase wyœwietliæ?\t";
	linia = get_number();
	if (check_linia(linia)) {
		m_linie[int_linia(linia)].print_trasa();
	}
	else {
		cout << "Nie ma takiej linii w bazie\n";
	}
}

void Miasto::print_rozklad_przystanku(void)
{
	cout << "WprawdŸ nazwe przystanku, która jest zgodna z dostêpnymi w bazie\n";
	print_przystanki();
	string przystanek;
	cin.ignore();
	getline(cin, przystanek);
	if (check_przystanek(przystanek)) {
		m_przystanki[int_przystanek(przystanek)].print_rozklad();
	}
	else {
		cout << "Nie rozpoznano przystanku\n";
	}
}

void Miasto::print_linie_na_przystanku(void)
{
	cout << "WprowadŸ nazwe przystanku spoœród dostêpnych\n";
	print_przystanki();
	string przystanek;
	cin.ignore();
	getline(cin, przystanek);
	if (check_przystanek(przystanek)) {
		m_przystanki[int_przystanek(przystanek)].print_linie();
	}
	else {
		cout << "Nie znaleziono takiego przystanku\n";
	}

}

void Miasto::add_roklady_do_przystankow(vector<string> trasa, vector<time_t> czasy, vector<Godzina> odjazdy, vector<Godzina> odjazdy2, int nr)
{
	time_t adt = 0;
	string kierunek = trasa[size(trasa) - 1];
	for (int i = 0; i < size(trasa) - 1; i++) {
		adt = adt + czasy[i];
		for (int j = 0; j < size(odjazdy); j++) {
			Godzina nowa(odjazdy[j].get_h(), odjazdy[j].get_m() + adt);
			m_przystanki[int_przystanek(trasa[i])].add_roklad(nowa.get_h(), nowa.get_m(), nr, kierunek);
		}
	}
	adt = 0;
	czasy.erase(czasy.begin());
	czasy.push_back(0);
	kierunek = trasa[0];
	for (int i = size(trasa) - 1; i > 0; i--) {
		adt = adt + czasy[i];
		for (int j = 0; j < size(odjazdy2); j++) {
			Godzina nowa(odjazdy2[j].get_h(), odjazdy2[j].get_m() + adt);
			m_przystanki[int_przystanek(trasa[i])].add_roklad(nowa.get_h(), nowa.get_m(), nr, kierunek);
		}
	}
}

void Miasto::del_rozklady_z_przystankow(int linia)
{
	vector<string> trasa = m_linie[int_linia(linia)].get_trasa();
	for (int i = 0; i < size(trasa); i++) {
		map<vector<int>, string> rozklad = m_przystanki[int_przystanek(trasa[i])].get_rozklad();
		map<vector<int>, string> rozklad_new;
		for (map<vector<int>, string>::iterator it = rozklad.begin(); it != rozklad.end(); ++it) {
			vector<int> liczby = it->first;
			string kierunek = it->second;
			if (liczby[2] != linia) {
				rozklad_new[liczby] = kierunek;
			}
		}
		m_przystanki[int_przystanek(trasa[i])].set_rozklad(rozklad_new);
	}
}

void Miasto::del_linia_z_przystanku(int linia)
{
	vector<string> trasa = m_linie[int_linia(linia)].get_trasa();
	for (int i = 0; i < size(trasa); i++) {
		m_przystanki[int_przystanek(trasa[i])].del_linia(linia);
	}
}

void Miasto::add_linia_do_przystanku(int linia)
{
	vector<string> petle = m_linie[int_linia(linia)].get_petle();
	vector<string> trasa = m_linie[int_linia(linia)].get_trasa();
	string kierunki = petle[0] + " <-> " + petle[1];
	for (int i = 0; i < size(trasa); i++) {
		m_przystanki[int_przystanek(trasa[i])].add_linia(linia, kierunki);
	}
}

void Miasto::polaczenie(const string& przystanek1, const string& przystanek2, Godzina czas)
{
	constexpr time_t INF = numeric_limits<time_t>::max();
	constexpr time_t DOBA = 24 * 60;

	int p1 = int_przystanek(przystanek1);
	int p2 = int_przystanek(przystanek2);

	vector<time_t> czasy(size(m_przystanki), INF);
	vector<int> poprzedni_przystanek(size(m_przystanki), -1);
	vector<int> poprzednia_linia(size(m_przystanki), -1);
	vector<time_t> poprzedni_odjazd(size(m_przystanki), INF);

	czasy[p1] = czas.to_minuty();

	for (int przesiadka = 0; przesiadka < 10; przesiadka++) {
		for (auto& linia : m_linie) {
			vector<string> trasa = linia.get_trasa();
			vector<vector<Godzina>> rozklad1 = linia.get_rozklad_1();
			vector<vector<Godzina>> rozklad2 = linia.get_rozklad_2();

			for (int i = 0; i + 1 < size(trasa); i++) {
				int from = int_przystanek(trasa[i]);
				int to = int_przystanek(trasa[i + 1]);

				if (czasy[from] == INF) {
					continue;
				}

				time_t czas = czasy[from];
				time_t offset = czas / DOBA * DOBA;
				time_t best = INF, bestOdjazd = INF;

				for (size_t j = 0; j < size(rozklad1[i]); j++) {
					time_t odjazd = rozklad1[i][j].to_minuty() + offset;
					time_t przyjazd = rozklad1[i + 1][j].to_minuty() + offset;

					while (odjazd < czas) {
						odjazd += DOBA;
						przyjazd += DOBA;
					}

					while (przyjazd < odjazd) {
						przyjazd += DOBA;
					}

					if (przyjazd < best) {
						best = przyjazd;
						bestOdjazd = odjazd;
					}
				}

				if (best < czasy[to]) {
					czasy[to] = best;
					poprzedni_przystanek[to] = from;
					poprzednia_linia[to] = linia.get_numer();
					poprzedni_odjazd[to] = bestOdjazd;
				}
			}

			for (int i = 0; i + 1 < size(trasa); i++) {
				int from = int_przystanek(trasa[size(trasa) - i - 1]);
				int to = int_przystanek(trasa[size(trasa) - i - 2]);

				if (czasy[from] == INF) {
					continue;
				}

				time_t czas = czasy[from];
				time_t offset = czas / DOBA * DOBA;
				time_t best = INF, bestOdjazd = INF;

				for (size_t j = 0; j < size(rozklad2[i]); j++) {
					time_t odjazd = rozklad2[i][j].to_minuty() + offset;
					time_t przyjazd = rozklad2[i + 1][j].to_minuty() + offset;

					while (odjazd < czas) {
						odjazd += DOBA;
						przyjazd += DOBA;
					}

					while (przyjazd < odjazd) {
						przyjazd += DOBA;
					}

					if (przyjazd < best) {
						best = przyjazd;
						bestOdjazd = odjazd;
					}
				}

				if (best < czasy[to]) {
					czasy[to] = best;
					poprzedni_przystanek[to] = from;
					poprzednia_linia[to] = linia.get_numer();
					poprzedni_odjazd[to] = bestOdjazd;
				}
			}
		}
	}

	if (czasy[p2] == INF) {
		cout << "Brak polaczenia!\n";
		return;
	}

	vector<int> trasa;
	int pos = p2;

	while (pos != -1) {
		trasa.push_back(pos);
		pos = poprzedni_przystanek[pos];
	}

	reverse(trasa.begin(), trasa.end());

	for (int i = 1; i < size(trasa); i++) {
		int from = trasa[i - 1], to = trasa[i];
		time_t odjazd = poprzedni_odjazd[to];
		time_t przyjazd = czasy[to];
		int linia = poprzednia_linia[to];

		cout << m_przystanki[from].get_nazwa() << " ";
		Godzina(0, odjazd).print_bez_linii();
		cout << " -> ";
		Godzina(0, przyjazd).print_bez_linii();
		cout << " " << m_przystanki[to].get_nazwa() << ", linia " << linia << endl;
	}

	cout << endl;
}

void Miasto::polaczenie_lu(void)
{
	cout << "Wpisz przystanek z którego rozpoczynasz podró¿:\t";
	string przyst1, przyst2;
	cin.ignore();
	while (1) {
		getline(cin, przyst1);
		if (check_przystanek(przyst1)) {
			break;
		}
		else {
			cout << "Nie rozpoznano przystanku\nSpróbuj ponownie\nOto dostêpne przystanki w mieœcie\n";
			print_przystanki();
		}
	}
	cout << "Wpisz nazwe przystanku koñcowego:\t";
	while (1) {
		getline(cin, przyst2);
		if (check_przystanek(przyst2)) {
			break;
		}
		else {
			cout << "Nie rozpoznano przystanku\nSpróbuj ponownie\nOto dostêpne przystanki w mieœcie\n";
			print_przystanki();
		}
	}
	cout << "WprowadŸ godzine rozpoczêcia podróŸy w formacie HH:MM\n";
	string godz;
	cout << "HH:MM\b\b\b\b\b";
	cin >> godz;
	polaczenie(przyst1, przyst2, { godz });
}

void Miasto::update_trasa(const string& przystanek_old, const string& przystanek_new)
{
	map<int, string> linie = m_przystanki[int_przystanek(przystanek_new)].get_linie();
	for (pair<int, string>element : linie) {
		vector<string> trasa = m_linie[int_linia(element.first)].get_trasa();
		vector<string> trasa_new;
		for (int i = 0; i < size(trasa); i++) {
			if (trasa[i] == przystanek_old) {
				trasa_new.push_back(przystanek_new);
			}
			else {
				trasa_new.push_back(trasa[i]);
			}
		}
		m_linie[int_linia(element.first)].add_trasa(trasa_new);
	}
}

void Miasto::open_file_stop(void)
{
	ifstream file;
	file.open("przystanki.txt", ios::in);
	if (file.is_open()) {
		string tr, nazwa, typ, nz, strefa;
		int i = 0;
		float gps_n, gps_e;
		map<int, string> linie = {};
		map<vector<int>, string> linie_r;
		while (getline(file, tr)) {
			switch (i)
			{
			case 0:
				nazwa = tr;
				break;
			case 1:
				gps_n = stof(tr);
				break;
			case 2:
				gps_e = stof(tr);
				break;
			case 3:
				nz = tr;
				break;
			case 4:
				typ = tr;
				break;
			case 5:
				strefa = tr;
				break;
			default:
				break;
			}
			if (i == 5) {
				BTS_przystanek przyst(nazwa, gps_n, gps_e, typ, nz, strefa, linie, linie_r);
				m_przystanki.push_back(przyst);
				i = -1;
			}
			i++;
		}
		file.close();
	}
}

void Miasto::open_file_bus(void)
{
	ifstream pliki;
	pliki.open("linie.txt", ios::in);
	string fname, tmp, rodzaj, strefa;
	while (getline(pliki, fname)) {
		ifstream plik;
		vector<string> trasa;
		vector<Godzina> odjazdy, odjazdy2;
		vector<time_t> czas;
		int nr;
		int i{};
		int j{};
		int k{};
		plik.open(fname, ios::in);
		if (plik.is_open()) {
			while (getline(plik, tmp)) {
				if (i == 0) {
					nr = stoi(tmp);
					i++;
				}
				else if (i == 1) {
					rodzaj = tmp;
					i++;
				}
				else if (i == 2) {
					strefa = tmp;
					i++;
				}
				else if (i == 3) {
					if (tmp == "pêtla") {
						i++;
					}
					else {
						trasa.push_back(tmp);
						j++;
					}
				}
				else if (i == 4) {
					if (k == j) {
						i++;
					}
					else {
						czas.push_back(stoi(tmp));
						k++;
					}
				}
				else if (i == 5) {
					if (tmp[0] == '9' && tmp[1] == '9') {
						i++;
					}
					else {
						odjazdy.push_back(Godzina(tmp));
					}
				}
				else if (i == 6) {
					if (tmp[0] == '9' && tmp[1] == '9') {
						break;
					}
					else {
						odjazdy2.push_back(Godzina(tmp));
					}
				}
			}
			if (i > 5) {
				BTS_linia nowa(nr, rodzaj, strefa, trasa, odjazdy, odjazdy2, czas);
				add_roklady_do_przystankow(trasa, czas, odjazdy, odjazdy2, nr);
				m_linie.push_back(nowa);
				add_linia_do_przystanku(nr);
			}
			else {
				BTS_linia nowa(nr, rodzaj, strefa);
				m_linie.push_back(nowa);
			}
			plik.close();
		}
	}
	pliki.close();
}

void Miasto::edit_file_linia(int numer)
{
	string fname = "linia_" + to_string(numer) + ".txt";
	remove(fname.c_str());
	fstream tmp;
	tmp.open(fname, ios::in | ios::out | ios::app);
	int t = int_linia(numer);
	tmp << m_linie[t].get_numer() << endl;
	tmp << m_linie[t].get_rodzaj() << endl;
	tmp << m_linie[t].get_strefa() << endl;
	vector<string> trasa = m_linie[t].get_trasa();
	for (int x = 0; x < size(m_linie[t].get_trasa()); x++) {
		tmp << trasa[x] << endl;
	}

	tmp << "pêtla" << endl;
	vector<time_t> czasy = m_linie[t].get_czas();
	for (int x = 0; x < size(m_linie[t].get_czas()); x++) {
		tmp << czasy[x] << endl;
	}
	tmp << "99" << endl;
	vector<Godzina> vec_temp = m_linie[t].get_odjazdy_1();
	for (int x = 0; x < size(m_linie[t].get_odjazdy_1()); x++) {
		tmp << vec_temp[x].get_h() << ":" << vec_temp[x].get_m() << endl;
	}
	tmp << "99" << endl;
	vec_temp = m_linie[t].get_odjazdy_2();
	for (int x = 0; x < size(m_linie[t].get_odjazdy_2()); x++) {
		tmp << vec_temp[x].get_h() << ":" << vec_temp[x].get_m() << endl;
	}
	tmp << "99" << endl;
	tmp.close();
}

double Miasto::get_number_d(void)
{
	double number;
	while (1)
	{
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "To nie jest liczba..." << endl;
		}
		else
			break;
		cout << "Spróbuj ponownie" << endl;
	}
	return number;
}

int Miasto::get_number(void)
{
	int number;
	while (1)
	{
		cin >> number;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "To nie jest liczba..." << endl;
		}
		else
			break;
		cout << "Spróbuj ponownie" << endl;
	}
	return number;
}


