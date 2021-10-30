# Producer Consumer Problem


Producer generates items and put items onto table. Consumer will pick up items. The table can only hold 2 items at the same time. When the table is full, producer will wait. When there are no items, consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. We use pthreads in producer program and consumer program. Shared memory is used for “table”.

How does the program work?

We use an array called buffer[] that works as the shared memory between the producer and the consumer. We start by creating two threads, the first one calls the producer function to produce items and the second one calls the consumer function to consume items. We use both semaphore and mutex to make sure only one thread is executed at the same time. pthread_mutex_lock and pthread_mutex_unlock functions are used to make sure the code in between is executed without any intervention from another thread. For the producer we put an item in the buffer and increment the count, while for the producer we take out the item and decrement the count. We use sem_wait and sem_post functions to make sure when we have no items in the buffer the consumer wait on the producer to produce items before it can consume them, similarly when the count is 2 the producer wait on the consumer to consume items before it can produce more items.

How to compile and run the program:

-	To compile the program, you need to have pthread library and gcc compiler installed in your linux machine than use the following command:

gcc producerConsumer.c -pthread -lrt -o producerConsumer

this will generate a new object file producerConsumer.o

-	To run the program, use the following command:

./producerConsumer
