#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>

class Domain {
public:
    // Virtual function to be overridden by subclasses
    virtual void PrintGrid(std::string outputFileName) const = 0;

    // Destructor for the base class
    virtual ~Domain() {}
};

#endif // DOMAIN_H

