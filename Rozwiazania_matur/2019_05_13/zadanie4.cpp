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
	// x == 3 jest już niepotrzebne, ponieważ zostanie to efektywnie sprawdzone w drugin wykonaniu pętli
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

// Jest udowodnione, że wspólny podzielnik a i b jest też podzielnikiem a%b
// Liczymy takie a%b i b%a na zmianę, redukując na zmianę liczby a i b do ich reszt z 
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
// Można to uprościć do rekurencji
// Na której nawet więcej lepiej jak to działa
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
		// Niestety nie da się w miejscu tego zrobić
		// 10 10 30 30 30 60 3 3 3 6 12
		// Najdłuższa sekwencja powinna być 30 - 12
		// "Przelatując" w miejscu otrzymalibyśmy sekwencję 10 - 60
		// trzeba by było operując na buforze wracać za każdym i sprawdzać
		// inne możliwości. Lub utworzyć tablicę tylko obecnie rozpatrywanej sekwencji 		
		// i połączyć jakoś podejście w miejscu z tablicami
		// jendak lepiej sobie życia w takim zadaniu nie utrudniać
		// (więcej przy samym kodzie)
		
	}
	
	
	
	unsigned int cur_sequence_GCD = GCD_rec(z3[0], z3[1]);
	unsigned int cur_sequence_len = 2; // zaczynamy od 2, ponieważ teoretycznie mamy już dwa elementy, 0 i 1.
										// Jeżeli ich NWD jest jednak równy 1, w pętli jest else który poszukuje dwóch faktycznych
										// pierwszych elementów pierwszego ciągu (czyli dwa pierwsze elementy występujące w pliku któych
										// NWD jest większy od 1)
	unsigned int cur_sequence_beg_numb = z3[0];
	
	unsigned int long_sequence_GCD = 0;
	unsigned int long_sequence_len = 0;
	unsigned int long_sequence_beg_numb = 0;
	
	int i = 2;
	while(i < z3.size()){
		if(cur_sequence_GCD != 1){ // sytuacja, kiedy pierwsze dwa elementy mają podzielnik większy niż 1
			unsigned int this_it_GCD = GCD_rec(cur_sequence_GCD, z3[i]);
			if(this_it_GCD == cur_sequence_GCD){ // kontynacja ciągu
				cur_sequence_len++;
			}
			else{ //ciąg się skończył
				if(cur_sequence_len>long_sequence_len){ // jeżeli obecny ciąg jest tym najdłuższym
					long_sequence_GCD = cur_sequence_GCD;
					long_sequence_len = cur_sequence_len;
					long_sequence_beg_numb = cur_sequence_beg_numb;
				}
				cur_sequence_len = 2; // przede wszystkim ustawiamy 2, ponieważ niezależne jak 
				// nową sekwencję zaczniemy, jej wyjściowa długość będzie równa 2
				
				
				cur_sequence_GCD = 	GCD_rec(z3[i], z3[i-1]);// Muszę sprawdzić czy element poprzedni 
				// z obcnym nie mają wspólnych dzielników innych niż jeden:
				// 10 10 30 30 30 60 3 6 6 6 12
				// Jesteśmy na 3.
				// Sprawdzamy 3 i 60 ma wspólny dzielnik 3
				// Cofamy się aż do 30
				// i później idziemy od 3 w prawo do 12
				
				
				// 
				if(cur_sequence_GCD != 1){
					cur_sequence_beg_numb = z3[i-1]; // ustawiam nowy możliwy początek sekwencji
					
					int j = i-2; // wiemy że obecny i poprzedni mają jakiś wspólny dzielnik inny niż 
					// właśnie ukończona sekwencja, więc wystarczy żeby iść od i-2
					
					this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
					
					while(this_it_GCD != cur_sequence_GCD and j > 0){
						// jeżeli kolejne poprzednie liczby też mają ten sam dzielnik to sekwencję 
						// trzeba wydłużać "w tył"
						cur_sequence_beg_numb = z3[j];
						j--;
						this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
						cur_sequence_len++;
					}
					// Teraz głowna pętla while zabierze nas dalej "w prawo" od i
					
				}
				else{ // jeżeli nie ma sensu się cofać:
					// przede wszystkim trzeba pamietać że nawet jeżeli w "środku" obecnie znalezionej
					// sekwencji byłaby inna sekwencja to nie ma sensu po nią "iść" do tyłu bo będzie 
					// ona i tak krótsza od obecnej:
					// 10 20 40 800 800 40 20 10
					
					// sytuacja w sumie identyczna jak else pod spodem. Trzeba jakoś zacząć nową sekwencję
					cur_sequence_GCD = 	GCD_rec(z3[i], z3[i+1]);
					cur_sequence_beg_numb = z3[i];
					
				}
			}
			
		}
		else{ // sytuacja, kiedy pierwsze dwa elementy nie mają podzielnika większego niż 1
		 	// inaczej:
			// else który poszukuje pierwszą sytuację, kiedy NWD będzie większy od 1
			// Ponownie kod mooże wejść tutaj, kiedy zakończy się sekwencja i będzie poszukiwany
			// nowy początek sekwencji
			cur_sequence_GCD = GCD_rec(z3[i-1], z3[i]);
			cur_sequence_beg_numb = z3[i-1];
		}		
				
		i++;		
	}
	
	if(cur_sequence_len>long_sequence_len){ // sprawdzenie czy ostatnia sekwencja nie jest tą najdłuższą
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
