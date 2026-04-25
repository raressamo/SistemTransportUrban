#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>

// baza tuturor exceptiilor din aplicatie
// mosteneste std::exception ca sa fie compatibila cu catch (std::exception&)
class TransportException : public std::exception {
    std::string mesaj;
public:
    explicit TransportException(const std::string& mesaj) : mesaj(mesaj) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

// aruncata cand capacitatea unui vehicul este <= 0
class CapacitateInvalidaException : public TransportException {
public:
    explicit CapacitateInvalidaException(const std::string& mesaj = "Capacitatea trebuie sa fie pozitiva!")
        : TransportException(mesaj) {}
};

// aruncata cand incerci sa urci mai multi pasageri decat capacitatea sau sa cobori mai multi decat sunt
class PasageriInvalidException : public TransportException {
public:
    explicit PasageriInvalidException(const std::string& mesaj = "Numar invalid de pasageri!")
        : TransportException(mesaj) {}
};

// aruncata cand cauti o linie dupa ID si nu exista
class LinieInexistentaException : public TransportException {
public:
    explicit LinieInexistentaException(const std::string& mesaj = "Linia nu exista!")
        : TransportException(mesaj) {}
};

// aruncata cand cauti un vehicul dupa ID si nu exista
class VehiculInexistentException : public TransportException {
public:
    explicit VehiculInexistentException(const std::string& mesaj = "Vehiculul nu exista!")
        : TransportException(mesaj) {}
};

// aruncata cand un vehicul electric nu are suficienta baterie pentru distanta ceruta
class BaterieInsuficientaException : public TransportException {
public:
    explicit BaterieInsuficientaException(const std::string& mesaj = "Baterie insuficienta pentru distanta ceruta!")
        : TransportException(mesaj) {}
};

// aruncata cand un fisier nu poate fi deschis pentru citire sau scriere
class FisierException : public TransportException {
public:
    explicit FisierException(const std::string& mesaj = "Fisierul nu poate fi deschis!")
        : TransportException(mesaj) {}
};

// aruncata cand config.txt lipseste sau contine valori invalide
class ConfigInvalidException : public TransportException {
public:
    explicit ConfigInvalidException(const std::string& mesaj = "Configuratie invalida!")
        : TransportException(mesaj) {}
};

#endif
