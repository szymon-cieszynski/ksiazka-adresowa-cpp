//Ksiazka adresowa z uzytkownikami
#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Adresat
{
    int idAdresata = 0;
    int idUsera = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa = "", haslo = "";
};

void wczytajOsobyZPliku (vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat wczytaj;
    const int koniecListy = 7;
    string linia = "";
    fstream file;
    file.open("ksiazka.txt", ios::in);
    if (file.good())
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 7; i++)
            {
                switch (i)
                {
                case 0:
                    wczytaj.idAdresata = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    wczytaj.idUsera = atoi(pomocniczy[i].c_str());
                    break;
                case 2:
                    wczytaj.imie = pomocniczy[i];
                    break;
                case 3:
                    wczytaj.nazwisko = pomocniczy[i];
                    break;
                case 4:
                    wczytaj.numerTelefonu = pomocniczy[i];
                    break;
                case 5:
                    wczytaj.email = pomocniczy[i];
                    break;
                case 6:
                    wczytaj.adres = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
            }
            if (wczytaj.idUsera == idZalogowanegoUzytkownika)
            {
                adresaci.push_back(wczytaj);
            }
        }
        file.close();
    }
}

int sprawdzOstatniID()
{
    Adresat sprawdz;
    int ostatniID = 0;
    vector<Adresat> ostatni;
    const int koniecListy = 7;
    string linia = "";
    fstream file;
    file.open("ksiazka.txt", ios::in);
    while (getline(file, linia))
    {
        string s = linia;
        stringstream ss(s);
        string item;
        vector <string> pomocniczy;
        while (getline(ss, item, '|'))
        {
            pomocniczy.push_back(item);
        }
        for (int i = 0; i < 7; i++)
        {
            switch (i)
            {
            case 0:
                sprawdz.idAdresata = atoi(pomocniczy[i].c_str());
                break;
            case 1:
                sprawdz.idUsera = atoi(pomocniczy[i].c_str());
                break;
            case 2:
                sprawdz.imie = pomocniczy[i];
                break;
            case 3:
                sprawdz.nazwisko = pomocniczy[i];
                break;
            case 4:
                sprawdz.numerTelefonu = pomocniczy[i];
                break;
            case 5:
                sprawdz.email = pomocniczy[i];
                break;
            case 6:
                sprawdz.adres = pomocniczy[i];
                break;
            }
            if (i >= koniecListy)
            {
                i = 0;
            }
        }
    }
    file.close();

    ostatni.push_back(sprawdz);
    int i = ostatni.size() - 1;
    ostatniID = ostatni[i].idAdresata;
    return ostatniID;
}

void dodajNowego(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    Adresat nowy;
    system("cls");
    cout<<"Podaj imie: ";
    cin.sync();
    getline(cin, nowy.imie);
    cout<<"Podaj nazwisko: ";
    cin.sync();
    getline(cin, nowy.nazwisko);
    cout<<"Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nowy.numerTelefonu);
    cout<<"Podaj e-mail: ";
    cin.sync();
    getline(cin, nowy.email);
    cout<<"Podaj miejsce zamieszkania: ";
    cin.sync();
    getline(cin, nowy.adres);
    nowy.idAdresata = sprawdzOstatniID() + 1;
    adresaci.push_back(nowy);

    //DODAWANIE DO PLIKU:
    fstream file;
    file.open("ksiazka.txt", ios::out | ios::app);
    if (file.good() == true)
    {
        file << nowy.idAdresata << "|" << idZalogowanegoUzytkownika << "|" << nowy.imie << "|" << nowy.nazwisko << "|" << nowy.numerTelefonu << "|" << nowy.email << "|" << nowy.adres << "|"<<endl;
        file.close();
        cout << "Osoba dodana do ksiazki adresowej" << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Plik nie istnieje!!" << endl;
        Sleep(1500);
    }
}

