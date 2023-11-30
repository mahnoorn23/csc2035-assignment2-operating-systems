/*
 * Replace the following string of 0s with your student number
 * 220298089
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "job.h"

/* 
 * DO NOT EDIT the job_new function.
 */
job_t* job_new(pid_t pid, unsigned int id, unsigned int priority, 
    const char* label) {
    return job_set((job_t*) malloc(sizeof(job_t)), pid, id, priority, label);
}

/* 
 * TODO: you must implement this function
 */
job_t* job_copy(job_t* src, job_t* dst) {
    // to check for null src pointer?
    if(src == NULL) {
        return NULL;
    }
    // to check if src and dst are identical
    else if (src == dst) {
        return dst;
    }

    // dst is null
    else if (dst == NULL) {
        // to allocate a new job
        dst = job_new(src->pid, src->id, src->priority, src->label);
        // new job is returned
        return dst;
    }
    else if (dst != NULL && dst != src){
        dst->pid = src->pid;
        dst->id = src->id;
        dst->priority = src->priority;
        dst->label = src->label;
        strncpy(dst->label, src->label, MAX_NAME_SIZE -1)
        dst->label[MAX_NAME_SIZE - 1] = '\0';
        return dst
    }


    // return src;
}

/* 
 * TODO: you must implement this function
 */
void job_init(job_t* job) {
    return;
}

/* 
 * TODO: you must implement this function
 */
bool job_is_equal(job_t* j1, job_t* j2) {
    return false;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - read the information in job.h about padding and truncation of job
 *      labels
 */
job_t* job_set(job_t* job, pid_t pid, unsigned int id, unsigned int priority,
    const char* label) {
    return job;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see malloc and calloc system library functions for dynamic allocation, 
 *      and the documentation in job.h for when to do dynamic allocation
 */
char* job_to_str(job_t* job, char* str) {
    return NULL;
}

/*
 * TODO: you must implement this function.
 * Hint:
 * - see the hint for job_to_str
 */
job_t* str_to_job(char* str, job_t* job) {
    return NULL;
}

/* 
 * TODO: you must implement this function
 * Hint:
 * - look at the allocation of a job in job_new
 */
void job_delete(job_t* job) {
    return;
}