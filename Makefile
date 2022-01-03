all: programovanie
TMP=./build
SHELL=bash

programovanie: programovanie.tex
	mkdir -p ${TMP}
	cp programovanie.tex ${TMP}
	mkdir -p ${TMP}/data
	cp -r data/* ${TMP}/data
	pushd ${TMP}; pdflatex -shell-escape -output-directory=. programovanie.tex; popd
	mv ${TMP}/programovanie.pdf .
