#include <stdio.h>
#include <stdbool.h>

#define MAX 20

typedef struct {
    int pid;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int arrival_time;
    bool completed;
} Process;

void calculate_waiting_time(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
    }
}

void calculate_turnaround_time(Process p[], int n, int total_time) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = total_time - p[i].arrival_time;
    }
}

int main() {
    Process p[MAX];
    int n;
    int current_time = 0, completed_processes = 0;
    int min_priority, shortest = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time, burst time and priority for process P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
        p[i].completed = false;
    }

    while (completed_processes != n) {
        min_priority = 9999;
        shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= current_time && !p[i].completed && p[i].priority < min_priority) {
                min_priority = p[i].priority;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        p[shortest].remaining_time--;
        current_time++;

        if (p[shortest].remaining_time == 0) {
            p[shortest].completed = true;
            completed_processes++;
            p[shortest].turnaround_time = current_time - p[shortest].arrival_time;
        }
    }

    calculate_waiting_time(p, n);

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    return 0;
}

