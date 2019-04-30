/*
 *  test_pngWrite.cpp
 *
 *  Created by Pete Willemsen on 10/6/09.
 *  Copyright 2009 Department of Computer Science, University of Minnesota-Duluth. All rights reserved.
 *
 * This file is part of CS5721 Computer Graphics library (cs5721Graphics).
 *
 * cs5721Graphics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cs5721Graphics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with cs5721Graphics.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdlib>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Random.h"
#include "Vector3D.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);

  float u, v, z, r, g, b, imagePlaneWidth = 0.5;

  //compute left, bottom and top, right
  float left = -1 * imagePlaneWidth/2;
  float right = imagePlaneWidth/2;

  // since the image is square and to be simpler
  float top = right;
  float bottom = left;

  //
  // Create image
  //
  int w = args.width, h = args.height;
  
  png::image< png::rgb_pixel > imData( w, h );
  for (size_t y = 0; y < imData.get_height(); ++y)
    {
      for (size_t x = 0; x < imData.get_width(); ++x)
	{
        u = left + (right - left) * (x + 0.5)/imData.get_width();
        v = bottom + (top - bottom) * (y + 0.5)/imData.get_height();
        z = 0.5;

        std::cout << u << " " << v << " " << std::endl;

        if (u < 0)
            u = 0;
        if (v < 0)
            v = 0;

        r = u * 255;
        g = v * 255;
        b = (u*u - v*v) * 255;
	  // non-checking equivalent of image.set_pixel(x, y, ...);
	  imData[y][x] = png::rgb_pixel(r, g, b);
	}
    }
  imData.write( "red_DualLoop.png" );

  exit(EXIT_SUCCESS);
}


