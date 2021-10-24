import numpy as np


def chars_length_graph_text(graph_text, titles):
    input_characters = set()
    target_characters = set()
    for text in graph_text:
        for word in text:
            for char in word:
                if char not in input_characters:
                    input_characters.add(char)
    for title in titles:
        for word in title:
            for char in word:
                if char not in target_characters:
                    target_characters.add(char)
    return input_characters, target_characters


def vector_size_operation(word_of_data, titles, input_characters, target_characters):
    num_encoder_tokens = len(input_characters)
    num_decoder_tokens = len(target_characters)
    max_encoder_seq_length = max([len(txt) for txt in word_of_data])
    max_decoder_seq_length = max([len(txt) for txt in titles])
#    print('Number of samples:', len(word_of_data))
#    print('Number of unique input tokens:', num_encoder_tokens)
#   print('Number of unique output tokens:', num_decoder_tokens)
#    print('Max nodes count for inputs:', max_encoder_seq_length)
#    print('Max sequence length for outputs:', max_decoder_seq_length)
    return num_encoder_tokens, num_decoder_tokens, max_encoder_seq_length, max_decoder_seq_length


def create_model_vector(word_of_data, num_encoder_tokens, num_decoder_tokens, max_encoder_seq_length,
                        max_decoder_seq_length):
    encoder_input_data = np.zeros((len(word_of_data), max_encoder_seq_length, num_encoder_tokens), dtype='float32')
    decoder_input_data = np.zeros((len(word_of_data), max_decoder_seq_length, num_decoder_tokens), dtype='float32')
    decoder_target_data = np.zeros((len(word_of_data), max_decoder_seq_length, num_decoder_tokens), dtype='float32')
    return encoder_input_data, decoder_input_data, decoder_target_data
