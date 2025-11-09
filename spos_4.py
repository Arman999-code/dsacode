# Function to find the waiting time for all processes
def findWaitingTime(processes, n, wt):
    rt = [p[1] for p in processes]  # Remaining burst times
    complete = 0
    t = 0
    check = False
    short = 0

    while complete != n:
        minm = float('inf')  # ✅ Reset each loop

        # Find process with minimum remaining time at current time
        for j in range(n):
            if processes[j][2] <= t and rt[j] < minm and rt[j] > 0:
                minm = rt[j]
                short = j
                check = True

        if not check:
            t += 1
            continue

        # Reduce remaining time
        rt[short] -= 1

        # If process finishes
        if rt[short] == 0:
            complete += 1
            check = False
            fint = t + 1
            wt[short] = fint - processes[short][1] - processes[short][2]
            if wt[short] < 0:
                wt[short] = 0

        t += 1


# Function to calculate turn around time
def findTurnAroundTime(processes, n, wt, tat):
    for i in range(n):
        tat[i] = processes[i][1] + wt[i]


# Function to calculate average waiting and turn-around times
def findavgTime(processes, n):
    wt = [0] * n
    tat = [0] * n

    findWaitingTime(processes, n, wt)
    findTurnAroundTime(processes, n, wt, tat)

    print("Processes\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time")

    total_wt = 0
    total_tat = 0
    for i in range(n):
        total_wt += wt[i]
        total_tat += tat[i]
        print(f"{processes[i][0]}\t\t{processes[i][1]}\t\t{processes[i][2]}\t\t{wt[i]}\t\t{tat[i]}")

    print(f"\nAverage waiting time = {total_wt / n:.2f}")
    print(f"Average turn around time = {total_tat / n:.2f}")


# Driver code
if __name__ == "__main__":
    print("Running SRTF Scheduler...\n")  

    # Format: [Process ID, Burst Time, Arrival Time]
    processes = [
        [11, 6, 1],
        [21, 8, 1],
        [31, 7, 2],
        [41, 3, 3]
    ]
    n = len(processes)
    findavgTime(processes, n)
