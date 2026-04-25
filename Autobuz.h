#ifndef AUTOBUZ_H
#define AUTOBUZ_H

#include "TransportTerestru.h"

class Autobuz : public TransportTerestru {
    std::string tipCarburant; // "Diesel", "GPL", "Hibrid"
    double consumLa100km; // litri sau mc la 100 km

    // preturile carburantului - statice, setate o singura data din config.txt
    // static ca sa nu fie variabile globale dar sa fie accesibile in formula de cost
    static double pretDiesel;
    static double pretGPL;

public:
    Autobuz();
    Autobuz(const std::string& numar, int capacitate,
            double vitezaMaxima, const std::string& tipCaroserie,
            const std::string& tipCarburant, double consumLa100km);
    Autobuz(const Autobuz& obj);
    Autobuz& operator=(const Autobuz& obj);
    ~Autobuz() override;

    // getteri
    std::string getTipCarburant() const;
    double getConsumLa100km() const;

    // setteri
    void setTipCarburant(const std::string& tip);
    void setConsumLa100km(double consum);

    // seteaza pretul carburantului din config - apelat o singura data la pornire
    static void setPretDiesel(double pret);
    static void setPretGPL(double pret);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Autobuz& obj);
    friend std::istream& operator>>(std::istream& is, Autobuz& obj);

    // implementarea metodelor pur virtuale din Vehicul
    double calculeazaCostCursa(double distanta) const override;
    std::string getTip() const override;
    void afisareDetaliata() const override;

    void serializeaza(std::ostream& out) const override;
    void deserializeaza(std::istream& in) override;
};

#endif
