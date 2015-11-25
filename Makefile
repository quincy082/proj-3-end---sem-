COMPUTER = ubuntu
PORTNO = 51719
carrom : main.c
	@gcc main.c -o carrom -lGLU -lglut -lm
	@./carrom $(PORTNO)
client2p : car_client2p.c
	@gcc car_client2p.c -o client2p -lGLU -lglut -lm 
	@./client2p $(COMPUTER) $(PORTNO)
client1 : car_client4p1.c
	@gcc car_client4p1.c -o client1 -lGLU -lglut -lm 
	@./client1 $(COMPUTER) $(PORTNO)
client2 : car_client4p2.c
	@gcc car_client4p2.c -o client2 -lGLU -lglut -lm 
	@./client2 $(COMPUTER) $(PORTNO)
client3 : car_client4p3.c
	@gcc car_client4p3.c -o client3 -lGLU -lglut -lm 
	@./client3 $(COMPUTER) $(PORTNO)
clean :
	rm carrom client2p client1 client2 client3
