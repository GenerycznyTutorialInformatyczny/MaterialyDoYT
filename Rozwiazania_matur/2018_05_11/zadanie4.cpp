#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;


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

// funkcja opiera się na kodzie ASCII. Każda liter ma przyporządkowany numer w kodzie ASCII.
// Aby taki kod uzyskać trzeba zamienić chara na inta. Jako że liczby w kodzie ASCII idą "po kolej"
// https://en.wikipedia.org/wiki/ASCII
// trzeba poszukać litery o maksymalnym kodzie ascii i minimalnym i na końcu wystarczy je odjąć.
int max_word_distance(string word){	
	int max_letter = (int)word[0]; // Pierwsza litera jest początkową maksymalną i minimalną
	int min_letter = (int)word[0]; // zamieniam chara na inta instrukcją (int), chociaż i bez tego kompilator też by się sam domyślił
	for(int i = 1; i<word.size(); i++){ // przechodzę po reszcie słowa
		int asInt = (int)word[i]; // wyciągam kolejne litery jako inty z kodu ASCII
		//DODATKOWY FRAGMENT:
		// Widać że tu w danych wszystkie słowa są capsem
		// ale przydałoby się tak czy siak kod udebiloodpornić
		// 1. co jeżeli znak nie będzie literą?
		// 2. co jeżeli fragment słowa będzie capsem fragment normalnie? Wtedy a i A będą oddalone o +- 32
		// Co z tym można zrobić?
		// Nie jest nic dokładnie zdefiniowane w zadaniu więc trzeba coś samemu wymyślić:
		// a i A potraktuję jako to samo, czyli trzeba wszystkie małe litery zamienić na duże
		// jeżeli będzie coś co nie jest literą to niech zostanie przez program olane
		
		if(asInt >= (int)'a' and asInt <= (int)'z') asInt = asInt + (int)'A' - (int)'a'; // jeżeli jest mała literka, zamieniam ją na dużą
		// oczywiście jakby się komuś chciało to można autentyczne wartości z kodu ascii wpisać, zamiast zamieniać za każdym razem
		
		if(asInt >= (int)'A' and asInt <= (int)'Z'){
			// jedynie niestety w sytuacji kiedy będą same dziwne znaki, zwróci na pewno 0. Możnaby się przed czymś takim zabezpieczyć 
			// przed samym zwracaniem na końcu funkcji
		
			// KONIEC DODATKOWEGO FRAMGMENTU
			if(asInt < min_letter) min_letter = asInt; // i sprawdzam czy są mniejsze niż min, większe niż maks i podstawiam jeżeli tak
			if(asInt > max_letter) max_letter = asInt;
		}
	}
	// DODATKOWY FRAGMENT 2
	// w sytuacji kiedy wszystkie litery nie są literami (opisana powyżej):
	if(min_letter < (int)'A') return -1;
	if(max_letter > (int)'Z') return -1;
	// Zwracam -1. Jest to oznaka że jest jakiś błąd.
	// Można to sprawdzić na wiele sposobów, ale taka metoda pozwala wychwycić też inne nieprzewidziane przez nas błędy
	// generalnie nie sprawdzamy tylko warunku "wszystkie zaki są nie-literami"
	// ale bardziej generalny warunek: "na wyjście przeszła jakakolwiek znak nie będący literą".
	// lepsze zamiast return -1 byłoby:
	// throw invalid_argument("out char out of letter range!");
	// ale to jest rochę bardziej zaawansowana technika
	// Możnaby także rzucić jakiegoś error kiedy jakimś cudem max będzie mniejszy od min:
	if(max_letter <  min_letter) return -1;
	// Takie zabezpieczanie, zwłaszcza (w przyszłości) z użyciem throw pozwala dużo lepiej wychwytywać
	// i poprawnie interpretować dziwne zachowanie programu
	// KONIEC DODATKOWEGO FRAGMENTU 2
	return max_letter - min_letter; // zwracam róznicę
}

int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	string s = "";	 // string do którego będe wczytywał kolejne śłowa
	
	//Zadanie 1
	ostringstream z1; // Wirtualny bufor do którego będę zapisywać kolejne słowa
	// można użyć zamiast niego wektora czy tablicy
	
	unsigned int i = 1;// potrzebuję iteratora który będzie liczył słowa. 
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
				int i = 0;
				// Nie jest to jednak potrzebne. Gdyby iterator był resetowany możnaby także zastosować jakiegoś 
				// short short inta albo innego unsigned int8 któy trzyma liczby od 0 - 256, aby zoptymalizować kod.
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
		if(max_word_distance(s) <= 10) z3 << s << endl;
	}
	
	odp << "zadanie 1" << endl;
	odp << z1.str() << endl;
	odp << "zadanie 2" << endl;
	odp << max_word << " " << max_letter_count << endl;
	odp << "zadanie 3" << endl;
	odp << z3.str();
}
