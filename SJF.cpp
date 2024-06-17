#include <stdio.h>

#define MAX 20

typedef struct {
    int pid;
    int burst_time;
    int waiting_time;
    int turnaround_time;
} Process;

void sort_by_burst_time(Process p[], int n) {
    int i, j;
    Process temp;
    for (i = 0; i < n-1; i++) {
        for (j = i+1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculate_waiting_time(Process p[], int n) {
    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = p[i-1].waiting_time + p[i-1].burst_time;
    }
}

void calculate_turnaround_time(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].waiting_time + p[i].burst_time;
    }
}

void print_gantt_chart(Process p[], int n) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf(" | P%d ", p[i].pid);
    }
    printf("|\n");
    printf("0");
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst_time;
        printf("   %d", time);
    }
    printf("\n");
}

int main() {
    Process p[MAX];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i+1;
        printf("Enter burst time for process P%d: ", p[i].pid);
        scanf("%d", &p[i].burst_time);
    }

    sort_by_burst_time(p, n);
    calculate_waiting_time(p, n);
    calculate_turnaround_time(p, n);

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    print_gantt_chart(p, n);

    return 0;
}

