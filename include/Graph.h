#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <memory>
#include <sstream>
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
    NodePtr findNode(Label label)
    {
        for (NodePtr& node : nodes)
        {
            if (node->label == label)
            {
                return node;
            }
        }

        return nullptr;
    }

    /**
     * \brief Attemps to find an edge in the edges list
     * \param node_1 Node the link is from
     * \param node_2 Node the link is to
     * \return Pointer to the weight of the node if found, otherwise a null pointer
     */
    EdgePtr findEdge(const NodePtr& node_1, const NodePtr& node_2)
    {
        for (auto& edge : edges)
        {
            if (std::get<0>(*edge) == node_1 && std::get<1>(*edge) == node_2)
            {
                return edge;
            }
        }

        return nullptr;
    }

    /**
     * \brief Finds all the edges starting from a node
     * \param label Label of node to find the edges of
     * \return Edges starting from that node
     */
    EdgePtrList findEdgesForNode(Label label)
    {
        const auto node = findNode(label);
        if (node == nullptr)
        {
            return {};
        }

        EdgePtrList found_edges;

        for (auto& edge : edges)
        {
            if (std::get<0>(*edge) == node)
            {
                found_edges.emplace_back(edge);
            }
        }

        return found_edges;
    }

    /**
     * \brief Attempts to insert a new node in the list if it is NOT already present
     * \param label Label for the new node to be inserted
     * \return True if the insertion was successful
     */
    bool insertNode(Label label)
    {
        if (findNode(label) == nullptr)
        {
            nodes.push_back(std::make_shared<Node>(label));

            return true;
        }

        return false;
    }

    /**
     * \brief Creates a edge from node A to B with a weight, if the edge already exists, updates it's weight
     * \param label_1 Label of the node to create the link from
     * \param label_2 Label of the node to create the link to
     * \param weight Weight of the edge
     */
    bool insertEdge(Label label_1, Label label_2, const int& weight = 0)
    {
        const auto node_1 = findNode(label_1);
        if (node_1 == nullptr) return false;

        const auto node_2 = findNode(label_2);
        if (node_2 == nullptr) return false;

        const EdgePtr edge = findEdge(node_1, node_2);

        if (edge == nullptr)
        {
            edges.push_back(std::make_shared<Edge>(node_1, node_2, weight));

            return true;
        }

        std::get<2>(*edge) = weight;

        return true;
    }

    [[nodiscard]] std::string getNodesAsString() const
    {
        std::stringstream ss;

        for (const auto& node : nodes)
        {
            ss << node->label << '\n';
        }

        return ss.str();
    }

    [[nodiscard]] std::string getEdgesAsString() const
    {
        std::stringstream ss;

        for (const auto& edge : edges)
        {
            ss << std::get<0>(*edge)->label << " -> " << std::get<1>(*edge)->label << " : " << std::get<2>(*edge) << '\n';
        }

        return ss.str();
    }

    [[nodiscard]] static std::string getEdgesAsStringFromEdges(const EdgePtrList& _edges)
    {
        std::stringstream ss;

        for (const auto& edge : _edges)
        {
            ss << std::get<0>(*edge)->label << " -> " << std::get<1>(*edge)->label << " : " << std::get<2>(*edge) << '\n';
        }

        return ss.str();
    }
};
} // namespace Flanky

#endif // GRAPH_H
