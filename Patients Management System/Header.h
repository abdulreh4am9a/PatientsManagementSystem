#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

enum gkk { Privat, TK, BEK, AOK, DAK, BKK };
// Sie dürfen gerne andere Krankenkassen verwenden, solange die Anzahl bei 6 bleibt

struct datum {
	int jahr, monat, tag;
	// Jahr vierstellig, unsere Patienten sind schon älter
 };

struct patient{
	string name;
	datum geborn;
	gkk kkasse;
	bool geimpft;
	int impfprio;
	// höchste impfprio = 1, niedrigste Impfprio = 5
	// Alter < 20 -> Impfprio = 5
	// Alter > 60 -> Impfprio = 1
	// Alter zwischen 20 und 30 -> Impfprio = 4
	// Alter zwischen 30 und 45 -> Impfprio = 3
// Alter zwischen 45 und 60 -> Impfprio = 2
};
int menue();
void pat_erfassen(patient pat[], int& anz, const int MAX); //einen Patienten einführen
void patienten_auflisten(patient pat[], int anz); //Patientenliste anzeigen
bool datei_schreiben(patient pat[], int anz, string datuminame); //Patienten in die Akte schreiben
bool datei_lesen(patient pat[], int& no, const int MAX, string datuminame); //Lesen Sie Patienten aus der Datei
void patienten_sortieren(patient pat[], int anz); //Patienten nach Priorität sortieren
int finde_patient(patient pat[], int anz, int prio); //Finden Sie Patienten mit einer bestimmten Priorität
void impftermin_vergeben(patient pat[], int anz); //Impftermin vergeben