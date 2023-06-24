#include "happly.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
#define R1 1 // number of rows in Matrix-1
#define C1 4 // number of columns in Matrix-1
#define R2 4 // number of rows in Matrix-2
#define C2 4 // number of columns in Matrix-2


double mulMat(double mat1[][C1], double mat2[][C2], double rslt[R1][C2])
{
    
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i][j] = 0;
  
            for (int k = 0; k < R2; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
 
    }
}

double displacement(std::vector<std::array<double, 3>> vPos, double xDisplacement, double yDisplacement, double zDisplacement, double rslt[R1][C2]) {
	for (int i = 0; i < vPos.size(); i++) {
		rslt[i][0] = vPos[i][0] + xDisplacement;
		rslt[i][1] = vPos[i][1] + yDisplacement;
		rslt[i][2] = vPos[i][2] + zDisplacement;
	}

}
double rotationOperationYAxis (std::vector<std::array<double, 3>> vPos, double degrees, double rslt[R1][C2]) {
	
	double radian = degrees*3.14159/180;
	double data[1][4] = {0,0,0,1};
	double result[1][4] = {0,0,0,1};
	double rotationMatrix[4][4] = {{cos(radian),0,-sin(radian),0}, {0,1,0,0},{sin(radian),0,cos(radian),0},{0,0,0,1}};
	
	for (int i = 0; i < vPos.size(); i++) {
		data[0][0] = vPos[i][0];
		data[0][1] = vPos[i][1];
		data[0][2] = vPos[i][2];
		mulMat(data, rotationMatrix, result);
		rslt[i][0] = result[0][0];
		rslt[i][1] = result[0][1];
		rslt[i][2] = result[0][2];
		rslt[i][3] = result[0][3];
	}
}
double translationOperation (std::vector<std::array<double, 3>> vPos, double Dx, double Dy, double Dz, double rslt[R1][C2]) 
{
	double data[1][4] = {0,0,0,1};
	double result[1][4] = {0,0,0,1};
	double translationMatrix[4][4] = {{1,0,0,0}, {0,1,0,0},{0,0,1,0},{Dx,Dy,Dz,1}};

	for (int i = 0; i < vPos.size(); i++) {
		data[0][0] = vPos[i][0];
		data[0][1] = vPos[i][1];
		data[0][2] = vPos[i][2];
		mulMat(data, translationMatrix, result);
		rslt[i][0] = result[0][0];
		rslt[i][1] = result[0][1];
		rslt[i][2] = result[0][2];
		rslt[i][3] = result[0][3];
	}

}

int main() {

	
	// Construct a data object by reading from file
	happly::PLYData plyIn("Arne (001) (1).ply");

	// Get mesh-style data from the object
	std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
	std::vector<std::array<unsigned char, 3>> vCol = plyIn.getVertexColors();
	//cout<< vPos[30]<<endl;
	//cout<< typeid(vPos).name() << endl;
	//cout<< vPos[0] << endl;
	//double data[1][3] = vPos[9];  ERROR!!!
	//cout<< vPos[0][0] << endl;
	//cout << vPos.size() << endl;


	// Let's do translation, rotation and displacement operations. Define parameters
	double dx = 20;
	double dy = 4;
	double dz = 60;
	double lambda = 45; // for rotation in Y-axis
	double displacementX = 0;
	double displacementY = -0.90;
	double displacementZ = 1;

	double rslt[vPos.size()][C2];
	translationOperation(vPos, dx,dy,dz, rslt);
	rotationOperationYAxis(vPos, lambda, rslt); // let's rotate in the y-axis for 45 degrees
	displacement(vPos, displacementX, displacementY, displacementZ, rslt);


	// After the operations are done, convert the 2D doublearrays to std::array<double,3>
	std::vector<std::array<double, 3>> translatedVertex;
	for (int i = 0; i < vPos.size(); i++) {
		std::array<double, 3> res = {rslt[i][0], rslt[i][1], rslt[i][2]};
		translatedVertex.push_back(res);
	} 

	// and now write the resultant point cloud to a PLYData format
	happly::PLYData plyOut;
	// Add mesh data (elements are created automatically)
	plyOut.addVertexPositions(translatedVertex);
	plyOut.addVertexColors(vCol);

	plyOut.write("translated_and_rotated_displaced.ply", happly::DataFormat::ASCII);



	struct {
	  float x;
	  float y;
	  float z;
	  int R;
	  int G;
	  int B;
	  int A;
	} pointStruct;

	struct {
	  struct {
	  float x;
	  float y;
	  float z;
	  int R;
	  int G;
	  int B;
	  int A;
	} pointStruct[111431];
	} pointCloudStruct;





	
}