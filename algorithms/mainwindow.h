#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qgraphicsscene.h>
#include <QGraphicsTextItem>
#include "dijkstra.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

    void on_startBtn_clicked();
    void onVertexProcessing(int &name, QColor color);
    void onEdgeProcessing(int &from, int &to, int &weight);

private:
    Ui::MainWindow *ui;
    Dijkstra *dijkstra;

    QGraphicsScene *m_scene;
    QMap<int, QGraphicsEllipseItem*> m_vertices; // хранить вершины
    QMap<QPair<int, int>, QGraphicsTextItem*> m_edges; // хранить ребра
    void addVertex(qreal x, qreal y, const int &w);
    void addEdge(qreal x1, qreal y1, qreal x2, qreal y2, const int& from, const int& to);


};
#endif // MAINWINDOW_H
