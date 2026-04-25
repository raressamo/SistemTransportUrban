#include "Autobuz.h"

// initializam membrii statici in afara clasei
double Autobuz::pretDiesel = 7.50;
double Autobuz::pretGPL = 4.20;

// constructor default
Autobuz::Autobuz() : TransportTerestru() {
    this->tipCarburant = "Diesel";
    this->consumLa100km = 0.0;
}

// constructor cu parametri
Autobuz::Autobuz(const std::string& numar, int capacitate,
                 double vitezaMaxima, const std::string& tipCaroserie,
                 const std::string& tipCarburant, double consumLa100km)
    : TransportTerestru(numar, capacitate, vitezaMaxima, tipCaroserie) {
    if (consumLa100km <= 0)
        throw CapacitateInvalidaException("Consumul trebuie sa fie pozitiv!");
    if (tipCarburant != "Diesel" && tipCarburant != "GPL" && tipCarburant != "Hibrid")
        throw CapacitateInvalidaException("Tip carburant invalid! Folositi: Diesel, GPL sau Hibrid.");
    this->tipCarburant = tipCarburant;
    this->consumLa100km = consumLa100km;
}

// copy constructor
Autobuz::Autobuz(const Autobuz& obj) : TransportTerestru(obj) {
    this->tipCarburant = obj.tipCarburant;
    this->consumLa100km = obj.consumLa100km;
}

// operator=
Autobuz& Autobuz::operator=(const Autobuz& obj) {
    if (this == &obj)
        return *this;
    TransportTerestru::operator=(obj);
    this->tipCarburant = obj.tipCarburant;
    this->consumLa100km = obj.consumLa100km;
    return *this;
}

Autobuz::~Autobuz() {}

// getteri
std::string Autobuz::getTipCarburant() const { return tipCarburant; }
double Autobuz::getConsumLa100km() const { return consumLa100km; }

// setteri
void Autobuz::setTipCarburant(const std::string& tip) {
    if (tip != "Diesel" && tip != "GPL" && tip != "Hibrid")
        throw CapacitateInvalidaException("Tip carburant invalid! Folositi: Diesel, GPL sau Hibrid.");
    this->tipCarburant = tip;
}

void Autobuz::setConsumLa100km(double consum) {
    if (consum <= 0)
        throw CapacitateInvalidaException("Consumul trebuie sa fie pozitiv!");
    this->consumLa100km = consum;
}

// seteaza preturile din config - apelat o singura data de SistemTransport
void Autobuz::setPretDiesel(double pret) { pretDiesel = pret; }
void Autobuz::setPretGPL(double pret) { pretGPL = pret; }

// cost = distanta * (consum / 100) * pretCarburant
// pentru Hibrid: jumatate din consumul obisnuit la pretul Diesel
double Autobuz::calculeazaCostCursa(double distanta) const {
    if (tipCarburant == "Diesel")
        return distanta * (consumLa100km / 100.0) * pretDiesel;
    if (tipCarburant == "GPL")
        return distanta * (consumLa100km / 100.0) * pretGPL;
    // Hibrid - consuma jumatate fata de un autobuz conventional
    return distanta * (consumLa100km / 200.0) * pretDiesel;
}

std::string Autobuz::getTip() const { return "Autobuz"; }

// afisare completa cu toate campurile, inclusiv cele mostenite
void Autobuz::afisareDetaliata() const {
    std::cout << "  [Autobuz #" << id << "]\n";
    std::cout << "  Nr. inmatriculare : " << numarInmatriculare << "\n";
    std::cout << "  Capacitate        : " << capacitatePasageri << " pasageri\n";
    std::cout << "  Pasageri actuali  : " << pasageriActuali << "\n";
    std::cout << "  Grad ocupare      : " << getGradOcupare() << "%\n";
    std::cout << "  Viteza maxima     : " << vitezaMaxima << " km/h\n";
    std::cout << "  Tip caroserie     : " << tipCaroserie << "\n";
    std::cout << "  Tip carburant     : " << tipCarburant << "\n";
    std::cout << "  Consum            : " << consumLa100km << " l/100km\n";
}

// operator<< apeleaza afisareDetaliata - virtual dispatch garanteaza tipul corect
std::ostream& operator<<(std::ostream& os, const Autobuz& obj) {
    obj.afisareDetaliata();
    return os;
}

// operator>> citeste toate campurile unui autobuz
std::istream& operator>>(std::istream& is, Autobuz& obj) {
    std::cout << "  Numar inmatriculare: ";
    std::getline(is, obj.numarInmatriculare);

    std::cout << "  Capacitate pasageri: ";
    is >> obj.capacitatePasageri;
    if (obj.capacitatePasageri <= 0)
        throw CapacitateInvalidaException();

    std::cout << "  Viteza maxima (km/h): ";
    is >> obj.vitezaMaxima;
    if (obj.vitezaMaxima <= 0)
        throw CapacitateInvalidaException("Viteza maxima trebuie sa fie pozitiva!");

    is.ignore();
    std::cout << "  Tip caroserie (Normal/Articulat/Dublu etaj): ";
    std::getline(is, obj.tipCaroserie);

    std::cout << "  Tip carburant (Diesel/GPL/Hibrid): ";
    std::getline(is, obj.tipCarburant);
    if (obj.tipCarburant != "Diesel" && obj.tipCarburant != "GPL" && obj.tipCarburant != "Hibrid")
        throw CapacitateInvalidaException("Tip carburant invalid! Folositi: Diesel, GPL sau Hibrid.");

    std::cout << "  Consum la 100km: ";
    is >> obj.consumLa100km;
    is.ignore();
    if (obj.consumLa100km <= 0)
        throw CapacitateInvalidaException("Consumul trebuie sa fie pozitiv!");

    obj.pasageriActuali = 0; // autobuzul nou adaugat e gol
    return is;
}

void Autobuz::serializeaza(std::ostream& out) const {
    TransportTerestru::serializeaza(out); // scrie campurile din Vehicul + TransportTerestru
    out << tipCarburant << "\n";
    out << consumLa100km << "\n";
}

void Autobuz::deserializeaza(std::istream& in) {
    TransportTerestru::deserializeaza(in); // citeste campurile din Vehicul + TransportTerestru
    std::getline(in, tipCarburant);
    in >> consumLa100km;
    in.ignore();
}
