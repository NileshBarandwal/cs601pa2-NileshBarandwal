//acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _NODE_H_
#define _NODE_H_
#define DIM 2 ///< Dimensionality of the node's position (2D)
#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;
/**
 * @class Node
 * @brief Represents a node in a finite element mesh.
 *
 * Stores the position, interior status, and ID of the node within the mesh.
 */
class Node
{
 public:
  /**
   * @brief Default constructor for the Node class.
   */
  Node();
  /**
   * @brief Constructor that initializes the node with position, ID, and interior status.
   * @param a_position Array storing the node's x and y coordinates.
   * @param a_interiorNodeID ID of the node if it is an interior node.
   * @param a_isInterior Boolean indicating if the node is an interior node.
   */
  Node(double a_position[DIM],
       const int&  a_interiorNodeID, 
       const bool& a_isInterior);
  /**
   * @brief Retrieves the position of the node.
   * @param a_position Array to store the node's x and y coordinates.
   */
  void  getPosition(double a_position[DIM]) const;
   /**
   * @brief Gets the ID of the node if it is an interior node.
   * @return The interior node ID.
   */
  const int& getInteriorNodeID() const;
  /**
   * @brief Checks if the node is an interior node.
   * @return True if the node is interior, false otherwise.
   */
  const bool& isInterior() const;

 private:
  double m_position[DIM]; ///< Position of the node in 2D space.
  bool  m_isInterior; ///< True if the node is an interior node, false otherwise.
  int m_interiorNodeID; ///< Interior ID of the node if applicable.
};
#endif
