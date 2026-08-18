CC		:= sdcc
CFLAGS		:= -mstm8 --std-c90 --Werror -pedantic -I .
FLASH		:= stm8flash
DEVICE		:= stm8s103f3
PROGRAMMER	:= stlinkv2

CHECK		:= cppcheck
REPORT		:= report.txt
SUPPL		:= suppression.txt
CHECKF		:= --std=c90 --platform=avr8 \
		--addon=misra.py --enable=all --inline-suppr -I . \
		--suppressions-list=${SUPPL} --checkers-report=${REPORT}

DIR		:= out
HEX		:= output.ihx
SRC		:= ${wildcard *.c}
OBJ		:= ${patsubst %.c, ${DIR}/%.rel, ${SRC}}

.PHONY : flash syntax format clear misra

all : build ${HEX} flash


${DIR} :
	@echo "Creating an output directory ...\n"
	@mkdir -p $@

${DIR}/%.rel : %.c
	@echo "Compiling $< into $@ ..."
	@${CC} ${CFLAGS} -c $< -o $@

${HEX} : ${OBJ}
	@echo "Link the object files into firmware ..."
	@${CC} ${CFLAGS} ${OBJ} -o ${DIR}/${HEX}

build : syntax misra ${DIR} ${OBJ} ${OUT}

flash : ${DIR}/${OUT}
	@echo "\nUpdating MCU firmware ..."
	@${FLASH} -c ${PROGRAMMER} -p ${DEVICE} -w ${DIR}/${HEX}

misra :
	@${CHECK} ${CHECKF} .

syntax : ${SRC}
	@echo
	@for file in ${SRC}; do \
		echo "Checking $$file syntax ..."; \
		${CC} ${CFLAGS} --syntax-only $$file; \
	done
	@echo

format :
	@echo "\nFormatted!"
	@find * \( -name "*.h" -o -name "*.c" \) \
	-exec clang-format -i {} +;

pdf :
	@${MAKE} -C docs/

clear :
	@echo "\nCleared!"
	@rm -f *.asm *.sym *.lst *.rel *.lk \
	*.rst *.map *.ihx *.log *.aux *.pdf
	@${MAKE} -C docs/ clear
	@rm -rf ${DIR}
