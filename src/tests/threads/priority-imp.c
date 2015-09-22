#include <stdio.h>
#include "tests/threads/tests.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"
#include "devices/timer.h"

void print_thread1(){
	printf("Running the Thread 1\n");
}

void print_thread2(){
	printf("Running the Thread 2\n");
}

void print_thread3(){
	printf("Running the Thread 3\n");
}

void print_thread4(){
	printf("Running the Thread 4\n");
}

void print_thread5(){
	printf("Running the Thread 5\n");
}

void testing_priority(void){
	thread_create("Thread1", 20, print_thread1, NULL);
	thread_create("Thread2", 5, print_thread2, NULL);
	thread_create("Thread3", 15, print_thread3, NULL);
	thread_create("Thread4", 12, print_thread4, NULL);
	thread_create("Thread5", 34, print_thread5, NULL);
	return;
}