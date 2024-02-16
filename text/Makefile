TMP=./build
SHELL=bash
asy =$(wildcard tex/asy/*.asy)
data=$(wildcard data/*) 
tex =$(wildcard tex/*.tex)

all: ../programovanie.pdf

.PHONY: ${TMP}
${TMP}:
	mkdir -p ${TMP}/data
	mkdir -p ${TMP}/asy
	cp tex/asy/manual/*.png ${TMP}/asy
	
../programovanie.pdf: ${TMP} $(addprefix ${TMP}/,$(data)) $(patsubst tex/%.tex,${TMP}/%.tex,$(tex)) \
	$(patsubst tex/asy/%.asy,${TMP}/asy/%.pdf,$(asy))
	pushd ${TMP}; lualatex -shell-escape -output-directory=. programovanie.tex; popd
	mv ${TMP}/programovanie.pdf ..


${TMP}/data/%: data/% 
	cp -r $< $@ 

${TMP}/%.tex: tex/%.tex 
	cp -r $< $@

${TMP}/asy/%.pdf: tex/asy/%.asy $(wildcard tex/asy/include/*.asy)
	asy -cd ./tex/asy -f pdf -o $(abspath $@) $(notdir $<)

.PHONY: purge
purge:
	rm -r build
	rm programovanie.pdf

