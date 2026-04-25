#ifndef STATIE_H
#define STATIE_H

#include <iostream>
#include <string>
#include "Exceptii.h"

class Statie {
    static int totalStatii;
    const int id;
    std::string nume;
    std::string adresa;
    int numarLiniiDeservite; // cate linii opresc in aceasta statie

public:
    Statie();
    Statie(const std::string& nume, const std::string& adresa, int numarLinii = 0);
    Statie(const Statie& obj);
    Statie& operator=(const Statie& obj);
    ~Statie();

    // getteri
    int getId() const;
    std::string getNume() const;
    std::string getAdresa() const;
    int getNumarLiniiDeservite() const;
    static int getTotalStatii();

    // setteri
    void setNume(const std::string& nume);
    void setAdresa(const std::string& adresa);
    void setNumarLiniiDeservite(int nr);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Statie& obj);
    friend std::istream& operator>>(std::istream& is, Statie& obj);

    void serializeaza(std::ostream& out) const;
    void deserializeaza(std::istream& in);
};

#endif
