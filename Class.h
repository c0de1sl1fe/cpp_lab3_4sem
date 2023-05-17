#pragma once
#include <iostream> 
#include <memory>
#include <vector>
#include<map>
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

template<>
struct Edge<std::string, double>
{
    std::string id1;
    std::string id2;
    double dist;
    Edge(std::string id1_ = " ", std::string id2_ = " ", double distance_ = 0) : id1(id1_), id2(id2_), dist(distance_) {}
    bool operator ==(Edge& src)
    {
        return (id1 == src.id1 && id2 == src.id2 && dist == src.dist);
    }
    friend std::ostream& operator<<(std::ostream& os, Edge<std::string, double>& obj)
    {
        os << "(" << obj.id1 << ", " << obj.id2 << ")_" << obj.dist << " ";
        return os;
    }

};
template<typename vertexType, typename dist_type = double>
class MyGraph {
private:

    std::map<vertexType, std::map<vertexType, Edge<vertexType, dist_type>>> graph;
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
    //size_t order() const; //порядок
    //size_t degree() const; //степень
    ////поиск кратчайшего пути
    //std::vector<Edge> shortest_path(const vertexType& from,
    //    const vertexType& to) const;
    ////обход
    //std::vector<vertexType> walk(const vertexType& start_vertex)const;
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
};