#include "customer.h"

Customer::Customer(long pID, std::string pName)
    :id(pID), name(pName)
{

}

Customer::~Customer()
{

}

void Customer::addTravel(std::shared_ptr<Travel> travel)
{
    travelList.push_back(travel);
}

long Customer::getId() const
{
    return id;
}


const std::string &Customer::getName() const
{
    return name;
}

const std::vector<std::shared_ptr<Travel> > &Customer::getTravelList() const
{
    return travelList;
}

std::shared_ptr<Travel> Customer::checkTravelList(long id)
{
    std::shared_ptr<Travel> travel(NULL);
    for (std::shared_ptr<Travel> t : travelList) {
        if (t->getId() == id) {
            travel = t;
        }
    }
    return travel;
}

double Customer::getTotalCustomerPrice()
{
    double totalCustomerPrice = 0;

    for (unsigned int i = 0; i < travelList.size(); i++) {
        totalCustomerPrice = totalCustomerPrice + travelList[i]->getTotalTravelPrice();
    }
    return totalCustomerPrice;
}

