#ifndef SISTEMTRANSPORT_H
#define SISTEMTRANSPORT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Vehicul.h"
#include "Linie.h"
#include "Statie.h"
#include "Autobuz.h"
#include "Tramvai.h"
#include "Metrou.h"
#include "Exceptii.h"

class SistemTransport {
    std::string numeOras;
    std::vector<Vehicul*> vehicule; // toate vehiculele, owning
    std::vector<Linie*> linii; // toate liniile, owning
    std::vector<Statie*> statii; // toate statiile, owning

    // configuratie citita din config.txt - nu variabile globale
    double pretDiesel;
    double pretGPL;
    double pretKwh;

    // functii private ajutatoare
    void citesteConfig(const std::string& fisierConfig);
    Vehicul* gasesteVehicul(int id) const;
    Linie* gasesteLinie(int id) const;
    Statie* gasesteStatie(int id) const;
    static Vehicul* creeazaVehicul(const std::string& tip); // factory

public:
    SistemTransport(const std::string& numeOras, const std::string& fisierConfig);
    // nu permitem copierea sistemului - ar duplica toti pointerii si crea probleme la delete
    SistemTransport(const SistemTransport&) = delete;
    SistemTransport& operator=(const SistemTransport&) = delete;
    ~SistemTransport();

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const SistemTransport& obj);
    friend std::istream& operator>>(std::istream& is, SistemTransport& obj);

    // management vehicule
    void adaugaVehicul(Vehicul* v);
    void afiseazaToateVehiculele() const;
    void afiseazaVehiculDupaId(int id) const;
    void urcaPasageri(int idVehicul, int nr);
    void coboaraPasageri(int idVehicul, int nr);
    void incarcaBaterieVehicul(int idVehicul, double procente);

    // management linii
    void adaugaLinie(Linie* l);
    void atribuieVehiculLinie(int idVehicul, int idLinie);
    void scoateVehiculDinLinie(int idVehicul, int idLinie);
    void afiseazaToateLiniile() const;
    void afiseazaVehiculeleLiniei(int idLinie) const;
    void afiseazaGradOcupare(int idLinie) const;

    // management statii
    void adaugaStatie(Statie* s);
    void afiseazaToateStatiile() const;
    void editeazaStatie(int idStatie);

    // functii complexe
    void afiseazaLiniaCeaMaiAglomerata() const;
    void afiseazaVehiculeElectricePerDistanta(double distanta) const;
    void raportStatistici() const;

    // serializare
    void salveaza(const std::string& fisier) const;
    void incarca(const std::string& fisier);
};

#endif
