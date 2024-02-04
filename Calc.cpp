// mainwindow.cpp
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), result(0)
{
    createGUI();
}

void MainWindow::createGUI()
{
    // Create display
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    // Create digit buttons

        for (int i = 0; i < 10; ++i)
        {
            digitButtons[i] = new QPushButton(QString::number(i), this);
            connect(digitButtons[i], &QPushButton::clicked, this, &MainWindow::digitClicked);
        }



    // Create operator buttons
    addButton = new QPushButton("+", this);
    subtractButton = new QPushButton("-", this);
    multiplyButton = new QPushButton("*", this);
    divideButton = new QPushButton("/", this);
    equalsButton = new QPushButton("=", this);
    clearButton = new QPushButton("C", this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(subtractButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(multiplyButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(divideButton, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(equalsButton, &QPushButton::clicked, this, &MainWindow::equalsClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearClicked);

    // Create layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(display, 0, 0, 1, 4);

    for (int i = 1, row = 1; i < 10; ++i)
    {
        mainLayout->addWidget(digitButtons[i], row, (i - 1) % 3);
        if (i % 3 == 0)
            ++row;
    }

    mainLayout->addWidget(digitButtons[0], 4, 1);
    mainLayout->addWidget(addButton, 1, 3);
    mainLayout->addWidget(subtractButton, 2, 3);
    mainLayout->addWidget(multiplyButton, 3, 3);
    mainLayout->addWidget(divideButton, 4, 3);
    mainLayout->addWidget(equalsButton, 4, 2);
    mainLayout->addWidget(clearButton, 4, 0);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::digitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    currentInput += clickedButton->text();
    updateDisplay();
    qDebug() << "Digit Clicked: " << currentInput;
}

void MainWindow::operatorClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    pendingOperator = clickedButton->text();
    result = currentInput.toDouble();
    currentInput.clear();
    qDebug() << "Operator Clicked: " << pendingOperator << ", Result: " << result;
}


void MainWindow::equalsClicked()
{
    double operand = currentInput.toDouble();
    if (pendingOperator == "+")
        result += operand;
    else if (pendingOperator == "-")
        result -= operand;
    else if (pendingOperator == "*")
        result *= operand;
    else if (pendingOperator == "/")
    {
        if (operand != 0)
            result /= operand;
        else
            display->setText("Error");
    }

    currentInput = QString::number(result);
    pendingOperator.clear();
    updateDisplay();
    qDebug() << "Equals Clicked: " << currentInput << ", Pending Operator: " << pendingOperator << ", Result: " << result;
}


void MainWindow::clearClicked()
{
    currentInput.clear();
    pendingOperator.clear();
    result = 0;
    updateDisplay();
}

void MainWindow::updateDisplay()
{
    display->setText(currentInput);
}

// #include "mainwindow.moc"
