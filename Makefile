binaries=ff cf tf df lengths transform_tf idf tf_idf indexing qf query scores tune sim bonus
ff: io.cpp filter_files.cpp 
	g++ -o ff io.cpp filter_files.cpp
cf: io.cpp clean_files.cpp
	g++ -o cf io.cpp clean_files.cpp
tf: io.cpp term_frequencies.cpp
	g++ -o tf io.cpp term_frequencies.cpp
df: io.cpp document_frequencies.cpp
	g++ -o df io.cpp document_frequencies.cpp
lengths: io.cpp document_lengths.cpp
	g++ -o lengths io.cpp document_lengths.cpp
transform_tf: io.cpp transform_term_frequencies.cpp
	g++ -o transform_tf io.cpp transform_term_frequencies.cpp
idf: io.cpp inverse_document_frequencies.cpp
	g++ -o idf io.cpp inverse_document_frequencies.cpp
tf_idf: io.cpp tf_idf_weights.cpp
	g++ -o tf_idf io.cpp tf_idf_weights.cpp
indexing: io.cpp indexing.cpp
	g++ -o indexing io.cpp indexing.cpp
qf: io.cpp query_frequencies.cpp
	g++ -o qf io.cpp query_frequencies.cpp
query: io.cpp query.cpp
	g++ -o query io.cpp query.cpp
scores: io.cpp scores.cpp
	g++ -o scores io.cpp scores.cpp
tune: io.cpp tune.cpp
	g++ -o tune io.cpp tune.cpp
sim: io.cpp similarity.cpp
	g++ -o sim io.cpp similarity.cpp 
bonus: io.cpp bonus.cpp
	g++ -o bonus io.cpp bonus.cpp
clean:
	rm -f $(binaries) *.o