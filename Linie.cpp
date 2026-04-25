#include "Linie.h"
#include <algorithm>

int Linie::totalLinii = 0;

Linie::Linie() : id(++totalLinii) {
    this->numeLiniei = "N/A";
    this->lungimeTraseu = 0.0;
}

Linie::Linie(const std::string& numeLinie, double lungimeTraseu) : id(++totalLinii) {
    if (numeLinie.empty())
        throw CapacitateInvalidaException("Numele liniei nu poate fi gol!");
    if (lungimeTraseu <= 0)
        throw CapacitateInvalidaException("Lungimea traseului trebuie sa fie pozitiva!");
    this->numeLiniei = numeLinie;
    this->lungimeTraseu = lungimeTraseu;
}

// copy constructor - copiem pointerii non-owning, nu cloneaza vehiculele
Linie::Linie(const Linie& obj) : id(++totalLinii) {
    this->numeLiniei = obj.numeLiniei;
    this->lungimeTraseu = obj.lungimeTraseu;
    this->vehicule = obj.vehicule;   // copiem pointerii, nu obiectele
    this->numeStatii = obj.numeStatii;
}

// operator=
Linie& Linie::operator=(const Linie& obj) {
    if (this == &obj)
        return *this;
    this->numeLiniei = obj.numeLiniei;
    this->lungimeTraseu = obj.lungimeTraseu;
    this->vehicule = obj.vehicule;
    this->numeStatii = obj.numeStatii;
    return *this;
}

// destructorul NU sterge vehiculele - ele sunt detinute de SistemTransport
Linie::~Linie() {}

// getteri
int Linie::getId() const { return id; }
std::string Linie::getNumeLiniei() const { return numeLiniei; }
double Linie::getLungimeTraseu() const { return lungimeTraseu; }
const std::vector<Vehicul*>& Linie::getVehicule() const { return vehicule; }
const std::vector<std::string>& Linie::getNumeStatii() const { return numeStatii; }
int Linie::getTotalLinii() { return totalLinii; }

// setteri
void Linie::setNumeLiniei(const std::string& nume) {
    if (nume.empty())
        throw CapacitateInvalidaException("Numele liniei nu poate fi gol!");
    this->numeLiniei = nume;
}

void Linie::setLungimeTraseu(double lungime) {
    if (lungime <= 0)
        throw CapacitateInvalidaException("Lungimea traseului trebuie sa fie pozitiva!");
    this->lungimeTraseu = lungime;
}

std::ostream& operator<<(std::ostream& os, const Linie& obj) {
    os << "  [Linie #" << obj.id << " - " << obj.numeLiniei << "]\n";
    os << "  Lungime traseu    : " << obj.lungimeTraseu << " km\n";
    os << "  Vehicule          : " << obj.vehicule.size() << "\n";
    os << "  Statii            : " << obj.numeStatii.size() << "\n";
    if (!obj.numeStatii.empty()) {
        os << "  Traseu            : ";
        for (size_t i = 0; i < obj.numeStatii.size(); i++) {
            os << obj.numeStatii[i];
            if (i + 1 < obj.numeStatii.size()) os << " → ";
        }
        os << "\n";
    }
    os << "  Grad ocupare      : " << obj.getGradOcupare() << "%\n";
    return os;
}

std::istream& operator>>(std::istream& is, Linie& obj) {
    std::cout << "  Nume linie (ex: Linia 5, M2): ";
    std::getline(is, obj.numeLiniei);
    if (obj.numeLiniei.empty())
        throw CapacitateInvalidaException("Numele liniei nu poate fi gol!");

    std::cout << "  Lungime traseu (km): ";
    is >> obj.lungimeTraseu;
    is.ignore();
    if (obj.lungimeTraseu <= 0)
        throw CapacitateInvalidaException("Lungimea traseului trebuie sa fie pozitiva!");

    return is;
}

