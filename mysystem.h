#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include "exceptions.h"
#include "user.h"

using namespace std;

class Project;

class System {
public:
	void file_to_vect();
	void vect_to_file();

	void login(string username, string password);
	void logout();

	bool prevent_reiterative_user(string username);
	bool check_login_info(string username, string password);
	bool is_file (string file_folder); 
	
	void register_user(string role, string username, string password);
	void add_proj(string proj_name, string proj_address);

	void show(string proj_name, string para);
	void show_folder(string proj_name, string folder_name);
	void show_file(string proj_name, string file_name);

	//void commit(string proj_name, string file_folder, string file_addr);

	static System* get_instance() {
	if (n == 0)
		instance = new System();

	return instance;
}

	bool get_is_login() { return is_login; }
	User* get_login() { return login_user; }
	vector<User> get_users() { return users; }
	vector<Project> get_projects() { return projects; }
private:
	System() { n++; }

	static int n;
	static System* instance;

	bool is_login;
	User* login_user;
	vector<User> users;
	vector<Project> projects;
};





class Project {
public:
	Project(string n, User a) : proj_name(n), proj_admin(a) { }

	void hire(System* client, string programmer);
	void fire(System* client, string programmer);

	void set_proj_address(string proj_add) { proj_address = proj_add; }
	void set_last_version(string version) { last_version = version; }

	string get_proj_name() { return proj_name; }
	string get_proj_address() { return proj_address; }
	User get_proj_admin() { return proj_admin;}
	vector<User> get_proj_programmers() { return proj_programmers; }
	string get_last_version() { return last_version; }
private:
	string proj_name;
	string proj_address;

	User proj_admin;
	vector<User> proj_programmers;
	string last_version;
};


#endif


