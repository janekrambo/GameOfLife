#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "gol.h"
#include <iostream>

using namespace std;

int arrayDimension = 0; //n czyli długość i szerokość obrazka
int iterNum = 1;		//liczba iteracji które mają się wykonać
int currIterNum = 0;
bool ** inputArray;
bool ** outputArray;
bool saveOutput = false;

/* Przetwarzanie tablicy - główny algorytm*/

int ProcessArray(bool** inArr, bool ** outArr){
	int tmp = 0;
	for (int i = 1; i < (arrayDimension+1);i++){

		for (int j = 1; j < (arrayDimension + 1); j++){
			tmp = 0;
			tmp += (int)inArr[i + 1][j - 1];
			tmp += (int)inArr[i][j - 1];
			tmp += (int)inArr[i - 1][j - 1];
			tmp += (int)inArr[i - 1][j];
			tmp += (int)inArr[i - 1][j + 1];
			tmp += (int)inArr[i][j + 1];
			tmp += (int)inArr[i + 1][j + 1];
			tmp += (int)inArr[i + 1][j];

			if (inArr[i][j] == 0){
				switch (tmp) {
				case 3 :
					outArr[i][j] = 1;
					break;
				default :
					outArr[i][j] = 0;
				}
			}
			else {

				if (tmp < 2){
					outArr[i][j] = 0;
				}
				else{
					if (tmp < 4){
						outArr[i][j] = 1;
					}
					else{
						outArr[i][j] = 0;
					}
				}
			}
		}

	}

	return 0;
}

int main(int argc, char** argv) {
printf("Projekt: GRA W ZYCIE\n\n");
	if (argc != 4){
		printf("Podano niepoprawna liczbe argumentow\n");
		printf("Prawidlowe uzycie:\n\n %s filename.bmp n\n\n", argv[0]);
		printf("\t\tfilename.bmp\t- mapa bitowa BMP o rozmiarze nxn\n");
		printf("\t\tn\t\t- liczba iteracji\n");
		printf("\t\tt/n\t\t- czy zapisać do pliku\n");
		printf("\n");
	}
	else
	{
		//char tymczas[18] = "sample_input.bmp";
		iterNum = (int) atoi(argv[2]);
		/*Wczytanie do tablicy z pliku i weryfikacja*/
		ReadFile(argv[1], arrayDimension);
		//ReadFile(tymczas, arrayDimension);
		printf("\narray dimesion = %d\n", arrayDimension);

		char c = *argv[3];
		if(c=='t'){
            saveOutput=true;
            printf("\n - Wyniki zostaną zapisane do plików. \n\n");
		}else
		{
		    printf("\n - Wyniki nie zostaną zapisane do plików. \n\n");
		}
		allocArray(&outputArray, arrayDimension);
		initialArray(outputArray);
		for (int i = 0; i < iterNum; i++){
			currIterNum = i;
			/*Tutaj głowny algorytm*/
			ProcessArray(inputArray, outputArray);
			/*zapisanie zawartości outputArray do pliku wyjściowego*/
			if(saveOutput){
                SaveArrayToFile(outputArray);
            }
			/*output array staje się input array i vcvsa*/
			bool ** tmp = inputArray;
			inputArray = outputArray;
			outputArray = tmp;
		}
		/*zwalnianie pamięci*/
		deallocArray(&inputArray, arrayDimension);
		deallocArray(&outputArray, arrayDimension);
		freeMem();
		return 0;
    }
}
