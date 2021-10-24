import networkx as nx


# graphs are assigned to network_x digraph
def graph_data(filename):
    file = open(filename, 'r',  encoding='utf-8')
    text = file.read()
    file.close()
    return assign_graph(text)


# graphs are assigned to digraph objects
def assign_graph(text):
    graph_set = list()
    # split into tokens by white space
    tokens = text.split()
    for word in tokens:
        if word == "<START>":
            graph = nx.DiGraph()
        elif word == "<END>":
            graph_set.append(graph)
        else:
            if word == "->":
                out_coming = temp
            elif word == ".":
                graph.add_edge(out_coming, temp)
            else:
                temp = word
    return graph_set