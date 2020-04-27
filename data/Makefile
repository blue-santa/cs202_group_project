TARGET = prog 
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h*)
OBJECTS = $(SOURCES:%.cpp=%.o)
LD = g++
CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wfatal-errors -Iinclude -DGL_SILENCE_DEPRECATION -I..  -I../submodules/meta/include/analyzers/ -I../submodules/meta/include/meta/analyzers -I../submodules/meta/include/meta -I../submodules/meta/include/meta/corpus -I../submodules/meta/include -I../submodules/meta/build/ -I../submodules/meta/deps/cpptoml/include -I../submodules/meta/include/meta/learn/loss/ -I../submodules/meta/include/meta/caching/ -I../submodules/meta/include/meta/features/ -I../submodules/meta/include/meta/analyzers/filters/ -I../submodules/meta/include/meta/analyzers/ -I../submodules/meta/include/meta/classify/kernel/ -I../submodules/meta/include/meta/classify/classifier/ -I../submodules/meta/include/meta/corpus/ -I../submodules/meta/include/meta/parser/analyzers/featurizers/ -I../submodules/meta/include/meta/index/ranker/ -I../submodules/meta/tests/ -I../submodules/meta/io/ -I../submodules/meta/build/util/ -I../submodules/
LDFLAGS = -L../submodules/meta/build/lib/ -lmeta-analyzers -lmeta-classify -lmeta-corpus -lmeta-crf -lmeta-embeddings -lmeta-embeddings-analyzers -lmeta-eval -lmeta-features -lmeta-filters -lmeta-greedy-tagger -lmeta-hmm -lmeta-index -lmeta-io -lmeta-kernel -lmeta-language-model -lmeta-learn -lmeta-lm-analyzers -lmeta-loss -lmeta-parser -lmeta-parser-analyzers -lmeta-parser-featurizers -lmeta-parser-io -lmeta-parser-trees -lmeta-ranker -lmeta-regression -lmeta-sequence -lmeta-sequence-analyzers -lmeta-stats -lmeta-succinct -lmeta-tokenizers -lmeta-topics -lmeta-tree-visitors -lmeta-utf -lmeta-util -lpthread -lstdc++fs




.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) src/*.o
	$(RM) $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

