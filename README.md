# CLI Todo App

A simple command-line based Todo list manager written in modern C++17. Tasks are stored persistently in a `todo.txt` file using a lightweight custom format.

## Features

- Add tasks with descriptions
- Mark tasks as done or undone
- Remove tasks by ID
- View the list of tasks
- Auto-saves to file on exit

## Build Instructions

Make sure you have `clang++` or another C++17-compliant compiler installed.

```bash
clang++ -std=c++17 -o todo main.cpp