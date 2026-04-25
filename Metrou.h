#ifndef METROU_H
#define METROU_H

#include "TransportElectric.h"

class Metrou : public TransportElectric {
    std::string statiaTerminus; // statia de capat a liniei
    int numarVagoane;
    bool areAerConditionat;

    // consumul estimat al unui metrou - mai mare decat tramvaiul (vehicul mai greu, tunel)
    static constexpr double CONSUM_KWH_PER_KM = 5.0;

    // pretul kWh - static, setat din config.txt
    static double pretKwh;

public:
    Metrou();
    Metrou(const std::string& numar, int capacitate,
           double capacitateBaterie, double autonomie, double nivelIncarcare,
           const std::string& statiaTerminus, int numarVagoane, bool areAerConditionat);
    Metrou(const Metrou& obj);
    Metrou& operator=(const Metrou& obj);
    ~Metrou() override;

    // getteri
    std::string getStatiaTerminus() const;
    int getNumarVagoane() const;
    bool getAreAerConditionat() const;

    // setteri
    void setStatiaTerminus(const std::string& statie);
    void setNumarVagoane(int nr);
    void setAreAerConditionat(bool val);

    // seteaza pretul kWh din config
    static void setPretKwh(double pret);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Metrou& obj);
    friend std::istream& operator>>(std::istream& is, Metrou& obj);

    // implementarea metodelor pur virtuale din Vehicul
    double calculeazaCostCursa(double distanta) const override;
    std::string getTip() const override;
    void afisareDetaliata() const override;

    void serializeaza(std::ostream& out) const override;
    void deserializeaza(std::istream& in) override;
};

#endif
