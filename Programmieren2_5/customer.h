#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
#include "travel.h"


class Customer
{
public:
    Customer(long pID, std::string pName);
    ~Customer();

    void addTravel(std::shared_ptr<Travel> travel);
    std::shared_ptr<Travel> checkTravelList(long id);
    double getTotalCustomerPrice();

    long getId() const;


    const std::string &getName() const;


    const std::vector<std::shared_ptr<Travel> > &getTravelList() const;

private:
    long id;
    std::string name;
    std::vector<std::shared_ptr<Travel>> travelList;
};

#endif // CUSTOMER_H
