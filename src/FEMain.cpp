//This is CS601: PA2. The questions are indicated in lines having comments bearing the question number. Fill in your answers in place. 
//When you are done filling in your answers, the code must be compilable. Code with syntax errors receive Zero. Do not change any other lines other than what is indicated in the question.

/**
 * @file FEMain.cpp
 * @brief Main program for finite element analysis using a grid of nodes and elements.
 * 
 * This program reads in node and element data, computes the stiffness matrix, 
 * and outputs results in various formats. It includes responses to assignment questions
 * regarding optimization, matrix structure, and bandwidth.
 *
 * @section Description
 * The program:
 * - Reads node and element data from files with extensions .node and .elem, based on the provided prefix.
 * - Builds the global stiffness matrix based on finite element analysis.
 * - Optimizes matrix multiplication using CBLAS (if available).
 * - Dumps matrix data to binary files for debugging.
 * - Computes the lower and upper bandwidths of the global stiffness matrix.
 * 
 * @author Nilesh.R.Barandwal
 * @date 16-11-2024
 */

#include "FEGrid.h"
#include "GridFn.h"
#include <cstdlib> // For atoi and atof
#include<vector>
#include<string>
#include<cmath>
#include <iostream>
#include <cassert> // For assert
#include<iomanip>
#include<fstream>
#include <cblas.h> // Add this for CBLAS support if available
#define K 30


using namespace std;

/**
 * @brief Main function to perform finite element calculations and output results.
 * 
 * @param argc Argument count (should be 2 for node and element file inputs).
 * @param argv Argument values (expects a file prefix as the argument).
 * @return int Status code (0 for success, 1 for error).
 *
 * @note The input files should have the `.node` and `.elem` extensions based on the provided prefix.
 */

