#ifndef RIGIDBODY_H
#define RIGIDBODY_H 


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"


using namespace _math;
using namespace _st;


////////////////////////////////////////////////////////////
/// \brief This class present a rigid body and it's traits
///
////////////////////////////////////////////////////////////
struct RigidBody {

    ////////////////////////////////////////////////////////////
    /// \brief Shape traits of rigid body. Rigid body can be 
    ///        insert one of these shape(shells). Is connect 
    ///        rigid body with one of IShell's
    ///
    ////////////////////////////////////////////////////////////
    struct shape_traits {
       
        enum class type {
            Circle,
            Triangle,
            Box,
        } shapeTy;
    };
  

    ////////////////////////////////////////////////////////////
    /// \brief Construct rigid body with shape_traits, all other
    ///        members constructed by default values as a 
    ///        Constraints
    /// \param bodyType That defines a shape_traits::type
    ///
    ////////////////////////////////////////////////////////////    
    RigidBody(shape_traits::type bodyType) noexcept;

    ////////////////////////////////////////////////////////////
    /// \brief Function to set or change rigid body position,
    ///        size and mass
    /// \param position New position of rigid body
    /// \param size     New size of rigid body
    /// \param mass     New mass of rigid body. InvMass will
    ///                 recompute.
    ////////////////////////////////////////////////////////////
    void set (const Point& position, const Gvector& size, float mass);

    ////////////////////////////////////////////////////////////
    /// \brief Function to add new force to accumulated Force of
    ///        the rigid body
    /// \param force New force to add
    ////////////////////////////////////////////////////////////
    void addForce (const Gvector& force) noexcept;
    
    ////////////////////////////////////////////////////////////
    /// \brief Function to update position of rigid body after
    ///        a specified time
    /// \param dt Delta time = time change
    ////////////////////////////////////////////////////////////
    void updatePosition (float dt); 

    ////////////////////////////////////////////////////////////
    /// \brief Function to set velocity of rigid body after
    ///        a specified time
    /// \param velocity New velocity of rigid body
    /// \param dt Delta time = time change
    ////////////////////////////////////////////////////////////
    void updateVelocity (const Gvector& velocity, float dt);

    //////////////////////////////////////////////////////////// 
    /// Rigid body properties
        static shape_traits ShapeTraits;

    /// State
        Point   Position;
        float   Rotation;
        Gvector Velocity; // linear velocity
        float   AngularVelocity;
    
    /// Box properties
        Gvector Size; // if ShapeTraits.shapeTy == shape_traits::type::Circle
                      // => Size = (Radius, Radius), else [width, height]
        float   Mass, InvMass;
        float   InertiaTensor, InvI;
        float   Friction;

    /// Applied forces
        Gvector Force; // accumulated force
        float   Torque;
    ////////////////////////////////////////////////////////////
};

#endif // RIGIDBODY_H 
