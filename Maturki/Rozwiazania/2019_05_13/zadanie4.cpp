#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

bool is_power_of_3(unsigned int x){
	if(x == 0) return false;
	if(x == 1) return true;
	if(x%3 !=0 ) return false;
	
	for(unsigned int i = 3; i<=x; i*=3){
		if(i == x) return true;
	}
	return false;
}
bool is_power_of_3v2(unsigned int x){
    if(x == 0) return false;
    
	float l = log(x) / log(3); //https://www.matemaks.pl/logarytmy-najwazniejsze-wzory.html
	return l == round(l);
}

bool is_power_of_3v3(unsigned int x){
	if(x == 0) return false;
	if(x == 1) return true;
	// x == 3 jest ju� niepotrzebne, poniewa� zostanie to efektywnie sprawdzone w drugin wykonaniu p�tli
	unsigned int prev_i = x*3;
	for(unsigned int i = x; i>=1; i/=3){
		if(prev_i != i*3) return false;
		prev_i = i;
	}
	return true;		
}




unsigned int factorial(unsigned int x){
	if(x <= 1) return 1;
	return x*factorial(x - 1);
}


bool is_equal_to_sum_of_factorials(unsigned int x){
	unsigned int x_c = x;
	unsigned int sum = 0;
	while(x_c > 0){
		sum += tgamma(x_c%10 + 1); // https://en.wikipedia.org/wiki/Gamma_function
		x_c/=10;
	}
	return sum == x;
}

// Jest udowodnione, �e wsp�lny podzielnik a i b jest te� podzielnikiem a%b
// Liczymy takie a%b i b%a na zmian�, redukuj�c na zmian� liczby a i b do ich reszt z 
// dzielenia przez siebie
//
// Najpierw mamy a i b
// b i a%b
// a%b i b%a
// b%a i a%b % b%a
// a%b % b%a i b%a % (a%b % b%a)
unsigned int GCD(unsigned int a, unsigned int b){
	while(b!=0){
		unsigned int c = a%b;
		unsigned int a = b;
		unsigned int b = c;
	}
}
// Mo�na to upro�ci� do rekurencji
// Na kt�rej nawet wi�cej lepiej jak to dzia�a
unsigned int GCD_rec(unsigned int a, unsigned int b){
	if(b!=0) return GCD_rec(b, a%b);
	return a;
}


