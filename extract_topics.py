# This program transforms the topics to bags of words
# Input: COVID-19/topics.xml
# Output: data/topics/

import xml.etree.ElementTree as ET
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
import re
import pandas as pd
import json
import math
import numpy as np

# global
stopWords = stopwords.words('english')
ps = PorterStemmer()
base_topics = "data/topics/"

# save data in data/rankings 
def save(data, number):
    with open(base_topics + str(number) + ".txt", "w") as f:
        f.write(data)

# saves stemmed queries without stopwords and duplicates
def extract():
    root = ET.parse('COVID-19/topics.xml').getroot()
    for i in range(0, 50):
        query = ""
        for j in range(0, 3):
            query += root[i][j].text + " "
        step1 = re.sub(r'[^a-zA-Z]+', ' ', query).lower().split()
        step2 = [ps.stem(x) for x in step1 if x not in stopWords]
        save("\n".join(step2), i+1)

def main():
    extract()
 
if __name__ == '__main__':
    main()