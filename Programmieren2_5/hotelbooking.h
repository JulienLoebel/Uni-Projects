#ifndef HOTELBOOKING_H
#define HOTELBOOKING_H
#include "booking.h"

class HotelBooking : public Booking
{
public:
    HotelBooking();
    HotelBooking(std::string pID, double pPrice, std::string pFromDate, std::string pToDate, std::string pHotel, std::string pTown, std::string pRoomType,
                 std::string pHotelLat, std::string pHotelLong, long pTravelID);
    ~HotelBooking();

    std::string showDetails();
    std::string getFullRoomType();

    const std::string &getHotel() const;

    const std::string &getTown() const;

    void setHotel(const std::string &newHotel);

    void setTown(const std::string &newTown);

    void setRoomType(const std::string &newRoomType);

    const std::string &getHotelLat() const;

    const std::string &getHotelLong() const;

    const std::string &getRoomType() const;

private:
    std::string hotel;
    std::string town;
    std::string roomType;
    std::string hotelLat;
    std::string hotelLong;

};

#endif // HOTELBOOKING_H
