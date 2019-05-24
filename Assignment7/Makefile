CC := g++

all: a.out

a.out: main.o user.o publisher.o comment.o network.o command_handler.o film.o user_repository.o film_repository.o comment_repository.o exception.o notification.o validity.o notification_repository.o
	$(CC) main.o user.o publisher.o comment.o network.o command_handler.o film.o user_repository.o film_repository.o comment_repository.o exception.o notification.o validity.o notification_repository.o -o a.out

main.o: main.cpp command_handler.h 
	$(CC) -c main.cpp -o main.o

comment.o: comment.cpp comment.h
	$(CC) -c comment.cpp -o comment.o

user.o: user.cpp user.h  film_repository.h notification_repository.h film.h user_repository.h
	$(CC) -c user.cpp -o user.o

publisher.o: publisher.cpp publisher.h user.h film.h film_repository.h
	$(CC) -c publisher.cpp -o publisher.o

network.o: network.cpp network.h user.h user_repository.h film_repository.h
	$(CC) -c network.cpp -o network.o

command_handler.o: command_handler.cpp command_handler.h network.h validity.h
	$(CC) -c command_handler.cpp -o command_handler.o

film.o: film.cpp film.h publisher.h comment.h comment_repository.h notification.h
	$(CC) -c film.cpp -o film.o

user_repository.o: user_repository.cpp user_repository.h user.h
	$(CC) -c user_repository.cpp -o user_repository.o

film_repository.o: film_repository.cpp film_repository.h film.h
	$(CC) -c film_repository.cpp -o film_repository.o

comment_repository.o: comment_repository.cpp comment_repository.h comment.h
	$(CC) -c comment_repository.cpp -o comment_repository.o

exception.o: exceptions.cpp exceptions.h
	$(CC) -c exceptions.cpp -o exception.o

notification.o: notification.cpp notification.h
	$(CC) -c notification.cpp -o notification.o

notification_repository.o: notification_repository.cpp notification_repository.h
	$(CC) -c notification_repository.cpp -o notification_repository.o

validity.o: validity.cpp validity.h
	$(CC) -c validity.cpp -o validity.o	

.PHONY: clean
clean:
	rm *.o 
	rm a.out