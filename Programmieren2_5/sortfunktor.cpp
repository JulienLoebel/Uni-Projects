#include "sortfunktor.h"


SortFunktor::SortFunktor(SortFunktor::SortierParameter parameter)
    :sortierParameter(parameter)
{

}

bool SortFunktor::operator()(std::shared_ptr<Booking> booking1, std::shared_ptr<Booking> booking2)
{
    if (sortierParameter == price) {
        return booking1->getPrice() < booking2->getPrice();
    } else if (sortierParameter == fromDate) {
        return booking1->getQFromDate() < booking2->getQFromDate();
    } else if (sortierParameter == toDate){
        return booking1->getQToDate() < booking2->getQToDate();
    } else if (sortierParameter == travelId) {
        return booking1->getTravelID() < booking2->getTravelID();
    } else
        return false;

}
