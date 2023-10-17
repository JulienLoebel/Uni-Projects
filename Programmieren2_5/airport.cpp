#include "airport.h"

Airport::Airport(std::string pName, std::string pIso_country, std::string pMunicipality, std::string pIata_code)
    :name(pName), iso_country(pIso_country), municipality(pMunicipality), iata_code(pIata_code)
{

}

const std::string &Airport::getName() const
{
    return name;
}

const std::string &Airport::getIata_code() const
{
    return iata_code;
}
