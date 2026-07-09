CC		:= sdcc
CFLAGS		:= -mstm8 --std-c90 --Werror -pedantic
FLASH		:= stm8flash
DEVICE		:= stm8s103f3
PROGRAMMER	:= stlinkv2

CCHECK		:= cppcheck
RPORT		:= report.txt
SUPPL		:= suppression.txt
CCHECKF		:= --std=c90 --platform=avr8 --addon=misra.py --enable=all --inline-suppr -I . --suppressions-list=${SUPPL} --checkers-report=${RPORT}

DIR		:= out
OUT		:= output.ihx
SRC		:= ${wildcard *.c}
OBJ		:= ${patsubst %.c, ${DIR}/%.rel, ${SRC}}

.PHONY : all flash build syntax format clear standart

all : build flash


${DIR} :
	mkdir -p $@

${DIR}/%.rel : %.c
	${CC} ${CFLAGS} -c $< -o $@

${OUT} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${DIR}/${OUT}

build : syntax ${DIR} ${OBJ} ${OUT}

flash : ${DIR}/${OUT}
	${FLASH} -c ${PROGRAMMER} -p ${DEVICE} -w ${DIR}/${OUT}

standart :
	${CCHECK} ${CCHECKF} .

syntax : ${SRC}
	for file in ${SRC}; do \
		${CC} ${CFLAGS} --syntax-only $$file; \
	done

format :
	find * \( -name "*.h" -o -name "*.c" \) -exec clang-format -i {} +;

clear :
	rm -f *.asm *.sym *.lst *.rel *.lk *.rst *.map *.ihx
	rm -rf ${DIR}
