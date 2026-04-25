#include "Metrou.h"

double Metrou::pretKwh = 0.85;

// constructor default
Metrou::Metrou() : TransportElectric() {
    this->statiaTerminus = "N/A";
    this->numarVagoane = 1;
    this->areAerConditionat = false;
}

// constructor cu parametri
Metrou::Metrou(const std::string& numar, int capacitate,
               double capacitateBaterie, double autonomie, double nivelIncarcare,
               const std::string& statiaTerminus, int numarVagoane, bool areAerConditionat)
    : TransportElectric(numar, capacitate, capacitateBaterie, autonomie, nivelIncarcare) {
    if (numarVagoane <= 0)
        throw CapacitateInvalidaException("Numarul de vagoane trebuie sa fie pozitiv!");
    this->statiaTerminus = statiaTerminus;
    this->numarVagoane = numarVagoane;
    this->areAerConditionat = areAerConditionat;
}

// copy constructor
Metrou::Metrou(const Metrou& obj) : TransportElectric(obj) {
    this->statiaTerminus = obj.statiaTerminus;
    this->numarVagoane = obj.numarVagoane;
    this->areAerConditionat = obj.areAerConditionat;
}

// operator=
Metrou& Metrou::operator=(const Metrou& obj) {
    if (this == &obj)
        return *this;
    TransportElectric::operator=(obj);
    this->statiaTerminus = obj.statiaTerminus;
    this->numarVagoane = obj.numarVagoane;
    this->areAerConditionat = obj.areAerConditionat;
    return *this;
}

Metrou::~Metrou() {}

// getteri
std::string Metrou::getStatiaTerminus() const { return statiaTerminus; }
int Metrou::getNumarVagoane() const { return numarVagoane; }
bool Metrou::getAreAerConditionat() const { return areAerConditionat; }

// setteri
void Metrou::setStatiaTerminus(const std::string& statie) {
    if (statie.empty())
        throw CapacitateInvalidaException("Statia terminus nu poate fi goala!");
    this->statiaTerminus = statie;
}

void Metrou::setNumarVagoane(int nr) {
    if (nr <= 0)
        throw CapacitateInvalidaException("Numarul de vagoane trebuie sa fie pozitiv!");
    this->numarVagoane = nr;
}

void Metrou::setAreAerConditionat(bool val) {
    this->areAerConditionat = val;
}

void Metrou::setPretKwh(double pret) { pretKwh = pret; }

// cost = distanta * consum fix per km * pret kWh
// metroul consuma mai mult decat tramvaiul (5 kWh/km vs 2 kWh/km)
double Metrou::calculeazaCostCursa(double distanta) const {
    return distanta * CONSUM_KWH_PER_KM * pretKwh;
}

std::string Metrou::getTip() const { return "Metrou"; }

void Metrou::afisareDetaliata() const {
    std::cout << "  [Metrou #" << id << "]\n";
    std::cout << "  Nr. inmatriculare  : " << numarInmatriculare << "\n";
    std::cout << "  Capacitate         : " << capacitatePasageri << " pasageri\n";
    std::cout << "  Pasageri actuali   : " << pasageriActuali << "\n";
    std::cout << "  Grad ocupare       : " << getGradOcupare() << "%\n";
    std::cout << "  Baterie            : " << capacitateBaterie << " kWh\n";
    std::cout << "  Autonomie          : " << autonomie << " km\n";
    std::cout << "  Nivel incarcare    : " << nivelIncarcare << "%\n";
    std::cout << "  Statie terminus    : " << statiaTerminus << "\n";
    std::cout << "  Numar vagoane      : " << numarVagoane << "\n";
    std::cout << "  Aer conditionat    : " << (areAerConditionat ? "Da" : "Nu") << "\n";
}

std::ostream& operator<<(std::ostream& os, const Metrou& obj) {
    obj.afisareDetaliata();
    return os;
}

std::istream& operator>>(std::istream& is, Metrou& obj) {
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
    if (obj.nivelIncarcare < 0 || obj.nivelIncarcare > 100)
        throw CapacitateInvalidaException("Nivelul de incarcare trebuie sa fie intre 0 si 100!");

    std::cout << "  Numar vagoane: ";
    is >> obj.numarVagoane;
    if (obj.numarVagoane <= 0)
        throw CapacitateInvalidaException("Numarul de vagoane trebuie sa fie pozitiv!");

    is.ignore();
    std::cout << "  Statie terminus: ";
    std::getline(is, obj.statiaTerminus);

    std::cout << "  Are aer conditionat (1/0): ";
    is >> obj.areAerConditionat;
    is.ignore();

    obj.pasageriActuali = 0;
    return is;
}

void Metrou::serializeaza(std::ostream& out) const {
    TransportElectric::serializeaza(out);
    out << statiaTerminus << "\n";
    out << numarVagoane << "\n";
    out << areAerConditionat << "\n";
}

void Metrou::deserializeaza(std::istream& in) {
    TransportElectric::deserializeaza(in);
    std::getline(in, statiaTerminus);
    in >> numarVagoane >> areAerConditionat;
    in.ignore();
}
