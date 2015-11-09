#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);
static int *syscall_retrieve_args (struct intr_frame *f);
void syscall_t_exit (char * p_name, int status);
static int get_word_user (const int *uaddr);
void syscall_create (int *args, struct intr_frame *f );

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
  syscall_functions[SYS_CREATE] = &syscall_create; // added
  syscall_noa[SYS_CREATE] = 2; //added
}

//added
void syscall_t_exit (char * p_name, int status){
	printf ("%s: exit(%d)\n", p_name, status);
	thread_exit ();
}

static void
//syscall_handler (struct intr_frame *f UNUSED) 
syscall_handler (struct intr_frame *f) 
{
  struct thread *t = thread_current ();
  int syscall_number = get_word_user((int *)(f -> esp));
  if(syscall_number < SYS_HALT || syscall_number > SYS_MUNMAP) {
	syscall_t_exit (t -> name, -1);
  }
  int *args = syscall_retrieve_args (f);
  syscall_functions[syscall_number] (args, f);
  free (args);
  printf ("system call!\n");
  // thread_exit ();
}

static int *syscall_retrieve_args (struct intr_frame *f){
int *args = (int*) malloc(3);
int syscall_number = get_word_user((int *)(f -> esp));
int noa = syscall_noa[syscall_number];
int i;
for(i = 0; i <= noa; i++) {
args[i] = get_word_user((int *)(f -> esp) + i);
if(args[i] == -1) {
syscall_t_exit (thread_current () -> name, -1);
}
}
return args;
}

static int get_word_user (const int *uaddr)
{
int result;
if ((void *) uaddr >= PHYS_BASE)
{
syscall_t_exit (thread_current () -> name, -1);
}
asm ("movl $1f, %0; movl %1, %0; 1:" : "=&a" (result) :
"m" (*uaddr));
return result;
}

static int validate_user (const uint8_t *uaddr)
{
int result;
if ((void *) uaddr >= PHYS_BASE) {
syscall_t_exit (thread_current () -> name, -1);
}
asm ("movl $1f, %0; movzbl %1, %0; 1:" : "=&a"
(result) : "m" (*uaddr));
return result;
}

void syscall_create (int *args, struct intr_frame *f ){
validate_user ((uint8_t *) args[1]);
filesys_lock_acquire (); // implement this
f->eax = filesys_create ((char *) args[1], args[2]);
filesys_lock_release (); // implement this
}


