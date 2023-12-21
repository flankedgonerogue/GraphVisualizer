#include <sstream>

#include "../include/Graph.h"

namespace Flanky {
Graph::NodePtr Graph::findNode(Label label)
{
    for (NodePtr &node : nodes)
    {
        if (node->label == label)
        {
            return node;
        }
    }

    return nullptr;
}

Graph::EdgePtr Graph::findEdge(const NodePtr &node_1, const NodePtr &node_2)
{
    for (auto &edge : edges)
    {
        if (std::get<0>(*edge) == node_1 && std::get<1>(*edge) == node_2)
        {
            return edge;
        }
    }

    return nullptr;
}

Graph::EdgePtrList Graph::findEdgesForNode(Label label, const bool &to)
{
    const auto node = findNode(label);
    if (node == nullptr)
    {
        return {};
    }

    EdgePtrList found_edges;

    if (to)
    {
        for (auto &edge : edges)
        {
            if (std::get<0>(*edge) == node)
            {
                found_edges.emplace_back(edge);
            }
        }
    }
    else
    {
        for (auto &edge : edges)
        {
            if (std::get<1>(*edge) == node)
            {
                found_edges.emplace_back(edge);
            }
        }
    }

    return found_edges;
}

bool Graph::insertNode(const std::string &label)
{
    if (findNode(label) == nullptr)
    {
        nodes.push_back(std::make_shared<Node>(label));

        return true;
    }

    return false;
}

bool Graph::insertEdge(Label label_1, Label label_2, const int &weight)
{
    const auto node_1 = findNode(label_1);
    if (node_1 == nullptr)
        return false;

    const auto node_2 = findNode(label_2);
    if (node_2 == nullptr)
        return false;

    const EdgePtr edge = findEdge(node_1, node_2);

    if (edge == nullptr)
    {
        edges.push_back(std::make_shared<Edge>(node_1, node_2, weight));

        return true;
    }

    std::get<2>(*edge) = weight;

    return true;
}
bool Graph::removeNode(Label label)
{
    const NodePtr node = findNode(label);

    if (node == nullptr)
    {
        return false;
    }

    nodes.remove(node);

    return true;
}

std::string Graph::getNodesAsString() const
{
    std::stringstream ss;

    for (const auto &node : nodes)
    {
        ss << node->label << '\n';
    }

    return ss.str();
}

std::string Graph::getEdgesAsString() const
{
    std::stringstream ss;

    for (const auto &edge : edges)
    {
        ss << std::get<0>(*edge)->label << " -> " << std::get<1>(*edge)->label << " : " << std::get<2>(*edge) << '\n';
    }

    return ss.str();
}

std::string Graph::getEdgesAsStringFromEdges(const EdgePtrList &_edges)
{
    std::stringstream ss;

    for (const auto &edge : _edges)
    {
        ss << std::get<0>(*edge)->label << " -> " << std::get<1>(*edge)->label << " : " << std::get<2>(*edge) << '\n';
    }

    return ss.str();
}
} // Flanky