#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "tthread.h"

static int id = 0;

static tt_thread_t threads_head = NULL;
static tt_thread_t threads_tail = NULL;

static tt_thread_t current_thread = NULL;
static tt_context_t scheduler_context;

tt_context_t tt_new_context(tt_stack_t sp, void (*fun)(void *), void *arg) {
    tt_context_t ctx =
        (tt_context_t)((char *)sp - sizeof(struct tt_context));

    ctx->fun = fun;
    ctx->arg = arg;
    //ctx->ret = NULL;
    return ctx;
}

static void enqueue(tt_thread_t th) {
    if (threads_head == NULL) {
        assert(threads_tail == NULL);
        threads_head = threads_tail = th;
        th->next = NULL;
    }
    else {
        assert(threads_tail != NULL && threads_tail->next == NULL);
        threads_tail->next = th;
        threads_tail = th;
        th->next = NULL;
    }
}

static tt_thread_t dequeue(void) {
    if (threads_head == NULL) {
        assert(threads_tail == NULL);
        return NULL;
    }
    tt_thread_t th = threads_head;
    threads_head = th->next;
    return th;
}

void tt_initialize(void) {
    tt_thread_t th = malloc(sizeof(struct tt_tcb));
    if (th == NULL) {
        perror("init_threads");
        exit(EXIT_FAILURE);
    }
    th->id = id++;
    th->stack = NULL;
    th->context = NULL;
    th->state = TT_RUNNING;
    th->parent = NULL;
    enqueue(th);
    current_thread = th;
}

tt_thread_t tt_new_thread(void (*fun)(void *), void *arg) {
    tt_thread_t th = malloc(sizeof(struct tt_tcb));
    if (th == NULL) {
        perror("tt_new_thread");
        return NULL;
    }

    tt_stack_t stack = valloc(TT_STACK_SIZE);
    if (stack == NULL) {
        perror("tt_new_thread");
        free(th);
        return NULL;
    }

    th->id = id++;
    th->stack = stack;
    th->context = tt_new_context(stack + TT_STACK_DEPTH, fun, arg);
    th->state = TT_RUNNABLE;
    th->parent = current_thread;
    enqueue(th);
 
    return th;
}

void tt_start_threads(void) {
    tt_thread_t th = dequeue();
    assert(th->id == 0);
    enqueue(th);
    int a = 0;
    while (threads_head != threads_tail) {
        th = dequeue();
        if (th->id == 0) {
            if (a) {
                a = 0;
                enqueue(th);
            }
            else {
                fprintf(stderr, "deadlock detected\n");
                return;
            }
        }
        else {
            if (th->state == TT_RUNNABLE) {
                a = 1;
                current_thread = th;
                th->state = TT_RUNNING;
                tt_swtch(&scheduler_context, th->context);
                enqueue(current_thread);
            }
            else if(th->state == TT_DEAD) {
                free(th->stack);
                free(th);
                /* Don't enqueue */
            }
            else {
                enqueue(th);
            }
        }
    }
}

void tt_yield(void) {
    current_thread->state = TT_RUNNABLE;
    tt_swtch(&current_thread->context, scheduler_context);
}

static void wakeup(tt_thread_t th, void *event) {
    if (th->state == TT_WAITING && th->event == event)
        th->state = TT_RUNNABLE;
}

void tt_exit(void *result) {
    if (current_thread->id == 0) {
        fprintf(stderr, "tt_exit: thread 0 cannot exit.\n");
        return;
    }
    current_thread->state = TT_ZOMBIE;
    current_thread->result = result;
    wakeup(current_thread->parent, current_thread);
    tt_swtch(&current_thread->context, scheduler_context);
}

void *tt_join(tt_thread_t th) {
    if (th->parent != current_thread) {
        fprintf(stderr, "tt_join: %d is not a child of %d\n",
                th->id, current_thread->id);
        return NULL;
    }
    while (th->state != TT_ZOMBIE) {
        current_thread->state = TT_WAITING;
        current_thread->event = th;
        tt_swtch(&current_thread->context, scheduler_context);
    }
    th->state = TT_DEAD;
    void *result = th->result;
    return result;
}

tt_thread_t tt_myself(void) {
    return current_thread;
}

int tt_myid(void) {
    return current_thread->id;
}

static char *state_name(enum tt_state s) {
    switch (s) {
    case TT_UNUSED: return "UNUSED";
    case TT_RUNNABLE: return "RUNNABLE";
    case TT_RUNNING: return "RUNNING";
    case TT_WAITING: return "WAITING";
    case TT_ZOMBIE: return "ZOMBIE";
    default: return "UNKNOWN";
    }
}

void tt_show_threads(void) {
	tt_thread_t th;
    for (th = threads_head; th != NULL; th = th->next) {
        printf("id=%d, state=%s, ctx=%p\n",
               th->id, state_name(th->state), (void *)th->context);
    }
}
