#ifndef _MAT4_H
#define _MAT4_H

#include <cassert>
#include <iostream>
#include <cmath>
#include <vector>

class Mat4
{
  public:
    double data[16];

    Mat4(){
      for (int i = 0; i < 16; i++)
        data[i] = 0;
    }; // default constructor

    ~Mat4() {}; // destructor

    //!
    const double operator[](const int i) const
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 16); 
      return data[i]; 
    }
    
    // Allows the setting of vector values through the operator[]
    double& operator[](const int i)
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 16); 
      return data[i]; 
    }

    Mat4(const double a, const double b, const double c, const double d,
    const double e, const double f, const double g, const double h,
    const double i, const double j, const double k, const double l,
    const double m, const double n, const double o, const double p
    ) 
    {
      data[0] = a;
      data[1] = b;
      data[2] = c;
      data[3] = d;
      data[4] = e;
      data[5] = f;
      data[6] = g;
      data[7] = h;
      data[8] = i;
      data[9] = j;
      data[10] = k;
      data[11] = l;
      data[12] = m;
      data[13] = n;
      data[14] = o;
      data[15] = p;
    };

    //! 
    /** Sets the components, piecewise in the vector.
     */    
    void set(const double a, const double b, const double c, const double d,
    const double e, const double f, const double g, const double h,
    const double i, const double j, const double k, const double l,
    const double m, const double n, const double o, const double p
    )
    {
      data[0] = a;
      data[1] = b;
      data[2] = c;
      data[3] = d;
      data[4] = e;
      data[5] = f;
      data[6] = g;
      data[7] = h;
      data[8] = i;
      data[9] = j;
      data[10] = k;
      data[11] = l;
      data[12] = m;
      data[13] = n;
      data[14] = o;
      data[15] = p;
    };

    //Assignment operator
    Mat4 &operator=(const Mat4 &rhs)
    {
      data[0] = rhs[0];
      data[1] = rhs[1];
      data[2] = rhs[2];
      data[3] = rhs[3];
      data[4] = rhs[4];
      data[5] = rhs[5];
      data[6] = rhs[6];
      data[7] = rhs[7];
      data[8] = rhs[8];
      data[9] = rhs[9];
      data[10] = rhs[10];
      data[11] = rhs[11];
      data[12] = rhs[12];
      data[13] = rhs[13];
      data[14] = rhs[14];
      data[15] = rhs[15];
      return *this;
    };

    //! 
    Mat4 &operator+=(const Mat4 &rhs)
    {
      data[0] += rhs[0];
      data[1] += rhs[1];
      data[2] += rhs[2];
      data[3] += rhs[3];
      data[4] += rhs[4];
      data[5] += rhs[5];
      data[6] += rhs[6];
      data[7] += rhs[7];
      data[8] += rhs[8];
      data[9] += rhs[9];
      data[10] += rhs[10];
      data[11] += rhs[11];
      data[12] += rhs[12];
      data[13] += rhs[13];
      data[14] += rhs[14];
      data[15] += rhs[15];
      return *this;
    };

    Mat4 &operator-=(const Mat4 &rhs)
    {
      data[0] -= rhs[0];
      data[1] -= rhs[1];
      data[2] -= rhs[2];
      data[3] -= rhs[3];
      data[4] -= rhs[4];
      data[5] -= rhs[5];
      data[6] -= rhs[6];
      data[7] -= rhs[7];
      data[8] -= rhs[8];
      data[9] -= rhs[9];
      data[10] -= rhs[10];
      data[11] -= rhs[11];
      data[12] -= rhs[12];
      data[13] -= rhs[13];
      data[14] -= rhs[14];
      data[15] -= rhs[15];
      return *this;
    };
    
    Mat4& operator*=(const double c)
    {
      data[0] *= c;
      data[1] *= c;
      data[2] *= c;
      data[3] *= c;
      data[4] *= c;
      data[5] *= c;
      data[6] *= c;
      data[7] *= c;
      data[8] *= c;
      data[9] *= c;
      data[10] *= c;
      data[11] *= c;
      data[12] *= c;
      data[13] *= c;
      data[14] *= c;
      data[15] *= c;
      return *this;
    };

    Mat4& operator/=(const double c)
    {
      data[0] /= c;
      data[1] /= c;
      data[2] /= c;
      data[3] /= c;
      data[4] /= c;
      data[5] /= c;
      data[6] /= c;
      data[7] /= c;
      data[8] /= c;
      data[9] /= c;
      data[10] /= c;
      data[11] /= c;
      data[12] /= c;
      data[13] /= c;
      data[14] /= c;
      data[15] /= c;
      return *this;
    };

    void setIdentity()
    {
      data[0] = 1;
      data[5] = 1;
      data[10] = 1;
      data[15] = 1;
    };

    void print()
    {
      std::cout << "[ ";
      for (int i = 0; i < 15; i++)
        std::cout << data[i] << " ";
      std::cout << "]" << std::endl;
    };

    void transpose()
    {
      Mat4 temp = *this;
      data[0] = temp[0];
      data[1] = temp[4];
      data[2] = temp[8];
      data[3] = temp[12];
      data[4] = temp[1];
      data[5] = temp[5];
      data[6] = temp[9];
      data[7] = temp[13];
      data[8] = temp[2];
      data[9] = temp[6];
      data[10] = temp[10];
      data[11] = temp[14];
      data[12] = temp[3];
      data[13] = temp[7];
      data[14] = temp[11];
      data[15] = temp[15];
    };
    
};

#endif