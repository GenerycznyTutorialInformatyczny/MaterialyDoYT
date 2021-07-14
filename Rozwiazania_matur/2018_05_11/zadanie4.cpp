#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <stdexcept>
#include <string>


using namespace std;

//Zadanie 2

// Idea tej funkcji opiera się na przeiterowaniu po słowie i:
// 1) sprawdzenie czy danej litery nie ma już w pewnym wektorze
// 2) jeżeli jest to nie rób nic, jeżeli nie ma to dodaj
// 3) zwróć długość wektora
// jest to rozwiązanie raczej "drętwe"
int num_diff_letters1(string word){
	vector<char> letters; // wektor w którym będę przechowywał litery
	
	for(int i = 0; i < word.size(); i++){ // iteruję po słowie
		bool found = false;
		for(int j = 0; j < letters.size(); j++){ // dla każdej literki iteruję po wektorze
			if(word[i] == letters[j]) found = true; // jeżeli ta literka już w tym wektorze jest niech ustawi found na true
		}
		if(!found) letters.push_back(word[i]); // jeżeli literki w wektorze nie znalazło nieh literkę doda
		
	}
	
	return letters.size(); // niech zwróci ilość literek (długość wektora)
}

// Idea tej funkcji jest taka sama, jedynie wykonanie sprytniejsze
int num_diff_letters2(string word){
	vector<char> letters;
	
	for(int i = 0; i < word.size(); i++){ // tak samo iteruję po literkach w słowie
		// ale szukam tej literki w wektorze gotową funkcją find
		// funkcja przyjmuje iterator na początek wektora do przeszukania, iterator na pierwszy element "za" wektorem
		// (czyli nazwa_wektota.begin() i nazwa_wektora.end()) i jako 3 element daną do znalezienia. 
		// Jeżeli znajdzie to zwraca iterator na ten element, jeżeli nie, zwraca iterator na pierwszy element a wektorem (czyli nazwa_wektora.end()).
		// Dlatego właśnie przyrównuję do letters.end().
		// Iterator jest tak jakby wskaźnikiem na element zbioru danych. Możnaby powiedzieć że nazwa_wektora.begin() jest bardziej zaawansowaną wersją 
		// nazwa_wektor[0]. Umożliwiają one bardziej "niskopoziomowe" sposoby na iterowanie po zbiorach niż standardowy for typu for(int i ;i <; i++).
		if(find(letters.begin(), letters.end(), word[i]) == letters.end()){
			letters.push_back(word[i]); // jeżeli literki nie znajdzie, dodaję do wektora.
		}
	}
	
	return letters.size();
}

// Idea tej funkcji opiera się na set-cie
// Set jest zbiorem danych gdzie dane się nie powtarzają (czyli wystąpi tylko jedna kopia każdej literki).
// Tworzę więc set na podstawie stringa, podając do konstruktora klasy set
// iteratory na początek i koniec stringa (patrz wyjaśnienie iteratorów wyżej)
// i zwracam długość seta
int num_diff_letters3(string word){
	set<char> letters(word.begin(), word.end());// tworzę seta
	return letters.size();// zwracam długość seta
}

//Zadanie 3

// funkcja opiera się na kodzie ASCII. Każda liter ma przyporządkowany numer w kodzie ASCII.
// Aby taki kod uzyskać trzeba zamienić chara na inta. Jako że liczby w kodzie ASCII idą "po kolej"
// https://en.wikipedia.org/wiki/ASCII
// trzeba poszukać litery o maksymalnym kodzie ascii i minimalnym i na końcu wystarczy je odjąć.
int max_word_distance(string word){	
	int max_letter = static_cast<int>(word[0]); // Pierwsza litera jest początkową maksymalną i minimalną
	int min_letter = static_cast<int>(word[0]); // zamieniam chara na inta instrukcją static_cast<int>, chociaż i bez tego kompilator też by się sam domyślił
	// Istnieje także instrukcja (int)word[0]. Jest to instrukcja używana w starym języku C, która także działa w C++. 
	// Nie kontroluje ona jednak zamienianych typów i kompilator będzie na siłę próbował dokonać konwersj typów których przekonwertować się nie da.
	// static_cast takie sytuacje wychwyci i na nie nie pozwoli.
	for(int i = 1; i<word.size(); i++){ // przechodzę po reszcie słowa
		int asInt = static_cast<int>(word[i]); // wyciągam kolejne litery jako inty z kodu ASCII
		if(asInt < min_letter) min_letter = asInt; // i sprawdzam czy są mniejsze niż min, większe niż maks i podstawiam jeżeli tak
		if(asInt > max_letter) max_letter = asInt;
	}
	return max_letter - min_letter; // zwracam róznicę
}


