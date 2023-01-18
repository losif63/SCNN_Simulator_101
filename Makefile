TOP_EXE := SCNN
TEST_EXE := TESTER

CC := g++

CPP_SUFFIX				:= cc
CPP_PROTO_SUFFIX		:= pb.cc

INCLUDE_DIR := -I./include 
SRC_DIR := ./src
OBJ_DIR := ./obj
TEST_DIR := ./test
TESTOBJ_DIR = ./testobj
SANITY_DIR := ./sanity

#CFLAGS := -W -Wall -O3 -std=c++11 
#CFLAGS := -W -Wall -O3 -std=c++11 -DNDEBUG

#CFLAGS := -W -Wall -g -std=c++11 -D_DEBUG_
CFLAGS := -W -Wall -g -std=c++11
#CFLAGS := -W -Wall -O3 -std=c++11 -D_DEBUG_

#CFLAGS := -W -Wall --debug -std=c++11 -D_DEBUG_  
#CFLAGS := -W -Wall --debug -std=c++11 -D_DEBUG_ -D_GOLD_ 
#CFLAGS := -W -Wall --debug -std=c++11 -D_DEBUG_ -D_DENSE_
LDFLAGS :=

#LIBS := -lprotobuf

# all sources
SRC				= $(wildcard $(SRC_DIR)/*.$(CPP_SUFFIX))
SRC				+= $(wildcard $(SRC_DIR)/**/*.$(CPP_SUFFIX))

SRC2			= $(wildcard $(SRC_DIR)/**/*.$(CPP_SUFFIX))
#SRC_PROTO	= $(wildcard $(SRC_DIR)/**/*.$(CPP_PROTO_SUFFIX))
$(info $(SRC))

$(info $(SRC_DIR)/%.$(CPP_SUFFIX))
$(info $(OBJ_DIR)/%.o)
# objects
OBJ				= $(patsubst $(SRC_DIR)/%.$(CPP_SUFFIX), $(OBJ_DIR)/%.o, $(SRC))
OBJ2			= $(patsubst $(SRC_DIR)/%.$(CPP_SUFFIX), $(OBJ_DIR)/%.o, $(SRC2))
#OBJ_PROTO	= $(patsubst $(SRC_DIR)/%.$(CPP_PROTO_SUFFIX), $(OBJ_DIR)/%.o, $(SRC_PROTO))
## patsubst = pattern substitute
$(info $(OBJ))

$(info $(OBJ2))

TEST			= $(wildcard $(TEST_DIR)/*.$(CPP_SUFFIX))
TEST			+= $(wildcard $(TEST_DIR)/**/*.$(CPP_SUFFIX))

$(info $(TEST))

$(info $(TEST_DIR)/%.$(CPP_SUFFIX))

TESTOBJ			= $(patsubst $(TEST_DIR)/%.$(CPP_SUFFIX), $(TESTOBJ_DIR)/%.o, $(TEST))
$(info $(TESTOBJ))

# top program
all: $(OBJ) $(OBJ_PROTO)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(TOP_EXE)
#	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) $(OBJ_PROTO) -o $(TOP_EXE) $(LIBS) 


# objects (all sources)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(CPP_SUFFIX)
	$(CC) $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

# objects (protobuf)
#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(CPP_PROTO_SUFFIX)
#	$(CC) $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@

test: $(TESTOBJ) $(OBJ2)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TESTOBJ) $(OBJ2) -o $(TEST_EXE)
	./$(TEST_EXE) > RESULTS
	cat RESULTS


$(TESTOBJ_DIR)/%.o: $(TEST_DIR)/%.$(CPP_SUFFIX)
	$(CC) $(INCLUDE_DIR) $(CFLAGS) -c $< -o $@



clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(OBJ_DIR)/dlsim/*.o
#	rm -rf $(OBJ_DIR)/dadiannao/*.o
	rm -rf $(OBJ_DIR)/scnn/*.o
#	rm -rf $(OBJ_DIR)/meijoo/*.o
#	rm -rf $(OBJ_DIR)/protobuf/*.o
#	rm -rf $(SANITY_DIR)/*
	rm -rf $(TESTOBJ_DIR)/*.o
	rm -rf $(TESTOBJ_DIR)/dlsim/*.o
	rm -rf $(TESTOBJ_DIR)/scnn/*.o
	rm $(TOP_EXE)
	rm $(TEST_EXE)
	
