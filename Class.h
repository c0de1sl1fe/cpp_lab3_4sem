#pragma once
#include <iostream> 
#include <memory>
#include <vector>
#include<map>
#include <algorithm>
#include <functional>
#include <queue>
int compare(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}
template<typename vertexType, typename Distance = double>
void Print(const vertexType& val)
{
    std::cout << val << ' ';
}
template<typename vertexType, typename dist_type = double>
struct Edge
{
    vertexType id1;
    vertexType id2;
    dist_type dist;
    Edge(vertexType id1_ = 0, vertexType id2_ = 0, dist_type distance_ = 0) : id1(id1_), id2(id2_), dist(distance_) {}
    bool operator ==(Edge& src)
    {
        return (id1 == src.id1 && id2 == src.id2 && dist == src.dist);
    }
    friend std::ostream& operator<<(std::ostream& os, Edge<vertexType, dist_type>& obj)
    {
        os << "(" << obj.id1 << ", " << obj.id2 << ")_" << obj.dist << " ";
        return os;
    }

};

template<typename dist_type>
struct Edge<std::string, dist_type>
{
    std::string id1;
    std::string id2;
    dist_type dist;
    Edge(std::string id1_ = " ", std::string id2_ = " ", dist_type distance_ = 0) : id1(id1_), id2(id2_), dist(distance_) {}
    bool operator ==(Edge& src)
    {
        return (id1 == src.id1 && id2 == src.id2 && dist == src.dist);
    }
    friend std::ostream& operator<<(std::ostream& os, Edge<std::string, dist_type>& obj)
    {
        os << "(" << obj.id1 << ", " << obj.id2 << ")_" << obj.dist << " ";
        return os;
    }

};
template<typename vertexType, typename dist_type = double>
class MyGraph {
private:

    std::map<vertexType, std::map<vertexType, Edge<vertexType, dist_type>>> graph;
    std::map<vertexType, bool> visited;
    void walk_(const vertexType& start_vertex, std::function<void(const vertexType&)> action)
    {
        std::queue<vertexType> queue;
        queue.push(start_vertex);
        vertexType tmp = queue.front();
        while (!queue.empty())
        {
            queue.pop();
            if (!visited[tmp])
            {
                action(tmp);
                visited[tmp] = true;
                for (auto it = graph[tmp].begin(); it != graph[tmp].end(); it++)
                {
                    if (!visited[it->first])
                        queue.push(it->first);
                }
                if(!queue.empty())
                    tmp = queue.front();
            }
        }
    }
    vertexType getVertexWithMinDist(std::map<vertexType, bool>& unproceesedVertes, std::map<vertexType, dist_type>& distToNode)
    {
        vertexType vertexWithMinDist = 0;
        dist_type minDist= std::numeric_limits<dist_type>::max();
        for (auto it = unproceesedVertes.begin(); it != unproceesedVertes.end(); it++)
        {
            dist_type dist = distToNode[it->first];
            if (dist < minDist)
            {
                minDist = dist;
                vertexWithMinDist = it->first;
            }
        }
        return vertexWithMinDist;
    }
    void calculateDistToEachVertex(std::map<vertexType, bool>& unproceesedVertes, std::map<vertexType, dist_type>& distToNode)
    {
        while (!unproceesedVertes.empty())
        {
            vertexType vertex = getVertexWithMinDist(unproceesedVertes, distToNode);
            if (vertex == 0)
                return;
            if (distToNode[vertex] == std::numeric_limits<dist_type>::max())
                return;
            for (auto it = graph[vertex].begin(); it != graph[vertex].end(); it++)
            {
                vertexType adjacentVertex = it->first;
                if (unproceesedVertes.count(adjacentVertex) != 0)
                {
                    dist_type distToCheck = distToNode[vertex] + it->second.dist;
                    if (distToCheck < distToNode[adjacentVertex])
                    {
                        distToNode[adjacentVertex] = distToCheck;
                    }
                }
            }
            unproceesedVertes.erase(vertex);
        }
    }
    std::vector<Edge<vertexType, dist_type>> getShortestPath_(const vertexType& from, const vertexType& to, std::map<vertexType, dist_type>& distToNode)
    {
        std::vector<Edge<vertexType, dist_type>> path;
        vertexType vertex = to;
        while (vertex != from)
        {
            dist_type minDistToVertex = distToNode[vertex];
            for (auto i : collectPartents(vertex))
            {
                vertexType parent = i;
                Edge<vertexType, dist_type> parentEdge = graph[i][vertex];
                if (distToNode.count(parent) == 0)
                    continue;
                if (parentEdge.dist + distToNode[parent] == minDistToVertex)
                {
                    path.push_back(graph[parent][vertex]);
                    distToNode.erase(vertex);
                    vertex = parent;
                    break;
                }
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }
public:
    bool has_vertex(const vertexType& v) const
    {
        return (graph.count(v) != 0);
    }
    bool add_vertex(const vertexType& v)
    {
        if (!has_vertex(v))
        {
            std::map<vertexType, Edge<vertexType, dist_type>> tmp;
            graph[v] = tmp;
            return true;
        }
        return false;
    }
    bool remove_vertex(const vertexType& v)
    {
        if (!has_vertex(v))
        {
            return false;
        }
        graph.erase(v);
        for (auto it = graph.begin(); it != graph.end();it++)
        {
            if (it->second.count(v) != 0)
            {
                it->second.erase(v);
            }
        }
        return true;
    }
    std::vector<vertexType> vertices() const
    {
        std::vector<vertexType> vertextArray;
        for (auto i = graph.begin(); i != graph.end(); i++)
        {
            vertextArray.push_back(i->first);
        }
        return vertextArray;
    }
    bool add_edge(const vertexType& from, const vertexType& to, const dist_type& d)
    {
        if (has_vertex(from) && has_vertex(to))
        {
            Edge<vertexType, dist_type> tmp(from, to, d);
            if (!has_edge(tmp))
            {
                graph[from][to] = tmp;
                return true;
            }
            return false;
        }
        return false; 
    }
    bool remove_edge(const vertexType& from, const vertexType& to)
    {
        if (has_edge(from, to))
        {
            graph[from].erase(to);
            return true;
        }
        return false;
    }
    bool remove_edge(const Edge<vertexType, dist_type>& e)
    {
        if (has_edge(e))
        {
            graph[e.id1].erase(e.id2);
        }
        return false;
    }
    bool has_edge(const vertexType& from, const vertexType& to)
    {
        if (has_vertex(from) && has_vertex(to))
        {
            if (graph[from].count(to) != 0)//graph[from].find(to) != graph[from].end()
            {
                return true;
            }
        }
        return false;
    }
    bool has_edge(const Edge<vertexType, dist_type>& e)
    {
        if (has_vertex(e.id1) && has_vertex(e.id2))
        {
            if (graph[e.id1].find(e.id2) != graph[e.id1].end())
            {
                if (graph[e.id1][e.id2].dist == e.dist)
                {
                    return true;
                }
            }
        }
        return false;
    }
    std::vector<Edge<vertexType, dist_type>> edges(const vertexType& vertex)
    {
        
        std::vector<Edge<vertexType, dist_type>> edgesArray;
        if (has_vertex(vertex))
        {
            for (auto i = graph[vertex].begin(); i != graph[vertex].end(); i++)
            {
                edgesArray.push_back(i->second);
            }
            return edgesArray;
        }
        return edgesArray;
    }
    size_t order() const
    {
        return graph.size();
    }
    size_t degree() const
    {
        int maxSize = -1;
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            std::vector<Edge<vertexType, dist_type>> edgesTmp = edges(it->first);
            int size = edgesTmp.size();
            if (size > maxSize)
            {
                maxSize = size;
            }
        }
        return maxSize;
    }
    std::vector<Edge<vertexType, dist_type>> shortest_path(const vertexType& from, const vertexType& to)
    {
        std::map<vertexType, dist_type> distToNode;
        std::map<vertexType, bool> unproceesedVertes;
        std::vector<Edge<vertexType, dist_type>> shortestPath;
        for (auto i = graph.begin(); i != graph.end(); i++)
        {
            distToNode[i->first] = std::numeric_limits<dist_type>::max();
            unproceesedVertes[i->first] = true;
        }
        distToNode[from] = 0;
        calculateDistToEachVertex(unproceesedVertes, distToNode);
        std::vector<Edge<vertexType, dist_type>> test;
        std::vector<vertexType>test1;
        if (distToNode[to] == std::numeric_limits<dist_type>::max())
            return test;
        test = getShortestPath_(from, to, distToNode);
        test1 = vertices();
        return test;
    }
    void walk(const vertexType& start_vertex, std::function<void(const vertexType&)> action)
    {
        if (!has_vertex(start_vertex))
        {
            return;
        }
        init();
        walk_(start_vertex, action);
        for (auto& it : visited)
        {
            if (!it.second)
            {
                walk_(it.first, action);
                std::cout << std::endl;
            }
        }
    }
    vertexType findOptimalVertex()
    {
        std::map<vertexType, dist_type> arrayOfDist;
        for (auto it1 = graph.begin(); it1 != graph.end(); it1++)
        {
            int infCount = 0;
            int okCount = graph.size() / 4;
            dist_type sum = 0;
            for (auto it2 = graph.begin(); it2 != graph.end(); it2++)
            {
                if (it1 == it2)
                {
                    continue;
                }
                std::vector<Edge<vertexType, dist_type>> tmp = shortest_path(it1->first, it2->first);
                //if (tmp.size() == 0)
                //{
                //    infCount++;
                //}
                //if (infCount >= okCount)
                //{
                //    arrayOfDist[it1->first] = std::numeric_limits<dist_type>::max();//kind of inf
                //    break;
                //}
                if (tmp.size() == 0)
                {
                    arrayOfDist[it1->first] = std::numeric_limits<dist_type>::max();//kind of inf
                    break;
                }
                for (auto i : tmp)
                {
                    sum += i.dist;
                }
            }
            if (arrayOfDist[it1->first] != std::numeric_limits<dist_type>::max())
            {
                arrayOfDist[it1->first] = sum;
            }
            //if (infCount < okCount)
            //{
            //    arrayOfDist[it1->first] = sum;
            //    
            //}
        }
        vertexType vertexWithMinDist;
        dist_type minDist = std::numeric_limits<dist_type>::max();
        for (auto it = arrayOfDist.begin(); it != arrayOfDist.end(); it++)
        {
            dist_type dist = it->second;
            if (dist < minDist)
            {
                minDist = dist;
                vertexWithMinDist = it->first;
            }
        }
        return vertexWithMinDist;
    }
    void init()
    {
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            visited[it->first] = false;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, MyGraph<vertexType, dist_type>& obj)
    {
        for (auto it1 = obj.graph.begin(); it1 != obj.graph.end(); it1++)
        {
            os << it1->first<<": ";
            for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
            {
                os << it2->second;
            }
            os << "\n";
        }
        return os;
    }
    std::vector<vertexType> collectPartents(vertexType vertex)
    {
        std::vector<vertexType> parents;
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            if (it->second.count(vertex) != 0)//it->second.find(v) != it->second.end()
            {
                parents.push_back(it->first);
            }
        }
        return parents;
    }
};

