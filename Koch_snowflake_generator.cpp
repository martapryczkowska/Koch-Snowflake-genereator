//POP_2016_01_19_projekt_2_Pryczkowska_Marta_AIR_3_160858 Dev-C++ 5.11
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
using namespace std;

void licz_punkty(double x1, double y1, double x5, double y5, double &x2, double &y2, double &x3, double &y3, double &x4, double &y4)		// obliczenie punkt�w dla boku podzielonego na 4
{
	double dlugosc_x = (x5 - x1) / 3.0;
	double dlugosc_y = (y5 - y1) / 3.0;
	 x2 = x1 + dlugosc_x;
	 y2 = y1 + dlugosc_y;
	 x4 = x5 - dlugosc_x;
	 y4 = y5- dlugosc_y;
	 x3 = (x1 + x5) / 2 - (y5 - y1) / (2 * sqrt(3.0));
	 y3 = (y1 + y5) / 2 + (x5 - x1) / (2 * sqrt(3.0));
}


void dziel_bok(fstream &plik, double x1, double y1, double x5, double y5, int glebokosc, int max_glebokosc){								//dzielenie boku na 4 odcinki 
	if (glebokosc <  max_glebokosc){																										//sprawdzenie czy g�eboko�� mniejsza od maksymalnej
		double x2,y2,x3,y3,x4,y4;																											
		licz_punkty(x1, y1, x5, y5, x2, y2, x3, y3, x4, y4);																				
		dziel_bok(plik, x1, y1, x2, y2, glebokosc + 1,max_glebokosc);																		//rekurencja
		dziel_bok(plik, x2, y2, x3, y3, glebokosc + 1, max_glebokosc);
		dziel_bok(plik, x3, y3, x4, y4, glebokosc + 1, max_glebokosc);
		dziel_bok(plik, x4, y4, x5, y5, glebokosc + 1, max_glebokosc);
	}
	else {																																	//zapisanie do pliku, gdy g�eboko�� osi�gne�a wymagany poziom
		plik << x1 << ' ' << y1 << " moveto\n";
		plik << x5 << ' ' << y5 << " lineto\n";
		plik<< ((rand() % 6) +5)/10.0 << " setgray\n";
		plik << "stroke\n";
	}
}


void trojkat (fstream &plik, double x, double y, double dlugosc, int maxglebokosc){															//obliczanie bok�w tr�jk�ta r�wnobocznego
	double h = dlugosc * sqrt(3) / 2;																										//obliczenie wysoko�ci
	int glebokosc_poczatkowa=1;
	dziel_bok(plik, x, y + (2.0 / 3.0) * h, x + 0.5 * dlugosc, y - (1.0 / 3.0) * h, glebokosc_poczatkowa, maxglebokosc);					//pierwszy bok tr�jk�ta 
	dziel_bok(plik, x + 0.5 * dlugosc, y - (1.0 / 3.0) * h, x - 0.5 * dlugosc, y - (1.0 / 3.0) * h,glebokosc_poczatkowa, maxglebokosc);		//kolejne dwa boki 
	dziel_bok(plik, x - 0.5 * dlugosc, y - (1.0 / 3.0) * h, x, y + (2.0 / 3.0) * h, glebokosc_poczatkowa, maxglebokosc);
}

void petla(  int  max_glebokosc,int  min_glebokosc, fstream &plik, int max_dl, int min_dl, int &ilosc )	{
		
		for (int i =0; i < ilosc; i++){																				//p�tla wykonuje si� ilo�� razy podan� przez u�ytkownika
			int glebokosc = rand() % (max_glebokosc-min_glebokosc+1) + min_glebokosc;								//losowanie g�eboko�ci p�atka
			double 	dlugoscBoku = rand() % (max_dl-min_dl+1) + min_dl;												//losowanie dlugo�ci boku od minimalnej do maxymalnej									
			int x = rand() % 595 ;																					//losowanie �rodka  p�atka w zakresie wymiaru A4
			int y = rand() % 842;	
			trojkat(plik, x, y, dlugoscBoku, glebokosc);
		}
	}

int main(){

	int ilosc, min_dl, max_dl;
	int	max_glebokosc=7;
	int min_glebokosc=3;
	fstream plik;
	plik.open("example2.ps", fstream::out);
	plik << "%!PS\n";
	
	cout<<"Podaj ilosc platkow  sniegu "<<endl;				
	cin >> ilosc;
	cout<<"Podaj minimalna dlugosc boku  "<<endl;
	cin >> min_dl;
	cout<<"Podaj maksymalna dlugosc boku  "<<endl;
	cin >> max_dl;
	
	petla( max_glebokosc, min_glebokosc, plik, max_dl, min_dl, ilosc );
	
	
	plik << "showpage\n";
	plik.close();
	system("pause");
	return 0;
}
