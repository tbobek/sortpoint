/*
	This file is part of sortpoints.

    sortpoints is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    sortpoints is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __POINT3D_H_ 
#define __POINT3D_H_

#include <algorithm>
#include <vector>
#include <string>
#include <strstream>



class Point3d
{
public:
	double x, y, z; 

	Point3d(void);
	Point3d(double _x, double _y, double _z) { x=_x; y=_y; z=_z; }
	

	std::string toString() {
		std::ostrstream ostr; 
		ostr << "(" << x << "," << y << "," << y << ")" << std::ends; 
		return ostr.str(); 
	}
};

bool compare(Point3d const &a, Point3d const &b);

#endif