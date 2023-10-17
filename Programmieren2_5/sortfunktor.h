#ifndef SORTFUNKTOR_H
#define SORTFUNKTOR_H
#include "booking.h"

class SortFunktor
{
public:
    enum SortierParameter {
        price, fromDate, toDate, travelId
    };
    SortFunktor(SortFunktor::SortierParameter parameter = price);
    bool operator()(std::shared_ptr<Booking> booking1, std::shared_ptr<Booking> booking2);

private:
    SortFunktor::SortierParameter sortierParameter;
};

#endif // SORTFUNKTOR_H
