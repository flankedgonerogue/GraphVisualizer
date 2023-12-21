#include "../include/GraphVisualizer.h"

#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QGraphicsView>

GraphVisualizer::GraphVisualizer(QWidget *parent) : QWidget(parent)
{
    // Node Input Group
    QGroupBox *nodeGroupBox = new QGroupBox("Node", this);

    QLabel *nodeLabel = new QLabel("Name:", nodeGroupBox);

    nodeComboBox = new QComboBox(nodeGroupBox);
    nodeComboBox->setFocus();
    nodeComboBox->setEditable(true);

    QPushButton *addNodeButton = new QPushButton("Add Node", nodeGroupBox);
    QPushButton *delNodeButton = new QPushButton("Delete Node", nodeGroupBox);

    connect(addNodeButton, &QPushButton::clicked, this, &GraphVisualizer::addNodeButtonClicked);
    connect(delNodeButton, &QPushButton::clicked, this, &GraphVisualizer::delNodeButtonClicked);

    QGridLayout *nodeGridLayout = new QGridLayout(this);
    nodeGridLayout->addWidget(nodeLabel, 0, 0);
    nodeGridLayout->addWidget(nodeComboBox, 0, 1);
    nodeGridLayout->addWidget(addNodeButton, 1, 0, 1, 2);
    nodeGridLayout->addWidget(delNodeButton, 2, 0, 1, 2);

    nodeGroupBox->setLayout(nodeGridLayout);

    // End Node Input Group

    // Edge Input Group

    QGroupBox *edgeGroupBox = new QGroupBox("Edge", this);

    QLabel *edgeFromLabel = new QLabel("From:", edgeGroupBox);
    QLabel *edgeToLabel = new QLabel("To:", edgeGroupBox);

    edgeFromComboBox = new QComboBox(edgeGroupBox);
    edgeToComboBox = new QComboBox(edgeGroupBox);

    QPushButton *addEdgeButton = new QPushButton("Add Edge");
    QPushButton *delEdgeButton = new QPushButton("Delete Edge");

    connect(addEdgeButton, &QPushButton::clicked, this, &GraphVisualizer::addEdgeButtonClicked);
    connect(delEdgeButton, &QPushButton::clicked, this, &GraphVisualizer::delEdgeButtonClicked);

    QGridLayout *edgeGridLayout = new QGridLayout(this);
    edgeGridLayout->addWidget(edgeFromLabel, 0, 0);
    edgeGridLayout->addWidget(edgeFromComboBox, 0, 1);
    edgeGridLayout->addWidget(edgeToLabel, 1, 0);
    edgeGridLayout->addWidget(edgeToComboBox, 1, 1);
    edgeGridLayout->addWidget(addEdgeButton, 2, 0, 1, 2);
    edgeGridLayout->addWidget(delEdgeButton, 3, 0, 1, 2);

    edgeGroupBox->setLayout(edgeGridLayout);

    // End Edge Input Group

    // Node Info Output Group

    QGroupBox *nodeInfoGroupBox = new QGroupBox("Node Info", this);

    QLabel* densityLabel = new QLabel("Density:", nodeInfoGroupBox);
    QLabel* maxDegreeLabel = new QLabel("Max Degree:", nodeInfoGroupBox);
    QLabel* minDegreeLabel = new QLabel("Min Degree:", nodeInfoGroupBox);
    QLabel* degreeLabel = new QLabel("Degree:", nodeInfoGroupBox);
    QLabel* neighboursLabel = new QLabel("Neighbours:", nodeInfoGroupBox);

    density = new QLabel(nodeInfoGroupBox);
    maxDegree = new QLabel(nodeInfoGroupBox);
    minDegree = new QLabel(nodeInfoGroupBox);
    degree = new QLabel(nodeInfoGroupBox);
    neighbours = new QLabel(nodeInfoGroupBox);

    QGridLayout *nodeInfoGridLayout = new QGridLayout(this);
    nodeInfoGridLayout->addWidget(densityLabel, 0, 0);
    nodeInfoGridLayout->addWidget(density, 0, 1);
    nodeInfoGridLayout->addWidget(maxDegreeLabel, 1, 0);
    nodeInfoGridLayout->addWidget(maxDegree, 1, 1);
    nodeInfoGridLayout->addWidget(minDegreeLabel, 2, 0);
    nodeInfoGridLayout->addWidget(minDegree, 2, 1);
    nodeInfoGridLayout->addWidget(degreeLabel, 3, 0);
    nodeInfoGridLayout->addWidget(degree, 3, 1);
    nodeInfoGridLayout->addWidget(neighboursLabel, 4, 0);
    nodeInfoGridLayout->addWidget(neighbours, 4, 1);

    nodeInfoGroupBox->setLayout(nodeInfoGridLayout);

    // End Node Info Output Group

    // Adajency Matrix label setup

    matrix = new QLabel(this);
    matrix->setFont(QFont("monospace"));
    matrix->setAlignment(Qt::AlignCenter);
    matrix->setMinimumSize(250, 150);

    // End Adajency Matrix label setup

    // Graphics Scene setup

    scene = new QGraphicsScene(0, 0, 781, 400, this);
    QGraphicsView* view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing, true); // Optional: Enable antialiasing
    view->setFixedSize(781, 400); // Fix the size of the view
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Optional: Disable horizontal scrollbar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Optional: Disable vertical scrollbar

    connect(scene, &QGraphicsScene::selectionChanged, this, &GraphVisualizer::onSceneSelectedItemChanged);

    // End Graphics Scene setup

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(nodeGroupBox, 0, 0);
    layout->addWidget(nodeInfoGroupBox, 0, 1);
    layout->addWidget(edgeGroupBox, 0, 2);
    layout->addWidget(matrix, 0, 3);
    layout->addWidget(view, 1, 0, 1, 4);

    setLayout(layout);
}