void wyszukajImie (vector<Adresat> &adresaci)
{
    string wyszukajImie = "";
    bool flaga = true;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj imie osoby ktora chcesz wyszukac: ";
        cin>>wyszukajImie;
        vector <Adresat>::iterator itr = adresaci.begin();
        for (itr; itr != adresaci.end(); itr++)
        {
            if (itr->imie == wyszukajImie)
            {
                cout<<"********"<<endl;
                cout<<"Id osoby: "<<itr->idAdresata<<endl;
                cout<<"Imie: "<<itr->imie<<endl;
                cout<<"Nazwisko: "<<itr->nazwisko<<endl;
                cout<<"Numer telefonu: "<<itr->numerTelefonu<<endl;
                cout<<"Adres e-mail: "<<itr->email<<endl;
                cout<<"Adres zamieszkania: "<<itr->adres<<endl;
                cout<<"********"<<endl;
                flaga = false;
            }
        }
        if (flaga == false)
        {
            system("pause");
        }
        if (flaga == true)
        {
            cout<<"Nie ma uzytkownika z takim imieniem!"<<endl;
            Sleep(1500);
        }
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1500);
    }
}
void wyszukajNazwisko (vector<Adresat> &adresaci)
{
    string wyszukajNazwisko = "";
    bool flaga = true;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj nazwisko osoby ktora chcesz wyszukac: ";
        cin>>wyszukajNazwisko;
        vector <Adresat>::iterator itr = adresaci.begin();
        for (itr; itr != adresaci.end(); itr++)
        {
            if (itr->nazwisko == wyszukajNazwisko)
            {
                cout<<"********"<<endl;
                cout<<"Id osoby: "<<itr->idAdresata<<endl;
                cout<<"Imie: "<<itr->imie<<endl;
                cout<<"Nazwisko: "<<itr->nazwisko<<endl;
                cout<<"Numer telefonu: "<<itr->numerTelefonu<<endl;
                cout<<"Adres e-mail: "<<itr->email<<endl;
                cout<<"Adres zamieszkania: "<<itr->adres<<endl;
                cout<<"********"<<endl;
                flaga = false;
            }
        }
        if (flaga == false)
        {
            system("pause");
        }
        if (flaga == true)
        {
            cout<<"Nie ma uzytkownika z takim nazwiskiem!"<<endl;
            Sleep(1500);
        }
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1200);
    }
}

void usunZPliku (vector<Adresat> &adresaci, int idUsun)
{
    Adresat usun;
    const int koniecListy = 7;
    vector<Adresat> tymczasowy;
    fstream file, file1;
    file.open("ksiazka.txt", ios::in);
    file1.open("ksiazka_tmp.txt", ios::out | ios::app);
    string linia = "";
    if (file.good())
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 7; i++)
            {
                switch (i)
                {
                case 0:
                    usun.idAdresata = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    usun.idUsera = atoi(pomocniczy[i].c_str());
                    break;
                case 2:
                    usun.imie = pomocniczy[i];
                    break;
                case 3:
                    usun.nazwisko = pomocniczy[i];
                    break;
                case 4:
                    usun.numerTelefonu = pomocniczy[i];
                    break;
                case 5:
                    usun.email = pomocniczy[i];
                    break;
                case 6:
                    usun.adres = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
                tymczasowy.push_back(usun);
            }
            if (usun.idAdresata == idUsun)
            {
                continue;
            }
            else
            {
                file1 << linia << endl;
            }
        }
        file.close();
        file1.close();
    }
    remove("ksiazka.txt");
    rename("ksiazka_tmp.txt", "ksiazka.txt");
}

vector<Adresat> usunAdresata(vector<Adresat> &adresaci)
{
    int idUsun = 0;
    bool flaga = true;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj ID osoby ktora chcesz usunac z ksiazki adresowej: "<<endl;
        cin>>idUsun;
        vector <Adresat>::iterator itr = adresaci.begin();
        for (itr; itr != adresaci.end(); itr++)
        {
            if (itr->idAdresata == idUsun)
            {
                flaga = false;
                char akcept;
                cout<<"Czy na pewno chcesz usunac danego adresata? Jesli tak, wcisnij t"<<endl;
                cin>>akcept;
                if (akcept == 't')
                {
                    usunZPliku(adresaci, idUsun);
                    adresaci.erase(itr);
                    usunZPliku(adresaci, idUsun);
                    cout<<"Usunalem kontakt."<<endl;
                    Sleep(1000);
                    break;
                }
                else cout<<"Nie usunalem tego kontaktu."<<endl;
                Sleep(2000);
                break;
            }
        }
        if (flaga == true)
        {
            cout<<"Nie ma uzytkownika z takim ID!"<<endl;
            Sleep(2000);
        }
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1500);
    }
    return adresaci;
}

