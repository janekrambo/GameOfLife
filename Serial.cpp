/* 
 * File:   main.cpp
 * Author: Michal Zdrodowski
 *
 * Created on 5 maja 2014, 18:55
 */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "gol.h"

using namespace std;

int arrayDimension = 0; //n czyli długość i szerokość obrazka
int iterNum = 1;		//liczba iteracji które mają się wykonać
int currIterNum = 0;
bool ** inputArray;
bool ** outputArray;

/*
 * 
 */
int main(int argc, char** argv) {
printf("Projekt: GRA W ZYCIE\n\n");
	if (argc != 3){
		printf("Podano niepoprawna liczbe argumentow\n");
		printf("Prawidlowe uzycie:\n\n %s filename.bmp n\n\n", argv[0]);
		printf("\t\tfilename.bmp\t- mapa bitowa BMP o rozmiarze nxn\n");
		printf("\t\tn\t\t- liczba iteracji\n");
	}
	else{
		//char tymczas[18] = "sample_input.bmp";
		iterNum = (int) atoi(argv[2]);
		/*Wczytanie do tablicy z pliku i weryfikacja*/
		ReadFile(argv[1], arrayDimension);
		//ReadFile(tymczas, arrayDimension);
		printf("\n funkcja  main - array dimesion = %d\n", arrayDimension);

		allocArray(&outputArray, arrayDimension);
		initialArray(outputArray);
		for (int i = 0; i < iterNum; i++){
			currIterNum = i;
			/*Tutaj głowny algorytm*/
			ProcessArray(inputArray, outputArray);
			/*zapisanie zawartości outputArray do pliku wyjściowego*/
			SaveArrayToFile(outputArray);
			/*output array staje się input array i vcvsa*/
			bool ** tmp = inputArray;
			inputArray = outputArray;
			outputArray = tmp;
			//ShiftArrays(inputArray, outputArray);
		}
		/*zwalnianie pamięci*/
		deallocArray(&inputArray, arrayDimension);
		deallocArray(&outputArray, arrayDimension);
		freeMem;
		return 0;
}

}