int main(){
	ifstream dane ("przyklad.txt");
	ofstream odp ("wyniki4.txt");
	
	ostringstream odp_zad_2;
	
	
	unsigned int a = 0;
	unsigned int num_of_3_pows = 0;
	
	
	vector<unsigned int> z3;
	
	while(dane >> a){
		
		//Zadanie 1
		if(is_power_of_3v2(a)) ++num_of_3_pows;
		
		//Zadanie 2
		if(is_equal_to_sum_of_factorials(a)) odp_zad_2 << a;
		
		
		//Zadanie 3
		z3.push_back(a);
		// Niestety nie da si� w miejscu tego zrobi�
		// 10 10 30 30 30 60 3 3 3 6 12
		// Najd�u�sza sekwencja powinna by� 30 - 12
		// "Przelatuj�c" w miejscu otrzymaliby�my sekwencj� 10 - 60
		// trzeba by by�o operuj�c na buforze wraca� za ka�dym i sprawdza�
		// inne mo�liwo�ci. Lub utworzy� tablic� tylko obecnie rozpatrywanej sekwencji 		
		// i po��czy� jako� podej�cie w miejscu z tablicami
		// jendak lepiej sobie �ycia w takim zadaniu nie utrudnia�
		// (wi�cej przy samym kodzie)
		
	}
	
	
	
	unsigned int cur_sequence_GCD = GCD_rec(z3[0], z3[1]);
	unsigned int cur_sequence_len = 2; // zaczynamy od 2, poniewa� teoretycznie mamy ju� dwa elementy, 0 i 1.
										// Je�eli ich NWD jest jednak r�wny 1, w p�tli jest else kt�ry poszukuje dw�ch faktycznych
										// pierwszych element�w pierwszego ci�gu (czyli dwa pierwsze elementy wyst�puj�ce w pliku kt�ych
										// NWD jest wi�kszy od 1)
	unsigned int cur_sequence_beg_numb = z3[0];
	
	unsigned int long_sequence_GCD = 0;
	unsigned int long_sequence_len = 0;
	unsigned int long_sequence_beg_numb = 0;
	
	int i = 2;
	while(i < z3.size()){
		if(cur_sequence_GCD != 1){ // sytuacja, kiedy pierwsze dwa elementy maj� podzielnik wi�kszy ni� 1
			unsigned int this_it_GCD = GCD_rec(cur_sequence_GCD, z3[i]);
			if(this_it_GCD == cur_sequence_GCD){ // kontynacja ci�gu
				cur_sequence_len++;
			}
			else{ //ci�g si� sko�czy�
				if(cur_sequence_len>long_sequence_len){ // je�eli obecny ci�g jest tym najd�u�szym
					long_sequence_GCD = cur_sequence_GCD;
					long_sequence_len = cur_sequence_len;
					long_sequence_beg_numb = cur_sequence_beg_numb;
				}
				cur_sequence_len = 2; // przede wszystkim ustawiamy 2, poniewa� niezale�ne jak 
				// now� sekwencj� zaczniemy, jej wyj�ciowa d�ugo�� b�dzie r�wna 2
				
				
				cur_sequence_GCD = 	GCD_rec(z3[i], z3[i-1]);// Musz� sprawdzi� czy element poprzedni 
				// z obcnym nie maj� wsp�lnych dzielnik�w innych ni� jeden:
				// 10 10 30 30 30 60 3 6 6 6 12
				// Jeste�my na 3.
				// Sprawdzamy 3 i 60 ma wsp�lny dzielnik 3
				// Cofamy si� a� do 30
				// i p�niej idziemy od 3 w prawo do 12
				
				
				// 
				if(cur_sequence_GCD != 1){
					cur_sequence_beg_numb = z3[i-1]; // ustawiam nowy mo�liwy pocz�tek sekwencji
					
					int j = i-2; // wiemy �e obecny i poprzedni maj� jaki� wsp�lny dzielnik inny ni� 
					// w�a�nie uko�czona sekwencja, wi�c wystarczy �eby i�� od i-2
					
					this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
					
					while(this_it_GCD != cur_sequence_GCD and j > 0){
						// je�eli kolejne poprzednie liczby te� maj� ten sam dzielnik to sekwencj� 
						// trzeba wyd�u�a� "w ty�"
						cur_sequence_beg_numb = z3[j];
						j--;
						this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
						cur_sequence_len++;
					}
					// Teraz g�owna p�tla while zabierze nas dalej "w prawo" od i
					
				}
				else{ // je�eli nie ma sensu si� cofa�:
					// przede wszystkim trzeba pamieta� �e nawet je�eli w "�rodku" obecnie znalezionej
					// sekwencji by�aby inna sekwencja to nie ma sensu po ni� "i��" do ty�u bo b�dzie 
					// ona i tak kr�tsza od obecnej:
					// 10 20 40 800 800 40 20 10
					
					// sytuacja w sumie identyczna jak else pod spodem. Trzeba jako� zacz�� now� sekwencj�
					cur_sequence_GCD = 	GCD_rec(z3[i], z3[i+1]);
					cur_sequence_beg_numb = z3[i];
					
				}
			}
			
		}
		else{ // sytuacja, kiedy pierwsze dwa elementy nie maj� podzielnika wi�kszego ni� 1
		 	// inaczej:
			// else kt�ry poszukuje pierwsz� sytuacj�, kiedy NWD b�dzie wi�kszy od 1
			// Ponownie kod moo�e wej�� tutaj, kiedy zako�czy si� sekwencja i b�dzie poszukiwany
			// nowy pocz�tek sekwencji
			cur_sequence_GCD = GCD_rec(z3[i-1], z3[i]);
			cur_sequence_beg_numb = z3[i-1];
		}		
				
		i++;		
	}
	
	if(cur_sequence_len>long_sequence_len){ // sprawdzenie czy ostatnia sekwencja nie jest t� najd�u�sz�
		long_sequence_GCD = cur_sequence_GCD;
		long_sequence_len = cur_sequence_len;
		long_sequence_beg_numb = cur_sequence_beg_numb;
	}
	
	
	odp << "zadanie 1: " << num_of_3_pows << endl;
	odp << "zadanie 2: " << endl;
	odp << odp_zad_2.str();
	odp << "zadanie 3:" << endl;
	cout << long_sequence_beg_numb << " " << long_sequence_len << " " << long_sequence_GCD << endl;
	
	
	
	
	
	return 0;
}