int main(int argc, char** argv) {
  // Check for correct number of arguments
  if(argc != 2)
    {
      cout << "this program takes just one argument that is the common name prefix of .node and .elem files. (Note: do not give the file extension) ";
      return 1;
    }
  string prefix(argv[1]);
  string nodeFile = prefix+".node";
  string eleFile  = prefix+".elem";
  string q3Answer, q4AnswerA, q4AnswerB;

  // Initialize the FEGrid object with node and element files
  FEGrid grid(nodeFile, eleFile);

  //get the total number of nodes and interior nodes 
  int numInteriorNodes = grid.getNumInteriorNodes();
  int numNodes = grid.getNumNodes();

  //Global stiffness matrix stores the Kij values of all interior nodes.
  //The globalMatrixIndex array stores the index of the interior node in the global matrix
  int* globalMatrixIndex = (int*)malloc(sizeof(int)*numNodes);
  int interiorNodeIndex=0;

  // Map interior nodes to globalMatrixIndex
  for(int i=0;i<numNodes;i++) {
  	const Node& n = grid.node(i);
	if(n.isInterior())
		globalMatrixIndex[i]=interiorNodeIndex++;
	else
		globalMatrixIndex[i]=-1;
  }

  // Allocate global stiffness matrix (globalK)
  double *globalK=(double *)malloc(sizeof(double)*numInteriorNodes*numInteriorNodes);
  memset(globalK, 0, sizeof(double)*numInteriorNodes*numInteriorNodes);
  double kij[VERTICES*VERTICES]; //for storing B^T * C * B
  double kijpartial[VERTICES*VERTICES]; //for storing B^T * C
  double cMatrix[DIM*2]={K, 0, 0, K};

  /**
     * @brief Poisson operator over the grid elements to compute element matrices.
     * 
     * This loop iterates over all grid elements, computes the stiffness matrix for each element,
     * and assembles the global stiffness matrix.
     */

  //Poisson operator over the grid elements
  for(int i=0;i<grid.getNumElts();i++) {
	Element e=grid.element(i);
	//first count the number of interior nodes in the element e.
	std::vector<int> elementInteriorNodeID;
	for(int j=0;j<VERTICES;j++) {
		const Node& n= grid.getNode(i, j);
		if(n.isInterior()) {
			//storing nodeLocal number of the interior node of the element.
			elementInteriorNodeID.push_back(j); 
		}
	}
	int numInteriorNodesOfElement = elementInteriorNodeID.size();

	//allocate storage for gradient of shape functions for each interior node/vertex of the element 
	double* bMatrixTrans=(double *)malloc(sizeof(double)*numInteriorNodesOfElement*DIM);
	//get gradient of the shape functions for all interior nodes of the element.
	for(int j=0;j<numInteriorNodesOfElement;j++)		
			grid.gradient(bMatrixTrans+j*DIM, i, elementInteriorNodeID[j]);
#ifndef CBLAS_DGEMM
	//compute B^T * C (3x2 * 2x2) OR (2x2 * 2x2) or (1x2 * 2x2)
	for(int m=0;m<numInteriorNodesOfElement;m++) {
		for(int n=0;n<DIM;n++) {
  			kijpartial[m*DIM+n]=0.;
			for(int r=0;r<DIM;r++)
				kijpartial[m*DIM+n] = kijpartial[m*DIM+n]+bMatrixTrans[m*DIM+r] * cMatrix[r*DIM+n];
		}
	}
#else
	//https://www.intel.com/content/www/us/en/develop/documentation/mkl-tutorial-c/top/multiplying-matrices-using-dgemm.html
	/*Q1: if you had access to the CBLAS library routine cblas_dgemm, you can rewrite lines 70-76 by a single line that calls the cblas_dgemm routine. 
	 *Write how you would achieve the equivalentof 70-76 using cblas_dgemm routine. Make sure that you do not have syntax errors. You must make a call to the BLAS routine (i.e. not write your answer in double quotes).
	 */

	/**
	* @brief Q1. Use CBLAS to perform matrix multiplication for B^T * C. 
	* Replaces lines 70-76 by calling the CBLAS function `cblas_dgemm` to compute `kijpartial = B^T * C`.
	*
	* This single line performs the matrix multiplication for `B^T * C` efficiently using the CBLAS library to optimize performance.
	*/

    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, numInteriorNodesOfElement, DIM, DIM, 1.0, bMatrixTrans, DIM, cMatrix, DIM, 0.0, kijpartial, DIM);
#endif

		/**
	* @brief Q1. Use CBLAS to perform matrix multiplication for B^T * C. 
	* Replaces lines 70-76 by calling the CBLAS function `cblas_dgemm` to compute `kijpartial = B^T * C`.
	*
	* This single line performs the matrix multiplication for `B^T * C` efficiently using the CBLAS library to optimize performance.
	*/
	
	//Q2: Write routine to dump kijpartial in a file called kijdump.bin here (in binary format)
	
	/**
         * @brief Q2: Dump kijpartial matrix data to a binary file named "kijdump.bin".
         * 
         * This routine writes the kijpartial matrix in binary format for debugging purposes.
         */

	std::ofstream kijdumpFile("kijdump.bin", std::ios::binary);
    kijdumpFile.write(reinterpret_cast<const char*>(kijpartial), sizeof(double) * VERTICES * VERTICES);
    kijdumpFile.close();

	//creating B from B^T	
	double *bMatrix=(double *)malloc(sizeof(double)*DIM*numInteriorNodesOfElement);
	for(int m=0;m<DIM;m++)
		for(int n=0;n<numInteriorNodesOfElement;n++)
			bMatrix[m*numInteriorNodesOfElement+n]=bMatrixTrans[n*DIM+m];
			
	free(bMatrixTrans);

	//multiplying with B.
	for(int m=0;m<numInteriorNodesOfElement;m++) {
		for(int n=0;n<numInteriorNodesOfElement;n++) {
  			kij[m*numInteriorNodesOfElement+n]=0.;
			for(int r=0;r<DIM;r++)
				kij[m*numInteriorNodesOfElement+n] = kij[m*numInteriorNodesOfElement+n] + kijpartial[m*DIM+r] * bMatrix[r*numInteriorNodesOfElement+n];
		}
  	}

	free(bMatrix);


  	//Insert element matrix contents into global Matrix
	for(int m=0;m<numInteriorNodesOfElement;m++) {
			int nodeGlobalNumber = e[elementInteriorNodeID[m]];
			assert(globalMatrixIndex[nodeGlobalNumber] !=-1);
			int rowNumber = globalMatrixIndex[nodeGlobalNumber];
			for(int n=0;n<numInteriorNodesOfElement;n++) {
				int colNumber = globalMatrixIndex[e[elementInteriorNodeID[n]]];
				globalK[rowNumber*numInteriorNodes+colNumber] +=kij[m*numInteriorNodesOfElement+n];
		}
	}	
  }

	/*Q3: What is the structure of the global matrix globalK? Choose your option from: 1) Tridiagonal 2) Diagonal 3) BiDiagonal 4) Banded 5) Upper Hessenberg 6) Lower Hessenberg
	 * Write your answer (as a string that exactly matches one of the options above.) in the space provided below.*/

	/**
     * @brief Q3: Determine the structure of the global matrix `globalK`.
     * 
     * The structure of the global stiffness matrix `globalK` is assessed based on the pattern of non-zero elements.
     * - Options: 1) Tridiagonal 2) Diagonal 3) BiDiagonal 4) Banded 5) Upper Hessenberg 6) Lower Hessenberg
     */
  	q3Answer="Banded";
	  

	/**
     * @brief Q4: Compute the lower and upper bandwidth of the matrix `globalK`.
     * 
     * - Part A: Lower Bandwidth
     * - Part B: Upper Bandwidth
     */
  	q4AnswerA="2";
  	q4AnswerB="2";

	cout<<q3Answer<<endl;
	cout<<"Lower Bandwidth: "<<q4AnswerA<<endl;
	cout<<"Upper Bandwidth: "<<q4AnswerB<<endl;

#ifdef DEBUG

	/**
     * @brief If DEBUG is defined, write the global matrix into a file for visualization.
     * 
     * This section outputs the global stiffness matrix to a file for debugging purposes.
     */
			
  	//write the global matrix into a file for visualization.
	ofstream myoutputfile;
	myoutputfile.open("GlobalKMatrixFile.txt");
	for(int m=0;m<numInteriorNodes;m++) {
		for(int n=0;n<numInteriorNodes;n++){
				myoutputfile<<globalK[m*numInteriorNodes+n];
				if(n!=numInteriorNodes-1)
					myoutputfile<<" ";
				else
					myoutputfile<<"\n";
		}
	}
#endif
	
	//Jacobi solver goes here.
  
  return 0;
  
}
