#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <QObject>
#include <vector>
#include <queue>
#include <QDebug>
#include <qcolor.h>
#include <QTimer>
#include <QQueue>

using namespace std;

class Dijkstra : public QObject
{
    Q_OBJECT

public:
    explicit Dijkstra(QObject *parent = nullptr);
    void findShortestPath(vector<vector<pair<int, int>>>& graph, int startVertex);

signals:
    void vertexProcessing(int &name, QColor color);
    void edgeProcessing(int &from, int &to, int &weight, QColor color);

    void finished();

private:
    QTimer *m_timer;
    vector<int> distances; // массив кратчайших путей

    enum eventType {VERTEX_EVENT, EDGE_EVENT};
    struct visualEvent
    {
        eventType type;
        int from; // вершина или начало ребра
        int to; // конец ребра
        int weight;
        QColor color;
    };

    QQueue<visualEvent> visualizationQueue;

    void startVisualization();
    void stopVisualization();
    void visualStep();

};

#endif // DIJKSTRA_H
