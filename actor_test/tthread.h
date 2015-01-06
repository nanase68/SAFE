/**
 * The original version of tthread is wtakuo/tthread on github.
 * https://github.com/wtakuo/tthread
 */

#ifndef TTHREAD_H_
#define TTHREAD_H_

#define TT_STACK_SIZE 1024
#define TT_STACK_DEPTH (TT_STACK_SIZE / sizeof(void *))

#ifdef __cplusplus
extern "C" {
#endif

typedef void *tt_stack_t;

typedef struct tt_context {
    void *r8;
    void *r9;
    void *r10;
    void *r11;
    void *r12;
    void *arg;  // r0
    void *r4;
    void *r5;
    void *r6;
    void *r7;
    void (*fun)(void *);  // ip
    //void *ret;
    //void *arg;
} *tt_context_t;

tt_context_t tt_new_context(tt_stack_t sp, void (*fun)(void *), void *arg);

void tt_swtch(tt_context_t *from, tt_context_t to);

enum tt_state {
    TT_UNUSED, TT_RUNNABLE, TT_RUNNING, TT_WAITING, TT_ZOMBIE, TT_DEAD
};

typedef struct tt_tcb {
    struct tt_tcb *next;
    int id;
    enum tt_state state;
    tt_stack_t stack;
    tt_context_t context;
    struct tt_tcb *parent;
    void *event;
    void *result;
} *tt_thread_t;

// API
void tt_initialize(void);
tt_thread_t tt_new_thread(void (*fun)(void *), void *arg);
void tt_start_threads(void);
void tt_yield(void);
void tt_exit(void *);
void *tt_join(tt_thread_t th);
tt_thread_t tt_myself(void);
int tt_myid(void);

void tt_show_threads(void);

#ifdef __cplusplus
}
#endif

#endif /* TTHREAD_H_ */
