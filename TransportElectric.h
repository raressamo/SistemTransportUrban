#ifndef TRANSPORTELECTRIC_H
#define TRANSPORTELECTRIC_H

#include "Vehicul.h"

// clasa intermediara pentru orice vehicul electric din retea
// virtual public Vehicul - necesar pentru mostenirea diamant din Tramvai
class TransportElectric : virtual public Vehicul {
protected:
    double capacitateBaterie; // kWh - energia totala stocata la incarcare completa
    double autonomie; // km - distanta maxima pe o incarcare completa
    double nivelIncarcare; // procent curent (0.0 - 100.0)

public:
    TransportElectric();
    TransportElectric(const std::string& numar, int capacitate,
                      double capacitateBaterie, double autonomie, double nivelIncarcare);
    TransportElectric(const TransportElectric& obj);
    TransportElectric& operator=(const TransportElectric& obj);
    virtual ~TransportElectric();

    // getteri
    double getCapacitateBaterie() const;
    double getAutonomie() const;
    double getNivelIncarcare() const;

    // setteri
    void setCapacitateBaterie(double cap);
    void setAutonomie(double autonomie);
    void setNivelIncarcare(double nivel);

    // verifica daca bateria curenta este suficienta pentru distanta ceruta
    bool poateParcurgeDrumul(double distanta) const;

    // mareste nivelul de incarcare cu numarul de procente dat
    void incarca(double procente);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const TransportElectric& obj);
    friend std::istream& operator>>(std::istream& is, TransportElectric& obj);

    // suprascrie serializarea din Vehicul - adauga campurile proprii
    void serializeaza(std::ostream& out) const override;
    void deserializeaza(std::istream& in) override;
};

#endif
