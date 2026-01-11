//
// File:        salesentry.hpp
//
// Version:     1.0
// Date:        9/15/25
// Author:      Alivia Lee
//
// Description: Class definition for a sales entry.
//
//
//
 
#ifndef CS_SALESENTRY_H_
#define CS_SALESENTRY_H_

#include "string.hpp"
#include <iostream>
#include <vector>



// A single sales entry
class SalesEntry {
public:
    SalesEntry() {};
    SalesEntry(const String&);
    friend  std::ostream& operator<<(std::ostream&, const SalesEntry&);

    String getName() const { return name; }
    String getMainCategory() const { return mainCategory; }
    String getSubCategory() const { return subCategory; }
    String getImage() const { return image; }
    String getLink() const { return link; }
    double getRatings() const { return ratings; }
    int getNoOfRatings() const { return noOfRatings; }
    String getDiscountPrice() const { return discountPrice; }
    String getActualPrice() const { return actualPrice; }

private:
    String  name;
    String  mainCategory;
    String  subCategory;
    String  image;
    String  link;
    double  ratings;
    int     noOfRatings;
    String  discountPrice;
    String  actualPrice;
    
};


//
// Free functions
//

std::vector<SalesEntry> parse      (std::istream&);
void                    outputAll  (std::ostream&, const std::vector<SalesEntry>&);
void                    outputTotal(std::ostream&, const std::vector<SalesEntry>&);
void                    outputLink (std::ostream&, const std::vector<SalesEntry>&);
void                    outputUniqueRatings(std::ostream& out, const std::vector<SalesEntry>& s);

#endif
