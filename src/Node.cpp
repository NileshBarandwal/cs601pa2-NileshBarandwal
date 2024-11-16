//acknowledgement: cs294-73 colella@eecs.berkeley.edu

/**
 * @file Node.cpp
 * @brief Implementation of the Node class for representing nodes in the finite element grid.
 * 
 * This file contains methods for managing the properties of nodes, including their positions
 * in the grid and whether they are interior or boundary nodes.
 * 
 * Acknowledgement: cs294-73 colella@eecs.berkeley.edu
 */

#include <cstdio>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <vector>
#include "Node.h"
using namespace std;

/**
 * @brief Default constructor for the Node class.
 * 
 * Initializes the node with a position set to a large value (`FLT_MAX`), indicating 
 * an uninitialized state. Also sets the node as an interior node by default with an 
 * invalid interior node ID (`-1`).
 */

Node::Node()
{
  for (int idir = 0;idir < DIM;idir++)
    {
      m_position[idir] = FLT_MAX;
    }
  m_isInterior = true;
  m_interiorNodeID = -1;
};
  
/**
 * @brief Constructor for the Node class that initializes the node with a specified position.
 * 
 * Initializes the node with a given position in space, an interior node ID, and a flag indicating
 * whether the node is an interior node or not.
 * 
 * @param a_position An array representing the position of the node in space (with DIM dimensions).
 * @param a_interiorNodeID The ID of the node if it is an interior node. It is set to -1 if the node is on the boundary.
 * @param a_isInterior A boolean flag indicating whether the node is an interior node (true) or a boundary node (false).
 */

Node::Node(double a_position[DIM],
           const int& a_interiorNodeID,
           const bool& a_isInterior)
{
  for (int idir = 0;idir < DIM;idir++)
    {
      m_position[idir] = a_position[idir];
    }

  m_isInterior = a_isInterior;

  m_interiorNodeID = a_interiorNodeID;
};

/**
 * @brief Gets the position of the node.
 * 
 * This function retrieves the position of the node and stores it in the provided array.
 * 
 * @param a_x An array where the node's position will be stored (with DIM dimensions).
 */

void Node::getPosition(double a_x[DIM]) const
{
  for (int idir=0;idir < DIM; idir++)
    {
      a_x[idir] = m_position[idir];
    }
};

/**
 * @brief Gets the interior node ID.
 * 
 * This function returns the ID of the node if it is an interior node. If the node is on the boundary,
 * this ID will typically be invalid (e.g., -1).
 * 
 * @return const int& The interior node ID.
 */

const int& Node::getInteriorNodeID() const
{
  return m_interiorNodeID;
};

/**
 * @brief Checks if the node is an interior node.
 * 
 * This function returns a boolean value indicating whether the node is an interior node.
 * 
 * @return const bool& A boolean value indicating whether the node is an interior node (true) or not (false).
 */

const bool& Node::isInterior() const
{
  return m_isInterior;
};


  
