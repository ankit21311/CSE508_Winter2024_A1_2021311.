import os
import pickle
import q1
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import string

def create_inverted_index(input_folder, num_files, output_filepath):
    inverted_index = {}
    doc_index = 1
    while doc_index < num_files:
        try:
            with open(os.path.join(input_folder, f'p_file{doc_index}.txt'), 'r') as input_file:
                text = input_file.read()
                tokens = text.split()
                token_index = 0
                while token_index < len(tokens):
                    token = tokens[token_index]
                    if token not in inverted_index:
                        inverted_index[token] = []
                    if doc_index not in inverted_index[token]:
                        inverted_index[token].append(doc_index)
                    token_index += 1
        except Exception as e:
            print(f"An error occurred while processing file{doc_index}.txt: {e}")
        doc_index += 1
    try:
        with open(output_filepath, "wb") as f:
            pickle.dump(inverted_index, f)
    except Exception as e:
        print(f"An error occurred while saving the inverted index: {e}")

def load_inverted_index(filepath):
    try:
        with open(filepath, "rb") as f:
            loaded_inverted_index = pickle.load(f)
        return loaded_inverted_index
    except Exception as e:
        print(f"An error occurred while loading the inverted index: {e}")

def process_query(query_tokens, operations, inverted_index):
    results = set(inverted_index.get(query_tokens[0], []))
    i = 1
    operations_dict = {"AND": "&", "OR": "|", "AND NOT": "-", "OR NOT": "|"}
    while i < len(query_tokens):
        try:
            operation = operations[i - 1]
            term_docs = set(inverted_index.get(query_tokens[i], []))
            if operation in operations_dict:
                op = operations_dict[operation]
                if operation.endswith("NOT"):
                    results = eval(f"results {op} term_docs")
                else:
                    results = eval(f"results {op} term_docs")
                    i += 1
            else:
                print(f"Unknown operation: {operation}")
                break
            i += 1
        except Exception as e:
            print(f"An error occurred while processing the query: {e}")
            break
    return list(results)

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

def preprocess_text(text):
    text = lowercase_text(text)
    tokens = tokenize_text(text)
    tokens = remove_stopwords(tokens)
    tokens = remove_punctuations(tokens)
    tokens = remove_blank_space_tokens(tokens)
    return " ".join(tokens)

def main():
    input_folder = 'preprocessed_files'
    output_filepath = 'uii_file.pkl'
    create_inverted_index(input_folder, 1000, output_filepath)
    input_sequences = []
    operations = []
    try:
        num_queries = int(input('Enter the number of queries: '))
        for i in range(num_queries):
            input_sequences.append(input('Enter the input sequence: '))
            operations.append(input('Enter the operations separated by comma: ').upper())
        inverted_index = load_inverted_index(output_filepath)
        for i in range(num_queries):
            preprocessed_text = preprocess_text(input_sequences[i])
            query_tokens = [item for pair in zip(preprocessed_text.split(' '), operations[i].split(', ')) for item in pair] + [preprocessed_text.split(' ')[-1]]
            query_results = process_query(preprocessed_text.split(' '), operations[i].split(', '), inverted_index)
            retrieved_documents = [f"file{res}.txt" for res in query_results]
            print(f"Query {i + 1}: {' '.join(query_tokens)}")
            print(f"Number of documents retrieved for query {i + 1}: {len(retrieved_documents)}")
            print(f"Names of the documents retrieved for query {i + 1}: {', '.join(retrieved_documents)}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    main()
