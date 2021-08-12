#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;


// Zadanie 1

// funkcja ta jest uproszczoną wersją tego co dzieje się w zadaniu 4.
int modify_length(string type, char value, int len = 0){
	// wybieramt typ instrukcji (Coś typu switch, ale switch nie działa na typy których nie da się prosto porównać,
	// czyli np string: https://stackoverflow.com/questions/650162/why-the-switch-statement-cannot-be-applied-on-strings)
	if(type == "DOPISZ"){
		// dopisz - przedłuża o 1.
		return len + 1;
	}
	else if(type == "ZMIEN" or type == "PRZESUN"){
		// te warunki nie zmieniają długości napisu
		return len;
	}
	else if(type == "USUN"){
		return len - static_cast<int>(value)+48;
		// Nie jest wprost podane czy wartość przy USUN to ilość liter do usunięcia,
		// a wszystkie USUN w plikach mają wartość 1. MOżnaby było w takim razie zwrócić
		// len - 1, ale dla porządku uwzględnię to value jako ilość liter do usunięcia.
		// Dlatego zamieniam chara 'value' na waartość w kodzie ascii (static_cast<int>(value))
		// i robię poprawkę o 48, ponieważ jest to wartość z kodu ascii znaku '0'.
	}
	else throw invalid_argument("unrecognised instruction type!");
	// jeżeli dostał niezrozumiałą instrukcję niech zwróci błąd
	// (zamiast throw można dać else return -1 albo coś w ten deseś)
}

// tak samo jak w przypdaku zadania 4, można to zrobić w miejscu
void true_modify_length(string type, char value, int *len){
	if(type == "DOPISZ"){
		(*len)++;
	}
	else if(type == "ZMIEN" or type == "PRZESUN"){
	}
	else if(type == "USUN"){
		(*len) -= (static_cast<int>(value)-48);
	}
	else throw invalid_argument("unrecognised instruction type!");
}

// Zadanie 4

string modify_string(string type, char value, string str = ""){
	// wybieramt typ instrukcji (Coś typu switch, ale switch nie działa na typy których nie da się prosto porównać,
	// czyli np string: https://stackoverflow.com/questions/650162/why-the-switch-statement-cannot-be-applied-on-strings)
	if(type == "DOPISZ"){
		// Po prostu dopisuję
		str.push_back(value);
	}
	else if(type == "ZMIEN"){
		// podmieniam ostatnią
		str[str.size()-1] = value;
	}
	else if(type == "USUN"){
		// Usuwam ostatnie 'value' liter. W teorii istnieje tylko "USUN 1",
		// więc wystarczyłoby chyba str.substr(0, str.size()- 1), ale nie jest to nigdzie
		// doprecyzowane, więc usuwam 'value' liter.
		// Aby tego dokonać, zamieniam "charowe" value na intowe: static_cast<int>(value)+48
		// Następnie od rozmiaru odejmuję tą wartość: str.size()-static_cast<int>(value)+48
		// biorę substring
		// i podmieniam stringa
		str = str.substr(0, str.size()-static_cast<int>(value)+48);
	}
	else if(type == "PRZESUN"){
		int i = 0;
		int v = 0;
		for(i = 0; i< str.size(); i++){
			// szukam pierwszego wystąpienia value
			if(str[i] == value){
				// zapisuję wartość jaka powinna tam być
				
				// w normalnym przypadku jest to wartość (w ASCII) 1 większa
				v = static_cast<int>(str[i])+1;
				
				// ale jeżeli wyjdzie "poza" Z, to obracam się na A
				if(v == 91)
					v = 65;
				
				// break, aby zakończyło wykonywanie pętli po pierwszej takiej wartości.
				// instrukcja ta po prostu przedwcześnie wychodzi z "najbliższej " pętli.
				break;
			}
		}
		
		// sprawdzenie czy na pewno znalazło jakąś literę
		// (czy wyszło z pętli przed jej końcem)
		if(i!=str.size()){
			// jeżeli znalazło, niech podmieni.
			// i jest miejscem, gdzie z pętli wyszło
			// v jest wartością (litery w ASCII) jaka na tym miejsu powinna się znaleźć
			str[i] = static_cast<char>(v);
		}
		
	}
	else throw invalid_argument("unrecognised instruction type!");
	// jeżeli dostał niezrozumiałą instrukcję niech zwróci błąd
	// (zamiast throw można dać else return "error" albo coś w ten deseś)
	
	
	return str; // na koniec zwraca zmodyfikowanego stringa
}


