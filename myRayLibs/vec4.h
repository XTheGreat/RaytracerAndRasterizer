#ifndef _VEC4_H
#define _VEC4_H

#include "mat4.h"

class Vec4
{
  public:
    double data[4];

    Vec4(){
      for (int i = 0; i < 4; i++)
        data[i] = 0;
    }; // default constructor

    ~Vec4() {}; // destructor

    //!
    const double operator[](const int i) const
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 4); 
      return data[i]; 
    }
    
    // Allows the setting of vector values through the operator[]
    double& operator[](const int i)
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 4); 
      return data[i]; 
    }

    Vec4(const double a, const double b, const double c, const double d
    ) 
    {
      data[0] = a;
      data[1] = b;
      data[2] = c;
      data[3] = d;
    };

    //! 
    /** Sets the components, piecewise in the vector.
     */    
    void set(const double a, const double b, const double c, const double d
    )
    {
      data[0] = a;
      data[1] = b;
      data[2] = c;
      data[3] = d;
    };

    //Assignment operator
    Vec4 &operator=(const Vec4 &rhs)
    {
      data[0] = rhs[0];
      data[1] = rhs[1];
      data[2] = rhs[2];
      data[3] = rhs[3];
      return *this;
    };

    //! 
    Vec4 &operator+=(const Vec4 &rhs)
    {
      data[0] += rhs[0];
      data[1] += rhs[1];
      data[2] += rhs[2];
      data[3] += rhs[3];
      return *this;
    };

    Vec4 &operator-=(const Vec4 &rhs)
    {
      data[0] -= rhs[0];
      data[1] -= rhs[1];
      data[2] -= rhs[2];
      data[3] -= rhs[3];
      return *this;
    };
    
    Vec4& operator*=(const double c)
    {
      data[0] *= c;
      data[1] *= c;
      data[2] *= c;
      data[3] *= c;
      return *this;
    };

    Vec4& operator/=(const double c)
    {
      data[0] /= c;
      data[1] /= c;
      data[2] /= c;
      data[3] /= c;
      return *this;
    };

    void setIdentity()
    {
      data[0] = 1;
      data[1] = 1;
      data[2] = 1;
      data[3] = 1;
    };

    Vec4& operator*(const Mat4 &MatrixOf4){
      double temp1, temp2, temp3, temp4;
      temp1 = data[0]; temp2 = data[1]; temp3 = data[2]; temp4 = data[3];
      data[0]  = MatrixOf4[0] * temp1 + MatrixOf4[1] * temp2 + MatrixOf4[2] * temp3 + MatrixOf4[3] * temp4;
      data[1]  = MatrixOf4[4] * temp1 + MatrixOf4[5] * temp2 + MatrixOf4[6] * temp3 + MatrixOf4[7] * temp4;
      data[2]  = MatrixOf4[8] * temp1 + MatrixOf4[9] * temp2 + MatrixOf4[10] * temp3 + MatrixOf4[11] * temp4;
      data[3]  = MatrixOf4[12] * temp1 + MatrixOf4[13] * temp2 + MatrixOf4[14] * temp3 + MatrixOf4[15] * temp4;
      return *this;
    };
};

#endif