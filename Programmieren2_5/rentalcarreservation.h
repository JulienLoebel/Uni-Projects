#ifndef RENTALCARRESERVATION_H
#define RENTALCARRESERVATION_H
#include "booking.h"

class RentalCarReservation : public Booking
{
public:
    RentalCarReservation();
    RentalCarReservation(std::string pID, double pPrice, std::string pFromDate, std::string pToDate, std::string pPickupLocation, std::string pReturnLocation,
                         std::string pCompany, std::string pVehicleClass, std::string pPickupLocationLat, std::string pPickupLocationLong,
                         std::string pReturnLocationLat, std::string pReturnLocationLong, long pTravelID);
    ~RentalCarReservation();

    std::string showDetails();

    const std::string &getPickupLocation() const;

    const std::string &getReturnLocation() const;

    const std::string &getCompany() const;

    const std::string &getVehicleClass() const;

    void setPickupLocation(const std::string &newPickupLocation);

    void setReturnLocation(const std::string &newReturnLocation);

    void setCompany(const std::string &newCompany);

    void setVehicleClass(const std::string &newVehicleClass);

    const std::string &getPickupLocationLat() const;

    const std::string &getPickupLocationLong() const;

    const std::string &getReturnLocationLat() const;

    const std::string &getReturnLocationLong() const;

private:
    std::string pickupLocation;
    std::string returnLocation;
    std::string company;
    std::string vehicleClass;
    std::string pickupLocationLat;
    std::string pickupLocationLong;
    std::string returnLocationLat;
    std::string returnLocationLong;
};

#endif // RENTALCARRESERVATION_H
