#include <iostream> 
#include <memory>
#include <vector>
#include "Class.h"

void exampleOfDijkstraAlgorithm()
{
    MyGraph<std::string> a;
    a.add_vertex("a");
    a.add_vertex("b");
    a.add_vertex("c");
    a.add_vertex("d");
    a.add_vertex("e");
    a.add_vertex("f");
    a.add_edge("a", "c", 7);
    a.add_edge("a", "a", 7);
    a.add_edge("a", "b", 3);
    a.add_edge("b", "d", 8);
    a.add_edge("b", "e", 1);
    a.add_edge("c", "d", 5);
    a.add_edge("e", "f", 5);
    a.add_edge("f", "d", 1);
    std::cout << a;
    for (auto i : a.shortest_path("a", "d"))
    {
        std::cout << i;
    }
    a.walk("a", Print<std::string>);
}
double EnterNumber()
{
    double tmp;
    char stmp[24];
    bool exit1 = false;
    while (!exit1)
    {
        bool exit = true;
        gets_s(stmp);
        char* endptr = stmp;
        tmp = strtod(stmp, &endptr);
        if (endptr == stmp)
        {
            exit = false;
            continue;
        }
        if ((tmp == DBL_MAX || tmp == DBL_MIN) && errno == ERANGE)
        {
            exit = false;
            continue;
        }
        while (*endptr)
        {
            if ((*endptr != ' ') && (*endptr != '\n'))
            {
                exit = false;
                break;
            }
            endptr++;
        }
        if (exit)
        {
            exit1 = true;
        }
        else
        {
            exit1 = false;
            printf("\nsomething wrong with number\n");
        }
    }
    return tmp;
}

void menu()
{
    system("cls");
    std::cout << "1. Create a graph" << std::endl;
    std::cout << "2. Task" << std::endl;
    std::cout << "3. ExtraTask" << std::endl;
    std::cout << "4. Finish the program" << std::endl;
    std::cout << "choice: ";
}
void menu1()
{
    system("cls");
    std::cout << "Choose data type for the vertices:" << std::endl;
    std::cout << "1. int" << std::endl;
    std::cout << "2. double" << std::endl;
    std::cout << "3. string" << std::endl;
    std::cout << "4. back main menu " << std::endl;
    std::cout << "choice: ";
}
void menu11()
{
    system("cls");
    std::cout << "1. Add vertix" << std::endl;
    std::cout << "2. Remove vertix" << std::endl;
    std::cout << "3. Add edge" << std::endl;
    std::cout << "4. Exist edge" << std::endl;
    std::cout << "5. Remove edge weight" << std::endl;
    std::cout << "6. Remove edge weightless" << std::endl;
    std::cout << "7. Find the shortest path" << std::endl;
    std::cout << "8. BFS" << std::endl;
    std::cout << "9. Print graph" << std::endl;
    std::cout << "10. Back menu" << std::endl;
    std::cout << "choice: ";
}

