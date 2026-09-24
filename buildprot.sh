#xelatex -draftmode -8bit -no-pdf main.tex
xelatex -8bit --job-name=SVETH main.tex 
xelatex -8bit --job-name=SVETH main.tex 
cp main.pdf SVETH.pdf