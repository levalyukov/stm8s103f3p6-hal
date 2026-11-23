DIR		:= out
HEX		:= firmware.ihx
INC		:= ${wildcard inc/*.h}
SRC		+= ${wildcard src/*.c}
OBJ		:= ${patsubst %.c, ${DIR}/%.rel, ${SRC}}

CC		:= sdcc
CFLAGS		+= --opt-code-size -mstm8 --std-c90 --Werror 
CFLAGS		+= -pedantic -DSTM8S103F3P6_HAL -I inc
FLASH		:= stm8flash
DEVICE		:= stm8s103f3
PROGRAMMER	:= stlinkv2

CHECK		:= cppcheck
REPORT		:= report.txt
SPPLSS		:= suppression.txt
CHECKF		+= --std=c90 --platform=avr8 -DSTM8S103F3P6_HAL -Iinc
CHECKF		+= --suppressions-list=${SPPLSS} --checkers-report=${REPORT}
CHECKF		+= --addon=misra.py --enable=all --inline-suppr

.PHONY : build flash syntax format clear misra

all : build ${HEX} flash

${DIR} :
	@mkdir -p $@

${DIR}/%.rel : %.c
	@echo "Compiling $< into ${DIR}/${notdir $@} ..."
	@${CC} ${CFLAGS} -c $< -o ${DIR}/${notdir $@}

${HEX} : ${OBJ}
	@${CC} ${CFLAGS} ${patsubst %.rel, ${DIR}/%.rel, ${notdir ${OBJ}}} \
	-o ${DIR}/${HEX}

build : syntax misra ${DIR} ${OBJ} ${OUT}

flash : ${DIR}/${OUT}
	@echo "\nUpdating MCU firmware ..."
	@${FLASH} -c ${PROGRAMMER} -p ${DEVICE} -w ${DIR}/${HEX}

misra : ${SRC}
	@${CHECK} ${CHECKF} src/

syntax : ${SRC}
	@for file in ${SRC}; do \
		${CC} ${CFLAGS} --syntax-only $$file; \
	done

format :
	@find * \( -name "*.h" -o -name "*.c" \) \
	-exec clang-format -i {} +;

pdf :
	@${MAKE} -C docs/

clear :
	@rm -f *.asm *.sym *.lst *.rel *.lk \
	*.rst *.map *.ihx *.log *.aux *.pdf
	@${MAKE} -C docs/ clear
	@rm -rf ${DIR}
