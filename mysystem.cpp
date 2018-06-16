#include "mysystem.h"


void System::file_to_vect() {
	string temp_line;
	string role;
	string username;
	string password;
	fstream users_data;
	users_data.open("./root/users.data");

	users.clear();	
	User new_user("admin", "admin", "s3cret");
	users.push_back(new_user);

	while (users_data >> role >> username >> password) {
		User new_user(role, username, password);
		users.push_back(new_user);
		getline(users_data, temp_line);
	}

	users_data.close();

}


void System::vect_to_file() {
	fstream input_data;
	string sys_arg;
	string file_arg;
	
	for (int i=0 ; i<projects.size() ; i++) {
		file_arg = "./root/" + projects[i].get_proj_name() + ".txt";
		sys_arg = "rm ./root/" + projects[i].get_proj_name() + ".txt";
		system(sys_arg.c_str());
		input_data.open(file_arg.c_str());
		input_data << projects[i].get_proj_address() << endl << projects[i].get_proj_name() << endl << projects[i].get_last_version() << endl << projects[i].get_proj_admin().get_username() << endl;

		vector<User> p = projects[i].get_proj_programmers();
		for (int j = 0 ; j<p.size() ; j++)
			input_data << p[j].get_username() << endl;
	}		
	input_data.close();
}



void System::login(string username, string password) {
	if (username == "admin" && password == "s3cret") {
		login_user = &users[0];
		is_login = true;
	}

	else if (check_login_info(username, password) == true) {
		for (int i=0 ; i<users.size() ; i++)
			if (users[i].get_username() == username)
				login_user = &users[i];
		is_login = true;
	}

	else
		throw WrongPasswordException();
}





void System::logout() {
	is_login = false;
	login_user = NULL ;
}






bool System::prevent_reiterative_user(string username) {
	if (username == "admin")
		return false;

	for (int i=0 ; i<users.size() ; i++) {
		if (users[i].get_username() == username)
			return false;
	}
	return true;
}





bool System::check_login_info(string username, string password) {
	for (int i=0 ; i<users.size() ; i++)
		if (users[i].get_username() == username) {
			if (users[i].get_password() == password)
				return true;
			else
				return false;
		}

	throw InvalidUsernameException();
}
	





void System::add_proj(string proj_name, string proj_address) {
	User* proj_admin = login_user;

	for (int i=0 ; i<projects.size() ; i++)
		if (projects[i].get_proj_name() == proj_name)
			throw ReiterativeProjectNameException();

	Project new_proj(proj_name, *proj_admin);
	projects.push_back(new_proj);

	new_proj.set_proj_address(proj_address);
	new_proj.set_last_version("Version1");

	string file_arg = "mkdir " + proj_name;
	system(file_arg.c_str());
	string file_arg2 = "cp -R " + proj_address + " ./root/" + proj_name;
	system(file_arg2.c_str());

	ofstream proj_file;
	file_arg = "./root/" + proj_name + ".txt";
	proj_file.open(file_arg.c_str());
	proj_file << proj_address << endl << proj_name << endl << "Version1" << endl << login_user->get_username() << endl;
	proj_file.close();

	proj_file.open("./root/projects.data", fstream::in|fstream::out|fstream::app);
	proj_file << proj_name << endl;
	proj_file.close();
}






void System::register_user(string role, string username, string password) {
	ofstream registerInput;

	if (prevent_reiterative_user(username) == true) {
		User new_user(role, username, password);
		users.push_back(new_user);

		registerInput.open("./root/users.data", fstream::in|fstream::out|fstream::app);
		registerInput << role << " " << username << " " << password << endl;
		registerInput.close();
	}

	else
		throw ReiterativeUserException();
}




