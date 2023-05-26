
#include "../../include/Math.hpp"
#include "../../include/bodies/Verlet.hpp"

using namespace _math;

class Arbiter {
public:

    Arbiter() = default;
   
    // ??
    Verlet& addObject (Gvector position, float radius) {
        return _Objects.emplace_back(Verlet(position, radius));
    }
    void update(float dt);


private:

    uint32_t _SubStep = 1;
    Gvector _Gravity = {0.0f, 1000.0f};
    Gvector _ConstraintCenter;
    Gvector _ConstraintRadius = 100.0f;
    std::vector<Verlet> _Objects;
    float _Time = 0.0f;
    float _FrameDt = 0.0f;


};
