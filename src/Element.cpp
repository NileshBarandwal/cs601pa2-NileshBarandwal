//acknowledgement: cs294-73 colella@eecs.berkeley.edu
/**
 * @file Element.cpp
 * @brief Implementation of the Element class for finite element mesh representation.
 * 
 * This file contains methods for initializing and manipulating elements in the finite element model.
 * The class defines the vertices for each element and provides functions for accessing them.
 * 
 * Acknowledgement: cs294-73 colella@eecs.berkeley.edu
 */
#include <cassert>
#include "Element.h"

// Constructor that initializes an element with specified vertices
// a_vertices: Array of integers representing the vertices of the element

/**
 * @brief Constructor for initializing an element with specified vertices.
 * 
 * This constructor takes an array of integers representing the vertices of the element and 
 * initializes the element with the given vertices.
 * 
 * @param a_vertices Array of integers representing the vertices of the element.
 */
Element::Element(int a_vertices[VERTICES])
{
  // Loop through the provided vertices and assign them to the element's vertices
  for (int ivert = 0;ivert < VERTICES;ivert++)
    {
      m_vertices[ivert] = a_vertices[ivert];
    }
};

/**
 * @brief Default constructor for initializing an element with invalid vertices.
 * 
 * This constructor initializes all the element's vertices to -1, representing an uninitialized or invalid state.
 */
// Default constructor that initializes an element with invalid vertex values (-1)
Element::Element()
{
  // Set each vertex to -1, representing an uninitialized or invalid state
  for (int ivert = 0;ivert < VERTICES;ivert++)
    {
      m_vertices[ivert] = -1;
    }
};

// Overloaded operator[] to access the vertices of the element
// a_localNodeNumber: The index of the local node number (should be less than the number of vertices)
// Returns the vertex at the specified index
/**
 * @brief Accessor function to get a vertex by its local node number.
 * 
 * This overloaded operator allows accessing the vertices of the element using the array indexing syntax.
 * The local node number must be valid (less than the total number of vertices).
 * 
 * @param a_localNodeNumber The local node number (index) of the vertex.
 * @return const int& The vertex at the specified index.
 */
const int& Element::operator[](const int& a_localNodeNumber) const
{
  // Ensure the node index is within valid range
  assert(a_localNodeNumber < VERTICES);
  return m_vertices[a_localNodeNumber];
};

// Function to copy the vertices of the element into the provided array
// a_vertices: Array to store the vertices of the element
/**
 * @brief Copies the vertices of the element into the provided array.
 * 
 * This function copies all vertices of the current element into a user-provided array.
 * 
 * @param a_vertices Array to store the vertices of the element.
 */
void Element::vertices(int a_vertices[VERTICES]) const
{
  // Loop through each vertex and copy it to the provided array
  for(int i=0; i<VERTICES; i++)
    {
      a_vertices[i] = m_vertices[i];
    }
}
