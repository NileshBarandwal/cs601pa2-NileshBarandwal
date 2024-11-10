// acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _NODE_H_
#define _NODE_H_

/**
 * @file Node.h
 * @brief This header file defines the Node class, which represents a node in a finite element mesh.
 *
 * The Node class stores information about the position and properties of a node, such as whether it is an interior node
 * and its interior node ID.
 */

#define DIM 2

#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
using namespace std;

/**
 * @class Node
 * @brief A class that represents a node in a finite element mesh.
 *
 * This class stores the position of the node, whether it is an interior node, and its interior node ID.
 * Nodes are the fundamental units in a finite element mesh and are used to define the grid's structure.
 */
class Node
{
 public:
  /**
   * @brief Default constructor for the Node class.
   *
   * This constructor initializes the node with default values. The position is not set, and the node is not marked as interior.
   * This constructor is typically used when the node data is to be set later.
   */
  Node();

  /**
   * @brief Constructor for initializing a Node with a given position, interior node ID, and interior status.
   *
   * @param a_position An array representing the 2D position of the node. The position is stored in meters or another unit of length.
   * @param a_interiorNodeID The ID assigned to the interior node. This ID is used to uniquely identify interior nodes.
   * @param a_isInterior A boolean indicating whether the node is an interior node (true) or a boundary node (false).
   *
   * This constructor initializes the node with the given position, interior node ID, and status.
   * An interior node is one that is fully enclosed within the grid, while a boundary node lies on the grid's edge.
   */
  Node(double a_position[DIM],
       const int&  a_interiorNodeID,
       const bool& a_isInterior);

  /**
   * @brief Gets the position of the node.
   *
   * @param a_position An array to store the position of the node.
   * The array should be pre-allocated with space for at least `DIM` elements.
   *
   * This method retrieves the position of the node and stores it in the provided array.
   * The position is typically given in meters or another unit of length.
   */
  void getPosition(double a_position[DIM]) const;

  /**
   * @brief Gets the interior node ID.
   *
   * @return The interior node ID.
   *
   * This method returns the ID assigned to the interior node. The interior node ID is used for identification
   * and indexing purposes within the grid.
   */
  const int& getInteriorNodeID() const;

  /**
   * @brief Checks if the node is an interior node.
   *
   * @return A boolean indicating if the node is an interior node (true) or not (false).
   *
   * This method returns true if the node is an interior node, meaning it is not on the boundary of the grid.
   * Otherwise, it returns false.
   */
  const bool& isInterior() const;

 private:
  /**
   * @brief An array that stores the 2D position of the node.
   *
   * This array stores the coordinates of the node in a 2D space (x, y).
   * The coordinates are typically expressed in meters or another unit of length.
   */
  double m_position[DIM];

  /**
   * @brief A boolean indicating if the node is an interior node.
   *
   * This variable is true if the node is an interior node (not on the boundary of the grid).
   * It is false for boundary nodes.
   */
  bool m_isInterior;

  /**
   * @brief The interior node ID.
   *
   * This ID uniquely identifies the interior node within the grid.
   * Interior nodes are those that are fully enclosed within the grid, not located on the boundary.
   */
  int m_interiorNodeID;
};

#endif // _NODE_H_