void edytujPlik (Adresat adresat, int idEdytuj)
{
    Adresat edycja;
    const int koniecListy = 7;
    vector<Adresat> tymczasowy;
    fstream file, file1;
    file.open("ksiazka.txt", ios::in);
    file1.open("ksiazka_tmp.txt", ios::out | ios::app);
    string linia = "";
    if (file.good())
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 7; i++)
            {
                switch (i)
                {
                case 0:
                    edycja.idAdresata = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    edycja.idUsera = atoi(pomocniczy[i].c_str());
                    break;
                case 2:
                    edycja.imie = pomocniczy[i];
                    break;
                case 3:
                    edycja.nazwisko = pomocniczy[i];
                    break;
                case 4:
                    edycja.numerTelefonu = pomocniczy[i];
                    break;
                case 5:
                    edycja.email = pomocniczy[i];
                    break;
                case 6:
                    edycja.adres = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
                tymczasowy.push_back(edycja);
            }
            if (edycja.idAdresata == idEdytuj)
            {
                file1 << adresat.idAdresata << "|" << adresat.idUsera << "|" << adresat.imie << "|" << adresat.nazwisko << "|" << adresat.numerTelefonu << "|" << adresat.email << "|" << adresat.adres << "|" << endl;
            }
            else
            {
                file1 << linia << endl;
            }
        }
        file.close();
        file1.close();
    }
    remove("ksiazka.txt");
    rename("ksiazka_tmp.txt", "ksiazka.txt");
}

void edytujAdresata(vector<Adresat> &adresaci)
{
    int idEdytuj = 0;
    string zmiana = "";
    bool flaga = true;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj ID osoby ktorej dane chcesz edytowac: "<<endl;
        cin>>idEdytuj;
        for (int i=0; i<adresaci.size(); i++)
        {
            if (adresaci[i].idAdresata == idEdytuj)
            {
                flaga = false;
                char wybor;
                system("cls");
                cout<<"Edytujesz: "<<adresaci[i].imie<<" "<<adresaci[i].nazwisko<<endl;
                cout<<"1. Imie"<<endl;
                cout<<"2. Nazwisko"<<endl;
                cout<<"3. Numer telefonu"<<endl;
                cout<<"4. E-mail"<<endl;
                cout<<"5. Adres"<<endl;
                cout<<"6. Powrot do menu glownego"<<endl;
                cin>>wybor;
                switch(wybor)
                {
                case '1':
                    cout<<"Podaj nowe imie: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].imie = zmiana;
                    edytujPlik(adresaci[i], idEdytuj);
                    cout<<endl<<"Imie zostalo zmienione!";
                    Sleep(1000);
                    break;
                case '2':
                    cout<<"Podaj nowe nazwisko: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].nazwisko = zmiana;
                    edytujPlik(adresaci[i], idEdytuj);
                    cout<<endl<<"Naziwsko zostalo zmienione!";
                    Sleep(1000);
                    break;
                case '3':
                    cout<<"Podaj nowy numer: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].numerTelefonu = zmiana;
                    edytujPlik(adresaci[i], idEdytuj);
                    cout<<endl<<"Numer telefonu zostal zmieniony!";
                    Sleep(1000);
                    break;
                case '4':
                    cout<<"Podaj nowy e-mail: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].email=zmiana;
                    edytujPlik(adresaci[i], idEdytuj);
                    cout<<endl<<"E-mail zostal zmieniony!";
                    Sleep(1000);
                    break;
                case '5':
                    cout<<"Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].adres = zmiana;
                    edytujPlik(adresaci[i], idEdytuj);
                    cout<<endl<<"Adres zostal zmieniony!";
                    Sleep(1000);
                    break;
                case '6':
                    continue;
                    break;
                }
            }
        }
        if (flaga==true)
        {
            cout<< endl << "Nie ma uzytkownika z takim ID w Twojej ksiazce!" << endl;
            Sleep(2000);
        }
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1500);
    }
}

