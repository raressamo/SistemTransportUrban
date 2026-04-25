#include "Statie.h"

int Statie::totalStatii = 0;

Statie::Statie() : id(++totalStatii) {
    this->nume = "N/A";
    this->adresa = "N/A";
    this->numarLiniiDeservite = 0;
}

Statie::Statie(const std::string& nume, const std::string& adresa, int numarLinii)
    : id(++totalStatii) {
    if (nume.empty())
        throw CapacitateInvalidaException("Numele statiei nu poate fi gol!");
    this->nume = nume;
    this->adresa = adresa;
    this->numarLiniiDeservite = numarLinii;
}

// copy constructor - id nou, statia e un obiect independent
Statie::Statie(const Statie& obj) : id(++totalStatii) {
    this->nume = obj.nume;
    this->adresa = obj.adresa;
    this->numarLiniiDeservite = obj.numarLiniiDeservite;
}

// operator= - id-ul nu se copiaza, ramane cel al obiectului curent
Statie& Statie::operator=(const Statie& obj) {
    if (this == &obj)
        return *this;
    this->nume = obj.nume;
    this->adresa = obj.adresa;
    this->numarLiniiDeservite = obj.numarLiniiDeservite;
    return *this;
}

Statie::~Statie() {}

// getteri
int Statie::getId() const { return id; }
std::string Statie::getNume() const { return nume; }
std::string Statie::getAdresa() const { return adresa; }
int Statie::getNumarLiniiDeservite() const { return numarLiniiDeservite; }
int Statie::getTotalStatii() { return totalStatii; }

// setteri
void Statie::setNume(const std::string& n) {
    if (n.empty())
        throw CapacitateInvalidaException("Numele statiei nu poate fi gol!");
    this->nume = n;
}

void Statie::setAdresa(const std::string& a) {
    this->adresa = a;
}

void Statie::setNumarLiniiDeservite(int nr) {
    if (nr < 0)
        throw CapacitateInvalidaException("Numarul de linii nu poate fi negativ!");
    this->numarLiniiDeservite = nr;
}

std::ostream& operator<<(std::ostream& os, const Statie& obj) {
    os << "  [Statie #" << obj.id << "]\n";
    os << "  Nume              : " << obj.nume << "\n";
    os << "  Adresa            : " << obj.adresa << "\n";
    os << "  Linii deservite   : " << obj.numarLiniiDeservite << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, Statie& obj) {
    std::cout << "  Nume statie: ";
    std::getline(is, obj.nume);
    if (obj.nume.empty())
        throw CapacitateInvalidaException("Numele statiei nu poate fi gol!");

    std::cout << "  Adresa: ";
    std::getline(is, obj.adresa);

    std::cout << "  Numar linii deservite: ";
    is >> obj.numarLiniiDeservite;
    is.ignore();
    if (obj.numarLiniiDeservite < 0)
        throw CapacitateInvalidaException("Numarul de linii nu poate fi negativ!");

    return is;
}

void Statie::serializeaza(std::ostream& out) const {
    out << nume << "\n";
    out << adresa << "\n";
    out << numarLiniiDeservite << "\n";
}

void Statie::deserializeaza(std::istream& in) {
    std::getline(in, nume);
    std::getline(in, adresa);
    in >> numarLiniiDeservite;
    in.ignore();
}
