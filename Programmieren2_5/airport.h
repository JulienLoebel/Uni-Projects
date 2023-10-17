#ifndef AIRPORT_H
#define AIRPORT_H
#include <iostream>


class Airport
{
public:
    Airport(std::string pName, std::string pIso_country, std::string pMunicipality, std::string pIata_code);

    const std::string &getName() const;

    const std::string &getIata_code() const;

private:
    std::string name;
    std::string iso_country;
    std::string municipality;
    std::string iata_code;
};

#endif // AIRPORT_H
