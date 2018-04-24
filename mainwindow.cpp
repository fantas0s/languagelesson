#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_model = new WordPairModel(this);
    ui->setupUi(this);
    ui->listView->setModel(m_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
