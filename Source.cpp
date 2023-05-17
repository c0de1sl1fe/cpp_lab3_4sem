#include <iostream> 
#include <memory>
#include <vector>
#include "Class.h"
//struct Edge
//{
//    int id1;
//    int id2;
//    double dist;
//    Edge(int id1_ = 0, int id_2 = 0, double distance_ = 0) : id1(id1_), id2(id_2), dist(distance_) {}
//};
//
//void Foo(std::vector<std::shared_ptr<Edge>> &array)
//{
//    Edge a(1, 2, 10);
//    std::shared_ptr<Edge> pa(&a);
//    array.push_back(pa);
//}
//
//#include<map>
template<typename vertexType, typename dist_type = double>
void print(Edge<vertexType, dist_type>& i)
{
    std::cout << i;
}

int main() 
{
    //std::vector<std::shared_ptr<Edge>> array;
    //std::vector<Edge*> array1;
    //Foo(array);
    //std::map<int, int> test;
    //test[1] = 1;
    //std::cout << (test.find(1)==test.end());


    MyGraph<int> a;
    a.add_vertex(1);
    a.add_vertex(2);
    a.add_vertex(3);
    a.add_vertex(4);
    a.add_edge(1, 3, 5);
    a.add_edge(2, 4, 5);
    a.add_edge(1, 2, 5);
    std::cout << a;
    a.edges(1);
    
    

    //std::cout << a;
    //std::cout << a.has_edge(1, 2);
    //std::cout << std::endl;
    //for (auto i : a.vertices())
    //{
    //    std::cout << i;
    //}
    //std::cout << a.order();
    //std::cout << std::endl;
    //a.init();
    // 
    //std::vector<int> tmp11 = { 3, 2, 1 };
    //std::qsort(tmp11.data(), tmp11.size(),sizeof(int),  compare);
    //for (auto i : tmp11)
    //{
    //    std::cout << i;
    //}
    //MyGraph<std::string> a;
    //a.add_vertex("test1");
    //a.add_vertex("test2");
    //a.add_edge("test1", "test2", 5);

    ////std::cout << a;
    //std::cout << a.has_edge("test1", "test2");
    //std::cout << std::endl;
    //for (auto i : a.vertices())
    //{
    //    std::cout << i;
    //}
    //std::map<int, std::map<double, bool>> test;
    //test[1][1.1] = 0;
    //test[1][2.2] = 1;
    //test[2][23.12] = 0;
    //std::map<int, int>test;
    //test[1] = 2;
    //std::cout << test.count(121);
    //for (auto i = test.begin(); i != test.end(); i++)
    //{
    //    std::cout << i->first;
    //    std::cout << i->second;
    //}
    //std::cout << test.empty();
    //test.erase(1);
    //test.erase(2);
    //std::cout << test.empty();
    
    //if (test[1].find(13) != test[1].end())
    //{
    //    std::cout << test[1][1];
    //}
    //for (auto it1 = test.begin(); it1 != test.end(); it1++)
    //{
    //    //os << it->first()<<" ";
    //    std::cout << it1->first << ": ";
    //    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
    //    {
    //        std::cout << it2->second;
    //    }
    //    std::cout << "\n";

    //}
    //std::queue<int> test;
    //test.push(1);
    //test.push(2);
    //test.push(3);
    //test.push(4);
    //test.pop();
    //std::cout << test.front()   ;
    //while (test.empty())

    return 1;
}