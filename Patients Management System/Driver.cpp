#include"Header.h"
#define MAX 100
int main() {
	patient patients[MAX];
	int anzahl_der_patienten = 0;
	bool programmende = false;
	int auswahl;
	string dateiname;
	do
	{
		auswahl = menue();
		switch (auswahl)
		{
		case 0:
			programmende = true;
			cout << endl << "Vielen Dank, dass Sie Ihre Termine mit dem Terminplaner verwalten" << endl;
			cout << "Bis bald...!" << endl << endl;
			break;
		case 1:
			pat_erfassen(patients, anzahl_der_patienten, MAX);
			break;
		case 2:
			patienten_auflisten(patients, anzahl_der_patienten);
			break;
		case 3:
			cout << endl << "Bitte geben Sie den Dateinamen ein: ";
			cin >> dateiname;
			if (datei_schreiben(patients, anzahl_der_patienten, dateiname)) {
				cout << endl << "Patienten erfolgreich in Akte geschrieben!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht geöffnet werden" << endl << endl;
			}
			break;
		case 4:
			cout << endl << "Bitte geben Sie den Dateinamen ein: ";
			cin >> dateiname;
			if (datei_lesen(patients, anzahl_der_patienten, MAX, dateiname)) {
				cout << endl << "Patienten erfolgreich aus Datei gelesen!" << endl << endl;
			}
			else {
				cout << endl << "Datei kann nicht geöffnet werden" << endl << endl;
			}
			break;
		case 5:
			patienten_sortieren(patients, anzahl_der_patienten);
			break;
		case 6:
			impftermin_vergeben(patients, anzahl_der_patienten);
			break;
		default:
			cout << endl << "Diesen menueepunkt gibt es leider nicht.." << endl << endl;
			break;
		}
	} while (!programmende);
	return 0;
}