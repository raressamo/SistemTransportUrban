#include "Tramvai.h"

double Tramvai::pretKwh = 0.85;

// constructor default
// apelam explicit Vehicul() - in diamant, baza virtuala o initializeaza doar clasa cea mai derivata
Tramvai::Tramvai() : Vehicul(), TransportTerestru(), TransportElectric() {
    this->numarSine = 0;
    this->tipPantograf = "Unipolar";
    this->esteArticulat = false;
}

// constructor cu parametri
// Vehicul(numar, capacitate) - apelul din TransportTerestru si TransportElectric este IGNORAT
// doar acest apel explicit conteaza pentru baza virtuala
Tramvai::Tramvai(const std::string& numar, int capacitate,
                 double vitezaMaxima, const std::string& tipCaroserie,
                 double capacitateBaterie, double autonomie, double nivelIncarcare,
                 int numarSine, const std::string& tipPantograf, bool esteArticulat)
    : Vehicul(numar, capacitate),
      TransportTerestru(numar, capacitate, vitezaMaxima, tipCaroserie),
      TransportElectric(numar, capacitate, capacitateBaterie, autonomie, nivelIncarcare) {
    if (numarSine <= 0)
        throw CapacitateInvalidaException("Numarul de sine trebuie sa fie pozitiv!");
    if (tipPantograf != "Unipolar" && tipPantograf != "Bipolar")
        throw CapacitateInvalidaException("Tip pantograf invalid! Folositi: Unipolar sau Bipolar.");
    this->numarSine = numarSine;
    this->tipPantograf = tipPantograf;
    this->esteArticulat = esteArticulat;
}

// copy constructor - apelam explicit Vehicul(obj) pentru baza virtuala
Tramvai::Tramvai(const Tramvai& obj)
    : Vehicul(obj),
      TransportTerestru(obj),
      TransportElectric(obj) {
    this->numarSine = obj.numarSine;
    this->tipPantograf = obj.tipPantograf;
    this->esteArticulat = obj.esteArticulat;
}

// operator=
Tramvai& Tramvai::operator=(const Tramvai& obj) {
    if (this == &obj)
        return *this;
    Vehicul::operator=(obj);
    TransportTerestru::operator=(obj);
    TransportElectric::operator=(obj);
    this->numarSine = obj.numarSine;
    this->tipPantograf = obj.tipPantograf;
    this->esteArticulat = obj.esteArticulat;
    return *this;
}

Tramvai::~Tramvai() {}

// getteri
int Tramvai::getNumarSine() const { return numarSine; }
std::string Tramvai::getTipPantograf() const { return tipPantograf; }
bool Tramvai::getEsteArticulat() const { return esteArticulat; }

// setteri
void Tramvai::setNumarSine(int nr) {
    if (nr <= 0)
        throw CapacitateInvalidaException("Numarul de sine trebuie sa fie pozitiv!");
    this->numarSine = nr;
}

void Tramvai::setTipPantograf(const std::string& tip) {
    if (tip != "Unipolar" && tip != "Bipolar")
        throw CapacitateInvalidaException("Tip pantograf invalid! Folositi: Unipolar sau Bipolar.");
    this->tipPantograf = tip;
}

void Tramvai::setEsteArticulat(bool val) { this->esteArticulat = val; }

void Tramvai::setPretKwh(double pret) { pretKwh = pret; }

// cost = distanta * consum fix per km * pret kWh
// tramvaiul consuma aproximativ 2 kWh/km
double Tramvai::calculeazaCostCursa(double distanta) const {
    return distanta * CONSUM_KWH_PER_KM * pretKwh;
}

std::string Tramvai::getTip() const { return "Tramvai"; }

void Tramvai::afisareDetaliata() const {
    std::cout << "  [Tramvai #" << id << "]\n";
    std::cout << "  Nr. inmatriculare  : " << numarInmatriculare << "\n";
    std::cout << "  Capacitate         : " << capacitatePasageri << " pasageri\n";
    std::cout << "  Pasageri actuali   : " << pasageriActuali << "\n";
    std::cout << "  Grad ocupare       : " << getGradOcupare() << "%\n";
    std::cout << "  Viteza maxima      : " << vitezaMaxima << " km/h\n";
    std::cout << "  Tip caroserie      : " << tipCaroserie << "\n";
    std::cout << "  Baterie            : " << capacitateBaterie << " kWh\n";
    std::cout << "  Autonomie          : " << autonomie << " km\n";
    std::cout << "  Nivel incarcare    : " << nivelIncarcare << "%\n";
    std::cout << "  Numar sine         : " << numarSine << "\n";
    std::cout << "  Tip pantograf      : " << tipPantograf << "\n";
    std::cout << "  Articulat          : " << (esteArticulat ? "Da" : "Nu") << "\n";
}

std::ostream& operator<<(std::ostream& os, const Tramvai& obj) {
    obj.afisareDetaliata();
    return os;
}

std::istream& operator>>(std::istream& is, Tramvai& obj) {
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
    std::cout << "  Tip caroserie (Normal/Articulat): ";
    std::getline(is, obj.tipCaroserie);

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

    std::cout << "  Numar sine: ";
    is >> obj.numarSine;
    if (obj.numarSine <= 0)
        throw CapacitateInvalidaException("Numarul de sine trebuie sa fie pozitiv!");

    is.ignore();
    std::cout << "  Tip pantograf (Unipolar/Bipolar): ";
    std::getline(is, obj.tipPantograf);
    if (obj.tipPantograf != "Unipolar" && obj.tipPantograf != "Bipolar")
        throw CapacitateInvalidaException("Tip pantograf invalid! Folositi: Unipolar sau Bipolar.");

    std::cout << "  Este articulat (1/0): ";
    is >> obj.esteArticulat;
    is.ignore();

    obj.pasageriActuali = 0;
    return is;
}

// serializare - scriem campurile in ordinea: Vehicul, Terestru, Electric, proprii
// NU apelam TransportTerestru::serializeaza si TransportElectric::serializeaza separat
// ca sa evitam duplicarea campurilor din Vehicul (care ar fi scrise de doua ori)
void Tramvai::serializeaza(std::ostream& out) const {
    Vehicul::serializeaza(out);
    out << vitezaMaxima << "\n";
    out << tipCaroserie << "\n";
    out << capacitateBaterie << "\n";
    out << autonomie << "\n";
    out << nivelIncarcare << "\n";
    out << numarSine << "\n";
    out << tipPantograf << "\n";
    out << esteArticulat << "\n";
}

// deserializare - citim in aceeasi ordine ca la serializeaza
void Tramvai::deserializeaza(std::istream& in) {
    Vehicul::deserializeaza(in);
    in >> vitezaMaxima;
    in.ignore();
    std::getline(in, tipCaroserie);
    in >> capacitateBaterie >> autonomie >> nivelIncarcare;
    in.ignore();
    in >> numarSine;
    in.ignore();
    std::getline(in, tipPantograf);
    in >> esteArticulat;
    in.ignore();
}
