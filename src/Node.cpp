#include "Node.h"
#include <iostream>

using namespace std;

/**
 * @brief Default constructor for the Node class.
 *
 * This constructor initializes the node with default values: position not set, interior node status is false, and ID is -1.
 */
Node::Node() : m_isInterior(false), m_interiorNodeID(-1)
{
    for (int i = 0; i < DIM; ++i)
    {
        m_position[i] = 0.0;
    }
}

/**
 * @brief Constructor to initialize a Node with a given position, interior node ID, and interior status.
 *
 * @param a_position An array representing the 2D position of the node.
 * @param a_interiorNodeID The ID assigned to the interior node.
 * @param a_isInterior A boolean indicating whether the node is an interior node.
 */
Node::Node(double a_position[DIM],
           const int&  a_interiorNodeID,
           const bool& a_isInterior)
{
    for (int i = 0; i < DIM; ++i)
    {
        m_position[i] = a_position[i];
    }
    m_interiorNodeID = a_interiorNodeID;
    m_isInterior = a_isInterior;
}

/**
 * @brief Retrieves the position of the node.
 *
 * @param a_position An array to store the position of the node. The array should have space for `DIM` elements.
 */
void Node::getPosition(double a_position[DIM]) const
{
    for (int i = 0; i < DIM; ++i)
    {
        a_position[i] = m_position[i];
    }
}

/**
 * @brief Gets the interior node ID.
 *
 * @return The interior node ID.
 */
const int& Node::getInteriorNodeID() const
{
    return m_interiorNodeID;
}

/**
 * @brief Checks if the node is an interior node.
 *
 * @return A boolean indicating if the node is an interior node.
 */
const bool& Node::isInterior() const
{
    return m_isInterior;
}
