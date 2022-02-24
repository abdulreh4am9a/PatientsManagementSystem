#include"Header.h"
int menue()
{
	int wahl;
	cout << "++ Terminplaner ++" << endl;
	cout << "1. Neuen Patienten erfassen" << endl;
	cout << "2. Patientenliste ausgeben" << endl;
	cout << "3. Patientenliste in eine datumi schreiben" << endl;
	cout << "4. Patientenliste aus einer datumi lesen" << endl;
	cout << "5. Patienten nach Impfpriorität patienten_sortierenieren" << endl;
	cout << "6. Impftermine vergeben" << endl;
	cout << "0. Programmende" << endl;
	cin >> wahl;
	return wahl;
}
void pat_erfassen(patient pat[], int& anz, const int MAX) {
	if (anz >= MAX) {
		cout << endl << "Es können keine weiteren Patienten eingefügt werden" << endl << endl;
		return;
	}
	string name;
	datum geborn;
	gkk kkasse;
	int impfprio, jahr, monat, tag, ch, alter;
	cout << endl << "Geben Sie den Namen des Patienten ein: ";
	cin >> name;
	cout << "Geburtsdatum eingeben [DD/MM/YYYY]" << endl;
	cout << "Tag: ";
	cin >> tag;
	cout << "Monat: ";
	cin >> monat;
	cout << "Jahr: ";
	cin >> jahr;
	geborn.tag = tag;
	geborn.monat = monat;
	geborn.jahr = jahr;
	cout << "Krankenkasse auswählen" << endl;
	cout << "1. Privat\n2. TK\n3. BEK\n4. AOK\n5. DAK\n6. BKK" << endl;
	cout << "Auswahl: ";
	cin >> ch;
	cout << endl;
	switch (ch) {
	case 1:kkasse = Privat;break;
	case 2:kkasse = TK;break;
	case 3:kkasse = BEK;break;
	case 4:kkasse = AOK;break;
	case 5:kkasse = DAK;break;
	case 6:kkasse = BKK;break;
	}
	alter = 2022 - jahr;
	if (alter < 20) {
		impfprio = 5;
	}
	else if (alter > 60) {
		impfprio = 1;
	}
	else if (alter <= 60 && alter > 45) {
		impfprio = 2;
	}
	else if (alter <= 45 && alter > 30) {
		impfprio = 3;
	}
	else if (alter <= 30 && alter >= 20) {
		impfprio = 4;
	}
	patient p;
	p.geborn = geborn;
	p.kkasse = kkasse;
	p.name = name;
	p.impfprio = impfprio;
	p.geimpft = false;
	pat[anz] = p;
	anz++;
}
void patienten_auflisten(patient pat[], int anz) {
	cout << endl << "Liste der Patienten:" << endl;
	for (int i = 0;i < anz;i++) {
		cout << i + 1 << ". " << pat[i].name << "(" << pat[i].geborn.tag << ", " << pat[i].geborn.monat << ", " << pat[i].geborn.jahr << ") ";
		if (pat[i].geimpft) {
			cout << "Geimpft!";
		}
		else {
			cout << "Nicht geimpft!";
		}
		cout << endl << "   Krankenversicherung: ";
		switch (pat[i].kkasse) {
		case 0:cout << "Privat";break;
		case 1:cout << "TK";break;
		case 2:cout << "BEK";break;
		case 3:cout << "AOK";break;
		case 4:cout << "DAK";break;
		case 5:cout << "BKK";break;
		}
		cout << endl;
	}
	cout << endl;
}

//Die Daten werden im folgenden Format in die Datei geschrieben
//name,tag,monat,jahr,kkasse,impfprio,geimpft
bool datei_schreiben(patient pat[], int anz, string datuminame) {
	ofstream die_datumi(datuminame, ios_base::app);
	if (die_datumi.is_open()) {
		for (int i = 0;i < anz;i++) {
			die_datumi << pat[i].name << "," << pat[i].geborn.tag << "," << pat[i].geborn.monat << "," << pat[i].geborn.jahr << "," << pat[i].kkasse << "," << pat[i].impfprio << "," << pat[i].geimpft << endl;
		}
		die_datumi.close();
	}
	else {
		return false;
	}
}

//Die Daten werden im folgenden Format aus der Datei gelesen
//name,tag,monat,jahr,kkasse,impfprio,geimpft
bool datei_lesen(patient pat[], int& anz, const int MAX, string datuminame) {
	ifstream die_datumi(datuminame);
	if (die_datumi.is_open()) {
		string line, tag, monat, jahr, kkasse, impfprio, geimpft;
		while (getline(die_datumi, line)) {
			stringstream ss(line);
			patient p;
			getline(ss, p.name, ',');
			getline(ss, tag, ',');
			getline(ss, monat, ',');
			getline(ss, jahr, ',');
			getline(ss, kkasse, ',');
			getline(ss, impfprio, ',');
			getline(ss, geimpft, ',');
			p.impfprio = stoi(impfprio);
			if (stoi(geimpft)) {
				p.geimpft = true;
			}
			else {
				p.geimpft = false;
			}
			p.geborn.tag = stoi(tag);
			p.geborn.monat = stoi(monat);
			p.geborn.jahr = stoi(jahr);
			switch (stoi(kkasse)) {
			case 1:p.kkasse = Privat;break;
			case 2:p.kkasse = TK;break;
			case 3:p.kkasse = BEK;break;
			case 4:p.kkasse = AOK;break;
			case 5:p.kkasse = DAK;break;
			case 6:p.kkasse = BKK;break;
			}
			if (anz < MAX) {
				pat[anz] = p;
				anz++;
			}
			else {
				cout << endl << "Datei nicht vollständig gelesen, aber das Limit ist erreicht!" << endl << endl;
			}
		}
		die_datumi.close();
		return true;
	}
	else {
		return false;
	}
}
void patienten_sortieren(patient pat[], int anz) {
	for (int i = 1;i < anz;i++) {
		patient hinstellen = pat[i];
		int j = i - 1;
		while (j >= 0 && hinstellen.impfprio < pat[j].impfprio) {
			pat[j + 1] = pat[j];
			j--;
		}
		pat[j + 1] = hinstellen;
	}
}
int finde_patient(patient pat[], int anz, int prio){
	int gesamt = 0;
	for (int i = 0;i < anz;i++) {
		if (pat[i].impfprio == prio && !pat[i].geimpft) {
			gesamt++;
		}
	}
	return gesamt;
}
void impftermin_vergeben(patient pat[], int anz) {
	patienten_sortieren(pat, anz);
	int prio = pat[0].impfprio;
	int anzahl_der_patienten = finde_patient(pat, anz, prio);
	anzahl_der_patienten /= 6;
	anzahl_der_patienten *= 6;
	if (anzahl_der_patienten == 0) {
		cout << endl << "Die Anzahl der Patienten ist kein Vielfaches von sechs" << endl << endl;
	}
	int j = 0;
	for (int i = 0;i < anz;i++) {
		if (j < anzahl_der_patienten && !pat[i].geimpft) {
			pat[i].geimpft = true;
			cout << endl << "Name: " << pat[i].name << " Geimpft!" << endl;
			j++;
		}
		if (!pat[i].geimpft && pat[i].impfprio > prio) {
			pat[i].impfprio--;
		}
	}
	cout << endl;
}