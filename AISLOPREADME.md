# OS Lab Experiments 🖥️

Welcome to the collection of 16 essential Operating System lab experiments, designed specifically for KTU engineering undergraduates. These programs cover the core concepts of process management, IPC, scheduling, and memory.

## 📂 Project Structure

Each experiment is kept in its own folder for clarity. Inside each folder, you will find:
1.  **Source Code (`.c`)**: A simple, beginner-friendly C program.
2.  **Algorithm (`_algo.txt`)**: A step-by-step plain text breakdown of the logic.

```text
Experiment_Folder/
├── experiment_name.c
└── experiment_name_algo.txt
```

---

## 🚀 The Experiments

1.  **Linux Commands**: Running `file`, `ps`, `top`, etc., from C.
2.  **Proc Info**: Extracting CPU and RAM details from `/proc`.
3.  **Process Time**: Analyzing User vs. Kernel mode time.
4.  **Fork Tree**: Understanding parent-child process creation.
5.  **Exec Adder**: Replacing process images with `execvp`.
6.  **Wait Sync**: Using `wait()` for process synchronization.
7.  **IPC**: Pipes, Message Queues, and Shared Memory.
8.  **Thread Stats**: Multithreaded Mean, Median, and Std Dev.
9.  **CPU Scheduling**: FCFS, Priority, and Round Robin.
10. **Readers-Writers**: Synchronization with Writer Priority.
11. **Banker's Algorithm**: Deadlock avoidance and safety states.
12. **Deadlock Detection**: Finding deadlocked processes in a matrix.
13. **Dining Philosophers**: Classical sync problem (Deadlock-free).
14. **Page Translation**: Logical to Physical address conversion.
15. **Page Replacement**: FIFO and LRU simulation.
16. **Disk Scheduling**: SSTF and C-SCAN head movement.

---

## 🛠️ How to Compile and Run

Make sure you are on a Linux-based system (or WSL) with `gcc` installed.

### Standard Programs
```bash
gcc filename.c
./a.out
```

### Programs with Threads (Exp 8, 10, 13)
Use the `-lpthread` flag:
```bash
gcc experiment.c -lpthread
./a.out
```

### Programs with Math (Exp 8)
Use the `-lm` flag:
```bash
gcc thread_stats.c -lpthread -lm
./a.out
```

---

## 📝 Note
The code is written in a casual, student-friendly style. It prioritizes readability and logic over complex optimizations—perfect for lab exams and viva prep!

Happy Coding! 🚀
