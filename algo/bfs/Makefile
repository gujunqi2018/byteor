# ---------------------------------------------
#      BREADTH FIRST SEARCH AlGORITHM
#
# Copyright (c) Zhou Peng <p@ctriple.cn>
#
# ---------------------------------------------

CC = gcc
cflag = -Wall -g

objs += main.o
objs += bfs.o

bfs.out: $(objs)
	$(CC) $(objs) -o $@

main.o: main.c
	$(CC) $(cflag) -c $< -o $@

bfs.o: bfs.c
	$(CC) $(cflag) -c $< -o $@
