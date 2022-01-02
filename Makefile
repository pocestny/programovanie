all: programovanie
TMP=/tmp/programovanie
SHELL=bash

programovanie: programovanie.tex
	mkdir -p ${TMP}
	cp programovanie.tex ${TMP}
	mkdir -p ${TMP}/out
	cp -r out/* ${TMP}/out
	pushd ${TMP}; pdflatex -shell-escape -output-directory=${TMP} programovanie.tex; popd
	mv ${TMP}/programovanie.pdf .
