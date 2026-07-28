CC		:= sdcc
CFLAGS		:= -mstm8 --std-c90 --Werror -pedantic
FLASH		:= stm8flash
DEVICE		:= stm8s103f3
PROGRAMMER	:= stlinkv2

CCHECK		:= cppcheck
RPORT		:= report.txt
SUPPL		:= suppression.txt
CCHECKF		:= --std=c90 --platform=avr8 \
		--addon=misra.py --enable=all --inline-suppr -I . \
		--suppressions-list=${SUPPL} --checkers-report=${RPORT}

DIR		:= out
OUT		:= output.ihx
SRC		:= ${wildcard *.c}
OBJ		:= ${patsubst %.c, ${DIR}/%.rel, ${SRC}}

.PHONY : all flash build syntax format clear misra

all : build flash


${DIR} :
	@echo "Creating an output directory ...\n"
	@mkdir -p $@

${DIR}/%.rel : %.c
	@echo "Compiling $< into $@ ..."
	@${CC} ${CFLAGS} -c $< -o $@

${OUT} : ${OBJ}
	@echo "Link the object files into firmware ..."
	@${CC} ${CFLAGS} ${OBJ} -o ${DIR}/${OUT}

build : syntax ${DIR} ${OBJ} ${OUT}

flash : ${DIR}/${OUT}
	@echo "Updating MCU firmware ..."
	@${FLASH} -c ${PROGRAMMER} -p ${DEVICE} -w ${DIR}/${OUT}

misra :
	@${CCHECK} ${CCHECKF} .

syntax : ${INC} ${SRC}
	@echo
	@for file in ${SRC}; do \
		echo "Checking $$file syntax ..."; \
		${CC} ${CFLAGS} --syntax-only $$file; \
	done
	@echo

format :
	@echo "\nFormatted!"
	@find * \( -name "*.h" -o -name "*.c" \) -exec clang-format -i {} +;

clear :
	@echo "\nCleared!"
	@rm -f *.asm *.sym *.lst *.rel *.lk *.rst *.map *.ihx
	@rm -rf ${DIR}