void pokazWszystkich (vector<Adresat> &adresaci, int idZalogowanegoUzytkownika)
{
    vector <Adresat>::const_iterator itr = adresaci.begin();
    if (adresaci.size() > 0)
    {
        for (itr; itr != adresaci.end(); ++itr)
        {
            cout<<"********"<<endl;
            cout<<"Id osoby: "<<itr->idAdresata<<endl;
            cout<<"Imie: "<<itr->imie<<endl;
            cout<<"Nazwisko: "<<itr->nazwisko<<endl;
            cout<<"Numer telefonu: "<<itr->numerTelefonu<<endl;
            cout<<"Adres e-mail: "<<itr->email<<endl;
            cout<<"Adres zamieszkania: "<<itr->adres<<endl;
            cout<<"********"<<endl;
        }
        system("pause");
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1500);
    }
}

int sprawdzOstatniIDUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    Uzytkownik sprawdz;
    int ostatniID = 0;
    vector<Uzytkownik> ostatni;
    const int koniecListy = 3;
    string linia = "";
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    if(file.good() == false)
    {
        return 0;
    }
    else
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 3; i++)
            {
                switch (i)
                {
                case 0:
                    sprawdz.idUzytkownika = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    sprawdz.nazwa = atoi(pomocniczy[i].c_str());
                    break;
                case 2:
                    sprawdz.haslo = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
            }
        }
        file.close();
        ostatni.push_back(sprawdz);
        int i = ostatni.size() - 1;
        ostatniID = ostatni[i].idUzytkownika;
        return ostatniID;
    }
}

void wczytajUzytkownikow (vector<Uzytkownik> &uzytkownicy)
{
    Uzytkownik wczytaj;
    const int koniecListy = 3;
    string linia = "";
    fstream file;
    file.open("Uzytkownicy.txt", ios::in);
    if (file.good())
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 3; i++)
            {
                switch (i)
                {
                case 0:
                    wczytaj.idUzytkownika = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    wczytaj.nazwa = pomocniczy[i];
                    break;
                case 2:
                    wczytaj.haslo = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
            }
            uzytkownicy.push_back(wczytaj);
        }
        file.close();
    }
}

