



#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <math.h>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        int maxIndex = 5;
        unsigned long long w[maxIndex] = {0,0,0,0,0};
        int count = 0;;
        for(int i = k.size()-1; i >= 0; i--)
        {
            w[maxIndex-1] += letterDigitToNumber((char)tolower(k[i]))*pow(36, count);
            count++;
        
            if(count == 6 ) {
                maxIndex--;
                count = 0;
            }
        }
        
        HASH_INDEX_T hResult = 0;
        for(int i = 0; i < 5;i++)
        {
        hResult += rValues[i]*w[i];
        }
        return hResult;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        HASH_INDEX_T result = 0;
        if(letter >= '0' && letter <= '9' )
        result = letter - '0'+26;
        else
        result = letter - 'a';
        
        return result;
        
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
