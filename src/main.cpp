#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <filesystem>

int main()
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true)
  {
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);

    if (input == "exit")
    {
      break;
    }
    else if (input.substr(0, 4) == "echo")
    {
      std::string str = input.substr(5);
      std::vector<std::string> args;
      std::string curr="";

      bool in_squote = false;

      for (char c: str) {
        if (c=='\'') {
          in_squote = !in_squote;
        }
        else if (c==' ' && !in_squote) {
          if (!curr.empty()) {
            args.push_back(curr);
            curr="";
          }
        }
        else curr+=c;
      }

      if (!curr.empty()) args.push_back(curr);

      for (int i=0; i<args.size(); i++) {
        if (i>0) std::cout<<" ";
        std::cout<<args[i];
      }
      std::cout<<std::endl;
    }
    else if (input.substr(0, 4) == "type")
    {
      std::string command = input.substr(5);
      if (command == "echo" || command == "exit" || command == "type" || command == "pwd")
        std::cout << command << " is a shell builtin" << std::endl;
      else
      {
        std::string path = getenv("PATH");

        std::stringstream ss(path);
        std::string path_name;
        bool file_exists = false;

        while (getline(ss, path_name, ':'))
        {
          std::string file_name = path_name + '/' + command;

          if (access(file_name.c_str(), X_OK) != -1)
          {
            std::cout << command << " is " << file_name << std::endl;
            file_exists = true;
            break;
          }
        }
        if (!file_exists)
          std::cout << command << ": not found" << std::endl;
      }
    }

    else if (input == "pwd") {
      std::cout<<std::filesystem::current_path().string()<<std::endl;
    }
    else if (input.substr(0,2) == "cd") {
      std::string dir_path = input.substr(3);

      if (dir_path=="~") {
        std::string home_dir = getenv("HOME");
        chdir(home_dir.c_str());
      }

      else if (chdir(dir_path.c_str())!=0) {
        std::cout<<"cd: "<<dir_path<<": No such file or directory"<<std::endl;
      }
    }
    else
    {

      std::stringstream ss(input);
      std::string exec_command;
      getline(ss, exec_command, ' ');

      std::vector<std::string> args;
      std::string arg;

      while (getline(ss, arg, ' '))
      {
        args.push_back(arg);
      }

      std::string path = getenv("PATH");
      std::stringstream ss2(path);
      std::string path_name;

      bool has_executed = false;
      while (getline(ss2, path_name, ':'))
      {
        std::string file_name = path_name + '/' + exec_command;

        if (access(file_name.c_str(), X_OK) != -1)
        {
          std::string final_file = exec_command;
          for (std::string arg : args)
          {
            final_file += " ";
            final_file += arg;
            // std::cout<<arg<<std::endl;
          }
          // std::cout<<final_file<<std::endl;
          system(final_file.c_str());
          has_executed = true;
          break;
        }
      }

      if (!has_executed)
        std::cout << input << ": command not found" << std::endl;
    }
  }
}
