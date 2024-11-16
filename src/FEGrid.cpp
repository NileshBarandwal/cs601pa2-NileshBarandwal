//acknowledgement: cs294-73 colella@eecs.berkeley.edu
/**
 * @file FEGrid.cpp
 * @brief Implementation of the FEGrid class for managing finite element grid data.
 * 
 * This file contains methods for handling the grid's nodes and elements, including
 * methods for calculating gradients of shape functions, element areas, and accessing 
 * node and element data.
 * 
 * Acknowledgement: cs294-73 colella@eecs.berkeley.edu
 */
#include <cstdio>   
#include <cmath>    
#include <cstring>  
#include <cassert>  
#include <vector>
#include <fstream>
#include<iostream>
#include<iomanip>
#include<limits>
#include "Node.h"   
#include "Element.h"
#include "FEGrid.h"

/**
 * @brief Default constructor for the FEGrid class.
 * 
 * Initializes an empty grid with zero interior nodes.
 */
FEGrid::FEGrid(): m_numInteriorNodes(0)
{
}

/**
 * @brief Constructor for the FEGrid class that initializes the grid using node and element files.
 * 
 * This constructor reads the node and element data from the specified files and initializes
 * the grid's nodes and elements. It also counts the number of interior nodes.
 * 
 * @param a_nodeFileName The name of the file containing the node data.
 * @param a_elementFileName The name of the file containing the element data.
 */
FEGrid::FEGrid(const std::string& a_nodeFileName, const std::string& a_elementFileName) {
  // Read node data from file
  ifstream nodes(a_nodeFileName.c_str());
  int ncount;
  nodes>>ncount;

  m_nodes.resize(ncount);
  m_numInteriorNodes= 0;
  for(int i=0; i<ncount; i++)
    {
      int vertex;
      std::string tmp[DIM];
      double x[DIM];
      bool isInterior=true;
      nodes>>vertex>>tmp[0]>>tmp[1];
      x[0]=atof(tmp[0].c_str());
      x[1]=atof(tmp[1].c_str());

      // Check if the node is on the boundary
      if(((tmp[0].compare("0.60000"))==0) || ((tmp[1].compare("0.40000"))==0) || (x[0] == 0) || (x[1] == 0)) {
	isInterior = false;
	//printf("Node ID:%d is on Boundary\n",vertex);
	}
	else
  		m_numInteriorNodes++;
      
      vertex--;
      m_nodes[vertex] = Node(x,vertex, isInterior);
    }
  
  // Read element data from file
  ifstream elements(a_elementFileName.c_str());
  int ncell;
  elements>>ncell;
  int vert[VERTICES];
  m_elements.resize(ncell);
  for(int i=0; i<ncell; i++)
    {
      int cellID;
      elements>>cellID>>vert[0]>>vert[1]>>vert[2];
      vert[0]--; vert[1]--; vert[2]--;
      cellID--;
      m_elements[cellID] = Element(vert);
    }
}

/**
 * @brief Calculates the gradient of shape functions (N1, N2, N3) for a given element.
 * 
 * This function computes the gradient of the shape functions for a triangular element in 2D.
 * It calculates the gradient based on the positions of the element's nodes.
 * 
 * @param a_gradient The output array that will store the gradient of the shape functions.
 * @param a_eltNumber The element number for which the gradient is computed.
 * @param a_nodeNumber The local node number within the element for which the gradient is calculated.
 */
//returns the gradient of shape functions N1 N2 N3.
void FEGrid::gradient(double a_gradient[DIM],
		      const int& a_eltNumber, 
		      const int& a_nodeNumber) const
{
  const Element& e = m_elements[a_eltNumber];
  const Node& n=m_nodes[e[a_nodeNumber]];
  //assert(n.isInterior()); //make sure that you are computing it for interior node only.
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];
  for (int ivert = 0;ivert < VERTICES-1; ivert++)
    {
      int otherNodeNumber = e[(a_nodeNumber + ivert+1)%VERTICES];
      m_nodes[otherNodeNumber].getPosition(dx[ivert]);
      for (int idir = 0;idir < DIM;idir++)
        {
          dx[ivert][idir] -=xbase[idir];
        }
    }        
  
  // WARNING: the following calculation is correct for triangles in 2D *only*.
  double det = dx[0][0]*dx[1][1] - dx[1][0]*dx[0][1];
  
  a_gradient[0] = (-(dx[1][1] - dx[0][1])/det);
  a_gradient[1] = (-(dx[1][0] - dx[0][0])/det);

}

/**
 * @brief Calculates the area of an element.
 * 
 * This function calculates the area of a triangular element in 2D using the node positions.
 * 
 * @param a_eltNumber The element number for which the area is calculated.
 * @return double The area of the element.
 */
double FEGrid::elementArea(const int& a_eltNumber) const
{
  const Element& e = m_elements[a_eltNumber];
  const Node& n=m_nodes[e[0]];
  double xbase[DIM];
  n.getPosition(xbase);
  double dx[VERTICES-1][DIM];
  for (int ivert = 1;ivert < VERTICES; ivert++)
    {
      int otherNodeNumber = e[ivert];
      m_nodes[otherNodeNumber].getPosition(dx[ivert-1]);
      for (int idir = 0;idir < DIM;idir++)
        {
          dx[ivert-1][idir] -=xbase[idir];
        }
    }        
  
  // WARNING: the following calculation is correct for triangles in 2D *only*.
  double area = fabs(dx[0][0]*dx[1][1] - dx[1][0]*dx[0][1])/2;
  return area;
}

/**
 * @brief Gets a node from a specific element by local node number.
 * 
 * This function retrieves a node from a given element using its local node number.
 * 
 * @param a_eltNumber The element number.
 * @param a_localNodeNumber The local node number within the element.
 * @return const Node& The node corresponding to the local node number in the specified element.
 */
const Node& FEGrid::getNode(const int& a_eltNumber,const int& a_localNodeNumber) const
{
  return m_nodes[m_elements[a_eltNumber][a_localNodeNumber]];
}

/**
 * @brief Gets the number of elements in the grid.
 * 
 * This function returns the total number of elements in the grid.
 * 
 * @return int The number of elements.
 */
int FEGrid::getNumElts() const
{
  return m_elements.size();
}

/**
 * @brief Gets the number of nodes in the grid.
 * 
 * This function returns the total number of nodes in the grid.
 * 
 * @return int The number of nodes.
 */
int FEGrid::getNumNodes() const
{
  return m_nodes.size();
}

/**
 * @brief Gets the number of interior nodes in the grid.
 * 
 * This function returns the total number of interior nodes in the grid (not on the boundary).
 * 
 * @return int The number of interior nodes.
 */
int FEGrid::getNumInteriorNodes() const
{
  return m_numInteriorNodes;
}

/**
 * @brief Retrieves an element from the grid by its index.
 * 
 * This function returns a reference to the element at the specified index.
 * 
 * @param i The index of the element.
 * @return const Element& The element at the specified index.
 */
const Element& FEGrid::element(int i) const
{
  return m_elements[i];
}

/**
 * @brief Retrieves a node from the grid by its index.
 * 
 * This function returns a reference to the node at the specified index.
 * 
 * @param i The index of the node.
 * @return const Node& The node at the specified index.
 */
const Node& FEGrid::node(int i) const
{
  return m_nodes[i];
}
