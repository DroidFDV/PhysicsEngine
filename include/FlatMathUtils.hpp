// Math support structs and functions


#include <math.h>
#include <float.h>
#include <assert.h>
// #include <stdlib.h> 


namespace math { // BEGIN namespace math

const float PI = 3.14159265358979323846264f;

// https://stackoverflow.com/questions/17333/what-is-the-most-effective-way-for-float-and-double-comparison
bool AlmostEqual2sComplement(float A, float B, int maxUlps)    
{    
    // Make sure maxUlps is non-negative and small enough that the    
    // default NAN won't compare as equal to anything.    
    assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);    
    int aInt = *(int*)&A;    
    // Make aInt lexicographically ordered as a twos-complement int    
    if (aInt < 0)    
        aInt = 0x80000000 - aInt;    
    // Make bInt lexicographically ordered as a twos-complement int    
    int bInt = *(int*)&B;    
    if (bInt < 0)    
        bInt = 0x80000000 - bInt;    
    int intDiff = abs(aInt - bInt);    
    if (intDiff <= maxUlps)    
        return true;    
    return false;    
}

// geometric vector over a field of real number 
struct gvector {

    // constructor
    explicit gvector (float x = 0, float y = 0) noexcept : Xcoord(x), Ycoord(y) {}

    // copy constructor
    gvector (const gvector& _Right) noexcept = default;

    // move constructor
    gvector (gvector&& _Right) noexcept : Xcoord(_Right.Xcoord), Ycoord(_Right.Ycoord) {
        // ~_Right; // TODO: it's really bad to call destructor explicitly
        _Right.Xcoord = 0;
        _Right.Ycoord = 0;
    }

    // copy assigment
    gvector& operator= (const gvector& _Right) noexcept = default;

    // move assigment
    gvector& operator= (gvector&& _Right) noexcept {
        if (this != &_Right) {
            Xcoord = _Right.Xcoord;
            Ycoord = _Right.Ycoord;

            _Right.Xcoord = 0;
            _Right.Ycoord = 0;
        }

        return *this;
    }

    // destructor 
    ~gvector() noexcept = default;



    // arithmetics

    // set gvector values
    void set (float x, float y) noexcept {
        Xcoord = x;
        Ycoord = y;
    }

    // get opposit gvector
    // TODO: why I can't return a ref to gvector?
    gvector operator- () noexcept {
        return gvector(-Xcoord, -Ycoord);
    }

    // sum of two gvectors
    void operator+= (const gvector& _Right) noexcept {
        Xcoord += _Right.Xcoord;
        Ycoord += _Right.Ycoord;
    }

    // diff of two gvectors
    void operator-= (const gvector& _Right) noexcept {
        Xcoord -= _Right.Xcoord;
        Ycoord -= _Right.Ycoord;
    }

    // mult gvector and a number from field
    void operator*= (float M) noexcept {
        Xcoord *= M;
        Ycoord *= M;
    }

    // Euclidean norm of gvector 
    float length() const noexcept {
        return sqrtf(Xcoord * Xcoord + Ycoord * Ycoord);
    }



    float Xcoord;
    float Ycoord;
}; 



// matrix two by two over a field of real number
struct sq_matrix {
    
    explicit sq_matrix() {}

    // constructor (the matrix that defines the rotation on a given angle)
    explicit sq_matrix (float angle) noexcept {
        float cos_rot = cosf(angle);
        float sin_rot = sinf(angle);

        gvec1.Xcoord = cos_rot; gvec1.Ycoord = -sin_rot;
        gvec2.Xcoord = sin_rot; gvec2.Ycoord = cos_rot;
    }

    // copy constructor 
    sq_matrix (const sq_matrix&) noexcept = default;

    // move constructor 
    sq_matrix (sq_matrix&&) noexcept = default;

    // construct sq_matrix with two givven gvectors
    sq_matrix (const gvector& _Gvec1, const gvector& _Gvec2) noexcept : gvec1(_Gvec1), gvec2(_Gvec2) {}

    // copy assigment 
    sq_matrix& operator= (const sq_matrix&) noexcept = default;

    // move assigment 
    sq_matrix& operator= (sq_matrix&&) noexcept = default;

    ~sq_matrix() noexcept = default;



// arithmetics

    // transpose matrix  
    // TODO: why I can't return a ref to sq_matrix?
    sq_matrix transpose() const {
        return sq_matrix (gvector(gvec1.Xcoord, gvec2.Xcoord), gvector(gvec1.Ycoord, gvec2.Ycoord));
    }
    
    // get a determinant of sq_matrix
    float det() const {
        return gvec1.Xcoord * gvec2.Ycoord - gvec1.Ycoord * gvec2.Xcoord;
    }

    // TODO: it doesn't work properly
    bool is_invertible() const {
        return AlmostEqual2sComplement(gvec1.Xcoord * gvec2.Ycoord, gvec1.Ycoord * gvec2.Xcoord, 0);
    } 
    
    // TODO: need implement AXC::VERIFY
    sq_matrix invert() const {
        // AXC::VERIFY(this->is_invertible());
        
        float det = this->det();
        sq_matrix invert_matrix;
        // assert( det != 0.0f );
        float det_mult = 1.0f / det;

        invert_matrix.gvec1.Xcoord =  det_mult * gvec2.Ycoord;
        invert_matrix.gvec1.Ycoord = -det_mult * gvec1.Ycoord;

        invert_matrix.gvec2.Xcoord = -det_mult * gvec2.Xcoord;
        invert_matrix.gvec2.Ycoord =  det_mult * gvec1.Xcoord;

        return invert_matrix;
    }



    gvector gvec1;
    gvector gvec2;
};












































} // END namespace math


