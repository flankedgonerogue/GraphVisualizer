#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <memory>
#include <string>

namespace Flanky
{
class Graph
{
    typedef const std::string_view& Label;

    /**
     * \brief Struct that is used as nodes in the graph
     */
    struct Node
    {
        /**
         * \brief Text label used to identify the node
         */
        std::string label;

        /**
         * \brief Creates a new node, setting the passed string as label
         * \param label Text label identifying the node
         */
        explicit Node(Label label) : label(label)
        {
        }
    };

    typedef std::shared_ptr<Node> NodePtr;
    typedef std::list<NodePtr> NodePtrList;

    typedef std::tuple<NodePtr, NodePtr, int> Edge;
    typedef std::shared_ptr<Edge> EdgePtr;
    typedef std::list<EdgePtr> EdgePtrList;

    /**
     * \brief List of Node Pointers
     */
    NodePtrList nodes;
    /**
     * \brief List of Edges in the form of A, B and weight
     */
    EdgePtrList edges;

public:

    /**
     * \brief Attempts to find a node using the label in the nodes list
     * \param label Label used to search for the node
     * \return The node found otherwise a nullptr
     */
    NodePtr findNode(Label label);

    /**
   * \brief Attemps to find an edge in the edges list
   * \param node_1 Node the link is from
   * \param node_2 Node the link is to
   * \return Pointer to the weight of the node if found, otherwise a null pointer
   */
    EdgePtr findEdge(const NodePtr &node_1, const NodePtr &node_2);

    /**
     * \brief Finds all the edges starting from a node
     * \param label Label of node to find the edges of
     * \param to Find edges to a node if true, otherwise from a node
     * \return Edges starting from that node
     */
    EdgePtrList findEdgesForNode(Label label, const bool &to = true);

    /**
     * \brief Attempts to insert a new node in the list if it is NOT already present
     * \param label Label for the new node to be inserted
     * \return True if the insertion was successful
     */
    bool insertNode(const std::string &label);

    /**
     * \brief Creates a edge from node A to B with a weight, if the edge already exists, updates it's weight
     * \param label_1 Label of the node to create the link from
     * \param label_2 Label of the node to create the link to
     * \param weight Weight of the edge
     */
    bool insertEdge(Label label_1, Label label_2, const int &weight = 0);

    /**
     * \brief Removes a node if it's found in the nodes list
     * \param label Label of node to be removed
     * \return True if node has been removed successfully
     */
    bool removeNode(Label label);

    /**
     * \brief Returns a list of labels of nodes in the graph
     * \return A list of labels of all nodes
     */
    [[nodiscard]] std::list<std::string_view> getNodes() const
    {
        std::list<std::string_view> _nodes;

        for (const NodePtr& node : nodes)
        {
            _nodes.push_back(std::string_view(node->label));
        }

        return _nodes;
    }

    [[nodiscard]] std::string getNodesAsString() const;

    [[nodiscard]] std::string getEdgesAsString() const;

    [[nodiscard]] static std::string getEdgesAsStringFromEdges(const EdgePtrList &_edges);
};
} // namespace Flanky

#endif // GRAPH_H
