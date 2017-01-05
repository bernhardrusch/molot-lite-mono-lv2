# plugin name
PLUGIN = molot-lite-mono
PLUGIN_SO = $(PLUGIN).so

# installation path
ifndef INSTALL_PATH
INSTALL_PATH = /usr/local/lib/lv2/
endif
INSTALLATION_PATH = $(DESTDIR)$(INSTALL_PATH)/$(PLUGIN).lv2/

# compiler and linker
CXX ?= g++

# flags
CXXFLAGS += -I. -O3 -Wall -fPIC -DPIC -c
LDFLAGS += -shared -lm -Wl,--no-undefined

# remove command
RM = rm -f

# sources and objects
SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

$(PLUGIN_SO): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(PLUGIN_SO)

%.o: %.cpp
	$(CXX) $< $(CXXFLAGS) -o $@

clean:
	$(RM) src/*.o $(PLUGIN_SO)

install: $(PLUGIN_SO)
	mkdir -p $(INSTALLATION_PATH)
	cp $(PLUGIN_SO) $(INSTALLATION_PATH)
	cp -r *.ttl $(INSTALLATION_PATH)
	cp -r modgui $(INSTALLATION_PATH)