void GraphVisualizer::addNodeButtonClicked()
{
    // Add the node only if it hasn't been added in the combo box
    if (const QString node_label = nodeComboBox->currentText(); edgeFromComboBox->findText(node_label) == -1)
    {
        nodeComboBox->setEditText("");
        nodeComboBox->addItem(node_label);
        edgeFromComboBox->addItem(node_label);
        edgeToComboBox->addItem(node_label);

        NodeGraphicsItem *nodeItem = new NodeGraphicsItem(node_label, 30, 30, [this] {
            updateEdges();
        });

        nodeItems.insert(node_label, nodeItem);
        scene->addItem(nodeItem);

        updateMatrix();
        updateEdgesInfo();
    }
}

void GraphVisualizer::delNodeButtonClicked()
{
    const QString node_label = nodeComboBox->currentText();

    // If the node is the combo boxes then remove it and update the edges and matrix
    if (const int index = edgeFromComboBox->findText(node_label); index != -1)
    {
        nodeComboBox->removeItem(nodeComboBox->findText(node_label));
        edgeFromComboBox->removeItem(index);
        edgeToComboBox->removeItem(index);

        // Remove all related edges
        while (edges.contains(node_label))
        {
            edges.remove(node_label);
        }

        // Remove all related edges
        auto key = edges.key(node_label, "-1");
        while (key != "-1")
        {
            edges.remove(edges.key(node_label), node_label);
            key = edges.key(node_label, "-1");
        }

        QGraphicsEllipseItem *nodeItem = nodeItems.take(node_label);
        scene->removeItem(nodeItem);
        delete nodeItem;

        updateNodeInfo();
        updateEdges();
        updateEdgesInfo();
        updateMatrix();
    }
}

void GraphVisualizer::addEdgeButtonClicked()
{
    const QString edge_from_label = edgeFromComboBox->currentText();
    const QString edge_to_label = edgeToComboBox->currentText();

    // Check if both edges are selected and are not the same, if so do nothing
    if (edge_from_label.isEmpty() || edge_to_label.isEmpty() || (edge_from_label == edge_to_label))
        return;

    // Check if edge already exists, if not then add the edge
    if (edges.find(edge_from_label, edge_to_label) == edges.end())
    {
        edges.insert(edge_from_label, edge_to_label);
        edges.insert(edge_to_label, edge_from_label);

        updateNodeInfo();
        updateEdges();
        updateEdgesInfo();
        updateMatrix();
    }
}

