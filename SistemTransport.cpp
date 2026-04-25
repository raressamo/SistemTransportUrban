#include "SistemTransport.h"
#include <algorithm>
#include <sstream>

// citeste config.txt si seteaza preturile in clasele concrete
// fiecare linie din config are forma: cheie=valoare
void SistemTransport::citesteConfig(const std::string& fisierConfig) {
    std::ifstream fin(fisierConfig);
    if (!fin.is_open())
        throw ConfigInvalidException("Fisierul de configurare '" + fisierConfig + "' nu a putut fi deschis!");

    std::string linie;
    while (std::getline(fin, linie)) {
        if (linie.empty()) continue;
        size_t pos = linie.find('=');
        if (pos == std::string::npos) continue;

        std::string cheie = linie.substr(0, pos);
        double valoare = std::stod(linie.substr(pos + 1));

        if (cheie == "pret_diesel")         pretDiesel = valoare;
        else if (cheie == "pret_gpl")       pretGPL = valoare;
        else if (cheie == "pret_kwh")       pretKwh = valoare;
    }
    fin.close();

    // propagam preturile in clasele concrete prin membrii statici
    Autobuz::setPretDiesel(pretDiesel);
    Autobuz::setPretGPL(pretGPL);
    Tramvai::setPretKwh(pretKwh);
    Metrou::setPretKwh(pretKwh);
}

// cauta un vehicul dupa id in vectorul intern
Vehicul* SistemTransport::gasesteVehicul(int id) const {
    for (Vehicul* v : vehicule)
        if (v->getId() == id)
            return v;
    return nullptr;
}

// cauta o linie dupa id
Linie* SistemTransport::gasesteLinie(int id) const {
    for (Linie* l : linii)
        if (l->getId() == id)
            return l;
    return nullptr;
}

// cauta o statie dupa id
Statie* SistemTransport::gasesteStatie(int id) const {
    for (Statie* s : statii)
        if (s->getId() == id)
            return s;
    return nullptr;
}

// factory - creeaza obiectul potrivit dupa tipul citit din fisier
Vehicul* SistemTransport::creeazaVehicul(const std::string& tip) {
    if (tip == "Autobuz") return new Autobuz();
    if (tip == "Tramvai") return new Tramvai();
    if (tip == "Metrou")  return new Metrou();
    return nullptr;
}

SistemTransport::SistemTransport(const std::string& numeOras, const std::string& fisierConfig)
    : numeOras(numeOras), pretDiesel(7.50), pretGPL(4.20), pretKwh(0.85) {
    citesteConfig(fisierConfig);
}

// destructorul sterge toate vehiculele, liniile si statiile detinute
SistemTransport::~SistemTransport() {
    for (Vehicul* v : vehicule) delete v;
    for (Linie* l : linii)      delete l;
    for (Statie* s : statii)    delete s;
}

// operator<< afiseaza un sumar al sistemului de transport
std::ostream& operator<<(std::ostream& os, const SistemTransport& obj) {
    os << "  [Sistem de Transport - " << obj.numeOras << "]\n";
    os << "  Vehicule    : " << obj.vehicule.size() << "\n";
    os << "  Linii       : " << obj.linii.size() << "\n";
    os << "  Statii      : " << obj.statii.size() << "\n";
    return os;
}

// operator>> citeste numele orasului
std::istream& operator>>(std::istream& is, SistemTransport& obj) {
    std::cout << "  Nume oras: ";
    std::getline(is, obj.numeOras);
    if (obj.numeOras.empty())
        throw CapacitateInvalidaException("Numele orasului nu poate fi gol!");
    return is;
}

// management vehicule

void SistemTransport::adaugaVehicul(Vehicul* v) {
    if (v == nullptr)
        throw VehiculInexistentException("Vehiculul nu poate fi null!");
    vehicule.push_back(v);
}

void SistemTransport::afiseazaToateVehiculele() const {
    if (vehicule.empty()) {
        std::cout << "  Nu exista vehicule inregistrate.\n";
        return;
    }
    std::cout << "\n  === Toate vehiculele ===\n";
    for (const Vehicul* v : vehicule) {
        v->afisareDetaliata(); // dispatch dinamic
        std::cout << "\n";
    }
}

void SistemTransport::afiseazaVehiculDupaId(int id) const {
    Vehicul* v = gasesteVehicul(id);
    if (v == nullptr)
        throw VehiculInexistentException();
    v->afisareDetaliata();
}

void SistemTransport::urcaPasageri(int idVehicul, int nr) {
    Vehicul* v = gasesteVehicul(idVehicul);
    if (v == nullptr)
        throw VehiculInexistentException();
    v->urca(nr); // urca() arunca exceptie daca depaseste capacitatea
}

