#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #F8F9FA, stop:1 #495057);");
    ui->graphicsView->setStyleSheet("background-color: #F8F9FA");
    dijkstra = new Dijkstra;
    connect(dijkstra, &Dijkstra::vertexProcessing, this, &MainWindow::onVertexProcessing);
    connect(dijkstra, &Dijkstra::edgeProcessing, this, &MainWindow::onEdgeProcessing);
    connect(dijkstra, &Dijkstra::finished, this, [](){
        qDebug() << "Алгоритм завершил работу";
    });

    m_scene = new QGraphicsScene;
    ui->label->setStyleSheet("color: #495057; font-size: 16px; font-weight: bold;"); // введите веса
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);  // Сглаживание

    addVertex(-200, 100, 0);
    addVertex(-100, 0, 1);
    addVertex(-150, 200, 2);
    addVertex(-50, 200, 3);
    addVertex(-80, 110, 4);
    addVertex(100, 50, 5);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dijkstra;
}

void MainWindow::on_startBtn_clicked()
{
    // график
    if(!m_vertices.isEmpty())
    {
        for(auto &vertex : m_vertices)
        {
            vertex->setBrush(QBrush(Qt::lightGray));
        }
    }
    vector<vector<pair<int, int> > > graph =
    {
        {{1, ui->sb_01->value()}, {2, ui->sb_02->value()}},           // Вершина 0
        {{4, ui->sb_14->value()}, {5, ui->sb_15->value()}},           // Вершина 1
        {{4, ui->sb_24->value()}, {3, ui->sb_23->value()}},           // Вершина 2
        {{5, ui->sb_35->value()}},                                    // Вершина 3
        {{5, ui->sb_45->value()}},                                    // Вершина 4
        {}                                                            // Вершина 5
    };

    dijkstra->findShortestPath(graph, 0);


}

void MainWindow::onVertexProcessing(int &name, QColor color)
{
    if (m_vertices.contains(name)) {
        m_vertices[name]->setBrush(QBrush(color));
    }
}

void MainWindow::onEdgeProcessing(int &from, int &to, int &weight, QColor color)
{
    if(m_edges.contains({from, to}))
    {
        m_edges[qMakePair(from, to)]->setPlainText(QString::number(weight));
        m_edges[qMakePair(from, to)]->setDefaultTextColor(color);
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

void MainWindow::addEdge(qreal x1, qreal y1, qreal x2, qreal y2, const int& from, const int& to, int weight)
{
    m_scene->addLine(x1, y1, x2, y2);
    QGraphicsTextItem *edgeText = m_scene->addText(QString::number(weight));
    edgeText->setPos((x1+x2)/2, (y1+y2)/2);
    edgeText->setZValue(1);
    QFont font;
    font.setFamily("TimesNewRoman");
    font.setPointSize(12);
    edgeText->setFont(font);
    m_edges[qMakePair(from, to)] = edgeText;
}

void MainWindow::buildEdges()
{
    addEdge(-165, 105, -90, 37, 0, 1, ui->sb_01->value());
    addEdge(-175, 139, -135, 200, 0, 2, ui->sb_02->value());
    addEdge(-110, 220, -50, 220, 2, 3, ui->sb_23->value());
    addEdge(-120, 202, -75, 142, 2, 4, ui->sb_24->value());
    addEdge(-40, 130, 100, 70, 4, 5, ui->sb_45->value());
    addEdge(-60, 20, 100, 70, 1, 5, ui->sb_15->value());
    addEdge(-10, 220, 100, 70, 3, 5, ui->sb_35->value());
    addEdge(-75, 40, -60, 110, 1, 4, ui->sb_14->value());
}

void MainWindow::on_addWeightsBtn_clicked()
{
    if(m_edges.isEmpty())
        buildEdges();
    else
    {
        for(auto &edge : m_edges)
        {
            edge->setVisible(false);
        }

        buildEdges();
    }
}


void MainWindow::on_stopBtn_clicked()
{

}

