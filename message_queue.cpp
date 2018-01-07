#include "bigHeader.h"
#include "message_queue.h"


void get_option(int argument_count){
	if(argument_count == 1){
		message_queue_sender();
	}
	else{
		message_queue_reciever();
	}
	return;
}

/*
	program to receieve the message 
	writing to a particular queue
*/
void message_queue_reciever(){
	
	int run_status                   = 1;
	int queue_message_id             = 0;
	long int message_type_to_recieve = 0;
	struct queue_message_struct	queue_data;
	
	/*
		setting up the message queue
	*/

	queue_message_id = msgget((key_t)1234,0666|IPC_CREAT);
	if(-1 == queue_message_id){
		fprintf(stderr,"msgget failed with error%d\n",errno);
		return;
	}

	/*
		messages has to be retrievd from the message queue
		until and end message occurs
	*/

	while(run_status){
		if( -1 == msgrcv(
			queue_message_id,
			(void*)&queue_data,
			BUFSIZ,
			message_type_to_recieve,
			0)
		){
			fprintf(stderr,"message failed with error :%d\n",errno);
			return;
		}

		printf("You wrote :%s",queue_data.message_data);
		if(0 == strncmp(queue_data.message_data,"end",3)){
			run_status = 0;
		}
	}

	if(-1 == msgctl(queue_message_id,IPC_RMID,0)){
		fprintf(stderr,"mgctl(IPC_RMID) failed with error message:%d\n",errno);
		return;
	}

	return;
}
void message_queue_sender(){
	int run_status       = 1;
	int queue_message_id = 0;
	struct queue_message_struct queue_data;
	char message_buffer[MAX_TEXT_SZ];

	queue_message_id = msgget((key_t)1234,0666|IPC_CREAT);
	if(-1 == queue_message_id){
		fprintf(stderr,"msgget failed with error no : %d\n",errno);
		return;
	}

	while(run_status){
		printf("Enter some text:\n");
		fgets(message_buffer,BUFSIZ,stdin);
		queue_data.message_type = 1;
		strcpy(queue_data.message_data,message_buffer);

		/*
			send the message from the input terminal to the 
		*/

		if(-1 == msgsnd(queue_message_id,(void*)&queue_data,MAX_TEXT_SZ,0)){
			fprintf(stderr,"message sending to the queue failed with error message :%d\n",errno);
			return;
		}

		if(0 == strncmp(message_buffer,"end",3)){
		 	run_status = 0;
		}
		
	}

	return;
}