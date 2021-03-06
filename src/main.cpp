#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#define _USE_MATH_DEFINES

#include <math.h>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"
#include "shapes/sphere.h"
#include "cameras/ortographic.h"
#include "cameras/perspective.h"

void transformationsExercise()
{
    /* *************** */
    /* TRANSFORMATIONS */
    /* *************** */
    std::string separator     = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";

    std::cout << separatorStar << "Construct and visualize transforms" << separatorStar << std::endl;

    // Identity Matrix
    Matrix4x4 idMat; // By default, a matrix4x4 is initialized with the identity matrix
    std::cout << "The content of matrix idMat is: \n" << std::endl;
    std::cout << idMat << separator << std::endl;

    // Translation Matrix
    double deltaX, deltaY, deltaZ;
    deltaX = 1; deltaY = -2; deltaZ = 3;
    Vector3D delta(deltaX, deltaY, deltaZ);
    Matrix4x4 translationMat = Matrix4x4::translate(delta);
    std::cout << "The content of matrix translationMat is: \n" << std::endl;
    std::cout << translationMat << separator << std::endl;

    // Scale Matrix
	double Sx, Sy, Sz;
	Sx = 2; Sy = 1; Sz = -1;
	Vector3D scaleVect(Sx, Sy, Sz);
	Matrix4x4 scaleMatrix = Matrix4x4::scale(scaleVect);
	std::cout << "The content of matrix scaleMatrix is: \n" << std::endl;
    std::cout << scaleMatrix << separator << std::endl;

    // Rotate around X Matrix
    double angleInDegrees = 60;
    double thetaInRadians = Utils::degreesToRadians(angleInDegrees);
	Matrix4x4 rotateXMatrix = Matrix4x4::rotate(thetaInRadians, Vector3D(1, 0, 0));
	std::cout << "The content of matrix rotateXMatrix is: \n" << std::endl;
    std::cout << rotateXMatrix << separator << std::endl;

    // Rotate around an arbitrary axis Matrix
	double angleTorotate = 30;
	double angleTorotateinDegrees = Utils::degreesToRadians(angleTorotate);
	Matrix4x4 rotateArbitraryAxisMatrix = Matrix4x4::rotate(angleTorotateinDegrees, Vector3D(1, 1, 1));
	std::cout << "The content of matrix rotateArtitraryAxisMatrix is: \n" << std::endl;
    std::cout << rotateArbitraryAxisMatrix << separator << std::endl;

    // Transposed and Inversion
    std::cout << separatorStar << "Inverting and Transposing a Matrix" << separatorStar << std::endl;
    Matrix4x4 translationMatTransposed;
    translationMat.transpose(translationMatTransposed);
    std::cout << "The transpose of matrix \n\n" << translationMat << "\n is \n\n"
              << translationMatTransposed << separator << std::endl;

    Matrix4x4 inverseTranslationMat;
    //(...)
	translationMat.inverse(inverseTranslationMat);
    std::cout << "The inverse of matrix \n\n" << translationMat << "\n is \n\n" << inverseTranslationMat << std::endl;
    std::cout << "And their multiplication should thus give the identity matrix:\n\n";
	Matrix4x4 newIdMax = inverseTranslationMat * translationMat;
	std::cout << "The content of multiplicacion is: \n" << std::endl;
	std::cout << newIdMax << separator << std::endl;

    // Combine here some transforms, and visualize the result
    std::cout << separatorStar << "Combine transforms and visualize the result" << separatorStar << std::endl;

    Matrix4x4 scaleTranslate = scaleMatrix * translationMat;
    std::cout << "The content of matrix scaleTranslate is: \n" << std::endl;
    std::cout << scaleTranslate << separator << std::endl;

    Matrix4x4 translateScale = translationMat * scaleMatrix;
    std::cout << "The content of matrix translateScale is: \n" << std::endl;
    std::cout << translateScale << separator << std::endl;
}

