sources  = $(wildcard *.cc)
builddir = ./build
objects  = $(addprefix $(builddir)/,$(sources:.cc=.o))
depends  = $(objects:.o=.d)
cflags = -g 

main: $(objects)
	mkdir -p $(builddir)
	g++ $(cflags)  -std=c++20 $(objects) -o $@ -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

$(builddir)/%.d: %.cc
	mkdir -p $(builddir)
	echo -n $@" "$(builddir)/> $@
	g++ -MM $< >> $@

include $(depends)

$(builddir)/%.o: %.cc
	mkdir -p $(builddir)
	g++ $(cflags)  -std=c++20 -c $< -o $@

PHONY.: clean
clean:
	rm -rf $(builddir)
	rm -f main
