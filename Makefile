CC		:= sdcc
CFLAGS		:= -mstm8 --std-c90 --Werror -pedantic
FLASH		:= stm8flash
DEVICE		:= stm8s103f3
PROGRAMMER	:= stlinkv2

DIR		:= build
OUT		:= output.ihx
SRC		:= ${wildcard *.c}
OBJ		:= ${patsubst %.c, ${DIR}/%.rel, ${SRC}}

.PHONY : all flash syntax format clear

all : ${DIR} syntax ${OBJ} ${OUT} flash


${DIR} :
	@mkdir -p $@

${DIR}/%.rel : %.c
	${CC} ${CFLAGS} -c $< -o $@

${OUT} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${DIR}/${OUT}

flash : ${DIR}/${OUT}
	${FLASH} -c ${PROGRAMMER} -p ${DEVICE} -w ${DIR}/${OUT}

syntax : ${SRC}
	@for file in ${SRC}; do \
		${CC} ${CFLAGS} --syntax-only $$file; \
	done

format :
	@find * \( -name "*.h" -o -name "*.c" \) -exec clang-format -i {} +;

clear :
	@rm -f *.asm *.sym *.lst *.rel *.lk *.rst *.map *.ihx
	@rm -rf ${DIR}
