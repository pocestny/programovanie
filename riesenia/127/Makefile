sources  = $(wildcard *.cc)
builddir = ./build
objects  = $(addprefix $(builddir)/,$(sources:.cc=.o))
depends  = $(objects:.o=.d)

main: $(objects)
	mkdir -p $(builddir)
	g++ $(objects) -o $@

$(builddir)/%.d: %.cc
	mkdir -p $(builddir)
	echo -n $@" "$(builddir)/> $@
	g++ -MM $< >> $@

include $(depends)

$(builddir)/%.o: %.cc
	mkdir -p $(builddir)
	g++ -c $< -o $@

PHONY.: clean
clean:
	rm -rf $(builddir)
	rm -f main
