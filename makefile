CC=g++
STD=-std=c++11
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: my_server/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/show.o: my_server/show.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/show.cpp -o $(BUILD_DIR)/show.o

$(BUILD_DIR)/details_handler.o: my_server/details_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/details_handler.cpp -o $(BUILD_DIR)/details_handler.o

$(BUILD_DIR)/delete_handler.o: my_server/delete_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/delete_handler.cpp -o $(BUILD_DIR)/delete_handler.o

$(BUILD_DIR)/login_handler.o: my_server/login_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/login_handler.cpp -o $(BUILD_DIR)/login_handler.o

$(BUILD_DIR)/signup_handler.o: my_server/signup_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/signup_handler.cpp -o $(BUILD_DIR)/signup_handler.o

$(BUILD_DIR)/film_handler.o: my_server/film_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/film_handler.cpp -o $(BUILD_DIR)/film_handler.o

$(BUILD_DIR)/increase_handler.o: my_server/increase_handler.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/increase_handler.cpp -o $(BUILD_DIR)/increase_handler.o

$(BUILD_DIR)/search_handler.o: my_server/search_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/search_handler.cpp -o $(BUILD_DIR)/search_handler.o

$(BUILD_DIR)/profile_handler.o: my_server/profile_handler.cpp my_server/show.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/profile_handler.cpp -o $(BUILD_DIR)/profile_handler.o

$(BUILD_DIR)/my_server.o: my_server/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: my_server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/comment.o: Assignment7/comment.cpp Assignment7/comment.h
	$(CC) $(CF) -c Assignment7/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/user.o: Assignment7/user.cpp Assignment7/user.h  Assignment7/film_repository.h Assignment7/notification_repository.h Assignment7/film.h Assignment7/user_repository.h
	$(CC) $(CF) -c Assignment7/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/publisher.o: Assignment7/publisher.cpp Assignment7/publisher.h Assignment7/user.h Assignment7/film.h Assignment7/film_repository.h
	$(CC) $(CF) -c Assignment7/publisher.cpp -o $(BUILD_DIR)/publisher.o

$(BUILD_DIR)/network.o: Assignment7/network.cpp Assignment7/network.h Assignment7/user.h Assignment7/user_repository.h Assignment7/film_repository.h
	$(CC) $(CF) -c Assignment7/network.cpp -o $(BUILD_DIR)/network.o

$(BUILD_DIR)/film.o: Assignment7/film.cpp Assignment7/film.h Assignment7/publisher.h Assignment7/comment.h Assignment7/comment_repository.h Assignment7/notification.h
	$(CC) $(CF) -c Assignment7/film.cpp -o $(BUILD_DIR)/film.o

$(BUILD_DIR)/user_repository.o: Assignment7/user_repository.cpp Assignment7/user_repository.h Assignment7/user.h
	$(CC) $(CF) -c Assignment7/user_repository.cpp -o $(BUILD_DIR)/user_repository.o

$(BUILD_DIR)/film_repository.o: Assignment7/film_repository.cpp Assignment7/film_repository.h Assignment7/film.h
	$(CC) $(CF) -c Assignment7/film_repository.cpp -o $(BUILD_DIR)/film_repository.o

$(BUILD_DIR)/network_film_repository.o: Assignment7/network_film_repository.cpp Assignment7/network_film_repository.h Assignment7/film_repository.h
	$(CC) $(CF) -c Assignment7/network_film_repository.cpp -o $(BUILD_DIR)/network_film_repository.o

$(BUILD_DIR)/comment_repository.o: Assignment7/comment_repository.cpp Assignment7/comment_repository.h Assignment7/comment.h
	$(CC) $(CF) -c Assignment7/comment_repository.cpp -o $(BUILD_DIR)/comment_repository.o

$(BUILD_DIR)/exception.o: Assignment7/exceptions.cpp Assignment7/exceptions.h
	$(CC) $(CF) -c Assignment7/exceptions.cpp -o $(BUILD_DIR)/exception.o

$(BUILD_DIR)/notification.o: Assignment7/notification.cpp Assignment7/notification.h
	$(CC) $(CF) -c Assignment7/notification.cpp -o $(BUILD_DIR)/notification.o

$(BUILD_DIR)/notification_repository.o: Assignment7/notification_repository.cpp Assignment7/notification_repository.h
	$(CC) $(CF) -c Assignment7/notification_repository.cpp -o $(BUILD_DIR)/notification_repository.o

$(BUILD_DIR)/validity.o: Assignment7/validity.cpp Assignment7/validity.h
	$(CC) $(CF) -c Assignment7/validity.cpp -o $(BUILD_DIR)/validity.o	
	
myserver.out: $(BUILD_DIR)/handlers.o $(BUILD_DIR)/delete_handler.o $(BUILD_DIR)/details_handler.o $(BUILD_DIR)/signup_handler.o $(BUILD_DIR)/login_handler.o $(BUILD_DIR)/search_handler.o $(BUILD_DIR)/film_handler.o $(BUILD_DIR)/increase_handler.o $(BUILD_DIR)/profile_handler.o $(BUILD_DIR)/show.o $(BUILD_DIR)/main.o $(BUILD_DIR)/my_server.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/user.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/network.o $(BUILD_DIR)/film.o $(BUILD_DIR)/user_repository.o $(BUILD_DIR)/film_repository.o $(BUILD_DIR)/comment_repository.o $(BUILD_DIR)/exception.o $(BUILD_DIR)/notification.o $(BUILD_DIR)/validity.o $(BUILD_DIR)/notification_repository.o $(BUILD_DIR)/network_film_repository.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/delete_handler.o $(BUILD_DIR)/details_handler.o $(BUILD_DIR)/signup_handler.o $(BUILD_DIR)/login_handler.o $(BUILD_DIR)/search_handler.o $(BUILD_DIR)/film_handler.o $(BUILD_DIR)/increase_handler.o $(BUILD_DIR)/profile_handler.o $(BUILD_DIR)/show.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/user.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/network.o $(BUILD_DIR)/film.o $(BUILD_DIR)/user_repository.o $(BUILD_DIR)/film_repository.o $(BUILD_DIR)/comment_repository.o $(BUILD_DIR)/exception.o $(BUILD_DIR)/notification.o $(BUILD_DIR)/validity.o $(BUILD_DIR)/notification_repository.o $(BUILD_DIR)/network_film_repository.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
