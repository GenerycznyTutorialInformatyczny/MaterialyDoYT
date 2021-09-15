#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;


// Czy linia jest symetrzyna
bool is_line_symmetrical(vector<int> l){
	// iterujemy po połowie tablicy...
	for(int i =0; i<l.size()/2; i++){
		//... tak jakby od początku i od końca na raz
		// Przyrównujemy obecną wartość z odpowidnikiem "od końca"
		// jeżeli się różnią to zwracamy fałsz
		if(l[i] != l[l.size()-1-i]) return false;
	}
	
	// jeżeli przez całą tablicę to samo to zwracamy prawdę. Nie było żadnej niesymetrycznej pary.
	return true;
}


int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki6.txt");
	
	//ostringstream odp_zad_1;
	
	// Niestety niektóre zadania dużo łatwiej rozwiązać posiadając cały obrazek
	
	vector< vector<int> > image; // zmienna przechowująca cały obrazek
	
	int incoming_num = 0; // pojedyncza liczba
	vector<int> line; // cała jedna linia
	int i = 0; // licznik pozycji w jednej linii
	
	//Zadanie 1
	int z_1brigtest = INT_MIN;
	int z_1darkest = INT_MAX;
	//Zadanie 2
	int z2 = 0;
	
	while(dane >> incoming_num){
		line.push_back(incoming_num); // zapisujemy dane do linii
		i++;
		
		// Zadanie 1
		// klasyczne szukanie wartości maksymalnej i minimalnej
		// linijka w której sięznajdujemy nas nie obchodzi, wystarczą same liczby
		if(incoming_num > z_1brigtest) z_1brigtest = incoming_num;
		if(incoming_num < z_1darkest) z_1darkest = incoming_num;
		
		if(i == 320){ // kiedy licznik wskaże 320  jest koniec lini
			// Zadanie 2
			// wywołujemy funkcję is_line_symmetrical, która zwraca prawdę (1) jeżeli linia jest symetryczna lub fałsz (0) jeżeli nie jest.
			// negujemy to wykrzyknikiem, 1 jest linią niesymetryczną.
			// Zamieniamy wprost tą 1 na inta (nie jest to wymagane, kompilator się "domyśli")
			// i sumujemy wszystkie 1
			// if(!is_line_symmetrical(line)) z2++; // <- robi to samo, wersja alternatywna;
			z2 += static_cast<int>(!is_line_symmetrical(line));
			
			
			// dodajemy linię do całego obrazka
			image.push_back(line);
			// czyścimy iterator i linię, przygotowywując zmienne na początek kolejnej linii
			i = 0;
			line.clear();
		}
		
	}
	/*
	Testowy wypisanie całej tablicy
	for(i =0; i<image.size();i++){
		for(int j = 0; j<image[i].size(); j++){
			cout << image[i][j] << " ";
		}
		cout << endl;
	}
	*/
	
	cout << z_1darkest << " " << z_1brigtest << endl;
	
	cout << z2 << endl;
	
	return 0;
}