void SistemTransport::coboaraPasageri(int idVehicul, int nr) {
    Vehicul* v = gasesteVehicul(idVehicul);
    if (v == nullptr)
        throw VehiculInexistentException();
    v->coboara(nr);
}

// incarca bateria unui vehicul electric - verifica tipul cu dynamic_cast
void SistemTransport::incarcaBaterieVehicul(int idVehicul, double procente) {
    Vehicul* v = gasesteVehicul(idVehicul);
    if (v == nullptr)
        throw VehiculInexistentException();
    TransportElectric* te = dynamic_cast<TransportElectric*>(v);
    if (te == nullptr)
        throw VehiculInexistentException("Vehiculul cu ID-ul dat nu este electric!");
    te->incarca(procente);
}

// management linii

void SistemTransport::adaugaLinie(Linie* l) {
    if (l == nullptr)
        throw LinieInexistentaException("Linia nu poate fi null!");
    linii.push_back(l);
}

void SistemTransport::atribuieVehiculLinie(int idVehicul, int idLinie) {
    Vehicul* v = gasesteVehicul(idVehicul);
    if (v == nullptr)
        throw VehiculInexistentException();
    Linie* l = gasesteLinie(idLinie);
    if (l == nullptr)
        throw LinieInexistentaException();
    l->adaugaVehicul(v);
}

void SistemTransport::scoateVehiculDinLinie(int idVehicul, int idLinie) {
    Linie* l = gasesteLinie(idLinie);
    if (l == nullptr)
        throw LinieInexistentaException();
    l->eliminaVehicul(idVehicul);
}

void SistemTransport::afiseazaToateLiniile() const {
    if (linii.empty()) {
        std::cout << "  Nu exista linii inregistrate.\n";
        return;
    }
    std::cout << "\n  === Toate liniile ===\n";
    for (const Linie* l : linii)
        std::cout << *l << "\n";
}

void SistemTransport::afiseazaVehiculeleLiniei(int idLinie) const {
    Linie* l = gasesteLinie(idLinie);
    if (l == nullptr)
        throw LinieInexistentaException();
    l->afiseazaVehicule(); // polimorfism explicit in Linie
}

void SistemTransport::afiseazaGradOcupare(int idLinie) const {
    Linie* l = gasesteLinie(idLinie);
    if (l == nullptr)
        throw LinieInexistentaException();
    std::cout << "  Gradul de ocupare al liniei " << l->getNumeLiniei()
              << ": " << l->getGradOcupare() << "%\n";
}

// management statii

void SistemTransport::adaugaStatie(Statie* s) {
    if (s == nullptr)
        throw CapacitateInvalidaException("Statia nu poate fi null!");
    statii.push_back(s);
}

void SistemTransport::afiseazaToateStatiile() const {
    if (statii.empty()) {
        std::cout << "  Nu exista statii inregistrate.\n";
        return;
    }
    std::cout << "\n  === Toate statiile ===\n";
    for (const Statie* s : statii)
        std::cout << *s;
}

void SistemTransport::editeazaStatie(int idStatie) {
    Statie* s = gasesteStatie(idStatie);
    if (s == nullptr)
        throw CapacitateInvalidaException("Statia cu ID-ul dat nu exista!");
    std::cout << "  Statie curenta:\n" << *s;
    std::cin >> *s;
}

// functii complexe

// parcurge toate liniile si o afiseaza pe cea cu cel mai mare grad de ocupare
void SistemTransport::afiseazaLiniaCeaMaiAglomerata() const {
    if (linii.empty()) {
        std::cout << "  Nu exista linii inregistrate.\n";
        return;
    }
    Linie* ceaMaiAglomerata = linii[0];
    for (Linie* l : linii)
        if (l->getGradOcupare() > ceaMaiAglomerata->getGradOcupare())
            ceaMaiAglomerata = l;

    std::cout << "\n  Linia cea mai aglomerata:\n";
    std::cout << *ceaMaiAglomerata;
}

// filtreaza vehiculele electrice care pot parcurge distanta data
// foloseste dynamic_cast pentru a verifica daca vehiculul e electric
void SistemTransport::afiseazaVehiculeElectricePerDistanta(double distanta) const {
    std::cout << "\n  Vehicule electrice care pot parcurge " << distanta << " km:\n";
    bool gasit = false;
    for (Vehicul* v : vehicule) {
        TransportElectric* te = dynamic_cast<TransportElectric*>(v);
        if (te != nullptr && te->poateParcurgeDrumul(distanta)) {
            v->afisareDetaliata();
            std::cout << "\n";
            gasit = true;
        }
    }
    if (!gasit)
        std::cout << "  Niciun vehicul electric nu poate parcurge aceasta distanta.\n";
}