void normalTransformExercise()
{
    std::string separator = "\n----------------------------------------------\n";

    // NOTE: points, vectors and normals are represented, in this framework, using
    //  the Vector3D class. It is up to the programmer to take care of whether the
    //  Vector3D is representing a point, a vector or a normal. For example, when
    //  applying a transform using a Matrix4x4, the programmer must choose which
    //  "applyTransform" method of the namespace Matrix4x4 should be used.

    Vector3D v(1, 1, 0);
    Vector3D n(-1.0/sqrt(2), 1.0/sqrt(2), 0);
    Matrix4x4 S = Matrix4x4::scale(Vector3D(2, 1, 1));

    std::cout << "Vector v = " << v << "\n" << std::endl;
    std::cout << "Normal n = " << n << "\n" << std::endl;
    std::cout << "Scale Matrix: \n" << std::endl;
    std::cout << S << std::endl;

    Vector3D vTransformed = S.transformVector(v);
    std::cout << "Vector v\' = " << vTransformed << "\n" << std::endl;

	Vector3D nTransformed = S.transformVector(n);
	std::cout << "Vector n\' = " << nTransformed << "\n" << std::endl;

	double dotProd = dot(nTransformed, vTransformed);
	std::cout << "dot (n\',v\') = " << dotProd << "\n" << std::endl;

	Matrix4x4 transInvMat;
	Matrix4x4 transMat;
	S.transpose(transMat);
	transMat.inverse(transInvMat);
	Vector3D nGoodTransformed = transInvMat.transformVector(n);
	std::cout << "Vector n\' = " << nGoodTransformed << "\n" << std::endl;

	double goodDotProd = dot(nGoodTransformed, vTransformed);
	std::cout << "dot (n\',v\') = " << goodDotProd << "\n" << std::endl;
}

void paintingAnImageExercise()
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
	float pndcx = 0;
	float pndcy = 0;
    Film film(resX, resY);

    for(unsigned int col = 0; col < resX; col++)
        {
            for(unsigned int row = 0; row < resY; row++)
            {
				pndcx = (col + 0.5) / resX;
				pndcy = (row + 0.5) / resY;
				Vector3D color(pndcx,pndcy,0);
				film.setPixelValue(col, row, color);
            }
        }

    // Save the final result to file
    film.save("happyColours");
}

void generateSphere(int radius, int centerX, int centerY, Film * f1) {

	for (int lin = 0; lin<f1->getHeight(); lin++)
	{
		for (int col = 0; col<f1->getWidth(); col++)
		{
			// Use the equation of the sphere to determine the pixel color
			if ((lin - centerX)*(lin - centerX) + (col - centerY)*(col - centerY) < radius*radius)
				f1->setPixelValue(col, lin, Vector3D(1, 1, 0));
		}
	}
	f1->save("original");
}

void filteringAnImageExercise(bool isGaussian)
{
    // Create two instances of the film class with the same resolution
    int resX, resY;
    resX = 512;
    resY = 512;
    Film f1(resX, resY);
    Film f2(resX, resY);

    // Create the original image
    //  Draw a circle centered at centerX, centerY (in pixels, image space)
    //   and with ray r (also in pixels)
    int centerX = resX * .5;
    int centerY = resY * .5;
    int r = std::min(centerX, centerY)*.5;
	//Function to generate a sphere in the Film passed by Pointer
	generateSphere(r,centerX,centerY,&f1);

    // Filter-related variables
    // Declare here your filter-related variables
	int z, w;
	int iter = 20;
	const int fSize = 9;
	float avg = 0;
	int radius = fSize*0.5;
	int ilin, icol, flin, fcol;
	float weigh, gCte, edivisor;
	float gaus[fSize][fSize];
	weigh = 1.0;

	if (isGaussian) 
	{
		edivisor = 2 * radius * radius;
		gCte = 1 / ( edivisor * M_PI);

		for (int x = 0; x < fSize; x++)
			for (int y = 0; y < fSize; y++)
				gaus[x][y] = gCte * exp((pow(x - radius, 2) + pow(y - radius, 2)) / edivisor);
	}

	Film * aux1, * aux2,* aux3;
	aux1 = &f1;
	aux2 = &f2;
	Vector3D pColor = Vector3D();
	
	//GABRIELA'S and ISAAC'S and WAY
	for(int i = 0; i < iter;i++){
		ilin = icol = flin = fcol = radius;
		for (int lin = 0; lin<resX; lin++){
			
			if( lin <= radius ){
				ilin = lin;
			}
			else if( lin + radius > resX -1){
				flin = resX - lin - 1;
			}
			icol = fcol = radius;
			for (int col = 0; col<resY; col++){
				if( col <= radius ){
					icol = col;
				}
				else if( col + radius > resY -1 ){
					fcol = resY - col -1;
				}
				w = -1;
    			for (int x = lin - ilin; x <= (lin + flin); x++){
					z = -1;
					w++;
    				for (int y = col - icol; y <= (col + fcol); y++){
						z++;
						if (isGaussian) weigh = gaus[w][z];
						pColor += aux1->getPixelValue(x, y) * weigh;
						avg += weigh;
    				}
    			}
    			pColor /= avg;
    			aux2->setPixelValue(lin, col, pColor);
    			pColor -= pColor;
				avg = 0.0;
			}
		}
		aux3 = aux1;
		aux1 = aux2;
		aux2 = aux3;
	}

	aux1->save((isGaussian) ? "GaussianBluredImage" : "BluredImage");
}

