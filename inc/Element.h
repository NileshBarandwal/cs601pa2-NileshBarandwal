//acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#define VERTICES 3  ///< Number of vertices per element, fixed at 3 for triangular elements

/**
 * @class Element
 * @brief Represents an element in a finite element mesh.
 *
 * Stores vertex indices for each element, allowing access to its vertices.
 */

class Element
{
public: 
  /**
   * @brief Default constructor for the Element class.
   */
  Element();
  /**
   * @brief Constructor that initializes the vertices of the element.
   * @param a_vertices Array containing indices of the vertices.
   */
  Element(int a_vertices[VERTICES]);

   /**
   * @brief Accessor for vertex index based on local node number.
   * @param a_localNodeNumber Index of the local node.
   * @return The global index of the specified local node.
   */
  const int& operator[](const int& a_localNodeNumber) const;
	
  /**
   * @brief Retrieves the vertex indices of the element.
   * @param a_vertices Array to store vertex indices.
   */
  void vertices(int a_vertices[VERTICES]) const;

private:
  int m_vertices[VERTICES]; ///< Array storing indices of the vertices for this element.
};
#endif
