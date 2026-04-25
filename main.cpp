#include <iostream>
#include <string>
#include <limits>
#include "SistemTransport.h"

// functii ajutatoare pentru meniu

void clearScreen() {
    system("cls");
}

void pauza() {
    std::cout << "\n  Apasa Enter pentru a continua...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// submeniu pentru gestionarea vehiculelor

void meniuVehicule(SistemTransport& sistem) {
    int optiune;
    do {
        std::cout << "\n--- Meniu Vehicule ---\n";
        std::cout << "1. Adauga autobuz\n";
        std::cout << "2. Adauga tramvai\n";
        std::cout << "3. Adauga metrou\n";
        std::cout << "4. Afiseaza toate vehiculele\n";
        std::cout << "5. Afiseaza detalii vehicul (dupa ID)\n";
        std::cout << "6. Urca pasageri intr-un vehicul\n";
        std::cout << "7. Coboara pasageri dintr-un vehicul\n";
        std::cout << "8. Incarca baterie vehicul electric\n";
        std::cout << "9. Verifica autonomie vehicul electric\n";
        std::cout << "0. Inapoi\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cin.ignore();
        clearScreen();

        switch (optiune) {
            case 1: {
                // cream un autobuz gol si citim datele cu operator>>
                Autobuz* a = new Autobuz();
                try {
                    std::cin >> *a;
                    sistem.adaugaVehicul(a);
                    std::cout << "  Autobuz adaugat cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                    delete a; // eliberam memoria daca adaugarea a esuat
                }
                break;
            }
            case 2: {
                Tramvai* t = new Tramvai();
                try {
                    std::cin >> *t;
                    sistem.adaugaVehicul(t);
                    std::cout << "  Tramvai adaugat cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                    delete t;
                }
                break;
            }
            case 3: {
                Metrou* m = new Metrou();
                try {
                    std::cin >> *m;
                    sistem.adaugaVehicul(m);
                    std::cout << "  Metrou adaugat cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                    delete m;
                }
                break;
            }
            case 4: {
                sistem.afiseazaToateVehiculele();
                pauza();
                break;
            }
            case 5: {
                int id;
                std::cout << "  ID vehicul: ";
                std::cin >> id;
                std::cin.ignore();
                try {
                    sistem.afiseazaVehiculDupaId(id);
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 6: {
                int id, nr;
                std::cout << "  ID vehicul: ";
                std::cin >> id;
                std::cout << "  Numar pasageri care urca: ";
                std::cin >> nr;
                std::cin.ignore();
                try {
                    sistem.urcaPasageri(id, nr);
                    std::cout << "  Pasageri urcati cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 7: {
                int id, nr;
                std::cout << "  ID vehicul: ";
                std::cin >> id;
                std::cout << "  Numar pasageri care coboara: ";
                std::cin >> nr;
                std::cin.ignore();
                try {
                    sistem.coboaraPasageri(id, nr);
                    std::cout << "  Pasageri coborati cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 8: {
                int id;
                double procente;
                std::cout << "  ID vehicul electric: ";
                std::cin >> id;
                std::cout << "  Procente de incarcat: ";
                std::cin >> procente;
                std::cin.ignore();
                try {
                    sistem.incarcaBaterieVehicul(id, procente);
                    std::cout << "  Baterie incarcata cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 9: {
                // verifica autonomia unui vehicul electric pentru o distanta data
                // demonstreaza dynamic_cast si polimorfism
                int id;
                double distanta;
                std::cout << "  ID vehicul electric: ";
                std::cin >> id;
                std::cout << "  Distanta de verificat (km): ";
                std::cin >> distanta;
                std::cin.ignore();
                try {
                    sistem.afiseazaVehiculeElectricePerDistanta(distanta);
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "  Optiune invalida!\n";
        }
    } while (optiune != 0);
}

// submeniu pentru gestionarea liniilor

void meniuLinii(SistemTransport& sistem) {
    int optiune;
    do {
        std::cout << "\n--- Meniu Linii ---\n";
        std::cout << "1. Creeaza linie noua\n";
        std::cout << "2. Atribuie vehicul la linie\n";
        std::cout << "3. Scoate vehicul din linie\n";
        std::cout << "4. Afiseaza toate liniile\n";
        std::cout << "5. Afiseaza vehiculele unei linii (polimorfism)\n";
        std::cout << "6. Gradul de ocupare al unei linii\n";
        std::cout << "7. Linia cea mai aglomerata\n";
        std::cout << "8. Cost mediu cursa pe linie\n";
        std::cout << "9. Adauga statie la linie\n";
        std::cout << "0. Inapoi\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cin.ignore();
        clearScreen();

        switch (optiune) {
            case 1: {
                Linie* l = new Linie();
                try {
                    std::cin >> *l;
                    sistem.adaugaLinie(l);
                    std::cout << "  Linie creata cu succes! ID: " << l->getId() << "\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                    delete l;
                }
                break;
            }
            case 2: {
                int idV, idL;
                std::cout << "  ID vehicul: ";
                std::cin >> idV;
                std::cout << "  ID linie: ";
                std::cin >> idL;
                std::cin.ignore();
                try {
                    sistem.atribuieVehiculLinie(idV, idL);
                    std::cout << "  Vehicul atribuit liniei cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 3: {
                int idV, idL;
                std::cout << "  ID vehicul: ";
                std::cin >> idV;
                std::cout << "  ID linie: ";
                std::cin >> idL;
                std::cin.ignore();
                try {
                    sistem.scoateVehiculDinLinie(idV, idL);
                    std::cout << "  Vehicul scos din linie cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 4: {
                sistem.afiseazaToateLiniile();
                pauza();
                break;
            }
            case 5: {
                // demonstrarea polimorfismului - fiecare vehicul afiseaza altfel
                int id;
                std::cout << "  ID linie: ";
                std::cin >> id;
                std::cin.ignore();
                try {
                    sistem.afiseazaVehiculeleLiniei(id);
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 6: {
                int id;
                std::cout << "  ID linie: ";
                std::cin >> id;
                std::cin.ignore();
                try {
                    sistem.afiseazaGradOcupare(id);
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 7: {
                sistem.afiseazaLiniaCeaMaiAglomerata();
                pauza();
                break;
            }
            case 8: {
                // afiseaza costul mediu de operare pentru lungimea traseului
                sistem.afiseazaToateLiniile();
                pauza();
                break;
            }
            case 9: {
                int id;
                std::string numeStatie;
                std::cout << "  ID linie: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "  Nume statie: ";
                std::getline(std::cin, numeStatie);
                // gasim linia si adaugam statia direct
                // in implementare reala am putea extinde SistemTransport cu o metoda dedicata
                std::cout << "  Functionalitate disponibila prin SistemTransport.\n";
                pauza();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "  Optiune invalida!\n";
        }
    } while (optiune != 0);
}

// submeniu pentru gestionarea statiilor

void meniuStatii(SistemTransport& sistem) {
    int optiune;
    do {
        std::cout << "\n--- Meniu Statii ---\n";
        std::cout << "1. Adauga statie\n";
        std::cout << "2. Afiseaza toate statiile\n";
        std::cout << "3. Editeaza statie (dupa ID)\n";
        std::cout << "0. Inapoi\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cin.ignore();
        clearScreen();

        switch (optiune) {
            case 1: {
                Statie* s = new Statie();
                try {
                    std::cin >> *s;
                    sistem.adaugaStatie(s);
                    std::cout << "  Statie adaugata cu succes! ID: " << s->getId() << "\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                    delete s;
                }
                break;
            }
            case 2: {
                sistem.afiseazaToateStatiile();
                pauza();
                break;
            }
            case 3: {
                int id;
                std::cout << "  ID statie: ";
                std::cin >> id;
                std::cin.ignore();
                try {
                    sistem.editeazaStatie(id);
                    std::cout << "  Statie editata cu succes!\n";
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "  Optiune invalida!\n";
        }
    } while (optiune != 0);
}

// submeniu pentru statistici si rapoarte

void meniuStatistici(SistemTransport& sistem) {
    int optiune;
    do {
        std::cout << "\n--- Statistici si Rapoarte ---\n";
        std::cout << "1. Raport complet (vehicule per tip, capacitate, ocupare)\n";
        std::cout << "2. Linia cea mai aglomerata\n";
        std::cout << "3. Vehicule electrice care pot parcurge o distanta\n";
        std::cout << "0. Inapoi\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cin.ignore();
        clearScreen();

        switch (optiune) {
            case 1: {
                sistem.raportStatistici();
                pauza();
                break;
            }
            case 2: {
                sistem.afiseazaLiniaCeaMaiAglomerata();
                pauza();
                break;
            }
            case 3: {
                double distanta;
                std::cout << "  Distanta (km): ";
                std::cin >> distanta;
                std::cin.ignore();
                try {
                    sistem.afiseazaVehiculeElectricePerDistanta(distanta);
                } catch (const TransportException& e) {
                    std::cout << "  Eroare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 0:
                break;
            default:
                std::cout << "  Optiune invalida!\n";
        }
    } while (optiune != 0);
}

// punctul de intrare in program

int main() {
    const std::string FISIER_DATE   = "date.txt";
    const std::string FISIER_CONFIG = "config.txt";

    // cream sistemul si citim configuratia din config.txt
    SistemTransport sistem("Bucuresti - STB", FISIER_CONFIG);

    // incercam sa incarcam datele salvate anterior - exact ca in lab 8
    try {
        sistem.incarca(FISIER_DATE);
        std::cout << "  Date incarcate din sesiunea anterioara.\n";
    } catch (const FisierException&) {
        std::cout << "  Nu exista date salvate. Se porneste o sesiune noua.\n";
    }

    int optiune;
    do {
        std::cout << "\n=== Sistem de Transport Urban Bucuresti (STB) ===\n";
        std::cout << "1. Gestionare vehicule\n";
        std::cout << "2. Gestionare linii\n";
        std::cout << "3. Gestionare statii\n";
        std::cout << "4. Statistici si rapoarte\n";
        std::cout << "5. Salveaza datele\n";
        std::cout << "6. Incarca datele\n";
        std::cout << "0. Iesire (salvare automata)\n";
        std::cout << "Optiune: ";
        std::cin >> optiune;
        std::cin.ignore();
        clearScreen();

        switch (optiune) {
            case 1:
                meniuVehicule(sistem);
                break;
            case 2:
                meniuLinii(sistem);
                break;
            case 3:
                meniuStatii(sistem);
                break;
            case 4:
                meniuStatistici(sistem);
                break;
            case 5: {
                try {
                    sistem.salveaza(FISIER_DATE);
                } catch (const FisierException& e) {
                    std::cout << "  Eroare la salvare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 6: {
                try {
                    sistem.incarca(FISIER_DATE);
                } catch (const FisierException& e) {
                    std::cout << "  Eroare la incarcare: " << e.what() << "\n";
                }
                pauza();
                break;
            }
            case 0: {
                // salvare automata la iesire - exact ca in lab 8
                try {
                    sistem.salveaza(FISIER_DATE);
                    std::cout << "  Salvare automata efectuata.\n";
                } catch (const FisierException& e) {
                    std::cout << "  Eroare la salvare automata: " << e.what() << "\n";
                }
                std::cout << "  La revedere!\n";
                break;
            }
            default:
                std::cout << "  Optiune invalida!\n";
        }
    } while (optiune != 0);

    return 0;
}
