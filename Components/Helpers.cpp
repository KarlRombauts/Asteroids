//
// Created by Karl Rombauts on 15/3/21.
//

#include "Helpers.h"
#include <random>

double randf(double min, double max) {
    return min + (rand() / ( RAND_MAX / (max-min) ) ) ;
//    std::random_device rd;
//    std::mt19937 e2(rd());
//    std::uniform_real_distribution<> dist(min, max);
//    return dist(e2);
}