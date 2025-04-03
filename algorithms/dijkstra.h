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
    void edgeProcessing(int &from, int &to, int &weight);
    void finished();

private:
    QTimer *m_timer;
    vector<int> distances; // массив кратчайших путей

    struct str_edge
    {
        int from;
        int to;
        int weight;
        bool isUpdated;
    };

    QQueue<str_edge> weightsToVisualize;
    QQueue<int> vertexToVisualize;

    void startVisualization();
    void visualStep();

};

#endif // DIJKSTRA_H
