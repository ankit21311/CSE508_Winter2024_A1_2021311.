import os
import pickle
import q1
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import string

def preprocess_text(text):
    def lowercase_text(text):
        return text.lower()
    def tokenize_text(text):
        return word_tokenize(text)
    def remove_stopwords(tokens):
        stop_words = set(stopwords.words('english'))
        return [token for token in tokens if token.lower() not in stop_words]
    def remove_punctuations(tokens):
        translator = str.maketrans("", "", string.punctuation)
        return [text.translate(translator) for text in tokens]
    def remove_blank_space_tokens(tokens):
        return [token for token in tokens if token.strip()]
    text = lowercase_text(text)
    tokens = tokenize_text(text)
    tokens = remove_stopwords(tokens)
    tokens = remove_punctuations(tokens)
    tokens = remove_blank_space_tokens(tokens)
    return " ".join(tokens)

def create_positional_index(input_folder, num_files, output_filepath):
    positional_index = {}
    doc_index = 1
    while doc_index < num_files:
        try:
            with open(os.path.join(input_folder, f'p_file{doc_index}.txt'), 'r') as input_file:
                text = input_file.read()
                tokens = text.split()
                position = 0
                while position < len(tokens):
                    word = tokens[position]
                    if word not in positional_index:
                        positional_index[word] = {}
                    if doc_index not in positional_index[word]:
                        positional_index[word][doc_index] = []
                    positional_index[word][doc_index].append(position)
                    position += 1
        except Exception as e:
            print(f"An error occurred while processing file{doc_index}.txt: {e}")
        doc_index += 1
    try:
        with open(output_filepath, "wb") as f:
            pickle.dump(positional_index, f)
    except Exception as e:
        print(f"An error occurred while saving the positional index: {e}")

def load_positional_index(filepath):
    try:
        with open(filepath, "rb") as f:
            loaded_positional_index = pickle.load(f)
        return loaded_positional_index
    except Exception as e:
        print(f"An error occurred while loading the positional index: {e}")
        return None

def process_phrase_query(query_tokens, positional_index):
    results = set()
    doc_index = 1
    while True:
        try:
            positions = positional_index[query_tokens[0]][doc_index]
            position_index = 0
            while position_index < len(positions):
                pos = positions[position_index]
                match = True
                next_token_index = 1
                while next_token_index < len(query_tokens):
                    next_token = query_tokens[next_token_index]
                    next_positions = positional_index[next_token][doc_index]
                    if pos + next_token_index not in next_positions:
                        match = False
                        break
                    next_token_index += 1
                if match:
                    results.add(doc_index)
                    break
                position_index += 1
            doc_index += 1
        except KeyError:
            break
    return list(results)

def main():
    script_dir = os.path.dirname(__file__)
    input_folder = os.path.join(script_dir, 'preprocessed_files')
    output_filepath = os.path.join('pi_file.pkl')
    create_positional_index(input_folder, 1000, output_filepath)
    num_queries = int(input('Enter the number of phrase queries to execute: '))
    queries = []
    i = 0
    while i < num_queries:
        queries.append(input(f'Enter phrase query {i + 1}: '))
        i += 1
    positional_index = load_positional_index(output_filepath)
    if positional_index is None:
        return
    i = 0
    while i < len(queries):
        preprocessed_query = preprocess_text(queries[i])
        query_tokens = preprocessed_query.split()
        query_results = process_phrase_query(query_tokens, positional_index)
        retrieved_documents = [f"file{res}.txt" for res in query_results]
        print(f"Number of documents retrieved for phrase query {i + 1} using positional index: {len(retrieved_documents)}")
        print(f"Names of documents retrieved for phrase query {i + 1} using positional index: {', '.join(retrieved_documents)}")
        i += 1

if __name__ == "__main__":
    main()
