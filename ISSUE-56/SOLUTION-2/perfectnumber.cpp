//
//  perfectnumber.cpp
//
//  Created by Jin Chen on 6/7/14.
//  Copyright (c) 2014 ciccino. All rights reserved.
//

#include <string>
#include <iostream>
#include <stdio.h>

/*
 * Try to calculate the largest perfect number we already know
 * based on this formula:
 * PN = (2<<(p - 1)) * ((2<<p) - 1) = 2<<(2p-1) - 2<<(p-1)
 * p is prime number and 2<<p - 1 is prime number too.
 * the larget known prime number is 2<<57,885,161 - 1, mersenne prime
 * From wiki
 * To help visualize the size of the 48th known Mersenne prime, 
 * it would require 4,647 pages to display the number in base 10 with
 * 75 digits per line and 50 lines per page.
 * The largest known Mersenne prime (257,885,161 − 1) is
 * also the largest known prime number.
 * 4647 * 75 * 50 = 17426250
 */

void rsSelf(unsigned int *pn, int &width, int rs) {
    int carry = 0;

    for (int i = 0; i < width; i++) {
        pn[i] = (pn[i] << rs) + carry;
        carry = 0;
        while (pn[i] >= 1000000000) {
            carry++;
            pn[i] -= 1000000000;
        }
    }
    if (carry) {
        pn[width] = carry;
        width++;
    }
}

void minus(unsigned int *pn, unsigned int *ln, int width) {
    int carry = 0;
    for (int i = 0; i < width; i++) {
        if (pn[i] < ln[i]) {
            pn[i] = 1000000000 + pn[i] - ln[i] - carry;
            carry = 1;
        } else {
            pn[i] = pn[i] - ln[i];
            carry = 0;
        }
    }
    if (carry) {
        std::cout << "Error: 2<<(2p-1) - 2<<(p-1) < 0!" << std::endl;
    }
}

int mersenneExpo[48] = {
    2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279, 
    2203, 2281, 3217, 4253, 4423, 9689, 9941, 11213, 19937, 21701, 
    23209, 44497, 86243, 110503, 132049, 216091, 756839, 859433, 
    1257787, 1398269, 2976221, 3021377, 6972593, 13466917, 20996011, 
    24036583, 25964951, 30402457,
    //It is not verified whether any undiscovered Mersenne primes exist between the 43rd (M30,402,457) and the 48th (M57,885,161) on this chart
    32582657, 37156667, 42643801, 43112609, 57885161
};

int main() {
    int idx = 0;

    std::cout << "Please pick one Mensenne exponents(1 - 48): \n";
    std::cout << "\t2, 3, 5, 7, 13, 17 .... 57885161\n";

    std::cin >> idx;
    while (idx < 1 || idx > 48) {
        std::cout << "please choose its index between 1 and 48:\n";
        std::cin >> idx;
    }

    int p = mersenneExpo[idx - 1];
    // speculate the width of decimal number is 1/3 of width of binary number
    int w = 2 * p / 3 + 1;
    // each unsigned int represent 9 digits in the final number
    int l = w / 9 + 1;
    unsigned int *pn = new unsigned int[l];
    //memset(pn, 0, w);
    //pn[0] = 1;
    unsigned int *ln = new unsigned int[l];
    memset(ln, 0, l * sizeof(unsigned int));
    ln[0] = 1;
    
    //calculate 2<<(p-1)
    int width = 1;
    int j = 1024;
    int step = 2;
    if (p <= 32) {
        step = 1;
    }
    for (int i = 0; i < (p - 1) / step; i++) {
        if (i > j) {
            std::cout << "calculate 2<<" << i << ", current width is " << width << std::endl;
            j = j + j;
        }
        rsSelf(ln, width, step);
    }
    //width = 1;
    std::cout << ln[width - 1] << "..." << ln[0] << std::endl;
    
    memcpy(pn, ln, l * sizeof(unsigned int));
    for (int i = (p - 1) / step; i < (2 * p - 1) / step; i++) {
        if (i > j) {
            std::cout << "calculate 2 << " << i << std::endl;
            j = j + j;
        }
        rsSelf(pn, width, step);
    }
    for (int i = ((2 * p - 1) / step) * step; i < 2 * p - 1; i++) {
        rsSelf(pn, width, 1);
    }
    std::cout << pn[width - 1] << "..." << pn[0] << std::endl;

    if (width > l) {
        std::cout << "Error! Our array is not big enough for the perfect number with width: "
            << width << "!" << std::endl;
    } 
    minus(pn, ln, width);

    //save final result of perfect number
    std::cout << "save perfectnumber corresponding to " << idx 
        << "mersenne prime number\n";
    std::string fname = std::to_string(idx);
    fname.append(".");
    fname.append(std::to_string(p));
    fname.append(".perfectnumber.txt");
    FILE *f = fopen(fname.c_str(), "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    fprintf(f, "perfectnumber:\n");
    for (int i = width - 1; i >= 0; i--) {
        fprintf(f, "%.9u ", pn[i]);
    }
    fclose(f);
    return 0;
}