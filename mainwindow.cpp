#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_ptLeftTop.setX(0);
    m_ptLeftTop.setY(0);
    m_ptRightBottom.setX(0);
    m_ptRightBottom.setY(0);

    m_nIconWidth = 0;
    m_nIconHeight = 0;

    m_nStep = 1;

    setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getFile()
{
    QUrl qUrl = QFileDialog::getOpenFileUrl(this, tr("打开文件"), QUrl(), "*.png;; *.bmp;; *.jpg");
    if(!qUrl.isValid())
        return "";

    QString sPath = qUrl.path();
    sPath = sPath.right(sPath.length() - 1);
    return sPath;
}

void MainWindow::showIconPic()
{
    m_pixmap.load(m_sIconFilePath);
    ui->label->setPixmap(m_pixmap);
    ui->label->setMouseTracking(true);
    ui->label->setGeometry(0, 0, m_nIconWidth, m_nIconHeight);
    ui->label->show();
}

void MainWindow::on_actionAddFile_triggered()
{
    m_sIconFilePath = getFile();
    m_pixmap.load(m_sIconFilePath);

    m_ptRightBottom.setX(m_pixmap.width());
    m_ptRightBottom.setY(m_pixmap.height());

    m_nIconWidth = m_pixmap.width();
    m_nIconHeight = m_pixmap.height();

    showIconPic();
}

void MainWindow::on_actionDrawGrid_triggered()
{
    QString sRowCount = ui->leRowCount->text();
    if(sRowCount.isEmpty())
    {
        QMessageBox::information(this, "提示", "未填写行数！");
        return;
    }
    int nRowCount = sRowCount.toInt();
    QString sColumnCount = ui->leColumnCount->text();
    if(sColumnCount.isEmpty())
    {
        QMessageBox::information(this, "提示", "未填写列数！");
        return;
    }

    showIconPic();

    int nColumnCount = sColumnCount.toInt();

    int nIconWidth = (m_ptRightBottom.x() - m_ptLeftTop.x()) / nColumnCount;
    int nIconHeight = (m_ptRightBottom.y() - m_ptLeftTop.y()) / nRowCount;

    painter.begin(&m_pixmap);

    painter.setPen(Qt::green);

    // 绘制横线
    for(int i = 0; i <= nRowCount; i++)
    {
        painter.drawLine(m_ptLeftTop.x(), m_ptLeftTop.y() + nIconHeight * i, m_ptRightBottom.x(), m_ptLeftTop.y() + nIconHeight * i);
    }

    // 绘制竖线
    for(int i = 0; i <= nColumnCount; i++)
    {
        painter.drawLine(m_ptLeftTop.x() + nIconWidth * i, m_ptLeftTop.y(), m_ptLeftTop.x() + nIconWidth * i, m_ptRightBottom.y());
    }

    painter.setPen(Qt::red);

    painter.drawLine(0, 0, m_nIconWidth, 0);
    painter.drawLine(0, 0, 0, m_nIconHeight);
    painter.drawLine(m_nIconWidth - 1, 0, m_nIconWidth - 1, m_nIconHeight);
    painter.drawLine(0, m_nIconHeight - 1, m_nIconWidth, m_nIconHeight - 1);

    painter.end();

    ui->label->setPixmap(m_pixmap);
    ui->label->setGeometry(0, 0, m_nIconWidth, m_nIconHeight);
}

// 移动网格的顶点时
void MainWindow::on_btnLTMoveLeft_clicked()
{
    m_ptLeftTop.setX(m_ptLeftTop.x() - m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnLTMoveRight_clicked()
{
    m_ptLeftTop.setX(m_ptLeftTop.x() + m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnLTMoveUp_clicked()
{
    m_ptLeftTop.setY(m_ptLeftTop.y() - m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnLTMoveDown_clicked()
{
    m_ptLeftTop.setY(m_ptLeftTop.y() + m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnRBMoveLeft_clicked()
{
    m_ptRightBottom.setX(m_ptRightBottom.x() - m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnRBMoveRight_clicked()
{
    m_ptRightBottom.setX(m_ptRightBottom.x() + m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnRBMoveUp_clicked()
{
    m_ptRightBottom.setY(m_ptRightBottom.y() - m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_btnRBMoveDown_clicked()
{
    m_ptRightBottom.setY(m_ptRightBottom.y() + m_nStep);
    on_actionDrawGrid_triggered();
}

void MainWindow::on_actionSave_triggered()
{
    QUrl qUrl = QFileDialog::getSaveFileUrl(this, tr("打开文件"), QUrl());
    QString sFilePath = qUrl.path();
    if(sFilePath.isEmpty())
    {
        return;
    }
    sFilePath = sFilePath.right(sFilePath.length() - 1);
    m_pixmap.load(m_sIconFilePath);
    QPixmap pixmap = m_pixmap.copy(m_ptLeftTop.x(), m_ptLeftTop.y(), m_ptRightBottom.x() - m_ptLeftTop.x(), m_ptRightBottom.y() - m_ptLeftTop.y());
    pixmap.save(sFilePath);
}
