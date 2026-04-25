#include "TransportElectric.h"

// constructor default
TransportElectric::TransportElectric() : Vehicul() {
    this->capacitateBaterie = 0.0;
    this->autonomie = 0.0;
    this->nivelIncarcare = 100.0; // un vehicul nou porneste cu bateria plina
}

// constructor cu parametri
TransportElectric::TransportElectric(const std::string& numar, int capacitate,
                                     double capacitateBaterie, double autonomie, double nivelIncarcare)
    : Vehicul(numar, capacitate) {
    if (capacitateBaterie <= 0)
        throw CapacitateInvalidaException("Capacitatea bateriei trebuie sa fie pozitiva!");
    if (autonomie <= 0)
        throw CapacitateInvalidaException("Autonomia trebuie sa fie pozitiva!");
    if (nivelIncarcare < 0 || nivelIncarcare > 100)
        throw CapacitateInvalidaException("Nivelul de incarcare trebuie sa fie intre 0 si 100!");
    this->capacitateBaterie = capacitateBaterie;
    this->autonomie = autonomie;
    this->nivelIncarcare = nivelIncarcare;
}

// copy constructor
TransportElectric::TransportElectric(const TransportElectric& obj) : Vehicul(obj) {
    this->capacitateBaterie = obj.capacitateBaterie;
    this->autonomie = obj.autonomie;
    this->nivelIncarcare = obj.nivelIncarcare;
}

// operator=
TransportElectric& TransportElectric::operator=(const TransportElectric& obj) {
    if (this == &obj)
        return *this;
    Vehicul::operator=(obj);
    this->capacitateBaterie = obj.capacitateBaterie;
    this->autonomie = obj.autonomie;
    this->nivelIncarcare = obj.nivelIncarcare;
    return *this;
}

TransportElectric::~TransportElectric() {}

// getteri
double TransportElectric::getCapacitateBaterie() const { return capacitateBaterie; }
double TransportElectric::getAutonomie() const { return autonomie; }
double TransportElectric::getNivelIncarcare() const { return nivelIncarcare; }

// setteri
void TransportElectric::setCapacitateBaterie(double cap) {
    if (cap <= 0)
        throw CapacitateInvalidaException("Capacitatea bateriei trebuie sa fie pozitiva!");
    this->capacitateBaterie = cap;
}

void TransportElectric::setAutonomie(double aut) {
    if (aut <= 0)
        throw CapacitateInvalidaException("Autonomia trebuie sa fie pozitiva!");
    this->autonomie = aut;
}

void TransportElectric::setNivelIncarcare(double nivel) {
    if (nivel < 0 || nivel > 100)
        throw CapacitateInvalidaException("Nivelul de incarcare trebuie sa fie intre 0 si 100!");
    this->nivelIncarcare = nivel;
}

// distanta maxima la nivelul curent = autonomie * (nivelIncarcare / 100)
bool TransportElectric::poateParcurgeDrumul(double distanta) const {
    double distantaDisponibila = autonomie * (nivelIncarcare / 100.0);
    return distantaDisponibila >= distanta;
}

// incarca bateria cu un numar de procente - nu poate depasi 100%
void TransportElectric::incarca(double procente) {
    if (procente <= 0)
        throw CapacitateInvalidaException("Numarul de procente trebuie sa fie pozitiv!");
    nivelIncarcare += procente;
    if (nivelIncarcare > 100.0)
        nivelIncarcare = 100.0; // nu putem depasi 100%
}

// operator<< afiseaza campurile proprii clasei electrice
std::ostream& operator<<(std::ostream& os, const TransportElectric& obj) {
    os << "  Nr. inmatriculare : " << obj.numarInmatriculare << "\n";
    os << "  Capacitate        : " << obj.capacitatePasageri << " pasageri\n";
    os << "  Baterie           : " << obj.capacitateBaterie << " kWh\n";
    os << "  Autonomie         : " << obj.autonomie << " km\n";
    os << "  Nivel incarcare   : " << obj.nivelIncarcare << "%\n";
    return os;
}

// operator>> citeste campurile proprii clasei electrice
std::istream& operator>>(std::istream& is, TransportElectric& obj) {
    std::cout << "  Numar inmatriculare: ";
    std::getline(is, obj.numarInmatriculare);

    std::cout << "  Capacitate pasageri: ";
    is >> obj.capacitatePasageri;
    if (obj.capacitatePasageri <= 0)
        throw CapacitateInvalidaException();

    std::cout << "  Capacitate baterie (kWh): ";
    is >> obj.capacitateBaterie;
    if (obj.capacitateBaterie <= 0)
        throw CapacitateInvalidaException("Capacitatea bateriei trebuie sa fie pozitiva!");

    std::cout << "  Autonomie (km): ";
    is >> obj.autonomie;
    if (obj.autonomie <= 0)
        throw CapacitateInvalidaException("Autonomia trebuie sa fie pozitiva!");

    std::cout << "  Nivel incarcare (%): ";
    is >> obj.nivelIncarcare;
    is.ignore();
    if (obj.nivelIncarcare < 0 || obj.nivelIncarcare > 100)
        throw CapacitateInvalidaException("Nivelul de incarcare trebuie sa fie intre 0 si 100!");

    obj.pasageriActuali = 0;
    return is;
}

void TransportElectric::serializeaza(std::ostream& out) const {
    Vehicul::serializeaza(out);
    out << capacitateBaterie << "\n";
    out << autonomie << "\n";
    out << nivelIncarcare << "\n";
}

void TransportElectric::deserializeaza(std::istream& in) {
    Vehicul::deserializeaza(in);
    in >> capacitateBaterie >> autonomie >> nivelIncarcare;
    in.ignore();
}
