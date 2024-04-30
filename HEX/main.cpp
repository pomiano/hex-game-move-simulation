#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

struct Plansza {
	char pionki[11][11];
	int szerokosc;
	int czerwone, niebieskie;
};
struct Punkt {
	int x, y;
};

int DFS(int x, int y, Plansza &plansza, int kierunek, int odwiedzone[11][11]);
std::string sprawdz_game_over(Plansza &plansza);
std::string czy_plansza_mozliwa(Plansza &plansza);
bool perfect_2(Plansza &plansza, char kolor);
bool perfect_3(Plansza &plansza, char kolor);
bool perfect_4(Plansza &plansza, char kolor);
std::string sprawdz_poprawnosc(Plansza& plansza);
void wyzeruj_tablice(int tablica[11][11], int szerokosc);
std::string sprawdz_wygrana_z_naiwnym(Plansza& plansza, char kolor, int ile_ruchow);
std::string sprawdz_wygrana_z_perfekcyjnym(Plansza& plansza, char kolor, int ile_ruchow);
bool game_over_bez_jednego(Plansza& plansza, char kolor);
int przesun_xy(int& pion, int& poziom, bool po_polowie, int szerokosc);
void przetworz_polecenie(std::string& polecenie, Plansza& plansza);
void wczytaj_plansze(Plansza& plansza);
bool sprawdz_podstawe_do_wygranych(Plansza& plansza, int& ruchy, int ile_ruchow, char kolor, std::string& napis);

int main() {
	Plansza plansza;
	std::string komenda;
	while (std::cin >> komenda) {
		if (komenda == "---") {
			wczytaj_plansze(plansza);
		}
		else {
			przetworz_polecenie(komenda, plansza);
		}
	}
	return 0;
}

void wyzeruj_tablice(int tablica[11][11], int szerokosc) {
	for (int i = 0; i < szerokosc; i++) {
		for (int j = 0; j < szerokosc; j++) {
			tablica[i][j] = 0;
		}
	}
}

std::string sprawdz_wygrana_z_naiwnym(Plansza& plansza, char kolor, int ile_ruchow) {
	int ruchy;
	std::string napis;

	if (sprawdz_podstawe_do_wygranych(plansza, ruchy, ile_ruchow, kolor, napis) == false) {
		return "NO";
	}

	if (ile_ruchow == 1) {
		for (int i = 0; i < plansza.szerokosc; i++) {
			for (int j = 0; j < plansza.szerokosc; j++) {
				if (plansza.pionki[j][i] == ' ') {
					plansza.pionki[j][i] = kolor;
					if (sprawdz_game_over(plansza) != "NO") {
						plansza.pionki[j][i] = ' ';
						return "YES";
					}
					plansza.pionki[j][i] = ' ';
				}
			}
		}
	}
	else if (ile_ruchow == 2) {
		for (int i = 0; i < plansza.szerokosc; i++) {
			for (int j = 0; j < plansza.szerokosc; j++) {
				if (plansza.pionki[j][i] == ' ') {
					plansza.pionki[j][i] = kolor;
					if (sprawdz_game_over(plansza) == "NO") {
						for (int k = 0; k < plansza.szerokosc; k++) {
							for (int l = 0; l < plansza.szerokosc; l++) {
								if (plansza.pionki[l][k] == ' ') {
									plansza.pionki[l][k] = kolor;
									if (sprawdz_game_over(plansza) == napis) {
										plansza.pionki[l][k] = ' ';
										plansza.pionki[j][i] = ' ';
										return "YES";
									}
									plansza.pionki[l][k] = ' ';
								}
							}
						}
					}
					plansza.pionki[j][i] = ' ';
				}
			}
		}
	}
	return "NO";
}