/*

void System::commit(string proj_name, string file_folder, string file_addr) {
	bool is_exist = false;
	Project* commit_proj;
	string proj_add;
	string sys_arg;
	
	for (int i=0 ; i<projects.size() ; i++) {
		if (projects[i]->get_proj_name() == proj_name) {
			is_exist = true;
			commit_proj = projects[i];
			proj_add = projects[i]->get_proj_address();
		}
	}

	if (is_exist == false)
		throw InvalidProjNameException();



	int is_file_h = file_folder.find(".h");
	int is_file_cpp = file_folder.find(".cpp");
	
	//agar folder bood:
	if (is_file_h == string::npos && is_file_cpp == string::npos) {
		sys_arg = "mkdir " + file_folder;
		system(sys_arg.c_str());

		sys_arg = "cp ./root" + file_addr + " ./root" + proj_add + "/" + file_folder;
		system(sys_arg.c_str());
	}


	//agar file bood:
	if (is_file_h != string::npos || is_file_cpp != string::npos) {
		sys_arg = "cp ./root" + file_addr + " ./root" + file_folder;
	}

}

*/







bool System::is_file (string file_folder) {
	int is_file_h = file_folder.find(".h");
	int is_file_cpp = file_folder.find(".cpp");
	
	if (is_file_h == string::npos && is_file_cpp == string::npos)
		return false;

	else
		return true;
}



void System::show(string proj_name, string para) {
	vector<Project> proj;

	for (int i=0 ; i<projects.size() ; i++)
		if (projects[i].get_proj_name() == proj_name)
			proj.push_back(projects[i]);

	vector<User> programmers = proj[0].get_proj_programmers();
		
	if (para == "-a")
		cout << "Project Admin: " << proj[0].get_proj_admin().get_username() << endl;

	else if (para == "-d") {
		cout << "Project Programmers: " << endl;
		for (int i=0 ; i<programmers.size() ; i++)
			cout << i+1 << " " << programmers[i].get_username() << endl;
	}

	else if (para == "-v")
		cout << "Last Version: " << proj[0].get_last_version() << endl;

	else
		throw InvalidInputException();

}




void System::show_folder(string proj_name, string folder_name) {
	/*DIR* dir = opendir(????????????????);
	if (dir == NULL)
		throw DirectoryException();
	
	dirent *de;
	while (de = readdir(dir))
		cout << de->d_name << endl;*/

	string sys_arg = "cd ./root/" + proj_name + "/" + folder_name;
	system(sys_arg.c_str());
	system("ls -R");
}




void System::show_file(string proj_name, string file_name) {
	
}



/*
////////// ???????????????
void Project::show_file(string file_name) {
	DIR* dir = opendir(????????????????);
	if (dir == NULL)
		throw DirectoryException();

	fstream inFile;
	inFile.open(file_name.c_str());
	int ch = inFile.get();

	while (inFile.good()) {
		cout << (char) ch;
		ch = inFile.get();
	}
	inFile.close();
}


*/







void Project::hire(System* client, string programmer) {
	bool checker = false;
	vector<User> users = client->get_users();

	for (int i=0 ; i<users.size() ; i++) {
		if (users[i].get_username() == programmer) {
			for (int j=0 ; j<proj_programmers.size() ; j++)
				if (proj_programmers[j].get_username() == programmer)
					throw ReiterativeProgrammerException();
			checker = true;
			proj_programmers.push_back(users[i]);

			ofstream hireInput;
			string file_arg = "./root/" + proj_name + ".txt";
			hireInput.open(file_arg.c_str(), fstream::in|fstream::out|fstream::app);
			hireInput << programmer << endl;
			hireInput.close();
		}
	}

	if (checker == false)
		throw InvalidUsernameHireException();
}





void Project::fire(System* client, string programmer) {
	bool checker = false;
	vector<User> users = client->get_users();

	for (int i=0 ; i<users.size() ; i++) {
		if (users[i].get_username() == programmer) {
			checker = true;

			if (users[i].get_username() == proj_admin.get_username())
				throw BadFireException();

			for (int j=0 ; j<proj_programmers.size() ; j++) {
				if (proj_programmers[j].get_username() == programmer)
					proj_programmers.erase(proj_programmers.begin() + j);
			}
		}
	}

	if (checker == false)
		throw InvalidUsernameFireException();
}




