#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

//#define out_plik cout
// Jedna możliwość to zdefiniować out cout i wykomentować ofstream out_plik ("zapis_zadania.txt");
// i wszystko co do pliku będzie lądować w coutcie
// po zakończeniu pisania usunąć define i odkomentować zapis do pliku

using namespace std;

int main(){
	ofstream out_plik ("zapis_zadania.txt");
	
	// NIE MOŻNA ustawić ofstream cout ("zapis_zadania.txt");
	// i tylko odkomentowywać i zakomentowywać w zależności
	// czy chcemy zapis do pliku czy na ekran
	// jest to zła praktyka programistyczna,
	// ponieważ ktoś czytający kod po nas nie będzie od razu wiedział
	// czy naszą intecją był zapis do pliku
	
	// najlepszym rozwiązaniem jest zdefiniować 
	// wirtualny bufor ostringstream
	// bufor taki zachowuje się IDENTYCZNIE
	// jak cout czy out do pliku
	ostringstream out_1;
	ostringstream out_2;
	
	for(int i =0; i<11; i++){
		
		// a umożliwi on pracę na dwóch zadaniach w czasie wczytywania:
		out_1 << "linia z zadania 1: " << setw(3) << i << endl;
		out_2 << "linia z zadania 2: " << setw(3) << i << endl;
		// (wraz z ewentualnym zachowaniem formatwowania z iomanip)
	}
	
	// i tylko zbudowanie później odpowiedniej odpowiedź w zapisie do właściwego pliku:
	out_plik << "Zadanie 1: " << endl;
	// gdzie z wirtualnego bufora na bufor do pliku dane "przenosi się"
	// poprzez instrukcję str():
	out_plik << out_1.str(); 
	
	out_plik << "Zadanie 2: " << endl;
	out_plik << out_2.str();
	
	// W między czasie można też wyrzucać na ekran 
	// bufor który chcielibyśmy mieć na podglądzie cały czas:
	cout << out_2.str();
	
}
