SRC_PATH			:= src
INCLUDE_PATH	:= include
OBJ_PATH			:= obj

CC			:= gcc
CFLAGS	:= -O2

PROGRAM_NAME := launcher

FILES := $(wildcard $(SRC_PATH)/*.c)
OBJS 	:= $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(FILES))

compile: init_dirs $(OBJS) $(PROGRAM_NAME) clear

init_dirs:
	rm -rf	$(OBJ_PATH)
	mkdir		$(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	gcc -c $< -I$(INCLUDE_PATH) -o $@

$(PROGRAM_NAME):
	gcc $(CFLAGS) $(OBJS) -I$(INCLUDE_PATH) main.c -o $@

clear:
	rm -rf $(OBJ_PATH)
