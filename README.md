# PCCST403-exp-list
this repo contains a well organized list of Experiments and both it's soruce code and algorithm for the course PCCST403 (Operating Systems - S4 ktu 2024 scheme) 


---
---


## List of Experiments 

### Experiment 1: Linux Command Familiarization
Problem: Familiarization with basic Linux programming, process tracking, binary inspection, and debugging commands: ps, strace, gdb, strings, objdump, nm, file, od, xxd, time, fuser, top.

### Experiment 2: Machine Info Gathering via /proc
Problem: Use the /proc file system to gather machine specifications: (a) Number of CPU cores, (b) Total memory and fraction of free memory, (c) Number of processes currently running, (d) Number of processes in running/blocked states, (e) Number of processes forked since last bootup, (f) Number of context switches performed since last bootup for a specific process.

### Experiment 3: Process Execution Time Analysis via /proc
Problem: Write a simple program to print the system time. Use the /proc file system internally or via status maps to determine how long the process ran in user mode and kernel mode.

### Experiment 4: Process Creation using fork()
Problem: Create a new process using the fork system call. Print both parent and child process IDs. Use the pstree command to display the process tree starting from the init process.

### Experiment 5: Process Image Replacement via execvp()
Problem: Write an independent program "myadder" to add two command-line integers. Write a second program that forks a child process and replaces its image with "myadder" using the execvp system call.

### Experiment 6: Process Synchronization using wait()
Problem: Create a child process using fork(). The child must print "PCCSL407 " and the parent must print "Operating Systems Lab\n". Use the wait() system call to enforce strict execution ordering so the complete terminal output reads "PCCSL407 Operating Systems Lab".

### Experiment 7: Inter-Process Communication (IPC) Mechanisms
Problem: Implement three different IPC methods:
  (a) Pipe: A two-process pipeline evaluating mathematical expressions where results are passed sequentially via a pipe.
  (b) Message Queue: Process 1 sends a string to Process 2. Process 2 reverses it and returns it. Process 1 checks and prints if the string is a palindrome.
  (c) Shared Memory: Process 1 writes three strings to shared memory. Process 2 reads, concatenates them with spaces, and passes the result back. Process 1 prints the final text with flipped casing.

### Experiment 8: Multithreaded Statistical Calculator
Problem: Write a multithreaded application using POSIX threads. The parent thread reads an array of integers from the command line and creates three separate worker threads to concurrently calculate the global mean, median, and standard deviation before printing them.

### Experiment 9: CPU Scheduling Algorithms Simulation
Problem: Input a list of processes with arrival times, burst times, and priorities. Simulate and compare FCFS, SRTF, Non-Preemptive Priority, and Round Robin (Quantum = 3) scheduling algorithms to evaluate which one minimizes average waiting time.

### Experiment 10: Readers-Writers Problem with Writer Priority
Problem: Implement a thread-safe solution to the classic Readers-Writers synchronization problem using semaphores, giving explicit execution priority to waiting writers.

### Experiment 11: Banker's Algorithm Safe State Simulation
Problem: Simulate the Banker's Algorithm for deadlock avoidance. Given resource allocation, maximum requirements, and available vectors, evaluate if a process mix is safe and generate its execution sequence.

### Experiment 12: Resource Allocation Graph Deadlock Detection
Problem: Input a process resource mix consisting of Allocation, Maximum Request matrices, and Available resource vectors to programmatically evaluate if the current system state is deadlocked.

### Experiment 13: Deadlock-Free Dining Philosophers Solution
Problem: Implement a robust, deadlock-free solution for the Dining Philosophers synchronization challenge using POSIX semaphores and mutex constraints.

### Experiment 14: Paging Address Translation Simulation
Problem: Simulate structural memory translation in a single-level paging scheme. Receive virtual address space size, page size, and a target virtual address to compute and output the physical mapping in a `<frame_number, offset>` format.

### Experiment 15: Page-Replacement Algorithms Simulation
Problem: Generate a random page-reference sequence of page IDs 0-9. Simulate and track total page faults across FIFO, LRU, and Optimal page-replacement policies under varying frame allocations (1 to 7).

### Experiment 16: Disk Scheduling Algorithms Simulation
Problem: Service a disk track workspace spanning 5,000 cylinders (0-4,999). Read an initial disk head index and handle 10 random access requests using SSTF, LOOK, and C-SCAN algorithms to print their final seek performance metrics.


---

[[AISLOPREADME.md|Here's]] the aiSLop readme - just in case 


---


good luck :)
:wq