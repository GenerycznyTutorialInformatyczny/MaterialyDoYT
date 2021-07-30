#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;


int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	string instr;
	
	// Zadanie 2
	// najdłuższy ciąg takich samych wartości
	int z2_it = 1;
	string z2_last_type = "";
	int z2_max = 1;
	string z2_max_type = "";
	
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
		
		/////////////////////////
		// W tym miejscu można by dodać dodatkowe zabezpieczenia:
		// (dla bardziej zaawansowanych, można pominąć)
		
		// Sprawdzam czy wszystkie znaki w "typie" instrukcji są literami i jeżeli trafi się mała litera to zamieniam ją na dużą
		for(int i = 0; i<type.size(); i++){
			// https://en.cppreference.com/w/cpp/string/byte/isalpha
			if(!isalpha(static_cast<unsigned char>(type[i]))) 
				throw invalid_argument("non alphabetical character in instruction type!");
			// https://en.cppreference.com/w/cpp/error/invalid_argument
			
			//https://en.cppreference.com/w/cpp/string/byte/toupper
			type[i] = static_cast<char>(toupper(static_cast<unsigned char>(type[i])));
		}
		
		// sprawdzam czy "wartość" instrukcji jest literą albo cyfrą
		if(!(isdigit(static_cast<unsigned char>(value)) or isalpha(static_cast<unsigned char>(value))))
			throw invalid_argument("non alphabetical or numerical character in instruction value!");
		
		// i jeżeli jest literą podnoszę ją do dużej (toupper olewa nie-litery):
		value = static_cast<char>(toupper(static_cast<unsigned char>(value)));
		
		// jeżeli cokolwiek się nie zgadza, rzucam wyjąek
		// (Wytłumaczone w 2018 zadanie 3)
		
		// Możnaby jeszcze dodać kontrolę czy ktoś nie podał np. DOPISZ 1, albo USUN R,
		// Ponieważ teraz takie instrukcje przejdą, a są nieporawne.
		
		//////////////////////////
		
		
		
		// Zadanie 2
		// standardowe szukanie najdłuższego ciągu tych samych wartości
		// jeżeli poprzednia instrukcja jest taka sama jak ta, zwiększ iterator
		if(type == z2_last_type){
			z2_it++;
		}
		else{// jeżeli nastąpiła zmiana instrukcji
			if(z2_it > z2_max){ // jeżeli obecny ciąg był najdłuższy
				z2_max = z2_it; // podmień wartości maksymalne
				z2_max_type = z2_last_type;
			}
			z2_it = 1; // zresetuj iterator
			z2_last_type = type; // i typ
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
	if(z2_it > z2_max){
		z2_max = z2_it;
		z2_max_type = z2_last_type;
	}

	cout << z2_max_type << " (" << z2_max << " razy)"  << endl;
	
	// Zadanie 3
	
	// z2 jest wskaźnikiem na początek tablicy
	// max_element przyjmuje wskaźnik na początek i koniec zakresu, a zwraca wskaźnik na element o maksymalnej wartości
	// sizeof(z2)/sizeof(z2[0]) jest długością tablicy. sizeof(z2) da długość całej tablicy w bajtach. Podzielone przez sizeof(z2[0]), czyli
	// długość (w bajtach) jednego elementu, da ilość elementów tablicy. (W cpp każdy element zbioru ma taki sam rozmiar!)
	int* max_elem_pointer = max_element(z2, z2+sizeof(z2)/sizeof(z2[0]));
	// distance oblicza odległość między wskaźnikami - da nam to pozycję w tablicy, z której można "odzyskać" literę.
	int max_elem_pos = distance(z2, max_elem_pointer);
	// Odzyskuję literę i odwołuję się do odpowiedniego indeksu.
	cout << static_cast<char>(max_elem_pos+65) << " dodawane "<< z2[max_elem_pos] << " razy";
	// Należy jednak pamiętać, że w sytuacji kiedy będzie więcej "maksów" program bierze pierwszą literę z alfabetu.
	// Oznacza to że w przypadku braku instrukcji dopisz wypisze że A zostało dopisane 0 razy. Co technicznie wg. mnie jest poprawnym wynikiem.
	
	// Zadanie 4
	// TODO
	
	return 0;
}
