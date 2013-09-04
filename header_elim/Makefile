## ROSE installation contains
##   * libraries, e.g. "librose.la"
##   * headers, e.g. "rose.h"
ROSE_INSTALL=/home/nnmahaja/installs/rose.git.build

## ROSE uses the BOOST C++ libraries, the --prefix path
# BOOST_INSTALL=/usr

## Your translator
TRANSLATOR=translator
TRANSLATOR_SOURCE=$(TRANSLATOR).cpp

#-------------------------------------------------------------
# Makefile Targets
#-------------------------------------------------------------

all: $(TRANSLATOR)

# compile the translator and generate an executable
# -g is recommended to be used by default to enable debugging your code
$(TRANSLATOR): $(TRANSLATOR_SOURCE)
	g++ -g $(TRANSLATOR_SOURCE) -o $(TRANSLATOR).exe -I$(ROSE_INSTALL)/include -L$(ROSE_INSTALL)/lib -lrose

# test the translator
check: $(TRANSLATOR)
	./$(TRANSLATOR) -c -I. -I$(ROSE_INSTALL)/include $(TESTCODE) 

clean:
	rm -rf $(TRANSLATOR) *.o rose_* *.dot *.ti *.exe a.out

