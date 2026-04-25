#ifndef LINIE_H
#define LINIE_H

#include <iostream>
#include <string>
#include <vector>
#include "Vehicul.h"
#include "Exceptii.h"

class Linie {
    static int totalLinii;
    const int id;
    std::string numeLiniei;       // ex: "Linia 5", "M2"
    std::vector<Vehicul*> vehicule; // pointeri non-owning - vehiculele sunt detinute de SistemTransport
    std::vector<std::string> numeStatii; // statiile traseului in ordine
    double lungimeTraseu;         // km

public:
    Linie();
    Linie(const std::string& numeLinie, double lungimeTraseu);
    Linie(const Linie& obj);
    Linie& operator=(const Linie& obj);
    ~Linie(); // NU sterge vehiculele - ele sunt owning-uite de SistemTransport

    // getteri
    int getId() const;
    std::string getNumeLiniei() const;
    double getLungimeTraseu() const;
    const std::vector<Vehicul*>& getVehicule() const;
    const std::vector<std::string>& getNumeStatii() const;
    static int getTotalLinii();

    // setteri
    void setNumeLiniei(const std::string& nume);
    void setLungimeTraseu(double lungime);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Linie& obj);
    friend std::istream& operator>>(std::istream& is, Linie& obj);

    // management vehicule si statii
    void adaugaVehicul(Vehicul* v);
    void eliminaVehicul(int idVehicul);
    void adaugaStatie(const std::string& numeStatie);

    // functii complexe
    int getCapacitateTotala() const; // suma capacitatilor tuturor vehiculelor
    int getPasageriActuali() const; // suma pasagerilor actuali
    double getGradOcupare() const; // procent ocupare pe intreaga linie
    double calculeazaCostMediuCursa() const; // media costului per vehicul pentru lungimea traseului
    void afiseazaVehicule() const; // polimorfism explicit - apeleaza afisareDetaliata() virtual

    // pentru serializare salvam doar ID-urile vehiculelor, nu vehiculele in sine
    // vehiculele sunt salvate separat de SistemTransport
    void serializeazaIduri(std::ostream& out) const;
    void serializeaza(std::ostream& out) const;
    void deserializeaza(std::istream& in);
};

#endif
