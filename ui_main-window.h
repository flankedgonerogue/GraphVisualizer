#ifndef UI_MAIN_WINDOW
#define UI_MAIN_WINDOW

#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
  public:
    QMainWindow* mainWindow = nullptr;
    QWidget* centralwidget = nullptr;
    QWidget* horizontalLayoutWidget = nullptr;
    QHBoxLayout* horizontalLayout = nullptr;
    QLabel* node_label = nullptr;
    QLineEdit* node_label_input = nullptr;
    QPushButton* add_node_btn = nullptr;
    QPushButton* delete_node_btn = nullptr;
    QSpacerItem* horizontalSpacer = nullptr;
    QLabel* density_label = nullptr;
    QLabel* density_value = nullptr;
    QGraphicsView* graphicsView = nullptr;

    Flanky::Graph* graph = nullptr;

    void setupUi(QMainWindow* MainWindow)
    {
        mainWindow = MainWindow;

        if (MainWindow->objectName().isEmpty())
        {
            MainWindow->setObjectName("MainWindow");
        }
        MainWindow->resize(600, 400);
        MainWindow->setMinimumSize(QSize(600, 400));

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 581, 31));

        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);

        node_label = new QLabel(horizontalLayoutWidget);
        node_label->setObjectName("node_label");
        horizontalLayout->addWidget(node_label);

        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);

        node_label_input = new QLineEdit(horizontalLayoutWidget);
        node_label_input->setObjectName("node_label_input");
        node_label_input->setSizePolicy(sizePolicy);
        node_label_input->setMinimumSize(QSize(150, 0));
        sizePolicy.setHeightForWidth(node_label_input->sizePolicy().hasHeightForWidth());
        horizontalLayout->addWidget(node_label_input);

        add_node_btn = new QPushButton(horizontalLayoutWidget);
        add_node_btn->setObjectName("add_node_btn");
        horizontalLayout->addWidget(add_node_btn);

        delete_node_btn = new QPushButton(horizontalLayoutWidget);
        delete_node_btn->setObjectName("delete_node_btn");
        horizontalLayout->addWidget(delete_node_btn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);

        density_label = new QLabel(horizontalLayoutWidget);
        density_label->setObjectName("density_label");
        horizontalLayout->addWidget(density_label);

        density_value = new QLabel(horizontalLayoutWidget);
        density_value->setObjectName("density_value");
        density_value->setAlignment(Qt::AlignCenter);
        horizontalLayout->addWidget(density_value);

        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 50, 581, 341));

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi();

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void setupGraph()
    {
        graph = new Flanky::Graph;
    } // setupGraph

    void handleAddNodeBtnClick() const
    {
        const auto result = graph->insertNode(node_label_input->text().toStdString());
        qDebug("Node Insertion Label: %s Result: %hhd", node_label_input->text().toStdString().c_str(), result);
    } // handleAddNodeBtnClick

    void handleDeleteNodeBtnClick() const
    {
        const auto result = graph->removeNode(node_label_input->text().toStdString());
        qDebug("Node Deletion Label: %s Result: %hhd", node_label_input->text().toStdString().c_str(), result);
    } // handleDeleteNodeBtnClick

    void retranslateUi() const
    {
        mainWindow->setWindowTitle(QObject::tr("Graph Visualizer"));
        node_label->setText(QObject::tr("Node Label"));
        add_node_btn->setText(QObject::tr("Add"));
        delete_node_btn->setText(QObject::tr("Delete"));
        density_label->setText(QObject::tr("Density:"));
        density_value->setText(QObject::tr("100%"));
    } // retranslateUi
};

namespace Ui
{
class MainWindow : public Ui_MainWindow
{
};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW
