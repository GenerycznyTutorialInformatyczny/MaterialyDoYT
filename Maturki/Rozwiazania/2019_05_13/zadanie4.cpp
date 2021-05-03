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
	// x == 3 jest ju¿ niepotrzebne, poniewa¿ zostanie to efektywnie sprawdzone w drugin wykonaniu pêtli
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

// Jest udowodnione, ¿e wspólny podzielnik a i b jest te¿ podzielnikiem a%b
// Liczymy takie a%b i b%a na zmianê, redukuj¹c na zmianê liczby a i b do ich reszt z 
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
// Mo¿na to uproœciæ do rekurencji
// Na której nawet wiêcej lepiej jak to dzia³a
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
		// Niestety nie da siê w miejscu tego zrobiæ
		// 10 10 30 30 30 60 3 3 3 6 12
		// Najd³u¿sza sekwencja powinna byæ 30 - 12
		// "Przelatuj¹c" w miejscu otrzymalibyœmy sekwencjê 10 - 60
		// trzeba by by³o operuj¹c na buforze wracaæ za ka¿dym i sprawdzaæ
		// inne mo¿liwoœci. Lub utworzyæ tablicê tylko obecnie rozpatrywanej sekwencji 		
		// i po³¹czyæ jakoœ podejœcie w miejscu z tablicami
		// jendak lepiej sobie ¿ycia w takim zadaniu nie utrudniaæ
		// (wiêcej przy samym kodzie)
		
	}
	
	
	
	unsigned int cur_sequence_GCD = GCD_rec(z3[0], z3[1]);
	unsigned int cur_sequence_len = 2; // zaczynamy od 2, poniewa¿ teoretycznie mamy ju¿ dwa elementy, 0 i 1.
										// Je¿eli ich NWD jest jednak równy 1, w pêtli jest else który poszukuje dwóch faktycznych
										// pierwszych elementów pierwszego ci¹gu (czyli dwa pierwsze elementy wystêpuj¹ce w pliku któych
										// NWD jest wiêkszy od 1)
	unsigned int cur_sequence_beg_numb = z3[0];
	
	unsigned int long_sequence_GCD = 0;
	unsigned int long_sequence_len = 0;
	unsigned int long_sequence_beg_numb = 0;
	
	int i = 2;
	while(i < z3.size()){
		if(cur_sequence_GCD != 1){ // sytuacja, kiedy pierwsze dwa elementy maj¹ podzielnik wiêkszy ni¿ 1
			unsigned int this_it_GCD = GCD_rec(cur_sequence_GCD, z3[i]);
			if(this_it_GCD == cur_sequence_GCD){ // kontynacja ci¹gu
				cur_sequence_len++;
			}
			else{ //ci¹g siê skoñczy³
				if(cur_sequence_len>long_sequence_len){ // je¿eli obecny ci¹g jest tym najd³u¿szym
					long_sequence_GCD = cur_sequence_GCD;
					long_sequence_len = cur_sequence_len;
					long_sequence_beg_numb = cur_sequence_beg_numb;
				}
				cur_sequence_len = 2; // przede wszystkim ustawiamy 2, poniewa¿ niezale¿ne jak 
				// now¹ sekwencjê zaczniemy, jej wyjœciowa d³ugoœæ bêdzie równa 2
				
				
				cur_sequence_GCD = 	GCD_rec(z3[i], z3[i-1]);// Muszê sprawdziæ czy element poprzedni 
				// z obcnym nie maj¹ wspólnych dzielników innych ni¿ jeden:
				// 10 10 30 30 30 60 3 6 6 6 12
				// Jesteœmy na 3.
				// Sprawdzamy 3 i 60 ma wspólny dzielnik 3
				// Cofamy siê a¿ do 30
				// i póŸniej idziemy od 3 w prawo do 12
				
				
				// 
				if(cur_sequence_GCD != 1){
					cur_sequence_beg_numb = z3[i-1]; // ustawiam nowy mo¿liwy pocz¹tek sekwencji
					
					int j = i-2; // wiemy ¿e obecny i poprzedni maj¹ jakiœ wspólny dzielnik inny ni¿ 
					// w³aœnie ukoñczona sekwencja, wiêc wystarczy ¿eby iœæ od i-2
					
					this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
					
					while(this_it_GCD != cur_sequence_GCD and j > 0){
						// je¿eli kolejne poprzednie liczby te¿ maj¹ ten sam dzielnik to sekwencjê 
						// trzeba wyd³u¿aæ "w ty³"
						cur_sequence_beg_numb = z3[j];
						j--;
						this_it_GCD = GCD_rec(cur_sequence_GCD, z3[j]);
						cur_sequence_len++;
					}
					// Teraz g³owna pêtla while zabierze nas dalej "w prawo" od i
					
				}
				else{ // je¿eli nie ma sensu siê cofaæ:
					// przede wszystkim trzeba pamietaæ ¿e nawet je¿eli w "œrodku" obecnie znalezionej
					// sekwencji by³aby inna sekwencja to nie ma sensu po ni¹ "iœæ" do ty³u bo bêdzie 
					// ona i tak krótsza od obecnej:
					// 10 20 40 800 800 40 20 10
					
					// sytuacja w sumie identyczna jak else pod spodem. Trzeba jakoœ zacz¹æ now¹ sekwencjê
					cur_sequence_GCD = 	GCD_rec(z3[i], z3[i+1]);
					cur_sequence_beg_numb = z3[i];
					
				}
			}
			
		}
		else{ // sytuacja, kiedy pierwsze dwa elementy nie maj¹ podzielnika wiêkszego ni¿ 1
		 	// inaczej:
			// else który poszukuje pierwsz¹ sytuacjê, kiedy NWD bêdzie wiêkszy od 1
			// Ponownie kod moo¿e wejœæ tutaj, kiedy zakoñczy siê sekwencja i bêdzie poszukiwany
			// nowy pocz¹tek sekwencji
			cur_sequence_GCD = GCD_rec(z3[i-1], z3[i]);
			cur_sequence_beg_numb = z3[i-1];
		}		
				
		i++;		
	}
	
	if(cur_sequence_len>long_sequence_len){ // sprawdzenie czy ostatnia sekwencja nie jest t¹ najd³u¿sz¹
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
