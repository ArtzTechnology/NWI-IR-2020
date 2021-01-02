# This program stems all files with the nltk porterstemmer
# Input: data/valid_uids.txt data/metadata_clean/ data/documents_clean/
# Output: data/metadata_stemmed/ data/documents_stemmed/

from nltk.stem import PorterStemmer

# global variables
valid_uids = 'data/valid_uids.txt'
base_metadata_clean = 'data/metadata_clean/'
base_documents_clean = 'data/documents_clean/'
base_metadata_stemmed = 'data/metadata_stemmed/'
base_documents_stemmed = 'data/documents_stemmed/'
ps = PorterStemmer()

def get_uids():
    with open(valid_uids, 'r') as f:
        return [line.rstrip() for line in f]
    
# retrieve, stem and save file
def stem_file(infile, outfile):
    with open(infile, 'r') as f:
        words = [line.rstrip() for line in f]
    result = []
    for w in words:
        result += [ps.stem(w)]
    with open(outfile, 'w') as f:
        for word in result:
            f.write("%s\n" % word)

def process(uids):
    total = len(uids)
    checkpoint = int(total / 100)
    for i in range(0, total):
        if (i % checkpoint == 0):
            print(str(round((i) / total * 100)) + "%")
        stem_file(base_documents_clean + uids[i] + ".txt", base_documents_stemmed + uids[i] + ".txt")
        stem_file(base_metadata_clean + uids[i] + ".txt", base_metadata_stemmed + uids[i] + ".txt")

def main():
    uids = get_uids()
    process(uids)

if __name__ == '__main__':
    main()
