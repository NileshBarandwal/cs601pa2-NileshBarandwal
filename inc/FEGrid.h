//acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _FEGRID_H_
#define _FEGRID_H_

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
 * @brief Represents a finite element grid.
 *
 * This class handles the structure of the grid, including nodes and elements, and provides methods for 
 * calculations over elements, such as area and gradient computations.
 */

class FEGrid
{
public:
  /**
   * @brief Default constructor for the FEGrid class.
   */
  FEGrid();

  /**
   * @brief Constructor that initializes the grid with node and element data files.
   * @param nodeFile Filename of the node data file.
   * @param a_elementFileName Filename of the element data file.
   */
  FEGrid(const std::string& nodeFile, const std::string& a_elementFileName);

  /**
   * @brief Computes the gradient of a shape function for an element at a specified local node.
   * @param a_gradient Array to store the computed gradient.
   * @param a_eltNumber Element number.
   * @param a_localNodeNumber Local node number within the element.
   */
  void gradient(double a_gradient[DIM], 
		const int& a_eltNumber,
		const int& a_localNodeNumber) const;
   /**
   * @brief Calculates the area of a specified element.
   * @param a_eltNumber Element number.
   * @return The area of the element.
   */
  double elementArea(const int& a_eltNumber) const;
   /**
   * @brief Retrieves a node of an element by element and local node number.
   * @param a_eltNumber Element number.
   * @param a_localNodeNumber Local node number within the element.
   * @return Reference to the requested Node.
   */
  const Node& getNode(const int& a_eltNumber,
                      const int& a_localNodeNumber) const; 
  /**
   * @brief Gets the total number of elements in the grid.
   * @return Number of elements.
   */
  int getNumElts() const;
   /**
   * @brief Gets the total number of nodes in the grid.
   * @return Number of nodes.
   */
  int getNumNodes() const;
  /**
   * @brief Gets the number of interior nodes in the grid.
   * @return Number of interior nodes.
   */
  int getNumInteriorNodes() const;
  /**
   * @brief Accessor for a specified element by index.
   * @param i Index of the element.
   * @return Reference to the requested Element.
   */
  const Element& element(int i) const;
  /**
   * @brief Accessor for a specified node by index.
   * @param i Index of the node.
   * @return Reference to the requested Node.
   */
  const Node& node(int i) const;

  private:                            
  vector<Node > m_nodes; ///< Vector storing all nodes in the grid.
  vector<Element > m_elements; ///< Vector storing all elements in the grid.
  int m_numInteriorNodes; ///< Number of interior nodes in the grid.
};


#endif
