#ifndef VEHICUL_H
#define VEHICUL_H

#include <iostream>
#include <string>
#include "Exceptii.h"

class Vehicul {
protected:
    static int totalVehicule; // numarul total de vehicule create, apartine clasei nu unui obiect
    const int id; // id unic, se seteaza o singura data in constructor
    std::string numarInmatriculare; // ex: "B-101-TUR"
    int capacitatePasageri; // cati pasageri incap in vehicul
    int pasageriActuali; // cati pasageri sunt in vehicul la momentul curent

public:
    Vehicul();
    Vehicul(const std::string& numarInmatriculare, int capacitatePasageri);
    Vehicul(const Vehicul& obj);
    Vehicul& operator=(const Vehicul& obj);
    virtual ~Vehicul(); // virtual obligatoriu - fara el, delete prin pointer de baza nu apeleaza destructorul clasei derivate

    // getteri
    int getId() const;
    std::string getNumarInmatriculare() const;
    int getCapacitatePasageri() const;
    int getPasageriActuali() const;
    static int getTotalVehicule(); // static - apelabil fara obiect

    // setteri
    void setNumarInmatriculare(const std::string& numar);
    void setCapacitatePasageri(int capacitate);

    // operatori
    friend std::ostream& operator<<(std::ostream& os, const Vehicul& obj);
    friend std::istream& operator>>(std::istream& is, Vehicul& obj);

    // functii publice
    void urca(int nr); // urca pasageri in vehicul
    void coboara(int nr); // coboara pasageri din vehicul
    double getGradOcupare() const; // returneaza procentul de ocupare (0-100)

    // metode pur virtuale - fac clasa abstracta, nu poate fi instantiata direct
    virtual double calculeazaCostCursa(double distanta) const = 0;
    virtual std::string getTip() const = 0;
    virtual void afisareDetaliata() const = 0;

    // serializare virtuala - fiecare clasa derivata o suprascrie si apeleaza versiunea bazei
    virtual void serializeaza(std::ostream& out) const;
    virtual void deserializeaza(std::istream& in);
};

#endif
