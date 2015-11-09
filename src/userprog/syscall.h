#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);
static void syscall_handler (struct intr_frame *);
static int *syscall_retrieve_args (struct intr_frame *f);
void syscall_t_exit (char * p_name, int status);
static int get_word_user (const int *uaddr);
void syscall_create (int *args, struct intr_frame *f );

#endif /* userprog/syscall.h */
