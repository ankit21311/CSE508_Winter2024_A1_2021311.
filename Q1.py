import nltk
import os
import string
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize

nltk.download('punkt')
nltk.download('stopwords')

def preprocess_file(i, input_filepath, output_filepath):
    def print_if(condition, message):
        if condition:
            print(message)

    formatted_string = ""
    try:
        with open(input_filepath, 'r') as input_file:
            text = input_file.read()
            print_if(i < 6, f">> Input Text {i}: {text}")

            text = text.lower()
            print_if(i < 6, f">> Lowercase Text {i}: {text}")

            tokens = word_tokenize(text)
            print_if(i < 6, f">> Tokenized Text {i}: {tokens}")

            stop_words = set(stopwords.words('english'))
            tokens = [token for token in tokens if token.lower() not in stop_words]
            print_if(i < 6, f">> Stopwords Removed Text {i}: {tokens}")

            translator = str.maketrans("", "", string.punctuation)
            tokens = [text.translate(translator) for text in tokens]
            print_if(i < 6, f">> Punctuations Removed Text {i}: {tokens}")

            tokens = [token for token in tokens if token.strip()]
            print_if(i < 6, f">> Blank space tokens removed text {i}: {tokens}")

            formatted_string = " ".join(tokens)
            print_if(i < 6, f">> After Complete Operations File {i}: {formatted_string}\n")

        with open(output_filepath, 'w') as output_file:
            output_file.write(formatted_string)
    except Exception as e:
        print(f"An error occurred while processing {input_filepath}: {str(e)}")

def main():
    input_folder = 'text_files'
    output_folder = 'preprocessed_files'

    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    file_num = 1
    while file_num < 1000:
        input_filepath = os.path.join(input_folder, f'file{file_num}.txt')
        output_filepath = os.path.join(output_folder, f'p_file{file_num}.txt')
        preprocess_file(file_num, input_filepath, output_filepath)
        file_num += 1

if __name__ == "__main__":
    main()
