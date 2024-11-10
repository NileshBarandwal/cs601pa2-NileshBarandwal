// acknowledgement: cs294-73 colella@eecs.berkeley.edu
#ifndef _ELEMENT_H_
#define _ELEMENT_H_

/**
 * @file Element.h
 * @brief This header file defines the Element class, which represents a finite element in the grid.
 *
 * The Element class stores the vertices of a triangular element and provides methods to access and manipulate those vertices.
 * Each element has three vertices.
 */

/**
 * @def VERTICES
 * @brief The number of vertices in an element. For a triangular element, this is 3.
 */
#define VERTICES 3

/**
 * @class Element
 * @brief A class to represent a finite element in the grid.
 *
 * The Element class stores the three vertices of a triangular element. It provides methods for accessing the vertex data
 * and for initializing an element with specific vertices.
 */
class Element
{
public:
  /**
   * @brief Default constructor that initializes the element with default values.
   *
   * This constructor sets all vertices to -1. It is used when no specific vertex data is provided.
   */
  Element();

  /**
   * @brief Constructor that initializes the element with specific vertices.
   *
   * @param a_vertices An array of integers representing the vertex IDs for this element.
   * The array should contain 3 integers, one for each vertex.
   */
  Element(int a_vertices[VERTICES]);

  /**
   * @brief Accessor function to get the vertex at a specific local node number.
   *
   * @param a_localNodeNumber The index of the local node (0-2).
   * @return A constant reference to the vertex at the specified local node index.
   * @note The index is expected to be between 0 and 2, inclusive.
   */
  const int& operator[](const int& a_localNodeNumber) const;

  /**
   * @brief Function to get the vertices of the element.
   *
   * This function copies the vertices of the element into the provided array.
   *
   * @param a_vertices An array to store the vertices of the element. This array must be pre-allocated with 3 elements.
   */
  void vertices(int a_vertices[VERTICES]) const;

private:
  /**
   * @brief An array to store the vertices of the element.
   *
   * This array holds the vertex IDs for the 3 vertices of the element.
   */
  int m_vertices[VERTICES];
};

#endif // _ELEMENT_H_
