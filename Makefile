FILES = main.cpp randgen.cpp 

#  ---------------------
solver:	$(FILES)
	g++  $(FILES) -o makemovie
