#ifndef MIRROR_DISTRIBUTION_HPP
#define MIRROR_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

class mirror_distribution: public ray_distribution
{
public:
    mirror_distribution();
    vector<ray> random(int num);
};

#endif // MIRROR_DISTRIBUTION_HPP
