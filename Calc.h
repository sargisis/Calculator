// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void digitClicked();
    void operatorClicked();
    void equalsClicked();
    void clearClicked();

private:
    QLineEdit *display;
    QPushButton *digitButtons[10];
    QPushButton *addButton, *subtractButton, *multiplyButton, *divideButton, *equalsButton, *clearButton;

    QString currentInput;
    QString pendingOperator;
    double result;

    void createGUI();
    void updateDisplay();
};

#endif // MAINWINDOW_H
