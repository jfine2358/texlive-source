define redo
file kpsewhich
end

# afoot.sty
set env TEXMFCNF  /home/texlive/karl/Master/texmf/web2c
set env TEXMFDBS  /home/texlive/karl/Master/texmf-dist:/home/texlive/karl/Master/texmf
set env TEXINPUTS !!/home/texlive/karl/Master/texmf-dist/tex/latex//:!!/home/texlive/karl/Master/texmf/tex/generic//:!!/home/texlive/karl/Master/texmf/tex//
#
# preload.cfg
#set env TEXMFDBS  /home/texlive/karl/Master/texmf
#set env TEXINPUTS !!/home/texlive/karl/Master/texmf/tex/generic//:!!/home/texlive/karl/Master/texmf/tex//
set args --all --debug=32 preload.cfg
