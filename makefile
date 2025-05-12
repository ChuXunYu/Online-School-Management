# Makefile for Online School Management System

CC = gcc
CFLAGS = -Wall -std=c11 -I./includes

SRC_DIR = src
INC_DIR = includes
OBJ_DIR = obj
DATA_DIR = data

# 创建对象文件目录
$(shell mkdir -p $(OBJ_DIR))

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
EXECUTABLE = school_management_system

.PHONY: all clean data

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# 创建必要的数据文件和目录
data:
	@mkdir -p $(DATA_DIR)/student $(DATA_DIR)/teacher $(DATA_DIR)/college $(DATA_DIR)/bus
	@touch $(DATA_DIR)/college/colleges.txt
	@touch $(DATA_DIR)/college/College_number.txt
	@touch $(DATA_DIR)/college/majors.txt
	@touch $(DATA_DIR)/college/Major_number.txt
	@touch $(DATA_DIR)/student/Students_data.txt
	@touch $(DATA_DIR)/student/Student_number.txt
	@touch $(DATA_DIR)/student/student_password.txt
	@touch $(DATA_DIR)/student/Math.txt
	@touch $(DATA_DIR)/student/English.txt
	@touch $(DATA_DIR)/student/Computer.txt
	@touch $(DATA_DIR)/student/Politics.txt
	@touch $(DATA_DIR)/student/room_change_request.txt
	@touch $(DATA_DIR)/student/room_leave_request.txt
	@touch $(DATA_DIR)/student/money.txt
	@touch $(DATA_DIR)/teacher/Teachers_data.txt
	@touch $(DATA_DIR)/teacher/Teacher_number.txt
	@touch $(DATA_DIR)/teacher/teacher_password.txt
	@touch $(DATA_DIR)/bus/南湖-浑南.txt
	@touch $(DATA_DIR)/bus/浑南-南湖.txt
	@echo "数据文件已创建"

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)
	
clean-data:
	rm -f $(DATA_DIR)/*/*.txt 