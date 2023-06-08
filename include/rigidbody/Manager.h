#ifndef ARBITER_H
#define ARBITER_H


#include "../Math.hpp"
#include "../structures/Gvector.hpp"
#include "../structures/Point.hpp"
#include "../primitives/IShell.h"


using namespace _math;
using namespace _st;


// struct RigidBody;

////////////////////////////////////////////////////////////
/// \brief A union type which store contact edges and a key
///        key value
/// \param Edges Edges with contact points
/// \param value Key value to distinguish different pairs
////////////////////////////////////////////////////////////
union FeaturePair {
    
    struct Edges {
        char inEdge1;
        char outEdge1;
        char inEdge2;
        char outEdge2;
    } e;

    int value;
};


////////////////////////////////////////////////////////////
/// \brief Struct present and store a contact point
///
////////////////////////////////////////////////////////////
struct Contact {

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    Contact() noexcept :
        accNormalImpulse(0.0f),
        accTangentImpulse(0.0f), 
        accNormalImpulseBias(0.0f)
    {}


    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    Gvector     ContactPos;
    Gvector     Normal;
    Point       r1, r2;
    float       Separation;
    float       accNormalImpulse;        // Pn
    float       accTangentImpulse;       // Pt
    float       accNormalImpulseBias;    // Pnb
    float       MassNormal, MassTangent;
    float       Bias;
    FeaturePair Feature;
};


////////////////////////////////////////////////////////////
/// \brief Struct uses in std::map to store contacts with 
///        contact rigid bodies
///
////////////////////////////////////////////////////////////
struct ManagerKey {
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct manager key
    /// \param shellA First contact rigid body
    /// \param shellB Second contact rigid body
    ///
    ////////////////////////////////////////////////////////////
    ManagerKey (IShell* shellA, IShell* shellB) {
        shellA->getMass() < shellB->getMass() ? 
            smallShell = shellA, bigShell = shellB :
            smallShell = shellB, bigShell = shellA; 
    }


    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    IShell* smallShell; // has smaller mass
    IShell* bigShell;   // has bigger mass
};


////////////////////////////////////////////////////////////
/// \brief Struct to manage all contacts between rigid bodies
///
////////////////////////////////////////////////////////////
struct Manager {

    ////////////////////////////////////////////////////////////
    /// \brief Amount of contact points
    ///
    ////////////////////////////////////////////////////////////
    enum {MAX_POINTS = 2};
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct manager to solve the contact of two
    ///        rigid bodies
    /// \param shellA First contact rigid body
    /// \param shellB Second contact rigid body
    ///
    ////////////////////////////////////////////////////////////
    Manager (IShell* shellA, IShell* shellB) noexcept;
    
    ////////////////////////////////////////////////////////////
    /// \brief Function to update contact points
    /// \param contact An array of contact points
    /// \param numContacts Number of contacts = number of
    ///        elements in contact array
    ///
    ////////////////////////////////////////////////////////////
    void update (Contact* contacts, int numContacts);

    ////////////////////////////////////////////////////////////
    /// \brief Function calculate pre step positions of 
    ///        rigid bodies
    ////////////////////////////////////////////////////////////
    void preStep (float invDt);

    ////////////////////////////////////////////////////////////
    /// \brief Function to apply impulses when manager has been
    ///        solved a contact
    ///
    ////////////////////////////////////////////////////////////
    void applyImpulse();

    
    ////////////////////////////////////////////////////////////
    /// Member data
    ////////////////////////////////////////////////////////////
    Contact arrContacts[MAX_POINTS]; // TODO std::vector<Contact> vecContacts;
    int     numContacts; 

    IShell* smallShell;
    IShell* bigShell;

    float friction; // combined friction
};


////////////////////////////////////////////////////////////
/// \relates ManagerKey
/// \brief Overload of binary operator< to std::map using
///
/// \param _Lhs Left operand (a ManagerKey)
/// \param _Rhs Right operand (a ManagerKey)
///
/// \return If mass of body by left ManagerKey is greater
///         return false, else return true
///
////////////////////////////////////////////////////////////
inline bool operator< (const ManagerKey& _Lhs, const ManagerKey& _Rhs) {
    if (_Lhs.smallShell->getMass() < _Rhs.smallShell->getMass()) { return true; }
    if (
        _Lhs.smallShell->getMass() == _Rhs.smallShell->getMass() &&
        _Lhs.bigShell->getMass() < _Rhs.bigShell->getMass()
    ) { return true; }
    
    return false;
}


////////////////////////////////////////////////////////////
/// \relates ManagerKey
/// \brief Function to solve contact between two rigid bodies
////////////////////////////////////////////////////////////
int Collide (Contact* _contact, IShell* shellA, IShell* shellB);


#endif // ARBITER_H
