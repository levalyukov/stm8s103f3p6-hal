LATEX 	:= pdflatex
PDF	:= document.tex

all : pdf

pdf :
	${LATEX} ${PDF}
	@mv ${patsubst %.tex, %.pdf, ${PDF}} ../../

clear :
	@rm -rf *.pdf *.log *.aux *.out
