// acknowledgement: cs294-73 colella@eecs.berkeley.edu
#include "Element.h"
#include <iostream>
using namespace std;

/**
 * @brief Default constructor for the Element class.
 *
 * This constructor initializes the element with default values, setting all vertices to -1.
 */
Element::Element()
{
    for (int i = 0; i < VERTICES; ++i)
    {
        m_vertices[i] = -1;
    }
}

/**
 * @brief Constructor to initialize an Element with specific vertices.
 *
 * @param a_vertices An array of integers representing the vertex IDs for this element.
 * The array must contain 3 integers, one for each vertex.
 */
Element::Element(int a_vertices[VERTICES])
{
    for (int i = 0; i < VERTICES; ++i)
    {
        m_vertices[i] = a_vertices[i];
    }
}

/**
 * @brief Accessor function to get the vertex at a specific local node number.
 *
 * @param a_localNodeNumber The index of the local node (0-2).
 * @return A constant reference to the vertex ID at the specified local node index.
 */
const int& Element::operator[](const int& a_localNodeNumber) const
{
    if (a_localNodeNumber < 0 || a_localNodeNumber >= VERTICES)
    {
        cerr << "Error: Invalid local node number." << endl;
        exit(1);
    }
    return m_vertices[a_localNodeNumber];
}

/**
 * @brief Retrieves the vertices of the element.
 *
 * @param a_vertices An array to store the vertices of the element. This array must be pre-allocated with 3 elements.
 */
void Element::vertices(int a_vertices[VERTICES]) const
{
    for (int i = 0; i < VERTICES; ++i)
    {
        a_vertices[i] = m_vertices[i];
    }
}