string sprawdzNazwe(vector<Uzytkownik> &uzytkownicy, string nazwa)
{
    int i = 0;
    while (i < uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout<<"Taka nazwa uzytkownika juz istnieje! Podaj nazwe uzytkownika jeszcze raz: "<<endl;
            cin>>nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    return nazwa;
}

void rejestracja (vector<Uzytkownik> &uzytkownicy)
{
    string nazwa = "";
    string haslo = "";
    int idUzytkownika = 0;
    cout<<"Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    nazwa = sprawdzNazwe(uzytkownicy, nazwa);
    cout<<"Podaj haslo: ";
    cin >> haslo;
    idUzytkownika = sprawdzOstatniIDUzytkownika(uzytkownicy)+1;

    //Dodawanie nowego uzytkownika do pliku:
    fstream file;
    file.open("Uzytkownicy.txt", ios::out | ios::app);
    if (file.good())
    {
        file << idUzytkownika << "|" << nazwa << "|" << haslo << endl;
        file.close();
        cout << "Konto zalozone" << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Plik nie istnieje!!" << endl;
        Sleep(1500);
    }
}

int logowanie (vector<Uzytkownik> &uzytkownicy)
{
    string nazwa, haslo;
    cout<<"Podaj login: ";
    cin>>nazwa;
    int i=0;
    while(i<uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby = 0; proby<3; proby++)
            {
                cout<<"Podaj haslo. Pozostalo prob "<<3-proby<<": ";
                cin>>haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba."<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem!"<<endl;
    Sleep(1500);
    return 0;
}

void edytujPlikUzytkownicy (Uzytkownik uzytkownik, int idZalogowanegoUzytkownika)
{
    Uzytkownik noweHaslo;
    const int koniecListy = 3;
    vector<Uzytkownik> tymczasowy;
    fstream file, file1;
    string linia = "";
    file.open("Uzytkownicy.txt", ios::in);
    file1.open("Uzytkownicy_tmp.txt", ios::out | ios::app);
    if (file.good())
    {
        while (getline(file, linia))
        {
            string s = linia;
            stringstream ss(s);
            string item;
            vector <string> pomocniczy;
            while (getline(ss, item, '|'))
            {
                pomocniczy.push_back(item);
            }
            for (int i = 0; i < 3; i++)
            {
                switch (i)
                {
                case 0:
                    noweHaslo.idUzytkownika = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    noweHaslo.nazwa = pomocniczy[i];
                    break;
                case 2:
                    noweHaslo.haslo = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
                tymczasowy.push_back(noweHaslo);
            }
            if (noweHaslo.idUzytkownika == idZalogowanegoUzytkownika)
            {
                file1 << uzytkownik.idUzytkownika << "|" << uzytkownik.nazwa  << "|" << uzytkownik.haslo << endl;
            }
            else
            {
                file1 << linia << endl;
            }
        }
        file.close();
        file1.close();
    }
    remove("Uzytkownicy.txt");
    rename("Uzytkownicy_tmp.txt", "Uzytkownicy.txt");
}

void zmianaHasla (vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string zmiana = "";
    for (int i=0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            cout<<endl<<"Podaj nowe haslo: ";
            cin.sync();
            getline(cin, zmiana);
            uzytkownicy[i].haslo = zmiana;
            edytujPlikUzytkownicy(uzytkownicy[i], idZalogowanegoUzytkownika);
            cout<<endl<<"Haslo zostalo zmienione!";
            Sleep(1000);
            break;
        }
    }
}

int main()
{
    int idZalogowanegoUzytkownika = 0;
    int iloscUzytkownikow = 0;
    char wybor;
    vector<Adresat> adresaci;
    vector<Uzytkownik> uzytkownicy;

    while(true)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            wczytajUzytkownikow(uzytkownicy);
            cout<<"1. Rejestracja"<<endl;
            cout<<"2. Logowanie"<<endl;
            cout<<"9. Zamknij program"<<endl;
            cin>>wybor;
            switch (wybor)
            {
            case '1':
                rejestracja(uzytkownicy);
                break;
            case '2':
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                if(idZalogowanegoUzytkownika!=0)
                {
                    wczytajOsobyZPliku(adresaci, idZalogowanegoUzytkownika);
                }
                break;
            case '9':
                adresaci.clear();
                uzytkownicy.clear();
                exit(0);
                break;
            }
        }
        else
        {
            system("cls");
            cout<<"Zalogowany uzytkownik o ID: "<<idZalogowanegoUzytkownika<<endl;
            cout<<"1. Dodaj nowa osobe"<<endl;
            cout<<"2. Wyszukaj osobe po imieniu"<<endl;
            cout<<"3. Wyszukaj osobe po nazwisku"<<endl;
            cout<<"4. Pokaz wszystkich"<<endl;
            cout<<"5. Usun adresata"<<endl;
            cout<<"6. Edytuj adresata"<<endl;
            cout<<"7. Zmien haslo"<<endl;
            cout<<"8. Wyloguj sie"<<endl;
            cout<<"Twoj wybor: ";
            cin>>wybor;
            switch (wybor)
            {
            case '1':
                dodajNowego(adresaci, idZalogowanegoUzytkownika);
                break;
            case '2':
                wyszukajImie(adresaci);
                break;
            case '3':
                wyszukajNazwisko(adresaci);
                break;
            case '4':
                pokazWszystkich(adresaci, idZalogowanegoUzytkownika);
                break;
            case '5':
                adresaci = usunAdresata(adresaci);
                break;
            case '6':
                edytujAdresata(adresaci);
                break;
            case '7':
                zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case '8':
                adresaci.clear();
                idZalogowanegoUzytkownika = 0;
                break;
            }
        }
    }
    return 0;
}
