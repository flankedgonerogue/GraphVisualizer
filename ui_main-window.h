#ifndef UI_MAIN_WINDOW
#define UI_MAIN_WINDOW

#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *pushButton;

    int counter = 0;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");

        MainWindow->resize(800, 646);

        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());

        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(400, 600));
        centralwidget->setMaximumSize(QSize(16777214, 16777215));
        centralwidget->setSizePolicy(sizePolicy);

        // verticalLayoutWidget = new QWidget(centralwidget);
        // verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        // verticalLayoutWidget->setGeometry(QRect(10, 10, 781, 631));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout->setContentsMargins(5, 5, 5, 5);

        QFont font;
        font.setPointSize(14);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(120, 50));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
        QObject::connect(pushButton, &QPushButton::clicked, [this]
        {
            counter++;
            label->setText(QCoreApplication::translate("MainWindow", std::to_string(counter).c_str(), nullptr));
        });

    } // setupUi

    void retranslateUi(QMainWindow *MainWindow) const
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Hello World Application", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Hello World", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Increment Count", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW
