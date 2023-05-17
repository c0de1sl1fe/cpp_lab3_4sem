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

    void walk_(const vertexType& start_vertex/*, std::function<void(const vertexType&)> action*/)
    {
        std::cout << "ok";
        visited[start_vertex] = true;
        std::queue<vertexType> queue;
        queue.push(start_vertex);
        vertexType tmp = queue.front();
        while (!queue.empty())
        {
            queue.pop();
            std::cout << tmp;
            //action(tmp);
            for (auto it = graph[tmp].begin(); it != graph[tmp].end(); it++)
            {
                if(!visited[it->first])
                    queue.push(it->first);
            }
            tmp = queue.front();
            visited[tmp] = true;
        }
    }

    vertexType getVertexWithMinDist(std::map<vertexType, bool>& unproceesedVertes, std::map<vertexType, dist_type>& distToNode)
    {
        vertexType vertexWithMinDist; // will be error with string
        dist_type minDist= std::numeric_limits<dist_type>::max();
        for (auto it = unproceesedVertes.begin(); it != unproceesedVertes.end(); it++)
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
    void calculateDistToEachVertex(std::map<vertexType, bool>& unproceesedVertes, std::map<vertexType, dist_type>& distToNode)
    {
        while (!unproceesedVertes.empty())
        {
            vertexType vertex = getVertexWithMinDist(unproceesedVertes, distToNode);
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
            /*path.push_back(vertex);*/
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
        
        //path.push_back(graph[vertex][path[path.size()].id1]);
        std::reverse(path.begin(), path.end());
        return path;
    }
public:
    //проверка-добавление-удаление вершин
    bool has_vertex(const vertexType& v) const
    {
        return graph.count(v);
    }
    void add_vertex(const vertexType& v)
    {
        if (!has_vertex(v))
        {
            std::map<vertexType, Edge<vertexType, dist_type>> tmp;
            graph[v] = tmp;
        }
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
            if (it->second.count(v) != 0)//it->second.find(v) != it->second.end()
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
    ////проверка-добавление-удаление ребер
    void add_edge(const vertexType& from, const vertexType& to, const dist_type& d)
    {
        Edge<vertexType, dist_type> tmp(from, to, d);
        if (!has_edge(tmp))
        {
            graph[from][to] = tmp;
        }
      
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
    bool remove_edge(const Edge<vertexType, dist_type>& e) //c учетом расстояния
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
    bool has_edge(const Edge<vertexType, dist_type>& e) //c учетом расстояния в Edge
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
    ////получение всех ребер, выходящих из вершины
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
    size_t order() const //порядок
    {
        return graph.size();
    }
    size_t degree() const //степень
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
    void init()
    {
        for (auto it = graph.begin(); it != graph.end(); it++)
        {
            visited[it->first] = false;
        }
        //for (auto it = visited.begin(); it != visited.end(); it++)
        //{
        //    std::cout << it->first << " " << it->second;
        //}
    }



    ////поиск кратчайшего пути
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
    ////обход BFS
    void walk(const vertexType& start_vertex/*, std::function<void(const vertexType&)> action*/)
    {
        init();
        walk_(start_vertex);
        std::cout << std::endl;
        //for (auto& j : visited)
        //{
        //    std::cout << j.first << " - " << j.second << std::endl;
        //}
        for (auto& it : visited)
        {
            if (!it.second)
            {
                walk_(it.first);
                std::cout << std::endl;
                //for (auto& j : visited)
                //{
                //    std::cout << j.first << " - " << j.second << std::endl;
                //}
            }
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
