#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

struct Task
{
    int id;
    std::string description;
    bool done;

    std::string toString() const
    {
        return std::to_string(id) + "|" + (done ? "1" : "0") + "|" + description;
    }

    static Task fromString(const std::string &line)
    {
        std::stringstream ss(line);
        std::string token;
        Task task;

        std::getline(ss, token, '|');
        task.id = std::stoi(token);

        std::getline(ss, token, '|');
        task.done = (token == "1");

        std::getline(ss, task.description);

        return task;
    }
};

class TodoList
{
    std::vector<Task> tasks;
    int nextId = 1;
    const std::string filename = "todo.txt";

public:
    TodoList()
    {
        load();
    }

    ~TodoList()
    {
        save();
    }

    void addTask(const std::string &desc)
    {
        tasks.push_back({nextId++, desc, false});
    }

    void removeTask(int id)
    {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                                   [id](const Task &t)
                                   { return t.id == id; }),
                    tasks.end());
    }

    void toggleDone(int id)
    {
        for (auto &t : tasks)
        {
            if (t.id == id)
                t.done = !t.done;
        }
    }

    void showTasks() const
    {
        if (tasks.empty())
        {
            std::cout << "No tasks.\n";
            return;
        }

        for (const auto &t : tasks)
        {
            std::cout << "[" << (t.done ? "x" : " ") << "] "
                      << t.id << ": " << t.description << "\n";
        }
    }

    void save() const
    {
        std::ofstream out(filename);
        for (const auto &t : tasks)
        {
            out << t.toString() << "\n";
        }
    }

    void load()
    {
        std::ifstream in(filename);
        std::string line;
        while (std::getline(in, line))
        {
            Task t = Task::fromString(line);
            tasks.push_back(t);

            nextId = std::max(nextId, t.id + 1);
        }
    }
};

int main()
{
    TodoList todo;
    std::string command;

    std::cout << "Welcome to CLI Todo\n";

    while (true)
    {
        std::cout << "\nCommands: add, remove, done, list, exit\n> ";
        std::cin >> command;

        if (command == "add")
        {
            std::cin.ignore();
            std::cout << "Enter task description: ";
            std::string desc;
            std::getline(std::cin, desc);
            todo.addTask(desc);
        }
        else if (command == "remove")
        {
            int id;
            std::cout << "Enter task ID to remove: ";
            std::cin >> id;
            todo.removeTask(id);
        }
        else if (command == "done")
        {
            int id;
            std::cout << "Enter task ID to toggle done: ";
            std::cin >> id;
            todo.toggleDone(id);
        }
        else if (command == "list")
        {
            todo.showTasks();
        }
        else if (command == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Unknown command.\n";
        }
    }

    return 0;
}
