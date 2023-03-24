# ASDFR Assignment 2
**By Jonathan Schaaij and Tjeerd Bakker**

Compile for linux:
```bash
# Compile the program using sleep
g++ main_sleep.cpp -o main_sleep -lpthread
# Compile the program using timer
g++ main_timer.cpp -o main_timer -lpthread
```

Compile for xenomai:
```bash
g++ main_sleep.cpp -o main_sleep $(/usr/xenomai/bin/xeno-config --skin=posix --cflags --ldflags)
```