// dokładnie ta sama funkcja, jedynie ulepszone
// Nie zostało podane co robić jeżeli trafi się w słowie coś innego niż duża litra.
// Nie mniej powinno się takie zabezpieczenie dodać, zwłaszcza jak pisze się "praktyczny" program.
int max_word_distance2(string word){
	// Dodaję sprawdzenie czy nie ma żadnych znaków nie będących literami.
	// Polecenie nie definiuje co w takiej sytuacji trzeba robić, bo w teroii taka sytuacja nie powinna zajść
	// Ja jednak dointrpretowywuję, że jeżeli się coś takiego zdarzy to ma zwrócić błąd
	for(int i = 0; i<word.size(); i++){ // iteruję po słowie
		// sprawdzam funkcją isalpha czy char jest literą alfabetu.
		// isalpha przyjmuje tylko unsigned char, a operator [] zwraca "zwyczajny" char.
		// Dlatego należy dokonać konwersji (tak samo jak dokonywaliśmy konwersji char -> int).
		// Konwersja w tym przypadku jest o tyle ważna, że podawanie chara do tej funkcji jest 
		// zachowaniem niezdefiniowanym. Oznacza to że w zależności od kompilatora może to działać lub nie.
		// https://en.cppreference.com/w/cpp/string/byte/isalpha
		if(!isalpha(static_cast<unsigned char>(word[i]))) throw invalid_argument("non alphabetical character in string!");
		// Jeżeli trafi się jakikolwiek znak nie będący literą program ma rzucić błąd. Jest to zaawansowana "forma" instrukcji return
		// używana w przypadku, gdy chcemy zwrócić błąd.
		// Można zamiast tego dać return -1, jednak może to prowadzić do dalszych błędów.
		// https://en.cppreference.com/w/cpp/error/invalid_argument
		
		
		// kolejna modyfikacja to pojawienie się małych liter, które będą po prostu zamienione na duże.
		// Dokonuję takiego samego casta jak w przypadku isalpha, z dokłądnie tego samego powodu.
		// Funkcja toupper zwróci dużą literę jeżeli została podana mała, lub znak który został podany jeżeli ten znak małą literą nie jest.
		// dalej dokonuję zamiany na char, i wstawiam na "swoje" miejsce do stringa
		word[i] = static_cast<char>(toupper(static_cast<unsigned char>(word[i])));
	}
	//dalej po prostu wywołuję starą funkcję ponieważ już się nic więcej nie zmienia	
	return max_word_distance(word);
}

int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	string s = "";	 // string do którego będe wczytywał kolejne śłowa
	
	//Zadanie 1
	ostringstream z1; // Wirtualny bufor do którego będę zapisywać kolejne słowa
	// można użyć zamiast niego wektora czy tablicy
	
	int i = 1;// potrzebuję iteratora który będzie liczył słowa. 
	// Możliwe że trzeba będzie trochę poeksperymentować, czy w CKE liczą od 0 czy od 1
	
	// Zadanie 2
	string max_word = "";
	unsigned int max_letter_count = 0; // wszelakie max_letter_count.,letter_count itp są niepotrzebne, 
	    							   // można zawsze wywoływać funkcję num_diff_letters na odpowiednim słowie.
	// Zadanie 3
	ostringstream z3; // Wirtualny bufor (same co z1)
	
	while(dane >> s){
		
		// Zadanie 1
		if(i%40 == 0){// Co czterdziesty.
			if(s.length() >= 10){ // niby wiadomo że będzie 10 liter, 
								  // ale w praktycznych zastosowaniach tego wiadomo nie będzie
								  // więc lepiej sprawdzić. Plus CKE mogło się walnąć w akcji i nie dać gdzieś 10
				z1 << s[9]; // bierzemy 10 literę
				
				// Jeżeli mielibyśmy szczególnie dużo słów w pliku tutaj możnaby zrestować iterator:
				i = 0;
				// Nie jest to jednak potrzebne. Gdyby iterator był resetowany możnaby także zastosować jakiegoś 
				// "mniejszego" inta, np int8 który tryma liczby od -128 do 127 albo w ogóle uint8 któy trzyma liczby od 0 - 256, aby zoptymalizować kod. Typy te są 
				// jednak zdefiniowane dopiero w wersji kompilator 11, którego często na kompach maturalnych nie ma. (https://en.cppreference.com/w/cpp/types/integer)
			}
		}
		
		i++; // iterator, który musi się zwiększać
		
		// Zadanie 2
		// szukam słowa z największą liczbą różnych liter
		unsigned int letter_count = num_diff_letters3(s);
		if(letter_count > max_letter_count){
			max_letter_count = letter_count;
			max_word = s;
		}
		
		// Zadanie 3
		if(max_word_distance2(s) <= 10) z3 << s << endl;
	}
	
	odp << "zadanie 1" << endl;
	odp << z1.str() << endl;
	odp << "zadanie 2" << endl;
	odp << max_word << " " << max_letter_count << endl;
	odp << "zadanie 3" << endl;
	odp << z3.str();
}
