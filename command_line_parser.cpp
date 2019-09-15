#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fstream>
#include<sstream>
using namespace std;


int count_word(string str){ //count number of words in a string
    istringstream iss(str);
    int count=0;
    while(!iss.eof()){
        string word;
        iss>>word;
        count++;
    }
    return count;
}

void  split_command(string &command, string &directory){ //split the command into first word and the second word
  istringstream iss(command);
    int count=0;
    while(!iss.eof()){
        string word;
        iss>>word;
        count++;
        if(count ==1){
            command=word;
        }
        else if(count ==2){
            directory=word;
        }
    }
}

string trim(const string& str) //trims any trailing and after space
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}


 void parseCommand(string actual_command, char * str[]){ //parsing the command for the executable command,have to convert the string into a char array of pointer
	 istringstream iss(actual_command);
         int count=0;
         while(!iss.eof()){
                  string word;
                  iss>>word;
                  char * temp=new char[word.size()];
                  strcpy(temp, word.c_str());
                  str[count]=temp;
                  count++;
          }
          str[count]=NULL;
 }


 void runCommands(string actual_command,bool batch){
	int const MAX_LENGTH=512;
	string HOME=getenv("HOME");
	char error_message[30] = "An error has occurred\n";
	char buf[256];
	long size = pathconf(".", _PC_PATH_MAX);
	if(actual_command.size()>MAX_LENGTH){
		write(STDERR_FILENO, error_message, strlen(error_message));
		return;
	}
	string command,directory;//actual command is the command put in by the user, I split them into first word and the rest into command.directory
	actual_command=trim(actual_command); //trim any trailing after spaces
	command=actual_command;
	split_command(command,directory);//spilting the actual_command into two part, first word and the rest.
	if(command.size() == 0){
		return;
	}
	else if(command =="cd"){
		if(count_word(actual_command)>1){ //if this is true means there is directoy to visit.
			if(chdir(directory.c_str())== -1)  {//if the path specified can't be reached,, this function returns -1
                                write(STDERR_FILENO, error_message, strlen(error_message));
                        }
                    }
		else{
			chdir(HOME.c_str());//the commnand was only "cd"
		}
	}
	else if(command == "pwd"){ //for pwd,, we just call the getcwd() with the buffer
		cout<<getcwd(buf, size_t(size))<<endl;
	}
	else if(command == "exit"){ //exiting command
		exit(0);	
	}
	else {	 //if it is none of the build-in-command,,we will treat it as a executable command
		int child_stat;
		char ** executable_command = new char * [count_word(actual_command)+1]; //for the execvp() function,,parse the typed in command into this format
		parseCommand(actual_command, executable_command);
		pid_t child_pid;
		child_pid=fork();
		if(child_pid == 0) { //child process
			execvp(executable_command[0], executable_command);
			//if it returns means it has failed.
			write(STDERR_FILENO, error_message, strlen(error_message));
			exit(0);//if there is an error, have to exit out of the child process and return to parent process
		}
		else {	
			pid_t id;
			do{
	       			id = wait(&child_stat);
			}while(id != child_pid); //keep waiting until the child process is done
		}
	}	
}
int main(int argc, char *argv[]){
	string actual_command;
	bool batch;
	char error_message[30] = "An error has occurred\n";
	if(argc ==1){ //prompt shell mode
		batch = false;
		while(true){
		cout<<"mysh> ";
		getline(cin,actual_command);
		runCommands(actual_command,batch);
		}
	}
	else if(argc == 2){ //batch mode
		batch =true;
		string filename = argv[1];
		ifstream file_object;
		file_object.open(filename);
		if(!file_object.is_open()){
			write(STDERR_FILENO, error_message, strlen(error_message));
		}
		while(getline(file_object,actual_command)){
			string cmdline = actual_command+"\n";
			write(STDOUT_FILENO, cmdline.c_str(), cmdline.size());	
			runCommands(actual_command,batch);
		}
		file_object.close();
	}
	else {
		write(STDERR_FILENO, error_message, strlen(error_message));

	}	
}
