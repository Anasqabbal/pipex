# Pipex

![Score](https://img.shields.io/badge/score-100%2F100-success)
![C](https://img.shields.io/badge/language-C-blue)
![UNIX](https://img.shields.io/badge/concept-UNIX%20Pipes-success)

## 📌 Overview
**Pipex** is a project from 1337 (42 Network) designed to replicate the behavior of the UNIX shell pipe `|` operator. It takes an input file, passes it through two shell commands, and writes the output to a destination file.

For a Software Engineer, understanding how the underlying OS handles process creation, file descriptors, and data streams is vital. This project solidified my understanding of the UNIX environment and multiprocess architecture.

## 💡 Core Concepts Explored
### Inter-Process Communication & Pipes
**Definition:** Pipes are a method of Inter-Process Communication (IPC) in UNIX that connects the standard output of one process to the standard input of another process.
**Problem Solved:** It solves the problem of passing data between independent programs, allowing small, single-purpose utilities to be chained together into complex processing pipelines.

## 🚀 Features
- Mimics the shell command: `< infile cmd1 | cmd2 > outfile`.
- Uses `pipe()`, `fork()`, `dup2()`, and `execve()`.
- Proper error handling (e.g., command not found, permission denied).
- Ensures no memory leaks or zombie processes are left behind.
- **Bonus:** Support for multiple pipes (`cmd1 | cmd2 | cmd3 ...`) and `<< here_doc`.

## 📥 How to Clone
To clone this project, use the following command:
```bash
git clone git@github.com:Anasqabbal/pipex.git
cd pipex
```

## 🛠️ Usage
Compile the project:
```bash
make
```
Run the generated `pipex` executable:
```bash
./pipex infile "ls -l" "wc -l" outfile
```
This is exactly equivalent to running `ls -l < infile | wc -l > outfile` in bash.

## 🧠 What I Learned
- Process creation and management using `fork()` and `waitpid()`.
- Inter-process communication via `pipe()`.
- Redirecting standard I/O using `dup2()`.
- Environment variable parsing (`$PATH`) to locate executable binaries.

## 🌐 Connect with me
[![GitHub](https://img.shields.io/badge/GitHub-black?logo=github)](https://github.com/Anasqabbal)
[![LinkedIn](https://img.shields.io/badge/-IN-0A66C2?logo=linkedin&logoColor=0a66c2)](https://www.linkedin.com/in/anasqabbal/)

