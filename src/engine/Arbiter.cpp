#ifndef ARBITER_H
#define ARBITER_H


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

    void update()
    {
        _Time += _FrameDt;

        const float stepDt = getStepDt();
        for (uint32_t i = _SubSteps; i > 0; i--) {
            applyGravity();
            checkCollisions(stepDt);
            applyConstraint();
            updateObjects(stepDt);
        }
    }

    void setSimulationUpdateRate(uint32_t rate) 
    {
        _FrameDt = 1.0f / static_cast<float>(rate);
    }

    //
    void setConstraint(const Gvector& position, float radius) // or just value Gvector?
    { 
        _ConstraintCenter = position;
        _ConstraintRadius = radius;
    }

    void setSubStepsCount(uint32_t subSteps)
    {
       _SubSteps = subSteps; 
    }  
    
    // ??
    void setObjectVelecity(Verlet& object, const Gvector& velocity) 
    {
        object.setVelocity(velocity, getStepDt());
    }

    [[nodiscard]] const std::vector<Verlet>& getObjects() const 
    {
        return _Objects;
    }

    [[nodiscard]] std::vector<float> getConstraint() const 
    {
        std::vector<float> result {
            _ConstraintCenter.Xcoord,
            _ConstraintCenter.Ycoord,
            _ConstraintRadius
        };
    }

    [[nodiscard]] uint64_t getObjectsCount() const
    {
        return _Objects.size();
    }
    
    [[nodiscard]] float getTime() const 
    {
        return _Time;
    }

    [[nodiscard]] float getStepDt() const 
    {
        return _FrameDt / static_cast<float>(_SubSteps);
    }

private:
    
    void checkCollisions(float dt) 
{
        const float response_coef = 0.75f;
        const uint64_t objectCount = _Objects.size();

        for (uint64_t i = 0; i < objectCount; i++) 
        {
            Verlet& verletA = _Objects[i];
            for (uint64_t j = i + 1; j < objectCount; j++) 
            {
                Verlet& verletB = _Objects[j];
                const Gvector v = verletA.posNow - verletB.posNow;
                const float dist2 = dot(v, v); 
                const float min_dist = verletA.radius + verletB.radius;

                if (dist2 < min_dist * min_dist)
                {
                    const float dist = sqrtf(dist2);
                    const Gvector n = v * (1 / dist);
                    const float massRatioA = verletA.radius / (verletA.radius + verletB.radius);

                    const float massRatioB = verletB.radius / (verletA.radius + verletB.radius);
                    const float delta = 0.5f * response_coef * (dist - min_dist);

                    verletA.posNow -= n * (massRatioA * delta);
                    verletB.posNow += n * (massRatioB * delta);
                }
            }
        }
    }

    void applyGravity() 
    {
        for (auto& object : _Objects) 
        {
            object.accelerate(_Gravity);
        }
    }

    void applyConstraint() 
    {
        for (auto& object : _Objects)
        {
            const Gvector pos  = _ConstraintCenter - object.posNow;
            const float   dist = pos.norm();

            if (dist > (_ConstraintRadius - object.radius)) {
                const Gvector n = pos * (1 / dist);
                object.posNow = _ConstraintCenter - n * (_ConstraintRadius - object.radius);
            }
        }
    }

    void updateObjects(float dt) 
    {
        for (auto& object : _Objects) 
        {
            object.updatePosition(dt);
        }
    }



private:

    uint32_t            _SubSteps         = 1;
    Gvector             _Gravity          = {0.0f, 1000.0f};
    Point               _ConstraintCenter;
    float               _ConstraintRadius = 100.0f;
    float               _Time             = 0.0f;
    float               _FrameDt          = 0.0f;
    std::vector<Verlet> _Objects;

};

#endif 
