#include "sched.h"
//six sexies


static task_t* pick_next_task_prio(runqueue_t* rq,int cpu) {

	task_t* t=head_slist(&rq->tasks);
	
//eliminamos la tarea y la ponemos como current
	if(t) {
		remove_slist(&rq->tasks,t);
        t->on_rq=FALSE;
		rq->cur_task=t;
	}

	return t;
}

static int comparaTareas(void *t1,void *t2) {
	
	int diferencia = 0;

	task_t* tarea1 = (task_t*)t1;
	task_t* tarea2= (task_t*)t2;

	diferencia = tarea1->prio-tarea2->prio;
	return diferencia;
}


static void enqueue_task_prio(task_t* t,int cpu, int runnable) {

		runqueue_t* rq=get_runqueue_cpu(cpu);

	if (t->on_rq || is_idle_task(t)) return; //tarea ya esta encolada u ociosa

	//si la tarea desea ir al comienzo cola
	if(t->flags & TF_INSERT_FRONT) {
		//tarea ya insertada
		t->flags&=~TF_INSERT_FRONT;
		//empujamos tarea
        sorted_insert_slist_front(&rq->tasks, t, 1, comparaTareas);
	}

	else sorted_insert_slist(&rq->tasks, t, 1, comparaTareas);

	t->on_rq=TRUE;

	if (!runnable){
        task_t* current=rq->cur_task;
        rq->nr_runnable++;
        t->last_cpu=cpu;

		if (preemptive_scheduler && !is_idle_task(current) && t->prio<current->prio) {
            rq->need_resched=TRUE;
            current->flags|=TF_INSERT_FRONT; /* To avoid unfair situations in the event
                                                another task with the same prio wakes up as well*/
        }
	}
}


static void task_tick_prio(runqueue_t* rq,int cpu){

	task_t* current=rq->cur_task;
    
    if (is_idle_task(current))
        return;
    
    if (current->runnable_ticks_left==1) 
        rq->nr_runnable--; 
}


static task_t* steal_task_prio(runqueue_t* rq,int cpu){

    task_t* t=tail_slist(&rq->tasks);
    
    if (t) {
        remove_slist(&rq->tasks,t);
        t->on_rq=FALSE;
        rq->nr_runnable--;
    }
    return t;    
}


sched_class_t prio_sched = {
	.pick_next_task=pick_next_task_prio,
	.enqueue_task=enqueue_task_prio,
	.task_tick=task_tick_prio,
	.steal_task=steal_task_prio
};




