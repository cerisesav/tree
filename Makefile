CC = g++

CFLAGS = -Wall -D _DEBUG -ggdb3 -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts \
-Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual \
-Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=2 -Wsuggest-override -Wswitch-default -Wswitch-enum \
-Wundef -Wunreachable-code -Wunused -Wvariadic-macros -Wno-literal-range -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector \
-Wsuggest-override -Wlong-long -Wopenmp -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
-fno-omit-frame-pointer -Wlarger-than=8192 -Wstack-protector -fPIE -Werror=vla

EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): main.o dump.o functions.o
	$(CC) main.o dump.o functions.o -o $(EXECUTABLE)

main.o: main.cpp $(filename)
	$(CC) $(CFLAGS) -c main.cpp $(filename)

dump.o: dump.cpp
	$(CC) $(CFLAGS) -c dump.cpp

functions.o: functions.cpp
	$(CC) $(CFLAGS) -c functions.cpp

run:
	./$(EXECUTABLE) $(filename)

clean:
	rm -rf *.o $(EXECUTABLE)

