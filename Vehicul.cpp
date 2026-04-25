#include "Vehicul.h"

// membrul static se defineste o singura data in afara clasei
int Vehicul::totalVehicule = 0;

// constructor default
Vehicul::Vehicul() : id(++totalVehicule) {
    this->numarInmatriculare = "N/A";
    this->capacitatePasageri = 0;
    this->pasageriActuali = 0;
}

// constructor cu parametri
Vehicul::Vehicul(const std::string& numarInmatriculare, int capacitatePasageri) : id(++totalVehicule) {
    if (capacitatePasageri <= 0)
        throw CapacitateInvalidaException();
    this->numarInmatriculare = numarInmatriculare;
    this->capacitatePasageri = capacitatePasageri;
    this->pasageriActuali = 0; // la creare vehiculul e gol
}

// copy constructor - id nou pentru ca e un obiect independent
Vehicul::Vehicul(const Vehicul& obj) : id(++totalVehicule) {
    this->numarInmatriculare = obj.numarInmatriculare;
    this->capacitatePasageri = obj.capacitatePasageri;
    this->pasageriActuali = obj.pasageriActuali;
}

// operator= - id-ul ramane al obiectului curent, nu se copiaza
Vehicul& Vehicul::operator=(const Vehicul& obj) {
    if (this == &obj)
        return *this;
    this->numarInmatriculare = obj.numarInmatriculare;
    this->capacitatePasageri = obj.capacitatePasageri;
    this->pasageriActuali = obj.pasageriActuali;
    return *this;
}

// destructorul e virtual dar nu are nimic de eliberat - std::string se elibereaza singur
Vehicul::~Vehicul() {}

// getteri
int Vehicul::getId() const { return id; }
std::string Vehicul::getNumarInmatriculare() const { return numarInmatriculare; }
int Vehicul::getCapacitatePasageri() const { return capacitatePasageri; }
int Vehicul::getPasageriActuali() const { return pasageriActuali; }
int Vehicul::getTotalVehicule() { return totalVehicule; }

// setteri
void Vehicul::setNumarInmatriculare(const std::string& numar) {
    if (numar.empty())
        throw VehiculInexistentException("Numarul de inmatriculare nu poate fi gol!");
    this->numarInmatriculare = numar;
}

void Vehicul::setCapacitatePasageri(int capacitate) {
    if (capacitate <= 0)
        throw CapacitateInvalidaException();
    this->capacitatePasageri = capacitate;
}

// operator<<
std::ostream& operator<<(std::ostream& os, const Vehicul& obj) {
    os << "  [" << obj.getTip() << " #" << obj.id << "]\n";
    os << "  Nr. inmatriculare : " << obj.numarInmatriculare << "\n";
    os << "  Capacitate        : " << obj.capacitatePasageri << " pasageri\n";
    os << "  Pasageri actuali  : " << obj.pasageriActuali << "\n";
    os << "  Grad ocupare      : " << obj.getGradOcupare() << "%\n";
    return os;
}

// operator>>
std::istream& operator>>(std::istream& is, Vehicul& obj) {
    std::cout << "  Numar inmatriculare: ";
    std::getline(is, obj.numarInmatriculare);

    std::cout << "  Capacitate pasageri: ";
    is >> obj.capacitatePasageri;
    is.ignore();

    if (obj.capacitatePasageri <= 0)
        throw CapacitateInvalidaException();

    obj.pasageriActuali = 0; // vehiculul citit de la tastatura e gol la inceput
    return is;
}

// urca pasageri - arunca exceptie daca se depaseste capacitatea
void Vehicul::urca(int nr) {
    if (nr <= 0)
        throw PasageriInvalidException("Numarul de pasageri care urca trebuie sa fie pozitiv!");
    if (pasageriActuali + nr > capacitatePasageri)
        throw PasageriInvalidException("Nu incap toti pasagerii! Capacitate depasita.");
    pasageriActuali += nr;
}

// coboara pasageri - arunca exceptie daca se incearca coborarea mai multor pasageri decat sunt
void Vehicul::coboara(int nr) {
    if (nr <= 0)
        throw PasageriInvalidException("Numarul de pasageri care coboara trebuie sa fie pozitiv!");
    if (nr > pasageriActuali)
        throw PasageriInvalidException("Nu sunt atati pasageri in vehicul!");
    pasageriActuali -= nr;
}

// gradul de ocupare ca procent - daca vehiculul e gol returneaza 0
double Vehicul::getGradOcupare() const {
    if (capacitatePasageri == 0)
        return 0.0;
    return (static_cast<double>(pasageriActuali) / capacitatePasageri) * 100.0;
}

// serializeaza campurile din Vehicul - clasele derivate apeleaza aceasta si adauga campurile lor
void Vehicul::serializeaza(std::ostream& out) const {
    out << numarInmatriculare << "\n";
    out << capacitatePasageri << "\n";
    out << pasageriActuali << "\n";
}

// deserializeaza campurile din Vehicul
void Vehicul::deserializeaza(std::istream& in) {
    std::getline(in, numarInmatriculare);
    in >> capacitatePasageri >> pasageriActuali;
    in.ignore();
}
