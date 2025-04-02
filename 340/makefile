all: parser

parser: scanner.c parser.c datastructs.c quads.c tcode.c alphavm.c
	@gcc $^ -o $@ -lm
	@echo "Syntax analyzer is ready to syntactically analyze :D"

parser.c: parser.y
	@bison -d -v  $^

# al: scanner.c al.c cat_utils.c
# 	@gcc $^ -o $@
# 	@echo "Lexical analyzer is ready to lexically analyse :D"

scanner.c: scanner.l
	@flex $^

clean:
	@rm -f al parser scanner.c parser.c parser.h 
