/*
Lenin Fabricio Benavides Quintana
*/


#include "clientGame.h"
#include <sys/socket.h>



// funciones necesarias para el envio y la recepcion de los mensajes


void sendMessageToServer(char* msg,int socketfd ){

	// primero se enviara la longitud del mensaje
	int tamMsg = sizeof(msg);

	
	if(send(socketfd,&tamMsg,sizeof(int),0) < sizeof(int))
		showError("ERROR while writing the size to the socket");

		// ahora enviamos el el mensaje 
	if(send(socketfd,msg,sizeof(msg),0) < 0)
		showError("ERROR while writing the message to the socket");




}

void recvMessageToServer(char* msg,int sockefd){

	// primero recibimos el tamaño del mensaje
	int tamMsg ;
	char *aux ;
	int bytesRecibidos = 0 , totalBytesRecibidos = 0 ;


	tamMsg = recv(socketfd,&tamMsg,sizeof(int),0);

	// inicializamos la cadena para evitar fallos

	memset(msg, 0, STRING_LENGTH);

	/// recibimos el mensaje

	while(totalBytesRecibidos < tamMsg){

		bytesRecibidos = recv(socketfd,msg,STRING_LENGTH-1,0) ;

		totalBytesRecibidos += bytesRecibidos ;


	} 


}

unsigned int readMove (){

	int i, isValid, column;
	tString enteredMove;

		// Init...
		column = 0;

		// While player does not enter a correct move...
		do{

			// Init...
			bzero (enteredMove, STRING_LENGTH);
			isValid = TRUE;

			// Show input message
			printf ("Enter a move [0-%d]:", BOARD_WIDTH-1);

			// Read move
			fgets(enteredMove, STRING_LENGTH-1, stdin);

			// Remove new-line char
			enteredMove[strlen(enteredMove)-1] = 0;

			// Check if each character is a digit
			for (i=0; i<strlen(enteredMove) && isValid; i++){

				if (!isdigit(enteredMove[i]))
					isValid = FALSE;
			}

			// Entered move is not a number
			if (!isValid){
				printf ("Entered move is not correct. It must be a number between [0-%d]\n", BOARD_W@Benny250 IDTH-1);
			}

			// Entered move is a number...
			else{

				// Conver entered text to an int
				column = atoi (enteredMove);
			}

		}while (!isValid);

	return ((unsigned int) column);
}

int main(int argc, char *argv[]){
	//atributos necesarios 

	unsigned short  port ; // variable para almacenar el puerto
	int socketfd ;// descriptor del socket
	struct sockaddr_in server_address;
	char* serverIP;
	// Check arguments!
	if (argc != 3){
		fprintf(stderr,"ERROR wrong number of arguments\n");
		fprintf(stderr,"Usage:\n$>%s serverIP port\n", argv[0]);
		exit(0);
	}

/* 
Socket
connect
send 
recv 
close
*/

	// pimero vamos a parsear los argumentos recibidos 

	port = atoi(argv[2]);
	serverIP = argv[1];

	// inicializamos el socket 
	socketfd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);@Benny250 

	if(socketfd < 0)
		showError("ERROR while creating the socket ");

	//rellenar la estructura  de ceros 
	menset(&server_address,0,sizeof(server_address));
	// rellenamos la estrcutura con los valores necesarios 
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(serverIP);
	server_address.sin_port = htons(port);

	// realizamos la conection con el servidor 

	if (connect(fd,(struct sockaddr *)server_address,sizeof(server_address))<0)
		showError("ERROR while establishing connection");

	/*
	Apartir de aqui se implementa el envio y la recepcion de mensajes
	*/

  





}
