#include <stdio.h>
#include <stdlib.h>


struct process {
    int pid; 
    int burst_time; 
    int priority; 
    int remaining_time; 
    int waiting_time; 
    int turnaround_time; 
    int level; 
};


void enqueue(struct process *queue[], int *rear, struct process *proc) {
    queue[++(*rear)] = proc;
}


struct process* dequeue(struct process *queue[], int *front) {
    return queue[(*front)++];
}


void sort(struct process *queue[], int front, int rear, int type) {
    int i, j;
    struct process *temp;
    for (i = front; i <= rear; i++) {
        for (j = i + 1; j <= rear; j++) {
            if (type == 1) { 
                if (queue[i]->priority < queue[j]->priority) {
                    temp = queue[i];
                    queue[i] = queue[j];
                    queue[j] = temp;
                }
            } else { 
                if (queue[i]->remaining_time > queue[j]->remaining_time) {
                    temp = queue[i];
                    queue[i] = queue[j];
                    queue[j] = temp;
                }
            }
        }
    }
}

int main() {
    int i, n, current_time = 0, time_quantum = 2;
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    struct process *queue1[100], *queue2[100], *proc;
    int front1 = 0, rear1 = -1, front2 = 0, rear2 = -1;

    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    
    for (i = 0; i < n; i++) {
        proc = (struct process*) malloc(sizeof(struct process));
        printf("Enter details for process %d:\n", i + 1);
        printf("PID: ");
        scanf("%d", &proc->pid);
        printf("Burst Time: ");
        scanf("%d", &proc->burst_time);
        printf("Priority (0 is highest): ");
        scanf("%d", &proc->priority);
        proc->remaining_time = proc->burst_time;
        proc->level = 1;
        enqueue(queue1, &rear1, proc);
    }

    
    while (front1 <= rear1 || front2 <= rear2) {
        
        if (front1 <= rear1) {
            
            sort(queue1, front1, rear1, 1);
            proc = dequeue(queue1, &front1);
            
            if (proc->remaining_time <= time_quantum) {
                current_time += proc->remaining_time;
                proc->remaining_time = 0;
            proc->waiting_time = current_time - proc->burst_time;
            proc->turnaround_time = current_time;
            avg_waiting_time += proc->waiting_time;
            avg_turnaround_time += proc->turnaround_time;
           
            printf("Process %d:\n", proc->pid);
            printf("Waiting Time: %d\n", proc->waiting_time);
            printf("Turnaround Time: %d\n", proc->turnaround_time);
            free(proc);
        } else { 
            current_time += time_quantum;
            proc->remaining_time -= time_quantum;
            proc->level = 2;
            enqueue(queue2, &rear2, proc);
        }
    } else {
        
        sort(queue2, front2, rear2, 2);
        proc = dequeue(queue2, &front2);
        current_time += proc->remaining_time;
        proc->waiting_time = current_time - proc->burst_time;
        proc->turnaround_time = current_time;
        avg_waiting_time += proc->waiting_time;
        avg_turnaround_time += proc->turnaround_time;
        

        printf("Process %d:\n", proc->pid);
        printf("Waiting Time: %d\n", proc->waiting_time);
        printf("Turnaround Time: %d\n", proc->turnaround_time);
        free(proc);
    }
}

avg_waiting_time /= n;
avg_turnaround_time /= n;
printf("Average Waiting Time: %.2f\n", avg_waiting_time);
printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);

return 0;
}
