#pragma once

#define distanceInKmBetweenEarthCoordinates haversine_distance

double haversine_distance(double, double, double, double);
double vincenty_distance(double, double, double, double);