std::string sprawdz_wygrana_z_perfekcyjnym(Plansza& plansza, char kolor, int ile_ruchow) {
	int ruchy;
	std::string napis;
	
	if (sprawdz_podstawe_do_wygranych(plansza, ruchy, ile_ruchow, kolor, napis) == false) {
		return "NO";
	}

	switch (ruchy) {
	case 1:
		for (int i = 0; i < plansza.szerokosc; i++) {
			for (int j = 0; j < plansza.szerokosc; j++) {
				if (plansza.pionki[j][i] == ' ') {
					plansza.pionki[j][i] = kolor;
					if (sprawdz_game_over(plansza) != "NO") {
						plansza.pionki[j][i] = ' ';
						return "YES";
					}
					plansza.pionki[j][i] = ' ';
				}
			}
		}
		return "NO";
	case 2:
		if (perfect_2(plansza, kolor) == true)
			return "YES";
		else
			return "NO";

	case 3:
		if (perfect_3(plansza, kolor) == true)
			return "YES";
		else
			return "NO";
	case 4:
		if (perfect_4(plansza, kolor) == true)
			return "YES";
		else
			return "NO";
	}
	return "NO";
}

bool sprawdz_podstawe_do_wygranych(Plansza &plansza, int &ruchy,int ile_ruchow, char kolor, std::string&napis) {
	if (sprawdz_poprawnosc(plansza) == "YES") {
		if (sprawdz_game_over(plansza) != "NO") {
			return false;
		}
	}
	else {
		return false;
	}
	if (kolor == 'r') {
		if (plansza.czerwone + ile_ruchow < plansza.szerokosc)
			return false;

		if (plansza.czerwone == plansza.niebieskie)
			ruchy = ile_ruchow * 2 - 1;
		else if (plansza.czerwone == plansza.niebieskie + 1)
			ruchy = ile_ruchow * 2;
		napis = "YES RED";
	}
	else {
		if (plansza.niebieskie + ile_ruchow < plansza.szerokosc)
			return false;

		if (plansza.czerwone == plansza.niebieskie)
			ruchy = ile_ruchow * 2;
		else if (plansza.czerwone == plansza.niebieskie + 1)
			ruchy = ile_ruchow * 2 - 1;
		napis = "YES BLUE";
	}

	if (plansza.czerwone + plansza.niebieskie + ruchy > plansza.szerokosc * plansza.szerokosc) {
		return false;
	}

	return true;

}


bool perfect_2(Plansza& plansza, char kolor) {
	int ile_wygranych = 0;
	for (int i = 0; i < plansza.szerokosc; i++) {
		for (int j = 0; j < plansza.szerokosc; j++) {
			if (plansza.pionki[j][i] == ' ') {
				plansza.pionki[j][i] = kolor;
				if (sprawdz_game_over(plansza) != "NO") {
					ile_wygranych++;
					if (ile_wygranych > 1) {
						plansza.pionki[j][i] = ' ';
						return true;
					}
				}
				plansza.pionki[j][i] = ' ';
			}
		}
	}
	return false;
}

bool perfect_3(Plansza& plansza, char kolor) {
	for (int i = 0; i < plansza.szerokosc; i++) {
		for (int j = 0; j < plansza.szerokosc; j++) {
			if (plansza.pionki[j][i] == ' ') {
				plansza.pionki[j][i] = kolor;
				if (sprawdz_game_over(plansza) == "NO") {
					if (perfect_2(plansza, kolor) == true) {
						plansza.pionki[j][i] = ' ';
						return true;
					}
				}
				plansza.pionki[j][i] = ' ';
			}
		}
	}
	return false;
}

bool perfect_4(Plansza& plansza, char kolor) {
	char drugi_kolor;
	if (kolor == 'r')
		drugi_kolor = 'b';
	else
		drugi_kolor = 'r';

	for (int i = 0; i < plansza.szerokosc; i++) {
		for (int j = 0; j < plansza.szerokosc; j++) {
			if (plansza.pionki[j][i] == ' ') {
				plansza.pionki[j][i] = drugi_kolor;
				if (perfect_3(plansza, kolor) == false) {
					plansza.pionki[j][i] = ' ';
					return false;
				}
				plansza.pionki[j][i] = ' ';
			}
		}
	}

	return true;
}

std::string sprawdz_poprawnosc(Plansza& plansza) {
	if (plansza.niebieskie == plansza.czerwone || plansza.niebieskie + 1 == plansza.czerwone) {
		return "YES";
	}
	else
		return "NO";
}

