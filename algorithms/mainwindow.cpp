#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dijkstra = new Dijkstra;
    connect(dijkstra, &Dijkstra::vertexProcessing, this, &MainWindow::onVertexProcessing);
    connect(dijkstra, &Dijkstra::edgeProcessing, this, &MainWindow::onEdgeProcessing);
    connect(dijkstra, &Dijkstra::finished, this, [](){
        qDebug() << "Алгоритм завершил работу";
    });

    m_scene = new QGraphicsScene;
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);  // Сглаживание

    addVertex(-200, 100, 0);
    addVertex(-100, 0, 1);
    addVertex(-150, 200, 2);
    addVertex(-50, 200, 3);
    addVertex(-80, 110, 4);
    addVertex(100, 50, 5);

    addEdge(-165, 105, -90, 37, 0, 1);
    addEdge(-170, 137, -140, 203, 0, 2);
    addEdge(-110, 220, -50, 220, 2, 3);
    addEdge(-120, 202, -75, 142, 2, 4);
    addEdge(-40, 130, 100, 70, 4, 5);
    addEdge(-60, 20, 100, 70, 1, 5);
    addEdge(-10, 220, 100, 70, 3, 5);
    addEdge(-75, 40, -60, 110, 1, 4);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dijkstra;
}

void MainWindow::on_startBtn_clicked()
{
    // график
    vector<vector<pair<int, int> > > graph =
    {
        {{1, 4}, {2, 1}},           // Вершина 0
        {{4, 2}, {5, 8}},           // Вершина 1
        {{4, 3}, {3, 2}},           // Вершина 2
        {{5, 9}},                   // Вершина 3
        {{5, 5}},                   // Вершина 4
        {}                          // Вершина 5
    };

    dijkstra->findShortestPath(graph, 0);


}

void MainWindow::onVertexProcessing(int &name, QColor color)
{
    if (m_vertices.contains(name)) {
        m_vertices[name]->setBrush(QBrush(color));
    }
}

void MainWindow::onEdgeProcessing(int &from, int &to, int &weight)
{
    if(m_edges.contains({from, to}))
    {
        m_edges[qMakePair(from, to)]->setPlainText(QString::number(weight));
    }
}

void MainWindow::addVertex(qreal x, qreal y, const int &name)
{
    QGraphicsEllipseItem *vertex = m_scene->addEllipse(x, y, 40, 40, QPen(Qt::black), QBrush(Qt::lightGray));
    QGraphicsTextItem *text = m_scene->addText(QString::number(name));
    text->setPos(x+8, y+8);
    text->setParentItem(vertex);

    m_vertices[name] = vertex;
}

void MainWindow::addEdge(qreal x1, qreal y1, qreal x2, qreal y2, const int& from, const int& to)
{
    m_scene->addLine(x1, y1, x2, y2);
    QGraphicsTextItem *edgeText = m_scene->addText("∞");
    edgeText->setPos((x1+x2)/2, (y1+y2)/2);
    edgeText->setZValue(1);
    m_edges[qMakePair(from, to)] = edgeText;
}



