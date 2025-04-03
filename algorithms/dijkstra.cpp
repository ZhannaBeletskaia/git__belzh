#include "dijkstra.h"


const int INF = 1000000;

Dijkstra::Dijkstra(QObject *parent) : QObject(parent) {}


void Dijkstra::findShortestPath(vector<vector<pair<int, int> > > &graph, int startVertex)
{
    distances.assign(graph.size(), INF);
    distances[startVertex] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, startVertex});

    while(!pq.empty())
    {
        int currentDist = pq.top().first; // текущий вес вершины
        int u = pq.top().second; // текущая вершина
        vertexToVisualize.enqueue(u);
        pq.pop();

        if(currentDist > distances[u]) continue;

        for(const auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            int newDistance = distances[u] + weight;

            weightsToVisualize.enqueue({u, v, distances[v], false});

            if(newDistance < distances[v])
            {
                // Обновленное расстояние
                weightsToVisualize.enqueue({u, v, newDistance, true});
                distances[v] = newDistance;
                pq.push({distances[v], v});

            }
        }

    }

    startVisualization();
}

void Dijkstra::startVisualization()
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &Dijkstra::visualStep);
    m_timer->start(800);
}

void Dijkstra::visualStep()
{
    if(weightsToVisualize.isEmpty())
    {
        m_timer->stop();
        emit finished();
        return;
    }

    //логика для весов ребер

    str_edge currentEdge = weightsToVisualize.dequeue();
    emit edgeProcessing(currentEdge.from, currentEdge.to, currentEdge.weight);

    if(vertexToVisualize.isEmpty())
        return;

    int currentVertex = vertexToVisualize.dequeue();
    emit vertexProcessing(currentVertex, Qt::yellow);

}
