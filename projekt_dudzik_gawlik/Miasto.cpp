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
	cout << "Witamy w systemie zarz�dzania transporu publicznego miasta " << m_miasto << endl;
	string i, j;
	while (1) {
		cout << "Wpisz co chcesz zrobi�:\n";
		cout << "1\tAby sprawdzi� rozk�ad jazdy\n2\tAby znale�� po��czenie\n3\tAby edytowa� linie i przystanki\n99\tZako�cz\n";
		cin >> i;
		if (i == "1") {
			system("cls");
			cout << "1\tWy�wietl rozk�ad jazdy przystanku\n2\tSprawd� rozk�ad lini\n3\tSprawd� kt�re linie obs�uguj� konkretny przystanek\n4\tSprawd� tras� linii\n5\tSprawd� dost�pne przystanki\n6\tSprawd� dost�pne linie\n";
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
			cout << "1\tDodaj przystanek\n2\tDoda� linie\n3\tEdycja przystanku\n4\tEdycja lini\n";
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
		cout << "Czy przystanek jest na ��danie?\n";
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
		cout << "Przystanek o podanej nazwie istniej w bazie\nMo�esz wyedytowa� ten przystanek\n";
	}
}

void Miasto::print_przystanki(void)
{
	if (size(m_przystanki) > 0) {
		cout << "Przystanki w mie�cie " << m_miasto << endl;
		for (int i = 0; i < size(m_przystanki); i++) {
			cout << i + 1 << ". " << m_przystanki[i].get_nazwa() << endl;
		}
	}
	else {
		cout << "Brak przystank�w w mie�cie\n";
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
		cout << "Dodaj trase linia. Wpisz nazwe przystank�w po kolei dost�pnych w bazie. Wpisz \"p�tla\" aby zako�czy�.\n";
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
			if (przystanek == "p�tla") {
				if (size(trasa) != 0) {
					string kierunki = trasa[0] + " <-> " + trasa[size(trasa) - 1];
					if (file.is_open()) {
						file << "p�tla" << endl;
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
			cout << "Podaj czas jaki potrzebuje " << rodzaj << " aby dotrze� z przystanku do przystanku\n";
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
			cout << "Dodaj godziny startu o kt�rej " << rodzaj << " startuje z p�tli " << trasa[0] << "\nDane wporwadzaj w formacie HH:MM gdzie HH to godzina ':' i MM to minuta\nWpisz 99 aby zako�czy�" << endl;
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
			cout << "Dodaj godziny startu o kt�rej " << rodzaj << " startuje z p�tli " << trasa[size(trasa) - 1] << "\nDane wporwadzaj w formacie HH:MM gdzie HH to godzina ':' i MM to minuta\nWpisz 99 aby zako�czy�" << endl;
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
		cout << "Linia o podanym numerze ju� istnieje\n";
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
		cout << "Linie obs�uguj�ce miasto " << m_miasto << endl;
		for (int i = 0; i < size(m_linie); i++) {
			vector<string> trasa = m_linie[i].get_petle();
			cout << i + 1 << ". " << m_linie[i].get_numer() << "\t" << trasa[0] << "  <->  " << trasa[1] << endl;
		}
	}
	else {
		cout << "�adne linie nie s� dost�ne w mie�cie\nNajpierw dodaj linie\n";
	}

}

void Miasto::edit_przystanek(void)
{
	cout << "Jaki przystanek chcesz edytowa�, podaj jego nazwe\n";
	string przystanek, tr;
	cin.ignore();
	getline(cin, przystanek);
	if (check_przystanek(przystanek)) {
		int u;
		int i{};
		int t = int_przystanek(przystanek);
		cout << "Wybierz cz�� kt�r� chcesz zmieni�\n1 -> Nazwa\n2 -> Lokacja GPS N\n3 -> Lokacja GPS E\n4 -> Na ��danie\n5 -> Typ obs�ugi\n6 -> Strefa\n7 -> Aby zako�czy� edycje\n";
		u = get_number();
		string nazwa, nz, typ, strefa, tofile;
		double gps_n, gps_e;
		switch (u)
		{
		case 1:
			cout << "Wprowad� now� nazwe przystanku\n";
			cin.ignore();
			getline(cin, nazwa);
			tofile = nazwa;
			m_przystanki[t].set_nazwa(nazwa);
			update_trasa(przystanek, nazwa);
			break;
		case 2:
			cout << "Wprowad� now� lokacje GPS N\n";
			cin.ignore();
			gps_n = get_number_d();
			tofile = to_string(gps_n);
			m_przystanki[t].set_gps_n(gps_n);
			break;
		case 3:
			cout << "Wprowad� now� lokacje GPS E\n";
			cin.ignore();
			gps_e = get_number_d();
			tofile = to_string(gps_e);
			m_przystanki[t].set_gps_e(gps_e);
			break;
		case 4:
			cout << "Czy przystanek jest na ��danie?\n";
			cin.ignore();
			cin >> nz;
			tofile = nz;
			m_przystanki[t].set_nz(nz);
			break;
		case 5:
			cout << "Wprowad� co teraz obs�uguje przystanek BUS, TRAM, BUS-TRAM\n";
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
		cout << "Nie ma takiego przystanku w bazie\nNajpierw dodaj przystanek albo sprad� czy nazwa przystanku zosta�a poprawnie wprowadzona\n";
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
	cout << "Kt�r� linie chcesz edytowa�?\n";
	string l;
	int linia;
	cin.ignore();
	linia = get_number();
		if (check_linia(linia)) {
			int u, t, numer, z, j;
			t = int_linia(linia);
			cout << "Wybierz kt�r� cz�� chcesz wyedytowa�\n1 -> Numer\n2 -> Rodzaj\n3 -> Strefa\n4 -> Trasa\n5 -> Czasy mi�dzy przystankami\n6 -> Odjazdy z p�tli\t";
			u = get_number();
			j = 0;
			string rodzaj, strefa, trasa_s, przystanek;
			vector<string> trasa;
			vector<time_t> czas;
			switch (u) {
			case 1:
				cout << "Wprowad� nowy numer lini\n";
				cin.ignore();
				numer = get_number();
				if (check_linia(numer)) {
					cout << "Numer linii jest ju� u�ywany, nie wprowadzono zmian\n";
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
				cout << "Wprowad� nowy rodzaj lini\nBUS TRAM \n";
				cin.ignore();
				cin >> rodzaj;
				m_linie[t].set_rodzaj(rodzaj);
				edit_file_linia(linia);
				break;
			case 3:
				cout << "Wprowad� akutaln� strefe \n";
				cin.ignore();
				cin >> strefa;
				m_linie[t].set_strefa(strefa);
				edit_file_linia(linia);
				break;
			case 4:
				cout << "Je�li chcesz wproadzi� ca�� now� trase wybierz 1\nJe�li chcesz doda� jeden przystanek do aktualnej trasy wybierz 2\nJe�li chcesz usun�� przystanek z akualnej trasy wybierz 3\n";
				cin >> z;
				if (z == 1) {
					cout << "Wpisz nazwy przystank�w po kolei. Aby zako�czy� wpisz p�tla\n";
					cin.ignore();
					j = 1;
					while (1) {
						cout << j << ". ";
						getline(cin, przystanek);
						if (przystanek == "p�tla") {
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
					cout << "Podaj czas jaki potrzebuje " << rodzaj << " aby dotrze� z przystanku do przystanku\n";
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
						cout << "Najpierw dodaj tras� do linii\n";
						break;
					}
					cout << "Oto aktualna trasa lini " << linia << endl;
					vector<string> trasa_old = m_linie[t].get_trasa();
					m_linie[t].print_trasa();
					int nr;
					cout << "Wpisz numer jaki ma mie� nowy przystanek\n";
					nr = get_number();
					nr = nr - 1;
					if (nr <= trasa_old.size()) {
						cout << "Wpisz nazw� nowego przystanku\n";
						cin.ignore();
						while (1) {
							getline(cin, przystanek);
							if (check_przystanek(przystanek)) {
								break;
							}
							else {
								cout << "Nie ma takiego przystanku w bazie. Spr�buj ponownie\n";
							}
						}
						cout << nr << "\n" << trasa_old.size() << endl;
						trasa_old.insert(trasa_old.begin() + nr, przystanek);
						time_t t1, t2;
						cout << nr << "\n" << trasa_old.size() << endl;
						vector<time_t> czas = m_linie[t].get_czas();
						if (nr == 0) {
							cout << 1 << endl;
							cout << "Wprowad� czas jaki potrzebny jest aby pojazd dosta� si� z przystanku " << trasa_old[nr] << " do przystanku " << trasa_old[nr + 1] << endl;
							t1 = get_number();
							czas.insert(czas.begin() + 1, t1);
						}
						else if ((nr + 1) == trasa_old.size()) {
							cout << 2 << endl;
							cout << "Wprowad� czas jaki potrzebny jest aby pojazd dosta� si� z przystanku " << trasa_old[nr - 1] << " do przystanku " << trasa_old[nr] << endl;
							t1 = get_number();
							czas.push_back(t1);
						}
						else {
							cout << 3 << endl;
							cout << "Wprowad� czas jaki potrzebny jest aby pojazd dosta� si� z przystanku " << trasa_old[nr - 1] << " do przystanku " << trasa_old[nr] << endl;
							t1 = get_number();
							cout << "Wprowad� czas jaki potrzebny jest aby pojazd dosta� si� z przystanku " << trasa_old[nr] << " do przystanku " << trasa_old[nr + 1] << endl;
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
						cout << "Za du�a warto��, spr�buj ponownie.\n";
					}
				}
				else if (z == 3) {
					if (size(m_linie[t].get_trasa()) == 0) {
						cout << "Najpierw dodaj tras� do linii\n";
						break;
					}
					cout << "Oto aktualna trasa lini " << linia << endl;
					m_linie[t].print_trasa();
					int nr;
					cout << "Wpisz numer jaki ma zosta� usuni�ty\n";
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
							cout << "Wprowad� czas jaki potrzebny jest aby pojazd dosta� si� z przystanku " << trasa[nr - 1] << " do przystanku " << trasa[nr] << endl;
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
						cout << "Zakres przekroczny. Spr�buj ponownie.\n";
					}
				}
				else {
					cout << "Spr�buj ponownie\n";
				}
				edit_file_linia(linia);
				break;
			case 5:
				if (size(m_linie[t].get_trasa()) == 0) {
					cout << "Najpierw dodaj tras� do linii\n";
					break;
				}
				cout << "Zmie� czasy przejazd�w mi�dzy przystankami\n";
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
					cout << "Najpierw dodaj tras� do linii\n";
					break;
				}
				int x, y;
				cout << "Dodawanie nowych godzin odjazd�w z p�tli\n1 aby doda� kilka nowych odjazd�w\n2 aby doda� ca�kiem nowe godziny odjazd�w\n3 aby usun�� niekt�re godziny odjazd�w\n";
				x = get_number();
				cin.ignore();
				vector<string> petle = m_linie[t].get_petle();
				cout << "Z wyjazdy z kt�rej p�tli b�d� edytowane\n1. " << petle[0] << "\n2. " << petle[1] << endl;
				y = get_number();
				if (x == 1) {
					cout << "Podaj nowe dodatkowe godziny wyjazd�w z p�tli ";
					if (y == 1) {
						cout << petle[0] << "\nWpisz 99 aby zako�czy�\n";
					}
					else {
						cout << petle[1] << "\nWpisz 99 aby zako�czy�\n";
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
					cout << "Podaj ca�kiem nowe godizny odjazd�w z p�tli ";
					if (y == 1) {
						cout << petle[0] << "\nWpisz 99 aby zako�czy�\n";
					}
					else {
						cout << petle[1] << "\nWpisz 99 aby zako�czy�\n";
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
						cout << "Oto godziny odjazd�w z p�tli ";
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

						cout << "Kt�r� godzine chcesz usn��\nWprowad� 99 aby zako�czy� usuwanie\nhh\b\b";
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
							cout << "Nie mog� znale�� takiej godziny, spor�buj ponownie\n";
						}
					}
				}
				else {
					cout << "�le wprowadzony numer";
				}
				edit_file_linia(linia);
			}
		}
		else {
			cout << "Nie ma takiej lini w bazie\nSprawd� czy poprawnie wprowadzono poprawnie numer linii\n";
		}
}

void Miasto::print_rozklad_lini(void)
{
	cout << "Dost�pne linie w bazie to:\n";
	print_linie();
	cout << "Wpisz numer linii kt�rej chcesz sprawdzi� rozk�ad     \b\b\b";
	int nr, x;
	nr = get_number();
	if (check_linia(nr)) {
		if (size(m_linie[int_linia(nr)].get_trasa()) != 0) {
			cout << "Oto trasa linii\n";
			m_linie[int_linia(nr)].print_trasa();
			cout << "Wpisz pe�n� nazw� przystanku dla kt�rego chcesz sprawdzi� rozk�ad dla linii " << nr << endl;
			string przystanek;
			cin.ignore();
			getline(cin, przystanek);
			if (check_przystanek(przystanek)) {
				vector<string> petle = m_linie[int_linia(nr)].get_petle();
				cout << "W kt�r� storn� jedziesz?\n1. " << petle[0] << "\n2. " << petle[1] << endl;
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
	cout << "Kt�rej lini trase wy�wietli�?\t";
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
	cout << "Wprawd� nazwe przystanku, kt�ra jest zgodna z dost�pnymi w bazie\n";
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
	cout << "Wprowad� nazwe przystanku spo�r�d dost�pnych\n";
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
	cout << "Wpisz przystanek z kt�rego rozpoczynasz podr�:\t";
	string przyst1, przyst2;
	cin.ignore();
	while (1) {
		getline(cin, przyst1);
		if (check_przystanek(przyst1)) {
			break;
		}
		else {
			cout << "Nie rozpoznano przystanku\nSpr�buj ponownie\nOto dost�pne przystanki w mie�cie\n";
			print_przystanki();
		}
	}
	cout << "Wpisz nazwe przystanku ko�cowego:\t";
	while (1) {
		getline(cin, przyst2);
		if (check_przystanek(przyst2)) {
			break;
		}
		else {
			cout << "Nie rozpoznano przystanku\nSpr�buj ponownie\nOto dost�pne przystanki w mie�cie\n";
			print_przystanki();
		}
	}
	cout << "Wprowad� godzine rozpocz�cia podr�y w formacie HH:MM\n";
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
					if (tmp == "p�tla") {
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

	tmp << "p�tla" << endl;
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
		cout << "Spr�buj ponownie" << endl;
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
		cout << "Spr�buj ponownie" << endl;
	}
	return number;
}


