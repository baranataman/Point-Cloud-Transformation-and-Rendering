# Point-Cloud-Transformation-and-Rendering
C++  project for manipulating volumetric data. Load the provided point cloud file and apply different 3D transformations to the point cloud: Translation, rotation and displacement

1) To compile the code, you can simply run the command:
	g++ main.cpp happly.h -o main

And to execute it, just type

	./main


2) This code takes a .ply file, reads the data and then applies translation, rotation and displacement operations.

You can examine the methods, and also give different parameters as you wish. I save the resultant point cloud after all the operations. But I also prepared the result of only translation, the result of translation and rotation and the result of all 3 operations.

Their rendered images are also included with the relevant file names.

The parameters for the exampler operations are:

- Dx = 20, Dy = 4, Dz = 60 for the translation operation
- lamda = 45 degrees around the y-axis
- displacement in the: x-axis = 0,  y-axis = -0.9, z-axis = 1.0