std::string sprawdz_game_over(Plansza& plansza) {
	int odwiedzone[11][11];
	if (sprawdz_poprawnosc(plansza) == "NO") {
		return "NO";
	}
	for (int i = 0; i < plansza.szerokosc; i++) {
		if (plansza.pionki[i][0] == 'b') {
			wyzeruj_tablice(odwiedzone, plansza.szerokosc);
			if (DFS(i, 0, plansza, 2, odwiedzone) == 1) {
				return "YES BLUE";
			}
		}
	}
	for (int j = 0; j < plansza.szerokosc; j++) {
		if (plansza.pionki[0][j] == 'r') {
			wyzeruj_tablice(odwiedzone, plansza.szerokosc);
			if (DFS(0, j, plansza, 1, odwiedzone) == 1) {
				return "YES RED";
			}
		}
	}
	return "NO";
}

bool game_over_bez_jednego(Plansza& plansza, char kolor) {
	std::string napis;
	if (sprawdz_game_over(plansza) == "YES BLUE") {
		kolor = 'b';
		napis = "YES BLUE";
	}
	else {
		kolor = 'r';
		napis = "YES RED";
	}

	for (int i = 0; i < plansza.szerokosc; i++) {
		for (int j = 0; j < plansza.szerokosc; j++) {
			if (plansza.pionki[j][i] == kolor) {
				plansza.pionki[j][i] = ' ';
				if (sprawdz_game_over(plansza) == "NO") {
					plansza.pionki[j][i] = kolor;
					return true;
				}
				else {
					plansza.pionki[j][i] = kolor;
				}
			}
		}
	}
	return false;
}

std::string czy_plansza_mozliwa(Plansza& plansza) {
	if (sprawdz_poprawnosc(plansza) == "NO") {
		return "NO";
	}
	else {
		if (sprawdz_game_over(plansza) == "NO")
		{
			return "YES";
		}
		else if (sprawdz_game_over(plansza) == "YES RED") {
			if (plansza.czerwone != plansza.niebieskie + 1)
				return "NO";
			else {
				if (game_over_bez_jednego(plansza, 'r') == true)
					return "YES";
				else
					return "NO";
			}
		}
		else {
			if (plansza.czerwone != plansza.niebieskie)
				return "NO";
			else {
				if (game_over_bez_jednego(plansza, 'b') == true)
					return "YES";
				else
					return "NO";
			}
		}
	}
}


int DFS(int x, int y, Plansza& plansza, int kierunek, int odwiedzone[11][11]) {     //kierunek 1 - w poziomie , kierunek 2 - w pionie
	Punkt przesuniecie[6] = { {1,0},{1,1},{0,1},{0,-1},{-1,0},{-1,-1} };
	char szukana = plansza.pionki[x][y];
	int nx, ny;
	odwiedzone[x][y] = 1;
	if ((kierunek == 1 && x == plansza.szerokosc - 1) || (kierunek == 2 && y == plansza.szerokosc - 1)) {
		return 1;
	}
	for (int i = 0; i < 6; i++) {
		nx = x + przesuniecie[i].x;
		ny = y + przesuniecie[i].y;
		if (nx >= 0 && nx < plansza.szerokosc && ny >= 0 && ny < plansza.szerokosc && odwiedzone[nx][ny] == 0 && plansza.pionki[nx][ny] == szukana) {
			if (DFS(nx, ny, plansza, kierunek, odwiedzone) == 1) {
				return 1;
			}
		}
	}
	return 0;
}

int przesun_xy(int& pion, int& poziom, bool po_polowie, int szerokosc) {
	if (po_polowie == false) {
		if (pion == 0) {
			int zmiana = poziom;
			poziom = pion;
			pion = zmiana;
			pion++;
		}
		else {
			poziom++;
			pion--;
		}
	}
	else {
		if (poziom == szerokosc - 1) {
			int zmiana = poziom;
			poziom = pion;
			pion = zmiana;
			poziom++;
		}
		else {
			poziom++;
			pion--;
		}
	}
	return 0;
}