Sphere createSphere() {
	Matrix4x4 objectToWorld = Matrix4x4();
	objectToWorld = objectToWorld.translate(Vector3D(0, 0, 3));
	double sRadius = 1.0;
	return Sphere(sRadius, objectToWorld);
}

void printColision(bool impact, string number) 
{
	std::cout << "El rayo " << number;
	
	if (!impact)
		std::cout << " no";

	std::cout << " intersecta" << std::endl;
}

void completeSphereClassExercise()
{
    // Make your intersection tests here
    // (....)
	
	Sphere sphere = createSphere();

	std::cout << sphere.toString() << std::endl;

	Ray r1 = Ray(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
	Ray r2 = Ray(Vector3D(0, 0, 0), Vector3D(0, 1, 0));

	printColision(sphere.rayIntersectP(r1), "1");
	printColision(sphere.rayIntersectP(r2), "2");
}

void eqSolverExercise(double A, double B, double C)
{
    EqSolver solver;
    rootValues roots;

    // (...)
    bool hasRoots = solver.rootQuadEq(A, B, C, roots);

    if(!hasRoots)
    {
        std::cout << "Equation has no real roots!" << std::endl;
    }
    else
    {
        // SHOW THE SOLUTIONS OF THE EQUATION
        // (...)
		std::cout << "Equation has the following solutions:" <<std::endl;
		for (int i = 0; i < roots.nValues; i++) {
			std::cout << "t" << i << ": "<< roots.values[i] << std::endl;
		}
    }
}

void raytrace(bool option )
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);

	Vector3D color = Vector3D();
	Sphere sphere = createSphere();

    /* ******************* */
    /* Orthographic Camera */
    /* ******************* */
    Matrix4x4 cameraToWorld; // By default, this gives an ID transform
                             // meaning that the camera space = world space
    OrtographicCamera camOrtho(cameraToWorld, film);
    /* ******************* */
    /* Perspective Camera */
    /* ******************* */
    double fovRadians = Utils::degreesToRadians(60);
    PerspectiveCamera camPersp(cameraToWorld, fovRadians, film);

	Camera *camera;

	if (option)
		camera = &camPersp;
	else 	
		camera = &camOrtho;

	for (size_t i = 0; i < resX; ++i)
		for (size_t j = 0; j < resY; ++j)
		{
			color.x = sphere.rayIntersectP(camera->generateRay((i+.5)/resX, (j+.5)/resY));
			film.setPixelValue(i, j, color);
		}

    film.save((option ? "Perspective" : "Ortographic") + (string) " Camera");
}

int main()
{
    std::string separator = "\n----------------------------------------------\n";

    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // ASSIGNMENT 1
    //transformationsExercise();
    //normalTransformExercise();
    //paintingAnImageExercise();
    filteringAnImageExercise(0);

    // ASSIGNMENT 2
    //eqSolverExercise(4,0,1);
    //completeSphereClassExercise();
    //raytrace(0); //Perspective

    return 0;
}
