# This program retrieves all plain text from the
# parsed pmc files. 
# Input: COVID-19/pmc_json/ data/metadata.csv
# Output: data/metadata_text/ data/document_text 

import pandas as pd 
import json

# global variables
metadata_path = 'data/metadata.csv'
base_pmc = 'COVID-19/pmc_json/'
base_document = 'data/documents_text/'
base_metadata = 'data/metadata_text/'

# load metadata.csv and return as list
def get_metadata():
    data = pd.read_csv(metadata_path)
    return data.values.tolist()

# return plaintext from document by pmc id
def retrieve_plaintext(filename):
    with open(filename, "r") as f:
        json_data = json.loads(f.read())
    body_text = json_data['body_text']
    result = ""
    for i in range(0, len(body_text)):
        result += body_text[i]["text"]
    return result

# save data in txt file
def save(data, filename):
    with open(filename, "w") as f:
        f.write("%s\n" % data)

# retrieve pmc parsed json files and save as txt file
def process_documents(metadata):
    total = len(metadata)
    checkpoint = int(total / 100)
    for i in range(0, total):
        if (i % checkpoint == 0):
            print(str(round((i) / total * 100)) + "%")
        pcm_uid = metadata[i][16].split('.')[0][25:]
        plaintext = retrieve_plaintext(base_pmc + pcm_uid + '.xml.json')
        uid = metadata[i][0]
        save(plaintext, base_document + uid + ".txt")

def process_metadata(metadata):
    total = len(metadata)
    checkpoint = int(total / 100)
    for i in range(0, total):
        if (i % checkpoint == 0):
            print(str(round((i) / total * 100)) + "%")
        result = ""
        if not pd.isnull(metadata[i][3]):
            result += metadata[i][3]
        if not pd.isnull(metadata[i][8]):
            result += " " + metadata[i][8] 
        uid = metadata[i][0]
        save(result, base_metadata + uid + ".txt")
        
def main():
    metadata = get_metadata()
    process_documents(metadata)
    process_metadata(metadata)

if __name__ == '__main__':
    main()