void GraphVisualizer::delEdgeButtonClicked()
{
    const QString edge_from_label = edgeFromComboBox->currentText();
    const QString edge_to_label = edgeToComboBox->currentText();

    // Check if both edges are selected and not the same
    if (edge_from_label.isEmpty() || edge_to_label.isEmpty() || (edge_from_label == edge_to_label))
        return;

    // Find the edge, if it exits then remove it
    if (edges.find(edge_from_label, edge_to_label) != edges.end())
    {
        edges.remove(edge_from_label, edge_to_label);
        edges.remove(edge_to_label, edge_from_label);

        updateNodeInfo();
        updateEdges();
        updateEdgesInfo();
        updateMatrix();
    }
}

void GraphVisualizer::updateNodeInfo() const
{
    if (scene->selectedItems().empty())
    {
        degree->setText("");
        neighbours->setText("");
        return;
    }

    const QGraphicsEllipseItem *nodeItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(scene->selectedItems()[0]);

    // Return if the focused item is not a node
    if (nodeItem->childItems().empty()) return;

    // It is a node, show density and what not
    QList<QString> values = edges.values(qgraphicsitem_cast<QGraphicsTextItem*>(nodeItem->childItems().at(0))->toPlainText());
    degree->setText(QString("%1").arg(values.count()));
    QString neighbour_string;
    for (auto & value : values)
    {
        neighbour_string += value + ' ';
    }
    neighbours->setText(neighbour_string);
}

void GraphVisualizer::onSceneSelectedItemChanged() const
{
    updateNodeInfo();
}

void GraphVisualizer::updateEdgesInfo()
{
    std::unordered_map<QString, int> nodeDegrees;

    // Count the edges for each node
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        nodeDegrees[it.key()]++;
        nodeDegrees[it.value()]++;
    }
    for (int i = 0; i < nodeComboBox->count(); ++i)
    {
        nodeDegrees[nodeComboBox->itemText(i)];
    }

    // Find the node with the maximum degree
    QString maxDegreeNode;
    int _maxDegree = -1;

    for (const auto& pair : nodeDegrees) {
        if (pair.second > _maxDegree) {
            _maxDegree = pair.second;
            maxDegreeNode = pair.first;
        }
    }

    // Find the node with the minimum degree
    QString minDegreeNode;
    int _minDegree = std::numeric_limits<int>::max();

    for (const auto&[fst, snd] : nodeDegrees) {
        if (snd < _minDegree) {
            _minDegree = snd;
            minDegreeNode = fst;
        }
    }

    // Calculate the density of the graph
    const int numNodes = static_cast<int>(nodeDegrees.size());
    const int numEdges = static_cast<int>(edges.size()) / 2;

    const double _density = static_cast<double>(2 * numEdges) / (numNodes * (numNodes - 1));

    density->setText(QString("%1").arg(_density));
    maxDegree->setText(maxDegreeNode);
    minDegree->setText(minDegreeNode);
}

void GraphVisualizer::updateEdges()
{
    // Remove all old lines
    for (auto it = lineItems.begin(); it != lineItems.end(); ++it)
    {
        QGraphicsLineItem* lineItem = it.value();
        scene->removeItem(lineItem);
        delete lineItem;
    }

    lineItems.clear();

    // Add the new lines
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        const QString& fromNode = it.key();
        QString toNode = it.value();
        QPair<QString, QString> edge(fromNode, toNode);

        // TODO DO MATHS
        QGraphicsLineItem* lineItem = new QGraphicsLineItem(
            nodeItems[fromNode]->pos().x() + 15, nodeItems[fromNode]->pos().y() + 15,
            nodeItems[toNode]->pos().x() + 15, nodeItems[toNode]->pos().y() + 15
            );

        lineItem->setZValue(-1);

        lineItem->setPen(QPen(Qt::black, 2));

        lineItems.insert(edge, lineItem);

        scene->addItem(lineItem);
    }
}

void GraphVisualizer::updateMatrix()
{
    QString matrix_label;

    matrix_label += " ";
    for (int i = 0; i != edgeFromComboBox->count(); ++i)
    {
        matrix_label += " | " + edgeFromComboBox->itemText(i);
    }
    matrix_label += " |\n";

    for (int i = 0; i != edgeFromComboBox->count(); ++i)
    {
        matrix_label += edgeFromComboBox->itemText(i);

        for (int j = 0; j != edgeFromComboBox->count(); ++j)
        {
            matrix_label += " | " + std::to_string((edges.find(edgeFromComboBox->itemText(i), edgeToComboBox->itemText(j)) != edges.end()));
        }
        matrix_label += " |\n";
    }

    matrix->setText(matrix_label);
}
