BIN_DIR = bin
CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: search crawler

search: search.cpp webpage.o websearcheng.o setutility.h mdparser.o pagerank.o
	$(CXX) $(CPPFLAGS) webpage.o websearcheng.o mdparser.o pagerank.o search.cpp -o search

crawler: crawler.cpp webpage.o crawlerpage.o crawlersearch.o setutility.h mdparser.o
	$(CXX) $(CPPFLAGS) webpage.o crawlerpage.o crawlersearch.o mdparser.o crawler.cpp -o crawler

mdparser.o: mdparser.cpp parser.h setutility.h
	$(CXX) $(CPPFLAGS) -c mdparser.cpp -o mdparser.o

webpage.o: webpage.cpp setutility.h
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o webpage.o

crawlerpage.o: crawlerpage.cpp setutility.h
	$(CXX) $(CPPFLAGS) -c crawlerpage.cpp -o crawlerpage.o

websearcheng.o: websearcheng.cpp setutility.h
	$(CXX) $(CPPFLAGS) -c websearcheng.cpp -o websearcheng.o

crawlersearch.o: crawlersearch.cpp setutility.h
	$(CXX) $(CPPFLAGS) -c crawlersearch.cpp -o crawlersearch.o

pagerank.o: pagerank.cpp setutility.h
	$(CXX) $(CPPFLAGS) -c pagerank.cpp -o pagerank.o

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp