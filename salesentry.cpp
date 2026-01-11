//
//
// File:        salesentry.cpp
//
// Version:     1.0
// Date:        9/15/25
// Author:      Alivia Lee
//
// Description: Class implementation for a sales entry.
//
//
 
#include "string.hpp"
#include "salesentry.hpp"
#include <iostream>
#include <vector>
#include <set>

int stringToInt(const String& s) {
    int result = 0;
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c >= '0' && c <= '9') {
            result = result * 10 + (c - '0');
        }
    }
    return result;
}

// Convert String to double (no <cstdlib>)
double stringToDouble(const String& s) {
    double result = 0.0;
    double fraction = 0.1;
    bool isFraction = false;

    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (c == '.') {
            isFraction = true;
            continue;
        }
        if (c >= '0' && c <= '9') {
            if (isFraction) {
                result += (c - '0') * fraction;
                fraction *= 0.1;
            } else {
                result = result * 10 + (c - '0');
            }
        }
    }
    return result;
}


SalesEntry::SalesEntry(const String& line) {
    //Use split to create SalesEntry

    int endOfName = line.findch(1,'"');
    name = line.substr(1, endOfName - 1);
    String restOfLine = line.substr(endOfName + 2, line.length() - 1);
    std::vector<String> SalesEntryParts = restOfLine.split(',');
    mainCategory = SalesEntryParts[0];
    subCategory = SalesEntryParts[1];
    image = SalesEntryParts[2];
    link = SalesEntryParts[3];
    ratings = stringToDouble(SalesEntryParts[4]);
    noOfRatings = stringToInt(SalesEntryParts[5]); 
    discountPrice = SalesEntryParts[6];
    actualPrice = SalesEntryParts[7];
}

std::vector<SalesEntry> parse(std::istream& in) {
    std::vector<SalesEntry> result;
    char temp[500];
    bool firstLine = true;

    while(in.getline(temp, 500)){
        if(firstLine){
            firstLine = false;
            continue;
        }
        String line(temp);
        SalesEntry entry(line);
        result.push_back(entry);
    }

    return result;
}

void outputAll(std::ostream& out, const std::vector<SalesEntry>& s) {
    for(std::size_t i = 0; i < s.size(); ++i){
        out << "Sale entry " << i + 1 << ": " << std::endl;
        out << "Name: " << s[i].getName() << std::endl;
        out << "Main Category: " << s[i].getMainCategory() << std::endl;
        out << "Sub Category: " << s[i].getSubCategory() << std::endl;
        out << "Image: " << s[i].getImage() << std::endl;
        out << "Link: " << s[i].getLink() << std::endl;
        out << "Ratings: " << s[i].getRatings() << std::endl;
        out << "Number of Ratings: " << s[i].getNoOfRatings() << std::endl;
        out << "Discount price: " << s[i].getDiscountPrice() << std::endl;
        out << "Actual price: " << s[i].getActualPrice() << std::endl;
        out << std::endl;
    }
}


void outputTotal(std::ostream& out, const std::vector<SalesEntry>& s) {
    int total = 0;
    for(std::size_t i = 0; i < s.size(); ++i){
        total = total + s[i].getNoOfRatings();
    }
    out << "Total number of ratings: " << total << std::endl;

}


void outputLink(std::ostream& out, const std::vector<SalesEntry>& s) {
    for(std::size_t i = 0; i < s.size(); ++i){
        out << "Link for sales entry " << i+1 << ": " << s[i].getLink() << std::endl; 
    }
}


void outputUniqueRatings(std::ostream& out, const std::vector<SalesEntry>& s) {
    std::set<double> uniqueRatings;

    // collect unique ratings
    for (size_t i = 0; i < s.size(); ++i) {
        uniqueRatings.insert(s[i].getRatings());
    }

    // print them
    out << "Unique Ratings:" << std::endl;
    for (double rating : uniqueRatings) {
        out << rating << std::endl;
    }

    out << std::endl;
    out << "Total unique ratings: " << uniqueRatings.size() << std::endl;
}

//To find the number of unique product ratings, I used a std::set<double>.
//I iterated through the vector of SalesEntry objects and inserted each rating into the set, which automatically ignores duplicates.
//Then I printed every rating in the set and the total count of unique ratings.
//This works efficiently since std::set guarantees uniqueness and keeps the ratings sorted automatically.


