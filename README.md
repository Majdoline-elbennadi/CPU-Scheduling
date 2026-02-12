# 🖥 CPU Scheduling

CPU scheduling is a critical function of operating systems that determines **which process will run on the CPU** when multiple processes are ready.  
The main goal is to **maximize CPU utilization, throughput, and responsiveness** while managing processes efficiently.

---

## 🎯 Objectives

- Understand different CPU scheduling algorithms  
- Learn the difference between preemptive and non-preemptive scheduling  
- Analyze process execution order and performance metrics  
- Apply CPU scheduling concepts to operating system design  

---

## ⚙️ System Overview

Processes in an operating system can have the following states:

- **New** → process is created  
- **Ready** → waiting for CPU  
- **Running** → currently executing  
- **Waiting/Blocked** → waiting for I/O or an event  
- **Terminated** → finished execution  

The CPU scheduler selects which **ready process** will run next.

---

## 🚀 Types of CPU Scheduling

### **1️⃣ Non-Preemptive Scheduling**
- A process **cannot be interrupted** once it starts running.  
- Common algorithms:
  - **FCFS (First Come First Serve)** → run in arrival order  
  - **SJF (Shortest Job First) Non-Preemptive** → shortest burst time first  
  - **Priority Scheduling Non-Preemptive** → highest priority first  

**Behavior:**  
If a new process arrives while one is running → it **waits** until CPU is free.

---

### **2️⃣ Preemptive Scheduling**
- A running process **can be interrupted** if a higher priority or shorter job arrives.  
- Common algorithms:
  - **SRTF (Shortest Remaining Time First)** → preemptive version of SJF  
  - **Priority Scheduling Preemptive** → higher priority preempts  
  - **Round Robin (RR)** → each process gets a fixed time quantum; CPU rotates  

**Behavior:**  
If a new process has higher priority or shorter remaining time → **current process is preempted**.

---

## 🧩 Key CPU Scheduling Algorithms

| Algorithm | Type | How it Works | Pros | Cons |
|-----------|------|--------------|------|------|
| FCFS | Non-preemptive | Queue order | Simple, fair | Poor for long jobs (convoy effect) |
| SJF | Non-preemptive | Shortest burst first | Optimal avg. waiting time | Hard to predict burst time |
| SRTF | Preemptive | Shortest remaining time | Optimal avg. waiting time | Starvation possible |
| Priority | Non/Preemptive | Highest priority first | Important jobs fast | Low priority may starve |
| Round Robin | Preemptive | Fixed time quantum | Fair, responsive | Context switching overhead |

---

## ⚖️ Non-Preemptive vs Preemptive

| Feature | Non-Preemptive | Preemptive |
|---------|----------------|------------|
| Interrupt running process | ❌ No | ✅ Yes |
| Response time | Can be poor | Can be better |
| Starvation risk | Less | Possible |
| Examples | FCFS, SJF, Priority NP | SRTF, Priority P, RR |

---

## ▶ Example Scenario

Processes:

| Process | Arrival Time | Burst Time |
|---------|-------------|-----------|
| P1      | 0           | 6         |
| P2      | 1           | 8         |
| P3      | 2           | 7         |
| P4      | 3           | 3         |

- **FCFS Order:** P1 → P2 → P3 → P4  
- **SJF Non-preemptive:** P1 → P4 → P3 → P2  
- **SRTF:** P1 → P4 → P3 → P2 (can preempt depending on remaining time)  

---

## 📈 Learning Outcomes

- Understand process scheduling in operating systems  
- Differentiate between preemptive and non-preemptive scheduling  
- Analyze and calculate waiting time, turnaround time, and CPU utilization  
- Apply CPU scheduling concepts to real-world systems  

---

## 👩‍💻 Author

**Majdoline**  
Computer Engineering Student
