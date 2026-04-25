#include "TransportTerestru.h"

// constructor default
TransportTerestru::TransportTerestru() : Vehicul() {
    this->vitezaMaxima = 0.0;
    this->tipCaroserie = "Normal";
}

// constructor cu parametri - apeleaza constructorul din Vehicul prin lista de initializare
TransportTerestru::TransportTerestru(const std::string& numar, int capacitate,
                                     double vitezaMaxima, const std::string& tipCaroserie)
    : Vehicul(numar, capacitate) {
    if (vitezaMaxima <= 0)
        throw CapacitateInvalidaException("Viteza maxima trebuie sa fie pozitiva!");
    this->vitezaMaxima = vitezaMaxima;
    this->tipCaroserie = tipCaroserie;
}

// copy constructor - apeleaza copy constructor-ul din Vehicul
TransportTerestru::TransportTerestru(const TransportTerestru& obj) : Vehicul(obj) {
    this->vitezaMaxima = obj.vitezaMaxima;
    this->tipCaroserie = obj.tipCaroserie;
}

// operator=
TransportTerestru& TransportTerestru::operator=(const TransportTerestru& obj) {
    if (this == &obj)
        return *this;
    Vehicul::operator=(obj); // copiem mai intai campurile din Vehicul
    this->vitezaMaxima = obj.vitezaMaxima;
    this->tipCaroserie = obj.tipCaroserie;
    return *this;
}

TransportTerestru::~TransportTerestru() {}

// getteri
double TransportTerestru::getVitezaMaxima() const { return vitezaMaxima; }
std::string TransportTerestru::getTipCaroserie() const { return tipCaroserie; }

// setteri
void TransportTerestru::setVitezaMaxima(double viteza) {
    if (viteza <= 0)
        throw CapacitateInvalidaException("Viteza maxima trebuie sa fie pozitiva!");
    this->vitezaMaxima = viteza;
}

void TransportTerestru::setTipCaroserie(const std::string& tip) {
    if (tip.empty())
        throw CapacitateInvalidaException("Tipul caroseriei nu poate fi gol!");
    this->tipCaroserie = tip;
}

// timp = distanta / viteza, returneaza ore
double TransportTerestru::calculeazaTimp(double distanta) const {
    if (vitezaMaxima == 0)
        throw CapacitateInvalidaException("Viteza maxima este 0, nu se poate calcula timpul!");
    return distanta / vitezaMaxima;
}

// operator<< afiseaza campurile proprii clasei, dupa cele din Vehicul
std::ostream& operator<<(std::ostream& os, const TransportTerestru& obj) {
    os << "  Nr. inmatriculare : " << obj.numarInmatriculare << "\n";
    os << "  Capacitate        : " << obj.capacitatePasageri << " pasageri\n";
    os << "  Viteza maxima     : " << obj.vitezaMaxima << " km/h\n";
    os << "  Tip caroserie     : " << obj.tipCaroserie << "\n";
    return os;
}

// operator>> citeste campurile proprii clasei
std::istream& operator>>(std::istream& is, TransportTerestru& obj) {
    std::cout << "  Numar inmatriculare: ";
    std::getline(is, obj.numarInmatriculare);

    std::cout << "  Capacitate pasageri: ";
    is >> obj.capacitatePasageri;
    if (obj.capacitatePasageri <= 0)
        throw CapacitateInvalidaException();

    std::cout << "  Viteza maxima (km/h): ";
    is >> obj.vitezaMaxima;
    is.ignore();
    if (obj.vitezaMaxima <= 0)
        throw CapacitateInvalidaException("Viteza maxima trebuie sa fie pozitiva!");

    std::cout << "  Tip caroserie (Normal/Articulat/Dublu etaj): ";
    std::getline(is, obj.tipCaroserie);

    obj.pasageriActuali = 0;
    return is;
}

// serializeaza apeleaza mai intai Vehicul::serializeaza, dupa adauga campurile proprii
void TransportTerestru::serializeaza(std::ostream& out) const {
    Vehicul::serializeaza(out);
    out << vitezaMaxima << "\n";
    out << tipCaroserie << "\n";
}

// deserializeaza apeleaza mai intai Vehicul::deserializeaza, dupa citeste campurile proprii
void TransportTerestru::deserializeaza(std::istream& in) {
    Vehicul::deserializeaza(in);
    in >> vitezaMaxima;
    in.ignore();
    std::getline(in, tipCaroserie);
}
