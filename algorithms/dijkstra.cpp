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

        visualizationQueue.enqueue({VERTEX_EVENT, u, -1, currentDist, Qt::yellow});
        pq.pop();

        if(currentDist > distances[u]) continue;

        for(const auto &edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;
            int newDistance = distances[u] + weight;

            visualizationQueue.enqueue({EDGE_EVENT, u, v, newDistance, Qt::red});
            if(newDistance < distances[v])
            {
                // Обновленное расстояние
                visualizationQueue.enqueue({EDGE_EVENT, u, v, newDistance, Qt::green});
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

    QTimer::singleShot(0, this, &Dijkstra::visualStep);
}

void Dijkstra::stopVisualization()
{
    if (m_timer && m_timer->isActive()) {
        m_timer->stop();
        emit finished();
        return;
    }
}

void Dijkstra::visualStep()
{
    if(visualizationQueue.isEmpty())
    {
        m_timer->stop();
        emit finished();
        return;
    }

    //логика для весов ребер

    /*str_edge currentEdge = weightsToVisualize.dequeue();
    emit edgeProcessing(currentEdge.from, currentEdge.to, currentEdge.weight);
    if(vertexToVisualize.isEmpty())
        return;
    int currentVertex = vertexToVisualize.dequeue();
    emit vertexProcessing(currentVertex, Qt::yellow);*/

    auto event = visualizationQueue.dequeue();
    switch(event.type)
    {
        case VERTEX_EVENT:
        {
            emit vertexProcessing(event.from, event.color);
            break;
        }
        case EDGE_EVENT:
        {
            emit edgeProcessing(event.from, event.to, event.weight, event.color);
            break;
        }
    }
}