void przetworz_polecenie(std::string& polecenie, Plansza& plansza) {
	if (polecenie == "BOARD_SIZE") {
		std::cout << plansza.szerokosc << std::endl;
	}
	else if (polecenie == "PAWNS_NUMBER") {
		std::cout << plansza.niebieskie + plansza.czerwone << std::endl;
	}
	else if (polecenie == "IS_BOARD_CORRECT") {
		std::cout << sprawdz_poprawnosc(plansza) << std::endl;
	}
	else if (polecenie == "IS_GAME_OVER") {
		std::cout << sprawdz_game_over(plansza) << std::endl;
	}
	else if (polecenie == "IS_BOARD_POSSIBLE") {
		std::cout << czy_plansza_mozliwa(plansza) << std::endl;
	}
	else if (polecenie == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
		std::cout << sprawdz_wygrana_z_naiwnym(plansza, 'r', 1) << std::endl;
	}
	else if (polecenie == "CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT") {
		std::cout << sprawdz_wygrana_z_naiwnym(plansza, 'b', 1) << std::endl;
	}
	else if (polecenie == "CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
		std::cout << sprawdz_wygrana_z_naiwnym(plansza, 'r', 2) << std::endl;
	}
	else if (polecenie == "CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT") {
		std::cout << sprawdz_wygrana_z_naiwnym(plansza, 'b', 2) << std::endl;
	}
	else if (polecenie == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
		std::cout << sprawdz_wygrana_z_perfekcyjnym(plansza, 'r', 1) << std::endl;
	}
	else if (polecenie == "CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT") {
		std::cout << sprawdz_wygrana_z_perfekcyjnym(plansza, 'b', 1) << std::endl;
	}
	else if (polecenie == "CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
		std::cout << sprawdz_wygrana_z_perfekcyjnym(plansza, 'r', 2) << std::endl;
	}
	else if (polecenie == "CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT") {
		std::cout << sprawdz_wygrana_z_perfekcyjnym(plansza, 'b', 2) << std::endl;
	}
}

void wczytaj_plansze(Plansza& plansza) {
	char pole;
	bool obecnosc_pionka = false, po_polowie = false, ostatni_daszek = false, koniec = false;
	int pion = 0, poziom = 0;
	char ciag[5];
	plansza.czerwone = 0;
	plansza.niebieskie = 0;
	while (koniec == false) {
		if (scanf("%s", ciag)) {
			if (!strcmp(ciag, "<") || !strcmp(ciag, "--<")) {
				obecnosc_pionka = false;
			}
			else if (!strcmp(ciag, ">-<")) {
				if (obecnosc_pionka == true) {
					plansza.pionki[poziom][pion] = pole;
				}
				else {
					plansza.pionki[poziom][pion] = ' ';
				}
				przesun_xy(pion, poziom, po_polowie, plansza.szerokosc);
				obecnosc_pionka = false;
			}
			else if (!strcmp(ciag, ">--")) {
				if (obecnosc_pionka == true) {
					plansza.pionki[poziom][pion] = pole;
				}
				else {
					plansza.pionki[poziom][pion] = ' ';
				}
				przesun_xy(pion, poziom, po_polowie, plansza.szerokosc);

			}
			else if (!strcmp(ciag, ">")) {
				if (obecnosc_pionka == true) {
					plansza.pionki[poziom][pion] = pole;
				}
				else {
					plansza.pionki[poziom][pion] = ' ';
				}
				przesun_xy(pion, poziom, po_polowie, plansza.szerokosc);
				pion--;
				poziom++;
				po_polowie = true;
				plansza.szerokosc = pion + 1;
			}
			else if (obecnosc_pionka == false && (!strcmp(ciag, "r") || !strcmp(ciag, "b"))) {
				obecnosc_pionka = true;
				if (!strcmp(ciag, "r")) {
					pole = 'r';
					plansza.czerwone++;
				}
				else {
					pole = 'b';
					plansza.niebieskie++;
				}

			}
			else if (!strcmp(ciag, "---")) {
				koniec = true;
			}
		}
	}
}