from graphs_nodes_chars import chars_length_graph_text, vector_size_operation, create_model_vector
from load_data import load_data_set, creating_graph, clean_doc, target_titles
from node_embeddings import node_embeddings
from word_graphs import graph_data
from keras.models import Model
from keras.layers import Input, LSTM, Dense, Dropout, Concatenate, Bidirectional
import numpy as np
import matplotlib.pyplot as plt
from gensim.models import Word2Vec
from nltk.translate.bleu_score import sentence_bleu
from keras.models import model_from_json
import keras


def draw_loss_epoch_graph():
#    print(history.history.keys())
    # summarize history for loss
#    plt.plot(history.history['loss'])
#    plt.plot(history.history['val_loss'])
    plt.title('model loss')
    plt.ylabel('loss')
    plt.xlabel('epoch')
    plt.legend(['train', 'test'], loc='upper left')
    plt.show()


def graph_encoder(graph_list, encoder_input_data):
    count = 0
    for graph in graph_list:
        path = "embeddings/" + str(count) + ".model"
        #   getting node embeddings with random walks.
        #   nodes = node_embeddings(graph, path)
        #   to get vectors from saved model for node embeddings.
        nodes = Word2Vec.load(path).wv.vectors
        y_count = 0
        for y in nodes:
            z_count = 0
            for z in y:
                encoder_input_data[count][y_count][z_count] = z
                z_count += 1
            y_count += 1
        count += 1
    return encoder_input_data


def decode_sequence(predict_input):
    # Encode the input as state vectors.
    states_value = encoder_model.predict(predict_input)
    # Generate empty target sequence of length 1.
    target_seq = np.zeros((1, 1, num_decoder_tokens))
    # Populate the first character of target sequence with the start character.
    target_seq[0, 0, target_token_index['\t']] = 1.
    # Sampling loop for a batch of sequences
    # (to simplify, here we assume a batch of size 1).
    stop_condition = False
    decoded_sentence = ''
    while not stop_condition:
        output_tokens, h, c = decoder_model.predict(
            [target_seq] + states_value)

        # Sample a token
        sampled_token_index = np.argmax(output_tokens[0, -1, :])
        sampled_char = reverse_target_char_index[sampled_token_index]
        decoded_sentence += sampled_char

        # Exit condition: either hit max length
        # or find stop character.
        if (sampled_char == '\n' or
                len(decoded_sentence) > max_decoder_seq_length):
            stop_condition = True

        # Update the target sequence (of length 1).
        target_seq = np.zeros((1, 1, num_decoder_tokens))
        target_seq[0, 0, sampled_token_index] = 1.
        # Update states
        states_value = [h, c]

    return decoded_sentence


blue_size = 100

#   return arrays of words in each file
graph_data_set = load_data_set("news")
#   return titles of word of graphs
titles = graph_data_set[1]
#   return graphs
word_of_data = graph_data_set[0]

#   convert to words of graph from words of each file
#   creating_graph(word_of_data)

# We getting word of graphs and titles of new texts
# graph_data return list of graphs
graph_list = graph_data("news_graph.txt")

# getting chars of graph texts and sequence titles.
input_characters, target_characters = chars_length_graph_text(word_of_data, titles)
input_characters = sorted(list(input_characters))
target_characters = sorted(list(target_characters))

# determining size of numpy vectors
num_encoder_tokens, num_decoder_tokens, max_encoder_seq_length, max_decoder_seq_length = \
    vector_size_operation(word_of_data, titles, input_characters, target_characters)

# creating numpy vectors for models
encoder_input_data, decoder_input_data, decoder_target_data = create_model_vector(word_of_data, num_encoder_tokens,
                                                                                  num_decoder_tokens,
                                                                                  max_encoder_seq_length,
                                                                                  max_decoder_seq_length)
# graph (1501, 488, 48)
print(encoder_input_data.shape)
# sequence (1501, 72, 46)
print(decoder_input_data.shape)
print(decoder_target_data.shape)


# graph side vectorization
# getting node embeddings with Random walks
# updating encoder_input_data
encoder_input_data = graph_encoder(graph_list, encoder_input_data)

# sequence side vectorization
# 46 chars(a,b,c,.....) 0..45'e in terms of number in a sequence
target_token_index = dict([(char, i) for i, char in enumerate(target_characters)])

for i, (title) in enumerate(titles):
    # softmax katmanından ötürü decoder input decoder output'u t + 1 oranla birbirlerini dengeliyorlar
    for t, char in enumerate(title):
        decoder_input_data[i, t, target_token_index[char]] = 1.
        if t > 0:
            decoder_target_data[i, t - 1, target_token_index[char]] = 1.

# encoder (48)
encoder_inputs = Input(shape=(None, num_encoder_tokens))
encoder = Bidirectional(LSTM(256, return_state=True))
encoder_outputs, forward_h, forward_c, backward_h, backward_c = encoder(encoder_inputs)
state_h = Concatenate()([forward_h, backward_h])
state_c = Concatenate()([forward_c, backward_c])
encoder_states = [state_h, state_c]

# decoder
decoder_inputs = Input(shape=(None, num_decoder_tokens))
decoder_lstm = LSTM(256 * 2, return_sequences=True, return_state=True)
# decoder feed with last encoder states
decoder_outputs, _, _ = decoder_lstm(decoder_inputs, initial_state=encoder_states)
# 46
decoder_dense = Dense(num_decoder_tokens, activation='softmax')
decoder_outputs = decoder_dense(decoder_outputs)

model = Model([encoder_inputs, decoder_inputs], decoder_outputs)
model.load_weights('final_weight.h5')
# Run training
model.compile(optimizer='rmsprop', loss='categorical_crossentropy', metrics=['accuracy'])
#history = model.fit([encoder_input_data, decoder_input_data], decoder_target_data, batch_size=80, epochs=65,
                    #validation_split=0.2)
#model.save_weights('final_weight.h5')
# model.summary()
#scores = model.evaluate([encoder_input_data, decoder_input_data], decoder_target_data, verbose=0)
#print("%s: %.2f%%" % (model.metrics_names[1], scores[1] * 100))

#draw_loss_epoch_graph()

# define inference encoder
encoder_model = Model(encoder_inputs, encoder_states)
# define inference decoder
decoder_state_input_h = Input(shape=(256 * 2,))
decoder_state_input_c = Input(shape=(256 * 2,))
decoder_states_inputs = [decoder_state_input_h, decoder_state_input_c]
decoder_outputs, state_h, state_c = decoder_lstm(decoder_inputs, initial_state=decoder_states_inputs)
decoder_states = [state_h, state_c]
decoder_outputs = decoder_dense(decoder_outputs)
decoder_model = Model([decoder_inputs] + decoder_states_inputs, [decoder_outputs] + decoder_states)

reverse_target_char_index = dict((i, char) for char, i in target_token_index.items())

target_title = target_titles("news_titles.txt")
total = 0
for i in range(blue_size):
    # Take one sequence (part of the training set)
    # for trying out decoding.
    x = encoder_input_data[i: i + 1]
    # removing '\n'
    reference = target_title[i].strip()
    decoded_sentence = decode_sequence(x)
    print('-')
    print('Girdi Haber Çizgesi:', word_of_data[i])
    print('Çıktı Haber Başlığı Dizilimi:', decoded_sentence)
    print('Gerçek Haber Başlığı Dizilimi: ', reference)
    score = sentence_bleu([reference.strip().split()], decoded_sentence.strip().split(), weights=(1.0, 0, 0, 0))
    print("=> " + str(score))
    total += score
print("BLUE Skor = " + str(total/blue_size))
