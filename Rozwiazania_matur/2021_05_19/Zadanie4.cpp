#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;


int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	string instr;
	
	// Zadanie 2
	// najdłuższy ciąg takich samych wartości
	int z1_it = 1;
	string z1_last_type = "";
	int z1_max = 1;
	string z1_max_type = "";
	
	// Zadanie 3
	// Tablica do sortowania kubełkowego
	// 26 - ilość liter w alfabecie
	int z2[26] = {0};
	
	
	/////////////////
	// Zamiast standardowego "dane >> instr" używam getline. Powoduje to że dostaję całą linijkę, 
	// zamiast na zmianę typu instrukcji i wartości. Tak samo jak >> zwróci eof kiedy skończy się plik,
	// co przez while-a zostanie potrakotwane jako fałsz i "wyjdzie" z pętli.
	// Taki gtetline wpisze do instr kolejną linijkę z dane
	while(getline (dane, instr)){
		
		int pos = instr.find(" "); // szukam w instr spacji, dostaję pozycję tej spacji
		string type = instr.substr(0, pos); // biorę podciąg ciągu instr, od początku do spacji, zapisuję jako type
		char value = instr[pos+1]; // uwyciągam kolejną literę za spacją
		// Pod type mamy teraz typ instrukcji a pod value zostaje mi "końcówka" (wartość) instrukcji
		
		
		
		// Zadanie 2
		// standardowe szukanie najdłuższego ciągu tych samych wartości
		// jeżeli poprzednia instrukcja jest taka sama jak ta, zwiększ iterator
		if(type == z1_last_type){
			z1_it++;
		}
		else{// jeżeli nastąpiła zmiana instrukcji
			if(z1_it > z1_max){ // jeżeli obecny ciąg był najdłuższy
				z1_max = z1_it; // podmień wartości maksymalne
				z1_max_type = z1_last_type;
			}
			z1_it = 1; // zresetuj iterator
			z1_last_type = type; // i typ
		}
		
		// Zadanie 3
		if(type == "DOPISZ"){ /// jeżeli dopisujemy literę
			// zamieniamy instrukcją static_cast<int> chara na inta, ponieważ jest to duża litera, będzie z zakresu 65 - 90. 
			// Odejmuje 65 aby 'A' było równe 0, 'B' - 1 itd. Podnoszę tą wartość w tablicy o 1. Jest to sortowanie kubełkowe.
			// Teraz wartość każdego "kubełka" jest równa ilości takich liter dopisywanych do ciągu
			z2[static_cast<int>(value)-65]++;
		}

	}
	
	// Zadanie 1
	// TODO
	
	
	// Zadanie 2
	// Jeszcze trzeba sprawdzić czy ostatni ciąg nie był tym najdłuższym
	if(z1_it > z1_max){
		z1_max = z1_it;
		z1_max_type = z1_last_type;
	}

	cout << z1_max_type << " (" << z1_max << " razy)"  << endl;
	
	// Zadanie 3
	
	// z2 jest wskaźnikiem na początek tablicy
	// max_element przyjmuje wskaźnik na początek i koniec zakresu, a zwraca wskaźnik na element o maksymalnej wartości
	// sizeof(z2)/sizeof(z2[0]) jest długością tablicy. sizeof(z2) da długość całej tablicy w bajtach. Podzielone przez sizeof(z2[0]), czyli
	// długość (w bajtach) jednego elementu, da ilość elementów tablicy. (W cpp każdy element zbioru ma taki sam rozmiar!)
	int* max_elem_pointer = max_element(z2, z2+sizeof(z2)/sizeof(z2[0]));
	// distance oblicza odległość między wskaźnikami - da nam to pozycję w tablicy, z której można "odzyskać" literę.
	int max_elem_pos = distance(z2, max_elem_pointer);
	// Odzyskuję literę i odwołuję się do odpowiedniego indeksu.
	cout << static_cast<char>(max_elem_pos+65) << " dodawane "<< z2[max_elem_pos];
	
	// Zadanie 4
	// TODO
	
	return 0;
}