// wersja poprawiona powyższej funkcji, gdzie modyfikuje stringa w miejscu
// opiera się na wskaźnikach.
void true_modify_string(string type, char value, string* str){ 
	// w nagłówku należy zmodyfikować stringa na wskaźnik na stringa (string str zamieniamy na string* str)
	//
	// teraz wszystkie odwołania do zmiennej str trzeba zamienić na wyjęcie wartości spod wskaźnika (str na *str),
	// ale istnieje pewien skrót.
	// Można skrócić odwołania do metod składowych klas do strzałki: ->
	// oznacza to, że zamiast (*str). można zamiastać str->
	// na przykład ((*str).push_back() jest równoznaczne z str->push_back())
	if(type == "DOPISZ"){
		str->push_back(value);
	}
	else if(type == "ZMIEN"){
		(*str)[str->size()-1] = value;
	}
	else if(type == "USUN"){
		*str = str->substr(0, str->size()-static_cast<int>(value)+48);
	}
	else if(type == "PRZESUN"){
		int i = 0;
		int v = 0;
		for(i = 0; i< str->size(); i++){
			if((*str)[i] == value){
				v = static_cast<int>((*str)[i])+1;
				
				if(v == 91)
					v = 65;
				break;
			}
		}
		
		if(i!=str->size()){
			(*str)[i] = static_cast<char>(v);
		}
		
	}
	else throw invalid_argument("unrecognised instruction type!");
	
}

int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	string instr;
	
	// Zadanie 1
	int str_len = 0;
	
	// Zadanie 2
	// najdłuższy ciąg takich samych wartości
	int z2_it = 1;
	string z2_last_type = "";
	int z2_max = 1;
	string z2_max_type = "";
	
	// Zadanie 3
	// Tablica do sortowania kubełkowego
	// 26 - ilość liter w alfabecie
	int z3[26] = {0};
	
	// Zadanie 4
	string output_word = "";
	
	
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
		
		// Zadanie 1
		// najprościej byłoby zrobić zadanie 4 i po prostu zrobić output_word.size() na końcu.
		// Jeżeli ktoś się jednak uprze można zrobić to zadanie bardzo podobnie do 4, czyli
		// podać instrukcję i inta z obecną długością do modyfikacji.
		// Może to być też dobre ćwiczenie jak ktoś nie jest w stanie tego zadania 4 zrozumieć.
		// Nie mniej najpierw warto spróbować zrobić zadanie 4.
		//
		// tak samo jak w zadaniu 4 można to zrobić ze zwracaniem:
		// str_len = modify_length(type, value, str_len); 
		// lub w miejscu na wskaźnikach:
		true_modify_length(type, value, &str_len);
		
		
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
			z3[static_cast<int>(value)-65]++;
		}
		
		// Zadanie 4
		// Można napisać funkcję która bierze stringa i zwraca wersję zmodyfikowaną o kolejną instrukcję
		//output_word = modify_string(type, value, output_word);
		
		// Lub funkcję do której podaje się wskaźnik na stringa i go modyfikuje "w miejscu"
		true_modify_string(type, value, &output_word);

	}
	
	// Zadanie 1
	odp << "Zadanie 1" << endl;
	// najprostrza metoda, zrobić zadanie 4 i wtedy mamy rozmiar stringa w taki sposób:
	// cout << output_word.size() << endl;
	// Lub alternatywa na piechotę:
	cout << str_len;
	
	
	// Zadanie 2
	// Jeszcze trzeba sprawdzić czy ostatni ciąg nie był tym najdłuższym
	if(z2_it > z2_max){
		z2_max = z2_it;
		z2_max_type = z2_last_type;
	}
	odp << "Zadanie 2" << endl;
	odp << z2_max_type << " (" << z2_max << " razy)"  << endl;
	
	// Zadanie 3
	
	// z2 jest wskaźnikiem na początek tablicy
	// max_element przyjmuje wskaźnik na początek i koniec zakresu, a zwraca wskaźnik na element o maksymalnej wartości
	// sizeof(z2)/sizeof(z2[0]) jest długością tablicy. sizeof(z2) da długość całej tablicy w bajtach. Podzielone przez sizeof(z2[0]), czyli
	// długość (w bajtach) jednego elementu, da ilość elementów tablicy. (W cpp każdy element zbioru ma taki sam rozmiar!)
	int* max_elem_pointer = max_element(z3, z3+sizeof(z3)/sizeof(z3[0]));
	// distance oblicza odległość między wskaźnikami - da nam to pozycję w tablicy, z której można "odzyskać" literę.
	int max_elem_pos = distance(z3, max_elem_pointer);
	// Odzyskuję literę i odwołuję się do odpowiedniego indeksu.
	odp << "Zadanie 3" << endl;
	odp << static_cast<char>(max_elem_pos+65) << " dodawane "<< z3[max_elem_pos] << " razy" << endl;
	// Należy jednak pamiętać, że w sytuacji kiedy będzie więcej "maksów" program bierze pierwszą literę z alfabetu.
	// Oznacza to że w przypadku braku instrukcji dopisz wypisze że A zostało dopisane 0 razy. Co technicznie wg. mnie jest poprawnym wynikiem.
	
	// Zadanie 4
	odp << "Zadanie 4" << endl;
	odp << output_word;
	
	return 0;
}
