#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAddFile_triggered();

    void on_actionDrawGrid_triggered();

    void on_btnLTMoveLeft_clicked();

    void on_btnLTMoveRight_clicked();

    void on_btnLTMoveUp_clicked();

    void on_btnLTMoveDown_clicked();

    void on_btnRBMoveLeft_clicked();

    void on_btnRBMoveRight_clicked();

    void on_btnRBMoveUp_clicked();

    void on_btnRBMoveDown_clicked();

    void on_actionSave_triggered();

private:
    QString getFile();
    void showIconPic();

private:
    QPoint      m_ptLeftTop;    // 网格的左上顶点坐标
    QPoint      m_ptRightBottom;// 网格的右下顶点坐标
    int         m_nIconWidth;   // 网格文件的宽度
    int         m_nIconHeight;  // 图标文件的高度
    int         m_nStep;        // 步长

    QString     m_sIconFilePath;
    QPixmap     m_pixmap;
    QPainter    painter;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
