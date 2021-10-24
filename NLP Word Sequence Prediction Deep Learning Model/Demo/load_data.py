import os
import string


def load_doc(filename):
    # open the file as read only
    file = open(filename, 'r', encoding='utf-8')
    title = file.readline()
    # read all text
    text = file.read()
    # close the file
    file.close()
    tokens = clean_doc(text)
    return tokens, load_title(title)


def load_title(text):
    tokens = clean_doc(text)
    title = "\t"
    for token in tokens:
        title += token + " "
    title += "\n"
    return title


def clean_doc(doc):
    # replace '--' with a space ' '
    doc = doc.replace('--', ' ')
    # split into tokens by white space
    tokens = doc.split()
    # remove punctuation from each token
    table = str.maketrans('', '', string.punctuation)
    tokens = [w.translate(table) for w in tokens]
    # remove remaining tokens that are not alphabetic
    #   tokens = [word for word in tokens if word.isalpha()]
    tokens = [word for word in tokens if word.isalpha() or word.isnumeric()]
    # make lower case
    tokens = [word.lower() for word in tokens]
    return tokens


def load_data_set(path):
    data_sets = []
    titles = []
    new_sections = os.listdir(path)
    for section in new_sections:
        news = ""
        title = ""
        graph = load_doc(str(path) + "/" + str(section))
        news = graph[0]
        title = graph[1]
        data_sets.append(news)
        titles.append(title)
        news = ""
        title = ""
    return data_sets, titles


# creating of "word of graph" format
def creating_graph(word_list):
    f = open("news_graph.txt", "w", encoding='utf-8')
    for sub_graphs in word_list:
        count = 0
        f.write("<START>\n")
        for index in range(0, len(sub_graphs)):
            try:
                f.write(str(sub_graphs[index]) + " -> " + str(sub_graphs[index + 1]) + " .\n")
            except Exception:
                pass
            count += 1
        f.write("<END>\n\n")
    f.close()


# creating of "word of graph" format
def target_titles(titles):
    f = open('news_titles.txt', "r", encoding='utf-8')
    lines = f.readlines()
    # read all lines at once
    return lines
