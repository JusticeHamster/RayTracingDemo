#ifndef DIFFUSE_DISTRIBUTION_HPP
#define DIFFUSE_DISTRIBUTION_HPP

#include "ray_distribution.hpp"

class diffuse_distribution: public ray_distribution
{
public:
    virtual ~diffuse_distribution();
    diffuse_distribution();
    vector<ray> random(int num) const;
};

#endif // DIFFUSE_DISTRIBUTION_HPP
