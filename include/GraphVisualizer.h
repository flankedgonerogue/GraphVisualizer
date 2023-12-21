#ifndef GRAPH_VISUALIZER_H
#define GRAPH_VISUALIZER_H

#include <QComboBox>
#include <QGraphicsScene>
#include <QLabel>
#include <QLineEdit>
#include <QGraphicsTextItem>
#include <functional>
#include <utility>

class NodeGraphicsItem final : public QGraphicsEllipseItem
{
    std::function<void()> updateEdges;

public:
    NodeGraphicsItem(const QString& label , const int w, const int h, std::function<void()> context): QGraphicsEllipseItem(0, 0, w, h), updateEdges(std::move(context))
    {
        setFlag(ItemSendsGeometryChanges);
        setFlag(ItemIsMovable);
        setFlag(ItemIsSelectable);

        setPos(340, 200);

        setBrush(Qt::lightGray);

        QGraphicsTextItem *textItem = new QGraphicsTextItem(label, this);
        textItem->setPos(w / 5.0, 0);
        textItem->setFont(QFont("monospace"));
    }

protected:
    QVariant itemChange(const GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionChange) {
            updateEdges();
        }

        if (change == ItemPositionChange && scene()) {
            // Check if the new position goes beyond the viewport boundaries with a margin of 20 pixels
            QPointF newPos = value.toPointF();
            const QRectF sceneRectWithMargin = scene()->sceneRect().adjusted(10, 10, -10, -10);
            const QRectF itemRect = rect();

            if (newPos.x() < sceneRectWithMargin.left()) {
                newPos.setX(sceneRectWithMargin.left());
            }
            if (newPos.x() + itemRect.width() > sceneRectWithMargin.right()) {
                newPos.setX(sceneRectWithMargin.right() - itemRect.width());
            }
            if (newPos.y() < sceneRectWithMargin.top()) {
                newPos.setY(sceneRectWithMargin.top());
            }
            if (newPos.y() + itemRect.height() > sceneRectWithMargin.bottom()) {
                newPos.setY(sceneRectWithMargin.bottom() - itemRect.height());
            }

            return newPos;
        }

        return QGraphicsItem::itemChange(change, value);
    }
};

class GraphVisualizer final : public QWidget
{
    Q_OBJECT

public:
    explicit GraphVisualizer(QWidget *parent = nullptr);

public slots:
    void addNodeButtonClicked();
    void delNodeButtonClicked();
    void addEdgeButtonClicked();
    void delEdgeButtonClicked();

    void updateNodeInfo() const;

    void onSceneSelectedItemChanged() const;

    void updateEdgesInfo();

private:
    QComboBox *nodeComboBox;
    QComboBox *edgeFromComboBox;
    QComboBox *edgeToComboBox;
    QLabel *density;
    QLabel *degree;
    QLabel *maxDegree;
    QLabel *minDegree;
    QLabel *neighbours;
    QGraphicsScene *scene;
    QLabel *matrix;
    QMultiMap<QString, QString> edges;
    QMap<QString, QGraphicsEllipseItem*> nodeItems;
    QMap<QPair<QString, QString>, QGraphicsLineItem*> lineItems;

    void updateEdges();
    void updateMatrix();
};

#endif // GRAPH_VISUALIZER_H