template<>
std::string MyGraph<std::string, double>::getVertexWithMinDist(std::map<std::string, bool>& unproceesedVertes, std::map<std::string, double>& distToNode)
{
    {
        std::string vertexWithMinDist = "";
        double minDist = std::numeric_limits<double>::max();
        for (auto it = unproceesedVertes.begin(); it != unproceesedVertes.end(); it++)
        {
            double dist = distToNode[it->first];
            if (dist < minDist)
            {
                minDist = dist;
                vertexWithMinDist = it->first;
            }
        }
        return vertexWithMinDist;
    }
}
template<>
void MyGraph<std::string, double>::calculateDistToEachVertex(std::map<std::string, bool>& unproceesedVertes, std::map<std::string, double>& distToNode)
{
    while (!unproceesedVertes.empty())
    {
        std::string vertex = getVertexWithMinDist(unproceesedVertes, distToNode);
        if (vertex == "")
            return;
        if (distToNode[vertex] == std::numeric_limits<double>::max())
            return;
        for (auto it = graph[vertex].begin(); it != graph[vertex].end(); it++)
        {
            std::string adjacentVertex = it->first;
            if (unproceesedVertes.count(adjacentVertex) != 0)
            {
                double distToCheck = distToNode[vertex] + it->second.dist;
                if (distToCheck < distToNode[adjacentVertex])
                {
                    distToNode[adjacentVertex] = distToCheck;
                }
            }
        }
        unproceesedVertes.erase(vertex);
    }
}