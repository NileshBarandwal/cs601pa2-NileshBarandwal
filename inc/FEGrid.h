// acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _FEGRID_H_
#define _FEGRID_H_

/**
 * @file FEGrid.h
 * @brief This header file defines the FEGrid class, which represents the finite element grid.
 *
 * The FEGrid class stores the nodes and elements of the grid, provides methods for accessing them,
 * and performs various operations related to the grid such as gradient calculation and element area.
 */

#include <cstdio>
#include <cmath>
#include <cassert>
#include <cstring>
#include <vector>
#include <string>
#include "Node.h"
#include "Element.h"

using namespace std;

/**
 * @class FEGrid
 * @brief A class that represents a finite element grid consisting of nodes and elements.
 *
 * This class manages the grid by storing a collection of nodes and elements. It provides methods for calculating
 * element gradients, computing areas, and accessing grid data.
 */
class FEGrid
{
public:
  /**
   * @brief Default constructor to initialize an empty FEGrid object.
   *
   * This constructor sets up an empty grid with no nodes or elements.
   */
  FEGrid();

  /**
   * @brief Constructor that initializes the FEGrid object with nodes and elements from files.
   *
   * @param nodeFile The name of the file containing node data.
   * @param a_elementFileName The name of the file containing element data.
   *
   * This constructor initializes the grid by reading node and element information from the specified files.
   */
  FEGrid(const std::string& nodeFile, const std::string& a_elementFileName);

  /**
   * @brief Calculates the gradient at a specific element and node.
   *
   * @param a_gradient An array to store the calculated gradient vector.
   * @param a_eltNumber The index of the element for which the gradient is to be calculated.
   * @param a_localNodeNumber The local node index within the element.
   *
   * This method calculates the gradient at the specified node within the given element and stores the result in a_gradient.
   * The gradient is computed based on the element's shape functions and geometry.
   */
  void gradient(double a_gradient[DIM],
                const int& a_eltNumber,
                const int& a_localNodeNumber) const;

  /**
   * @brief Calculates the area of a specific element.
   *
   * @param a_eltNumber The index of the element for which the area is to be calculated.
   * @return The area of the specified element, in square units.
   *
   * This method computes and returns the area of the given element based on its vertices' coordinates.
   */
  double elementArea(const int& a_eltNumber) const;

  /**
   * @brief Gets the node at a specific element and local node index.
   *
   * @param a_eltNumber The element index.
   * @param a_localNodeNumber The local node index within the element.
   * @return A reference to the node at the specified location.
   *
   * This method retrieves the node from the grid at the specified element and local node index.
   * The indices are zero-based, meaning the first node in the element has index 0.
   */
  const Node& getNode(const int& a_eltNumber,
                      const int& a_localNodeNumber) const;

  /**
   * @brief Gets the total number of elements in the grid.
   *
   * @return The total number of elements in the grid.
   */
  int getNumElts() const;

  /**
   * @brief Gets the total number of nodes in the grid.
   *
   * @return The total number of nodes in the grid.
   */
  int getNumNodes() const;

  /**
   * @brief Gets the number of interior nodes in the grid.
   *
   * @return The number of interior nodes in the grid.
   */
  int getNumInteriorNodes() const;

  /**
   * @brief Gets the element at a specific index.
   *
   * @param i The index of the element.
   * @return A reference to the element at the specified index.
   *
   * The index is zero-based, so the first element has index 0.
   */
  const Element& element(int i) const;

  /**
   * @brief Gets the node at a specific index.
   *
   * @param i The index of the node.
   * @return A reference to the node at the specified index.
   *
   * The index is zero-based, so the first node has index 0.
   */
  const Node& node(int i) const;

private:
  /**
   * @brief A vector to store the nodes in the grid.
   *
   * This vector holds the nodes of the finite element grid.
   */
  vector<Node> m_nodes;

  /**
   * @brief A vector to store the elements in the grid.
   *
   * This vector holds the elements of the finite element grid.
   */
  vector<Element> m_elements;

  /**
   * @brief The number of interior nodes in the grid.
   *
   * This integer stores the count of interior nodes in the grid.
   */
  int m_numInteriorNodes;
};

#endif // _FEGRID_H_
