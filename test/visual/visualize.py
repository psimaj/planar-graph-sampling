#!/usr/bin/python3.6

import networkx as nx
import matplotlib.pyplot as plt

def get_input_graph():
    n, m = map(int, input().split())
    graph = nx.Graph()
    graph.add_nodes_from([i for i in range(1, n+1)])
    for i in range(m):
        a, b = map(int, input().split())
        graph.add_edge(a, b)
    return graph

def draw_graph(graph):
    pos = nx.planar_layout(graph)
    nx.draw_networkx(graph, pos=pos)
    plt.show()

graph = get_input_graph()
draw_graph(graph)