// raport complet - numara per tip cu dynamic_cast, calculeaza statistici globale
void SistemTransport::raportStatistici() const {
    int nrAutobuze = 0, nrTramvaie = 0, nrMetrouri = 0;
    int capacitateTotal = 0;
    double gradOcupareTotal = 0.0;

    for (Vehicul* v : vehicule) {
        if (dynamic_cast<Tramvai*>(v))       nrTramvaie++;   // Tramvai verificat inaintea subclaselor
        else if (dynamic_cast<Autobuz*>(v))  nrAutobuze++;
        else if (dynamic_cast<Metrou*>(v))   nrMetrouri++;

        capacitateTotal += v->getCapacitatePasageri();
        gradOcupareTotal += v->getGradOcupare();
    }

    std::cout << "\n  === Raport Statistici - " << numeOras << " ===\n";
    std::cout << "  Total vehicule   : " << vehicule.size() << "\n";
    std::cout << "    Autobuze       : " << nrAutobuze << "\n";
    std::cout << "    Tramvaie       : " << nrTramvaie << "\n";
    std::cout << "    Metrouri       : " << nrMetrouri << "\n";
    std::cout << "  Total linii      : " << linii.size() << "\n";
    std::cout << "  Total statii     : " << statii.size() << "\n";
    std::cout << "  Capacitate retea : " << capacitateTotal << " pasageri\n";

    if (!vehicule.empty())
        std::cout << "  Grad mediu ocup. : "
                  << gradOcupareTotal / vehicule.size() << "%\n";
}

// serializare si deserializare

void SistemTransport::salveaza(const std::string& fisier) const {
    std::ofstream fout(fisier);
    if (!fout.is_open())
        throw FisierException("Fisierul '" + fisier + "' nu poate fi deschis pentru salvare!");

    // 1. salvam vehiculele
    fout << vehicule.size() << "\n";
    for (const Vehicul* v : vehicule) {
        fout << v->getTip() << "\n"; // tipul e citit de factory la incarcare
        v->serializeaza(fout);
    }

    // 2. salvam liniile cu ID-urile vehiculelor alocate
    fout << linii.size() << "\n";
    for (const Linie* l : linii) {
        l->serializeaza(fout);
        l->serializeazaIduri(fout);
    }

    // 3. salvam statiile
    fout << statii.size() << "\n";
    for (const Statie* s : statii)
        s->serializeaza(fout);

    fout.close();
    std::cout << "  Datele au fost salvate in '" << fisier << "'.\n";
}

void SistemTransport::incarca(const std::string& fisier) {
    std::ifstream fin(fisier);
    if (!fin.is_open())
        throw FisierException("Fisierul '" + fisier + "' nu poate fi deschis pentru incarcare!");

    // eliberam datele existente inainte de incarcare
    for (Vehicul* v : vehicule) delete v;
    for (Linie* l : linii)      delete l;
    for (Statie* s : statii)    delete s;
    vehicule.clear();
    linii.clear();
    statii.clear();

    // 1. incarcam vehiculele
    int nrVehicule;
    fin >> nrVehicule;
    fin.ignore();
    for (int i = 0; i < nrVehicule; i++) {
        std::string tip;
        std::getline(fin, tip);
        Vehicul* v = creeazaVehicul(tip); // factory creeaza tipul corect
        if (v == nullptr)
            throw FisierException("Tip vehicul necunoscut in fisier: " + tip);
        v->deserializeaza(fin);
        vehicule.push_back(v);
    }

    // 2. incarcam liniile si rezolvam pointerii la vehicule dupa ID
    int nrLinii;
    fin >> nrLinii;
    fin.ignore();
    for (int i = 0; i < nrLinii; i++) {
        Linie* l = new Linie();
        l->deserializeaza(fin);

        // citim ID-urile vehiculelor si le rezolvam la pointeri din vectorul vehicule
        int nrVehiculeLiniei;
        fin >> nrVehiculeLiniei;
        fin.ignore();
        for (int j = 0; j < nrVehiculeLiniei; j++) {
            int idVehicul;
            fin >> idVehicul;
            fin.ignore();
            Vehicul* v = gasesteVehicul(idVehicul);
            if (v != nullptr)
                l->adaugaVehicul(v);
        }
        linii.push_back(l);
    }

    // 3. incarcam statiile
    int nrStatii;
    fin >> nrStatii;
    fin.ignore();
    for (int i = 0; i < nrStatii; i++) {
        Statie* s = new Statie();
        s->deserializeaza(fin);
        statii.push_back(s);
    }

    fin.close();
    std::cout << "  Incarcate: " << vehicule.size() << " vehicule, "
              << linii.size() << " linii, " << statii.size() << " statii.\n";
}