int main() 
{
    int choice = 0;
    bool exit = false;
    while (!exit)
    {
        menu();
        choice = EnterNumber();
        switch (choice)
        {
        case(1):
        {
            int choice1 = 0;
            bool exit1 = false;
            while (!exit1)
            {
                menu1();
                choice1 = EnterNumber();
                switch (choice1)
                {
                case(1):
                {
                    //type_int
                    int choice11 = 0;
                    bool exit11 = false;
                    MyGraph<int> graph;
                    while (!exit11)
                    {
                        menu11();
                        choice11 = EnterNumber();
                        switch (choice11)
                        {
                        case(1):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            int vertex = (int)EnterNumber();
                            if (!graph.add_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " already exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been added successfully" << std::endl;
                            }
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(2):
                        {
                            std::cout << "Enter vertex: ";
                            system("cls");
                            int vertex = (int)EnterNumber();
                            if (!graph.remove_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(3):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            int vertex1 = (int)EnterNumber();
                            std::cout << "enter second vertex: ";
                            int vertex2 = (int)EnterNumber();
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            if (!graph.add_edge(vertex1, vertex2, weight))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " already exist or doesn't exist vertex1: " << vertex1 << " or vertex2: " << vertex2 << std::endl;
                            }
                            else
                            {
                                std::cout << "Edge has been added successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(4):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            int vertex1 = (int)EnterNumber();
                            std::cout << "enter second vertex: ";
                            int vertex2 = (int)EnterNumber();
                            if (!graph.has_edge(vertex1, vertex2))
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
                            }
                            system("pause");
                            break;
                        }
                        case(5):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            int vertex1 = (int)EnterNumber();
                            std::cout << "enter second vertex: ";
                            int vertex2 = (int)EnterNumber();
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            Edge<int> tmp(vertex1, vertex2, weight);
                            if (!graph.remove_edge(tmp))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(6):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            int vertex1 = (int)EnterNumber();
                            std::cout << "enter second vertex: ";
                            int vertex2 = (int)EnterNumber();
                            if (!graph.remove_edge(vertex1, vertex2))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(7):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            int vertex1 = (int)EnterNumber();
                            std::cout << "enter second vertex: ";
                            int vertex2 = (int)EnterNumber();
                            std::vector<Edge<int>> tmp = graph.shortest_path(vertex1, vertex2);
                            if (tmp.size() == 0)
                            {
                                std::cout << "Shortest path doesn't exist" << std::endl;
                            }
                            else
                            {
                                std::cout << std::endl << "Shortest path: ";
                                for (auto i : tmp)
                                {
                                    std::cout << i << " ";
                                }
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(8):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            int vertex = (int)EnterNumber();
                            if (!graph.has_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "BFS: ";
                                graph.walk(vertex, Print<int>);
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(9):
                        {
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(10):
                        {
                            std::cout << "Take care, polar bear!" << std::endl;
                            exit11 = true;
                            break;
                        }
                        default:
                            std::cout << "something went wrong, try again" << std::endl;
                            system("pause");
                            break;
                        }
                    }
                    break;
                }
                case(2):
                {
                    //type_double
                    int choice11 = 0;
                    bool exit11 = false;
                    MyGraph<double> graph;
                    while (!exit11)
                    {
                        menu11();
                        choice11 = EnterNumber();
                        switch (choice11)
                        {
                        case(1):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            double vertex = EnterNumber();
                            if (!graph.add_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " already exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been added successfully" << std::endl;
                            }
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(2):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            double vertex = EnterNumber();
                            if (!graph.remove_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(3):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            double vertex1 = EnterNumber();
                            std::cout << "enter second vertex: ";
                            double vertex2 = EnterNumber();
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            if (!graph.add_edge(vertex1, vertex2, weight))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " already exist or doesn't exist vertex1: " << vertex1 << " or vertex2: " << vertex2 << std::endl;
                            }
                            else
                            {
                                std::cout << "Edge has been added successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(4):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            double vertex1 = EnterNumber();
                            std::cout << "enter second vertex: ";
                            double vertex2 = EnterNumber();
                            if (!graph.has_edge(vertex1, vertex2))
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
                            }
                            system("pause");
                            break;
                        }
                        case(5):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            double vertex1 = EnterNumber();
                            std::cout << "enter second vertex: ";
                            double vertex2 = EnterNumber();
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            Edge<double> tmp(vertex1, vertex2, weight);
                            if (!graph.remove_edge(tmp))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(6):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            double vertex1 = EnterNumber();
                            std::cout << "enter second vertex: ";
                            double vertex2 = EnterNumber();
                            if (!graph.remove_edge(vertex1, vertex2))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(7):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            double vertex1 = EnterNumber();
                            std::cout << "enter second vertex: ";
                            double vertex2 = EnterNumber();
                            std::vector<Edge<double>> tmp = graph.shortest_path(vertex1, vertex2);
                            if (tmp.size() == 0)
                            {
                                std::cout << "Shortest path doesn't exist" << std::endl;
                            }
                            else
                            {
                                std::cout << std::endl << "Shortest path: ";
                                for (auto i : tmp)
                                {
                                    std::cout << i << " ";
                                }
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(8):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            double vertex = EnterNumber();
                            if (!graph.has_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "BFS: ";
                                graph.walk(vertex, Print<double>);
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(9):
                        {
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(10):
                        {
                            std::cout << "Take care, polar bear!" << std::endl;
                            exit11 = true;
                            break;
                        }
                        default:
                            std::cout << "something went wrong, try again" << std::endl;
                            system("pause");
                            break;
                        }
                    }
                    break;
                }
                case(3):
                {
                    //type_string
                    int choice11 = 0;
                    bool exit11 = false;
                    MyGraph<std::string> graph;
                    while (!exit11)
                    {
                        menu11();
                        choice11 = EnterNumber();
                        switch (choice11)
                        {
                        case(1):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            std::string vertex = " ";
                            std::cin >> vertex;
                            if (!graph.add_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " already exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been added successfully" << std::endl;
                            }
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(2):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            std::string vertex = " ";
                            std::cin >> vertex;
                            if (!graph.remove_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Vertex has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(3):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            std::string vertex1 = " ";
                            std::cin >> vertex1;
                            std::cout << "enter second vertex: ";
                            std::string vertex2 = " ";
                            std::cin >> vertex2;
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            if (!graph.add_edge(vertex1, vertex2, weight))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " already exist or doesn't exist vertex1: " << vertex1 << " or vertex2: " << vertex2 << std::endl;
                            }
                            else
                            {
                                std::cout << "Edge has been added successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(4):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            std::string vertex1 = " ";
                            std::cin >> vertex1;
                            std::cout << "enter second vertex: ";
                            std::string vertex2 = " ";
                            std::cin >> vertex2;
                            if (!graph.has_edge(vertex1, vertex2))
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
                            }
                            system("pause");
                            break;
                        }
                        case(5):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            std::string vertex1 = " ";
                            std::cin >> vertex1;
                            std::cout << "enter second vertex: ";
                            std::string vertex2 = " ";
                            std::cin >> vertex2;
                            std::cout << "enter weight of edge: ";
                            double weight = EnterNumber();
                            Edge<std::string> tmp(vertex1, vertex2, weight);
                            if (!graph.remove_edge(tmp))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(6):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            std::string vertex1 = " ";
                            std::cin >> vertex1;
                            std::cout << "enter second vertex: ";
                            std::string vertex2 = " ";
                            std::cin >> vertex2;
                            if (!graph.remove_edge(vertex1, vertex2))
                            {
                                std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "Edge has been erased successfully" << std::endl;
                            }
                            system("pause");
                            break;
                        }
                        case(7):
                        {
                            system("cls");
                            std::cout << "enter first vertex: ";
                            std::string vertex1 = " ";
                            std::cin >> vertex1;
                            std::cout << "enter second vertex: ";
                            std::string vertex2 = " ";
                            std::cin >> vertex2;
                            std::vector<Edge<std::string>> tmp = graph.shortest_path(vertex1, vertex2);
                            if (tmp.size() == 0)
                            {
                                std::cout << "Shortest path doesn't exist" << std::endl;
                            }
                            else
                            {
                                std::cout << std::endl << "Shortest path: ";
                                for (auto i : tmp)
                                {
                                    std::cout << i << " ";
                                }
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(8):
                        {
                            system("cls");
                            std::cout << "Enter vertex: ";
                            std::string vertex = " ";
                            std::cin >> vertex;
                            if (!graph.has_vertex(vertex))
                            {
                                std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
                            }
                            else
                            {
                                std::cout << "BFS: ";
                                graph.walk(vertex, Print<std::string>);
                            }
                            std::cout << std::endl;
                            system("pause");
                            break;
                        }
                        case(9):
                        {
                            std::cout << graph;
                            system("pause");
                            break;
                        }
                        case(10):
                        {
                            std::cout << "Take care, polar bear!" << std::endl;
                            exit11 = true;
                            break;
                        }
                        default:
                            std::cout << "something went wrong, try again" << std::endl;
                            system("pause");
                            break;
                        }
                    }
                    break;
                }
                case(4):
                {
                    std::cout << "See you later, alligator!" << std::endl;
                    exit1 = true;
                    break;
                }
                default:
                    std::cout << "something went wrong, try again" << std::endl;
                    system("pause");
                    break;
                }
            }
            break;
        }
        case(2):
        {
            MyGraph<int>graph;
            graph.add_vertex(1);
            graph.add_vertex(2);
            graph.add_vertex(3);
            graph.add_vertex(4);
            graph.add_vertex(5);
            graph.add_vertex(6);
            graph.add_edge(1, 2, 3);
            graph.add_edge(1, 4, 8);
            graph.add_edge(2, 1, 2);
            graph.add_edge(2, 5, 5);
            graph.add_edge(2, 3, 6);
            graph.add_edge(4, 6, 7);
            graph.add_edge(5, 4, 5);
            graph.add_edge(5, 3, 9);
            graph.add_edge(6, 5, 1);
            graph.add_edge(6, 2, 7);
            std::cout << graph << std::endl;
            std::cout << "Optimal point is: " << graph.findOptimalVertex() << std::endl;
            system("pause");
            break;
        }
        case(3):
        {
            system("cls");
            MyGraph<std::string> a;
            a.add_vertex("a");
            a.add_vertex("b");
            a.add_vertex("c");
            a.add_vertex("d");
            a.add_vertex("e");
            a.add_vertex("f");
            a.add_edge("a", "c", 7);
            a.add_edge("a", "a", 7);
            a.add_edge("a", "b", 3);
            a.add_edge("b", "d", 8);
            a.add_edge("b", "e", 1);
            a.add_edge("c", "d", 5);
            a.add_edge("e", "f", 5);
            a.add_edge("f", "d", 1);
            std::cout << a << std::endl;
            std::cout << "bfs through graph uning extra function \"Print<typedata>\"" << std::endl;
            a.walk("a", Print<std::string>);
            system("pause");
            break;
        }
        case(4):
        {
            std::cout << "See you soon, raccoon!" << std::endl;
            exit = true;
            break;
        }
        default:
            std::cout << "something went wrong, try again" << std::endl;
            system("pause");
            break;
        }
    }


    //int choice11 = 0;
    //bool exit11 = false;
    //while (!exit11)
    //{
    //    menu11();
    //    choice11 = EnterNumber();
    //    MyGraph<int> graph;
    //    switch (choice11)
    //    {
    //    case(1):
    //    {
    //        system("cls");
    //        std::cout << "Enter vertex: ";
    //        int vertex = (int)EnterNumber();
    //        if (!graph.add_vertex(vertex))
    //        {
    //            std::cout << "something went wrong: vertex " << vertex << " already exist";
    //        }
    //        else
    //        {
    //            std::cout << "Vertex has been added successfully" << std::endl;
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(2):
    //    {
    //        system("cls");
    //        int vertex = (int)EnterNumber();
    //        if (!graph.remove_vertex(vertex))
    //        {
    //            std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
    //        }
    //        else
    //        {
    //            std::cout << "Vertex has been erased successfully" << std::endl;
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(3):
    //    {
    //        system("cls");
    //        std::cout << "enter first vertex: ";
    //        int vertex1 = (int)EnterNumber();
    //        std::cout << "enter second vertex: ";
    //        int vertex2 = (int)EnterNumber();
    //        std::cout << "enter weight of edge: ";
    //        double weight = EnterNumber();
    //        if (!graph.add_edge(vertex1, vertex2, weight))
    //        {
    //            std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " already exist";
    //        }
    //        else
    //        {
    //            std::cout << "Edge has been added successfully" << std::endl;
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(4):
    //    {
    //        system("cls");
    //        std::cout << "enter first vertex: ";
    //        int vertex1 = (int)EnterNumber();
    //        std::cout << "enter second vertex: ";
    //        int vertex2 = (int)EnterNumber();
    //        if (!graph.has_edge(vertex1, vertex2))
    //        {
    //            std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
    //        }
    //        else
    //        {
    //            std::cout << "edge " << "(" << vertex1 << ", " << vertex2 << ")" << " exists";
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(5):
    //    {
    //        system("cls");
    //        std::cout << "enter first vertex: ";
    //        int vertex1 = (int)EnterNumber();
    //        std::cout << "enter second vertex: ";
    //        int vertex2 = (int)EnterNumber();
    //        std::cout << "enter weight of edge: ";
    //        double weight = EnterNumber();
    //        Edge<int> tmp(vertex1, vertex2, weight);
    //        if (!graph.remove_edge(tmp))
    //        {
    //            std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")_" << weight << " doesn't exist";
    //        }
    //        else
    //        {
    //            std::cout << "Edge has been erased successfully" << std::endl;
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(6):
    //    {
    //        system("cls");
    //        std::cout << "enter first vertex: ";
    //        int vertex1 = (int)EnterNumber();
    //        std::cout << "enter second vertex: ";
    //        int vertex2 = (int)EnterNumber();
    //        if (!graph.remove_edge(vertex1, vertex2))
    //        {
    //            std::cout << "something went wrong: edge " << "(" << vertex1 << ", " << vertex2 << ")" << " doesn't exist";
    //        }
    //        else
    //        {
    //            std::cout << "Edge has been erased successfully" << std::endl;
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(7):
    //    {
    //        system("cls");
    //        std::cout << "enter first vertex: ";
    //        int vertex1 = (int)EnterNumber();
    //        std::cout << "enter second vertex: ";
    //        int vertex2 = (int)EnterNumber();
    //        std::vector<Edge<int>> tmp = graph.shortest_path(vertex1, vertex2);
    //        if (tmp.size() == 0)
    //        {
    //            std::cout << "Shortest path doesn't exist" << std::endl;
    //        }
    //        else
    //        {
    //            std::cout << std::endl << "Shortest path: ";
    //            for (auto i : tmp)
    //            {
    //                std::cout << i << " ";
    //            }
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(8):
    //    {
    //        system("cls");
    //        std::cout << "Enter vertex: ";
    //        int vertex = (int)EnterNumber();
    //        if (!graph.has_vertex(vertex))
    //        {
    //            std::cout << "something went wrong: vertex " << vertex << " doesn't exist";
    //        }
    //        else
    //        {
    //            std::cout << "BFS: ";
    //            graph.walk(vertex, Print<int>);
    //        }
    //        system("pause");
    //        break;
    //    }
    //    case(9):
    //    {
    //        std::cout << graph;
    //        system("pause");
    //        break;
    //    }
    //    case(10):
    //    {

    //        std::cout << "Take care, polar bear!" << std::endl;
    //        exit11 = true;
    //        break;
    //    }
    //    default:
    //        std::cout << "something went wrong, try again" << std::endl;
    //        system("pause");
    //        break;
    //    }
    //}



    return 1;
}