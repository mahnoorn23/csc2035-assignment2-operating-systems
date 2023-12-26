/*
 * Replace the following string of 0s with your student number
 * 220298089
 */
#include <stdlib.h>
#include <stdbool.h>
#include "pri_jobqueue.h"
#include <string.h> // added for the dequeue function

/* 
 * TODO: you must implement this function that allocates a job queue and 
 * initialise it.
 * Hint:
 * - see job_new in job.c
 */
pri_jobqueue_t* pri_jobqueue_new() {
    pri_jobqueue_t* pjq = malloc(sizeof(pri_jobqueue_t));
    if (pjq == NULL) {
        return NULL;
    }
    pri_jobqueue_init(pjq);

    atexit(pri_jobqueue_delete);
    return pjq;
}

/* 
 * TODO: you must implement this function.
 */
void pri_jobqueue_init(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        strerror("error");
        exit(EXIT_FAILURE);
    }
    pjq->buf_size = JOB_BUFFER_SIZE;
    pjq->size = 0;

    for (int i = 0; i < JOB_BUFFER_SIZE; i++) {
        job_init(&(pjq->jobs[i]));
    }
}

/* 
 * TODO: you must implement this function.
 * Hint:
 *      - if a queue is not empty, and the highest priority job is not in the 
 *      last used slot on the queue, dequeueing a job will result in the 
 *      jobs on the queue having to be re-arranged
 *      - remember that the job returned by this function is a copy of the job
 *      that was on the queue
 */
job_t* pri_jobqueue_dequeue(pri_jobqueue_t* pjq, job_t* dst) {
    if (pri_jobqueue_is_empty(pjq)) {
        return NULL;
    }

    if(dst == NULL){
        dst =  (job_t*) malloc(sizeof(job_t));
        if(dst == NULL){
            return NULL;
        }
    }

    pri_jobqueue_peek(pjq, dst);

    int highest_priority_idx = 0;
    for (int i = 0; i < pjq->buf_size; i++) {
        if (job_is_equal(dst, &pjq->jobs[i])) {
            highest_priority_idx = i;
            break;
        }
    }

    for (int i = highest_priority_idx; i < pjq->size; i++) {
        job_copy(&pjq->jobs[i + 1], &pjq->jobs[i]);
    }

    job_init(&pjq->jobs[pjq->buf_size - 1]);
    pjq->size--;

    return dst;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 * - if a queue is not full, and if you decide to store the jobs in 
 *      priority order on the queue, enqueuing a job will result in the jobs 
 *      on the queue having to be re-arranged. However, it is not essential to
 *      store jobs in priority order (it simplifies implementation of dequeue
 *      at the expense of extra work in enqueue). It is your choice how 
 *      you implement dequeue (and enqueue) to ensure that jobs are dequeued
 *      by highest priority job first (see pri_jobqueue.h)
 * - remember that the job passed to this function is copied to the 
 *      queue
 */
void pri_jobqueue_enqueue(pri_jobqueue_t* pjq, job_t* job) {
    if (pjq == NULL || job == NULL || job->priority <= 0) {
        return;
    }

    if (pri_jobqueue_is_full(pjq)) {
        return;
    }

    int insertIndex = 0;
    while (insertIndex < pjq->size && job->priority >= pjq->jobs[insertIndex].priority) {
        ++insertIndex;
    }

    if (insertIndex < pjq->size) {
        memmove(&pjq->jobs[insertIndex + 1], &pjq->jobs[insertIndex], sizeof(job_t) * (pjq->size - insertIndex));
    }

    job_copy(job, &(pjq->jobs[insertIndex]));

    ++pjq->size;
}

/* 
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_empty(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        return true;
    }
    return pjq->size == 0;
}

/* 
 * TODO: you must implement this function.
 */
bool pri_jobqueue_is_full(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        return true;
    }
    return pjq->size == pjq->buf_size;
}

/* 
 * TODO: you must implement this function.
 * Hints:
 *      - remember that the job returned by this function is a copy of the 
 *      highest priority job on the queue.
 *      - both pri_jobqueue_peek and pri_jobqueue_dequeue require copying of 
 *      the highest priority job on the queue
 */
job_t* pri_jobqueue_peek(pri_jobqueue_t* pjq, job_t* dst) {
    if (pri_jobqueue_is_empty(pjq)) {
        return NULL;
    }

    int highest_priority_idx = 0;
    for (int i = 0; i < pjq->size; i++) {
        if (pjq->jobs[highest_priority_idx].priority > pjq->jobs[i].priority) {
            highest_priority_idx = i;
        }
    }

    if(dst == NULL){
        dst =  (job_t*) malloc(sizeof(job_t));
        if(dst == NULL){
            return NULL;
        }
    }
    job_copy(&pjq->jobs[highest_priority_idx], dst);
    if (dst) {
        return dst;
    }
    return NULL;
}

/* 
 * TODO: you must implement this function.
 */
int pri_jobqueue_size(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        return 0;
    }
    return pjq->size;
}

/* 
 * TODO: you must implement this function.
 */
int pri_jobqueue_space(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        return 0;
    }

    int used_slots = 0;
    for (int i = 0; i < pjq->size; i++) {
        if (pjq->jobs[i].priority > 0) {
            used_slots++;
        }
    }

    return pjq->buf_size - used_slots;
}

/* 
 * TODO: you must implement this function.
 *  Hint:
 *      - see pri_jobqeue_new
 */
void pri_jobqueue_delete(pri_jobqueue_t* pjq) {
    if (pjq == NULL) {
        return;
    }
    free(pjq);
}
