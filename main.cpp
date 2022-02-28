#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Adresat
{
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

vector<Adresat> wczytajOsobyZPliku (vector<Adresat> adresaci)
{
    Adresat wczytaj;
    const int koniecListy = 6;
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
            for (int i = 0; i < 6; i++)
            {
                switch (i)
                {
                case 0:
                    wczytaj.id = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    wczytaj.imie = pomocniczy[i];
                    break;
                case 2:
                    wczytaj.nazwisko = pomocniczy[i];
                    break;
                case 3:
                    wczytaj.numerTelefonu = pomocniczy[i];
                    break;
                case 4:
                    wczytaj.email = pomocniczy[i];
                    break;
                case 5:
                    wczytaj.adres = pomocniczy[i];
                    break;
                }
                if (i >= koniecListy)
                {
                    i = 0;
                }
            }
            adresaci.push_back(wczytaj);
        }
        file.close();
    }
    else
    {
        cout << "Plik nie istnieje!! Tworze nowy plik o nazwie 'ksiazka.txt'" << endl;
        Sleep(2000);
        fstream file;
        file.open("ksiazka.txt", ios::out);
    }
    return adresaci;
}

int sprawdzOstatniID(vector<Adresat> adresaci)
{
    int ostatniID;
    ifstream file;
    file.open("ksiazka.txt", ios::in);
    file.seekg(0, ios::end);
    if (file.tellg() == 0)
    {
        return ostatniID = 0;
    }
    else
    {
        vector <Adresat>::iterator itr = adresaci.end();
        int i = adresaci.size() - 1;
        ostatniID=adresaci[i].id;
        return ostatniID;
    }
}
vector<Adresat> dodajNowego(vector<Adresat> adresaci)
{
    Adresat nowy;
    system("cls");
    cout<<"Podaj imie: ";
    cin>>nowy.imie;
    cout<<"Podaj nazwisko: ";
    cin>>nowy.nazwisko;
    cout<<"Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nowy.numerTelefonu);
    cout<<"Podaj e-mail: ";
    cin>>nowy.email;
    cout<<"Podaj miejsce zamieszkania: ";
    cin.sync();
    getline(cin, nowy.adres);
    nowy.id=sprawdzOstatniID(adresaci)+1;
    adresaci.push_back(nowy);

    //DODAWANIE DO PLIKU:
    ofstream file;
    file.open("ksiazka.txt", ios::out | ios::app);
    if (file.good() == true)
    {
        file << nowy.id << "|" << nowy.imie << "|" << nowy.nazwisko << "|" << nowy.numerTelefonu << "|" << nowy.email << "|" << nowy.adres << "|"<<endl;
        file.close();
        cout << "Ososba dodana do ksiazki adresowej" << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Plik nie istnieje!!" << endl;
        Sleep(1500);
    }
    return adresaci;
}

