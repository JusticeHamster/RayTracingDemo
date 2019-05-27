#ifndef DIFFUSE_DISTRIBUTION_HPP
#define DIFFUSE_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

class diffuse_distribution: public ray_distribution
{
public:
    diffuse_distribution();
    vector<ray> random(int num);
};

#endif // DIFFUSE_DISTRIBUTION_HPP
