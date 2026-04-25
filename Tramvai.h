#ifndef TRAMVAI_H
#define TRAMVAI_H

#include "TransportTerestru.h"
#include "TransportElectric.h"

// Tramvai mosteneste din AMBELE clase intermediare - mostenire diamant
// Vehicul apare o singura data in ierarhie datorita "virtual" din TransportTerestru si TransportElectric
//
//          Vehicul (virtual)
//         /        \
// TransportTerestru  TransportElectric
//         \        /
//          Tramvai
class Tramvai : public TransportTerestru, public TransportElectric {
    int numarSine;
    std::string tipPantograf; // "Unipolar" sau "Bipolar"
    bool esteArticulat;

    // consumul estimat al unui tramvai per km
    static constexpr double CONSUM_KWH_PER_KM = 2.0;

    // pretul kWh - static, setat din config.txt
    static double pretKwh;

public:
    Tramvai();
    // constructorul trebuie sa apeleze explicit Vehicul() - regula pentru baza virtuala
    // in mostenirea diamant, doar clasa cea mai derivata apeleaza constructorul bazei virtuale
    Tramvai(const std::string& numar, int capacitate,
            double vitezaMaxima, const std::string& tipCaroserie,
            double capacitateBaterie, double autonomie, double nivelIncarcare,
            int numarSine, const std::string& tipPantograf, bool esteArticulat);
    Tramvai(const Tramvai& obj);
    Tramvai& operator=(const Tramvai& obj);
    ~Tramvai() override;

    // getteri
    int getNumarSine() const;
    std::string getTipPantograf() const;
    bool getEsteArticulat() const;

    // setteri
    void setNumarSine(int nr);
    void setTipPantograf(const std::string& tip);
    void setEsteArticulat(bool val);

    // seteaza pretul kWh din config
    static void setPretKwh(double pret);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Tramvai& obj);
    friend std::istream& operator>>(std::istream& is, Tramvai& obj);

    // implementarea metodelor pur virtuale din Vehicul
    double calculeazaCostCursa(double distanta) const override;
    std::string getTip() const override;
    void afisareDetaliata() const override;

    void serializeaza(std::ostream& out) const override;
    void deserializeaza(std::istream& in) override;
};

#endif
