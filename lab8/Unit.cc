#include "Unit.h"
#include <iostream>
#include <sstream>
#include <cassert> 

Unit::Unit() {
}

Unit::~Unit() {
}

void Unit::assertEquals(std::string msg, int expected, int actual) {
    if (expected != actual) {
        std::stringstream fmt;
        fmt << msg << ": Expected <" << expected << "> but was <" << actual << ">";
        failures.push_back(fmt.str());
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Expected <" << expected << "> and was <" << actual << ">";
        successes.push_back(fmt.str());
    }
}

void Unit::assert_LT(std::string msg, int lhs, int rhs) {
    if (lhs >= rhs) {
        std::stringstream fmt;
        fmt << msg << ": Expected " << lhs << " less than " << rhs;
        failures.push_back(fmt.str());
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Verified " << lhs << " less than " << rhs;
        successes.push_back(fmt.str());
    }
}

void Unit::assert_LE(std::string msg, int lhs, int rhs) {
    if (lhs > rhs) {
        std::stringstream fmt;
        fmt << msg << ": Expected " << lhs << " less than or equal " << rhs;
        failures.push_back(fmt.str());
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Verified " << lhs << " less than or equal " << rhs;
        successes.push_back(fmt.str());
    }
}

void Unit::assertvectorEquals(std::string msg, std::vector<int>& expected, std::vector<int>& actual) {
    bool fail = expected.size() != actual.size();
    for(unsigned int i=0; i < expected.size() && !fail; i++) {
        fail = expected[i] != actual[i];
    }
    if (fail) {
        std::stringstream fmt;
        fmt << msg << ": Expected\n";
        fmt << toStr(expected);
        fmt << "\nbut was\n";
        fmt << toStr(actual);
        failures.push_back(fmt.str());
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Verified ";
        fmt << toStr(expected);
        successes.push_back(fmt.str());
    }
}

void Unit::assertNonNull(std::string msg, void* actual) {
    if (actual == NULL) {
        std::stringstream fmt;
        fmt << msg << ": Expected non-null value.";
        failures.push_back(fmt.str());
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Verified non-null value.";
        successes.push_back(fmt.str());
    }
}
void Unit::insistNonNull(std::string msg, void* actual) {
// this is the same as assertNonNULL, except... 
    if (actual == NULL) {
        std::stringstream fmt;
        fmt << msg << ": Expected non-null value.";
        failures.push_back(fmt.str());
        // if test fails, then reportResults() and abend 
        printResults(); 
        assert( actual != NULL ); 
    }
    else { 
        std::stringstream fmt;
        fmt << msg << ": Verified non-null value.";
        successes.push_back(fmt.str());
    }
}

void Unit::assertNull(std::string msg, void* actual) {
    if (actual != NULL) {
        std::stringstream fmt;
        fmt << msg << ": Expected null value.";
        failures.push_back(fmt.str());
    }
    else {
        std::stringstream fmt;
        fmt << msg << ": Verified null value.";
        successes.push_back(fmt.str());
    }
}

void Unit::assertTrue(std::string msg, bool actual) {
    if (actual == false) {
        std::stringstream fmt;
        fmt << msg << ": Found false.";
        failures.push_back(fmt.str());
    }
    else {
        std::stringstream fmt;
        fmt << msg << ": Verified true.";
        successes.push_back(fmt.str());
    }
}

std::string Unit::toStr(std::vector<int>& v) {
    std::stringstream os;
    os << "[";
    for(unsigned int i=0; i < v.size(); i++) {
        os << v[i];
        if (i < v.size()-1) {
            os << ", ";
        }
    }
    os << "]";
    return os.str();
}

void Unit::printResults() {
    if (failures.empty()) {
        std::cout << "All " << successes.size() << " tests passed.\n";
    } 
    else {
        std::cerr << successes.size() << " successess, but "
                  << failures.size() << " failures:\n\n";
        for(unsigned int i=0; i < failures.size(); i++) {
            std::cerr << i+1 << ". " << failures[i] << "\n\n";
        }
    }
}

bool Unit::hasErrors(){ 
    if (failures.size() != 0) return (bool) 1;  
    return (bool) 0; 
}
bool Unit::isActive(){ 
    if (failures.size() != 0) return (bool) 1;  
    if (successes.size() != 0) return (bool) 1;  
    return (bool) 0; 
}


