#ifndef TRANSPORTTERESTRU_H
#define TRANSPORTTERESTRU_H

#include "Vehicul.h"

// clasa intermediara in ierarhie - nu poate fi instantiata direct
// (nu implementeaza metodele pur virtuale din Vehicul)
// virtual public Vehicul - necesar pentru mostenirea diamant din Tramvai
class TransportTerestru : virtual public Vehicul {
protected:
    double vitezaMaxima; // km/h - viteza maxima a vehiculului
    std::string tipCaroserie; // "Normal", "Articulat", "Dublu etaj"

public:
    TransportTerestru();
    TransportTerestru(const std::string& numar, int capacitate,
                      double vitezaMaxima, const std::string& tipCaroserie);
    TransportTerestru(const TransportTerestru& obj);
    TransportTerestru& operator=(const TransportTerestru& obj);
    virtual ~TransportTerestru();

    // getteri
    double getVitezaMaxima() const;
    std::string getTipCaroserie() const;

    // setteri
    void setVitezaMaxima(double viteza);
    void setTipCaroserie(const std::string& tip);

    // calculeaza cat timp dureaza o cursa la viteza maxima
    double calculeazaTimp(double distanta) const;

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const TransportTerestru& obj);
    friend std::istream& operator>>(std::istream& is, TransportTerestru& obj);

    // suprascrie serializarea din Vehicul - adauga campurile proprii
    void serializeaza(std::ostream& out) const override;
    void deserializeaza(std::istream& in) override;
};

#endif
