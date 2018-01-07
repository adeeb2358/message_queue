#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#define MAX_TEXT_SZ 512

struct queue_message_struct{
	long int message_type;
	char message_data[BUFSIZ];
};

void get_option(int argument_count);
void message_queue_sender();
void message_queue_reciever();

#endif // MESSAGE_QUEUE_H
