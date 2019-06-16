#include "serializable.hpp"

serializable::~serializable()
{

}

buffer serializable::serialize() const
{
    if (!need_serialize) {
        return {};
    }
    return _serialize();
}