// adauga un vehicul la linie - vehiculul trebuie sa existe deja in SistemTransport
void Linie::adaugaVehicul(Vehicul* v) {
    if (v == nullptr)
        throw VehiculInexistentException("Vehiculul nu poate fi null!");
    vehicule.push_back(v);
}

// elimina vehiculul cu id-ul dat din linie (nu il sterge din memorie)
void Linie::eliminaVehicul(int idVehicul) {
    auto it = std::find_if(vehicule.begin(), vehicule.end(),
        [idVehicul](Vehicul* v) { return v->getId() == idVehicul; });
    if (it == vehicule.end())
        throw VehiculInexistentException("Vehiculul cu ID-ul dat nu este pe aceasta linie!");
    vehicule.erase(it);
}

void Linie::adaugaStatie(const std::string& numeStatie) {
    if (numeStatie.empty())
        throw CapacitateInvalidaException("Numele statiei nu poate fi gol!");
    numeStatii.push_back(numeStatie);
}

// suma capacitatilor tuturor vehiculelor de pe linie
int Linie::getCapacitateTotala() const {
    int total = 0;
    for (const Vehicul* v : vehicule)
        total += v->getCapacitatePasageri();
    return total;
}

// suma pasagerilor actuali din toate vehiculele de pe linie
int Linie::getPasageriActuali() const {
    int total = 0;
    for (const Vehicul* v : vehicule)
        total += v->getPasageriActuali();
    return total;
}

// gradul de ocupare al intregii linii ca procent
double Linie::getGradOcupare() const {
    int capacitate = getCapacitateTotala();
    if (capacitate == 0)
        return 0.0;
    return (static_cast<double>(getPasageriActuali()) / capacitate) * 100.0;
}

// media costului de operare per vehicul pentru lungimea traseului
// apeleaza calculeazaCostCursa virtual - fiecare tip calculeaza altfel
double Linie::calculeazaCostMediuCursa() const {
    if (vehicule.empty())
        return 0.0;
    double totalCost = 0.0;
    for (const Vehicul* v : vehicule)
        totalCost += v->calculeazaCostCursa(lungimeTraseu);
    return totalCost / vehicule.size();
}

// afiseaza detalii despre fiecare vehicul - polimorfism explicit
// apelul la afisareDetaliata() se rezolva dinamic la runtime
void Linie::afiseazaVehicule() const {
    if (vehicule.empty()) {
        std::cout << "  Nu exista vehicule pe aceasta linie.\n";
        return;
    }
    std::cout << "  Vehiculele liniei " << numeLiniei << ":\n";
    for (const Vehicul* v : vehicule) {
        v->afisareDetaliata(); // dispatch dinamic - fiecare tip afiseaza altfel
        std::cout << "\n";
    }
}

// salveaza doar metadata liniei si ID-urile vehiculelor alocate
void Linie::serializeaza(std::ostream& out) const {
    out << numeLiniei << "\n";
    out << lungimeTraseu << "\n";
    out << numeStatii.size() << "\n";
    for (const std::string& s : numeStatii)
        out << s << "\n";
    out << vehicule.size() << "\n";
    for (const Vehicul* v : vehicule)
        out << v->getId() << "\n"; // salvam doar ID-ul, nu vehiculul in sine
}

void Linie::deserializeaza(std::istream& in) {
    std::getline(in, numeLiniei);
    in >> lungimeTraseu;
    in.ignore();

    int nrStatii;
    in >> nrStatii;
    in.ignore();
    numeStatii.clear();
    for (int i = 0; i < nrStatii; i++) {
        std::string statie;
        std::getline(in, statie);
        numeStatii.push_back(statie);
    }
    // ID-urile vehiculelor sunt citite si rezolvate de SistemTransport
}

void Linie::serializeazaIduri(std::ostream& out) const {
    out << vehicule.size() << "\n";
    for (const Vehicul* v : vehicule)
        out << v->getId() << "\n";
}
