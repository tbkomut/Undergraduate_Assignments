import networkx as nx
import random
from gensim.models import Word2Vec
from sklearn.decomposition import PCA
from matplotlib import pyplot


import warnings
warnings.filterwarnings('ignore')


def node_embeddings(graph, path):
    temp = nx.DiGraph(graph)
    # we will get random walks each node in graphs.
    walks = random_walks(temp)
    return skip_gram_model(walks, path)


# train skip-gram (word2vec) model with random walks
def skip_gram_model(random_walk, path):
    model = Word2Vec(size=48, window=4, sg=1, hs=0,
                     negative=10,
                     alpha=0.03, min_alpha=0.0007,
                     seed=14)
    model.build_vocab(random_walk, progress_per=2)
    model.train(random_walk, total_examples=model.corpus_count, epochs=20, report_delay=1)
    print(model)
    #   save embeddings
    model.save(path)
    return model.wv.vectors


def random_walks(graph):
    random_walks_each_node = []
    for node in graph.nodes:
        for i in range(5):
            random_walks_each_node.append(get_random_walk(graph, node, 10))
    return random_walks_each_node


def get_random_walk(graph, node, path_length):
    random_walk = [node]
    for i in range(path_length - 1):
        temp = list()
        for neighbour in graph.neighbors(node):
            temp.append(neighbour)
        temp = list(set(temp) - set(random_walk))
        if len(temp) == 0:
            break
        random_node = random.choice(temp)
        random_walk.append(random_node)
        node = random_node
    return random_walk


def plot_graph(model):
    X = model[model.wv.vocab]
    pca = PCA(n_components=2)
    result = pca.fit_transform(X)
    # create a scatter plot of the projection
    pyplot.scatter(result[:, 0], result[:, 1])
    words = list(model.wv.vocab)
    for i, word in enumerate(words):
        pyplot.annotate(word, xy=(result[i, 0], result[i, 1]))
    pyplot.show()
