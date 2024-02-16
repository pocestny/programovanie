sources      = $(wildcard *.cc)
builddir     = ./build
objects      = $(addprefix $(builddir)/,$(sources:.cc=.o))	
depends  		 = $(objects:.o=.d)
cc       		 = g++ -O3 -std=c++20 

main: $(objects) 
	mkdir -p $(builddir)
	${cc}  $(objects) -o $@ 

$(builddir)/%.d: %.cc
	mkdir -p $(builddir)
	echo -n $@" "$(builddir)/> $@
	${cc} -MM $< >> $@

include $(depends)

$(builddir)/%.o: %.cc
	mkdir -p $(builddir)
	${cc}  -c $< -o $@

PHONY.: clean
clean:
	rm -rf $(builddir)
	rm -f main
	rm -f .*.tmp
	rm -f net *.png
