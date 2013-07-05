/**
 * sortpoints.exe
 * 
 * Date: 5 Juli 2013
 * Author: T. Bobek
 * Version: 0.5
 * License: GPL
 *
 * 
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


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Point3d.h"

#define NPOINTS 9

int loadfile(std::ifstream &ifs, std::vector<Point3d>& v) {
	char buffer[100]; 
	std::stringstream strstr; 
	double x = 0, y = 0, z = 0; 
	int counter=0; 
	while(ifs.getline(buffer,100)) {
		counter++; 
		strstr << buffer; 
		strstr >> x >> y >> z; 
		if (strstr.fail()) {
			std::cout << "error in line " << counter << ": " << buffer << std::endl; 
			//std::runtime_error e("input error");
			//throw e;
			return -1; 
		}
		strstr.clear(); 
		v.push_back(Point3d(x,y,z)); 
	}
	ifs.close(); 
	return 0; 
}

int main(int argc, char* argv[])
{
	int temp; 

	// check arguments
	if(argc<2) {
		std::cout << "usage: sortpoints file1 [file2]" << std::endl
			<< "  if one file is given, it sorts its contents, " << std::endl
			<< "  if a second file is given, it is sorted as well " << std::endl
			<< "  and the z-coordinate of the first is subtracted from the second " << std::endl
			<< "  one (z_2 - z_1). The input file should be ascii and have \"x y z\" in each line. " << std::endl; 
		return 0; 
	}

	std::vector<Point3d> points1; // the vector holding the points of the first file
	std::vector<Point3d> points2; // the vector holding the points of the second file
	// read input file
	std::ifstream ifs; 
	ifs.open(argv[1]); 

	temp = loadfile(ifs, points1); 
	ifs.close(); 
	if( temp<0 ) 
		return -1; 

	if(argc==3) {
		ifs.open(argv[2]); 
		temp = loadfile(ifs, points2); 
		ifs.close(); 
		if(temp<0)
			return -1; 
	}
	// sorting
	std::sort(points1.begin(),points1.end(),compare);

	// write to output file
	if(argc==3) { // only to file if 3rd arg given
		std::sort(points2.begin(),points2.end(),compare);
		temp = points1.size(); 
		if(temp!=points2.size()) {
			std::cerr << "the two files don't have the same length. " << std::endl
				<< "Operation not possible...exiting." << std::endl; 
			return -1; 
		}
		else {
			for(int i=0; i<temp; i++) {
				if((points1.at(i).x != points2.at(i).x) || (points1.at(i).y != points2.at(i).y)) {
					std::cerr << "x- or y-coordinate at line " << i << " not equal. " << std::endl
						<< "line1: " << points1.at(i).toString() << std::endl
						<< "line2: " << points2.at(i).toString() << std::endl; 
					return -1; 
				}
				std::cout << points1.at(i).x << " " << points1.at(i).y << " " << (points2.at(i).z-points1.at(i).z) << std::endl; 
			}
		}
	}
	else { // no second file 
		for(std::vector<Point3d>::iterator i=points1.begin(); i!=points1.end(); i++) {
			std::cout << i->x << " " << i->y << " " << i->z << std::endl; 
		}
	}
	
	return 0;
}