void wyszukajImie (vector<Adresat> adresaci)
{
    string wyszukajImie = "";
    bool flaga = true;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj imie osoby ktora chcesz wyszukac: ";
        cin>>wyszukajImie;
        for (int i=0; i<adresaci.size(); i++)
        {
            if (wyszukajImie == adresaci[i].imie)
            {
                cout<<"********"<<endl;
                cout<<"Id osoby: "<<adresaci[i].id<<endl;
                cout<<"Imie: "<<adresaci[i].imie<<endl;
                cout<<"Nazwisko: "<<adresaci[i].nazwisko<<endl;
                cout<<"Numer telefonu: "<<adresaci[i].numerTelefonu<<endl;
                cout<<"Adres e-mail: "<<adresaci[i].email<<endl;
                cout<<"Adres zamieszkania: "<<adresaci[i].adres<<endl;
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
void wyszukajNazwisko (vector<Adresat> adresaci)
{
    string wyszukajNazwisko = "";
    bool flaga = true;;
    if (adresaci.size() > 0)
    {
        cout<<"Podaj nazwisko osoby ktora chcesz wyszukac: ";
        cin>>wyszukajNazwisko;
        for (int i=0; i< adresaci.size(); i++)
        {
            if (wyszukajNazwisko == adresaci[i].nazwisko)
            {
                cout<<"********"<<endl;
                cout<<"Id osoby: "<<adresaci[i].id<<endl;
                cout<<"Imie: "<<adresaci[i].imie<<endl;
                cout<<"Nazwisko: "<<adresaci[i].nazwisko<<endl;
                cout<<"Numer telefonu: "<<adresaci[i].numerTelefonu<<endl;
                cout<<"Adres e-mail: "<<adresaci[i].email<<endl;
                cout<<"Adres zamieszkania: "<<adresaci[i].adres<<endl;
                cout<<"********"<<endl;
                flaga=false;
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
vector<Adresat> usunAdresata(vector<Adresat> adresaci)
{
    int idUsun = 0;
    bool flaga = true;
    Adresat usun;
    vector <Adresat>::iterator itr = adresaci.begin();
    if (adresaci.size() > 0)
    {
        cout<<"Podaj ID osoby ktora chcesz usunac z ksiazki adresowej: "<<endl;
        cin>>idUsun;
        for (itr; itr != adresaci.end(); itr++)
        {
            if (itr->id == idUsun)
            {
                char akcept;
                cout<<"Czy na pewno chcesz usunac danego adresata? Jesli tak, wcisnij t"<<endl;
                cin>>akcept;
                if (akcept == 't')
                {
                    adresaci.erase(itr);
                    flaga = false;
                    cout<<"Usunalem kontakt."<<endl;
                    Sleep(1000);
                    break;
                }
                else cout<<"Nie usunalem tego kontaktu."<<endl;
                Sleep(2000);
                break;
            }
        }
        if (flaga == true) cout<<"Nie ma uzytkownika z takim ID!"<<endl;
        Sleep(2000);
    }
    else
    {
        cout<<"Dodaj pierwsza osobe do ksiazki. . . "<<endl;
        Sleep(1500);
    }

    fstream file;
    file.open("ksiazka_tmp.txt", ios::out | ios::app);
    if (file.good())
    {
        for (int i=0; i<adresaci.size(); i++)
        {
            if(adresaci[i].id == idUsun)
            {
                continue;
            }
            file << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << "|"<<endl;
        }
        file.close();
        remove("ksiazka.txt");
        rename("ksiazka_tmp.txt", "ksiazka.txt");
    }
    else
    {
        cout << "Plik nie istnieje!!" << endl;
        Sleep(2000);
    }

    return adresaci;
}

vector<Adresat> edytujAdresata(vector<Adresat> adresaci)
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
            if (adresaci[i].id == idEdytuj)
            {
                char wybor;
                system("cls");
                cout<<"1. Imie"<<endl;
                cout<<"2. Nazwisko"<<endl;
                cout<<"3. Numer telefonu"<<endl;
                cout<<"4. E-mail"<<endl;
                cout<<"5. Adres"<<endl;
                cout<<"6. Powrot do menu glownego"<<endl;
                cin>>wybor;
                if(wybor == '1')
                {
                    cout<<"Podaj nowe imie: ";
                    cin>>zmiana;
                    adresaci[i].imie = zmiana;
                    cout<<endl<<"Imie zostalo zmienione!";
                    Sleep(1000);
                }
                else if(wybor == '2')
                {
                    cout<<"Podaj nowe nazwisko: ";
                    cin>>zmiana;
                    adresaci[i].nazwisko = zmiana;
                    cout<<endl<<"Naziwsko zostalo zmienione!";
                    Sleep(1000);

                }
                else if(wybor == '3')
                {
                    cout<<"Podaj nowy numer: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].numerTelefonu = zmiana;
                    cout<<endl<<"Numer telefonu zostal zmieniony!";
                    Sleep(1000);

                }
                else if(wybor == '4')
                {
                    cout<<"Podaj nowy e-mail: ";
                    cin>>zmiana;
                    adresaci[i].email=zmiana;
                    cout<<endl<<"E-mail zostal zmieniony!";
                    Sleep(1000);

                }
                else if(wybor == '5')
                {
                    cout<<"Podaj nowy adres: ";
                    cin.sync();
                    getline(cin, zmiana);
                    adresaci[i].adres = zmiana;
                    cout<<endl<<"Adres zostal zmieniony!";
                    Sleep(1000);
                }
                else if(wybor == '6')
                {

                }
                flaga = false;
                break;
            }
        }
        if (flaga==true)
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

    fstream file;
    file.open("ksiazka_tmp.txt", ios::out | ios::app);
    if (file.good())
    {
        for (int i=0; i<adresaci.size(); i++)
        {
            file << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|";
            file << adresaci[i].numerTelefonu << "|";
            file << adresaci[i].email << "|";
            file << adresaci[i].adres << "|"<<endl;
        }
        file.close();
        remove("ksiazka.txt");
        rename("ksiazka_tmp.txt", "ksiazka.txt");
    }
    else
    {
        cout << "Plik nie istnieje!!" << endl;
        Sleep(2000);
    }
    return adresaci;
}
void pokazWszystkich (vector<Adresat> adresaci)
{
    vector <Adresat>::const_iterator itr = adresaci.begin();
    if (adresaci.size() > 0)
    {
        for (itr; itr != adresaci.end(); ++itr)
        {
            cout<<"********"<<endl;
            cout<<"Id osoby: "<<itr->id<<endl;
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
int main()
{
    vector<Adresat> adresaci;
    adresaci = wczytajOsobyZPliku(adresaci);
    char wybor;
    while(true)
    {
        system("cls");
        cout<<"1. Dodaj nowa osobe"<<endl;
        cout<<"2. Wyszukaj osobe po imieniu"<<endl;
        cout<<"3. Wyszukaj osobe po nazwisku"<<endl;
        cout<<"4. Pokaz wszystkich"<<endl;
        cout<<"5. Usun adresata"<<endl;
        cout<<"6. Edytuj adresata"<<endl;
        cout<<"9. Zakoncz program"<<endl;
        cout<<"Twoj wybor: "<<endl;
        cin>>wybor;
        if(wybor == '1')
        {
            adresaci = dodajNowego(adresaci);
        }
        else if(wybor == '2')
        {
            wyszukajImie(adresaci);
        }
        else if(wybor == '3')
        {
            wyszukajNazwisko(adresaci);
        }
        else if(wybor == '4')
        {
            pokazWszystkich(adresaci);
        }
        else if(wybor == '5')
        {
            adresaci = usunAdresata(adresaci);
        }
        else if(wybor == '6')
        {
            adresaci = edytujAdresata(adresaci);
        }
        else if(wybor == '9')
        {
            exit(0);
        }
    }
    return 0;
}
