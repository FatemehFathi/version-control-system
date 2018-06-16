#include "exceptions.h"
#include "mysystem.h"
#include "user.h"
class User;

System* System::instance = NULL;
int System::n = 0;


int main() {
	bool exit = false;

	while (!exit) {
		System* client = System::get_instance();
		client->file_to_vect();

		string input;
		cin >> input;

///////////////////////////////////////////
		if (input == "login") {
			if (client->get_is_login() == false) {
				string username;
				string password;
				cin >> username >> password;

				try {
					client->login(username, password);
					cout << "You are Login Now!" << endl;
				}
				catch (WrongPasswordException) { cout << "Wrong Password!" << endl; }
				catch (InvalidUsernameException) { cout << "This Username is Invalid!" << endl; }
			}
			else
				cout << "Invalid Input ! You were already loged in" << endl;
		}

////////////////////////////////////////////
		if (input == "logout") {
			if (client->get_is_login() == true) {
				client->logout();
				cout << "You are Logout Now!" << endl;
			}
			else
				cout << "You must First Login!" << endl;
		}

////////////////////////////////////////////
		if (input == "register") {
			if (client->get_is_login() == true) {
				if (client->get_login()->get_role() == "admin") {
					string role;
					string username;
					string password;
					cin >> role >> username >> password;
			
					try {
						client->register_user(role, username, password);
						cout << "Register Done!" << endl;
					}
					catch (ReiterativeUserException) { cout << "Register Failed! Reiterative User!" << endl; }
					catch (InvalidRoleInputException) { cout << "Invalid Role Input!" << endl; }
				}
				else
					cout << "Unauthorized Access!" << endl;
			}
			else
				cout << "You must First Login!" << endl;
		}
//////////////////////////////////////////
		if (input == "add") {
			if (client->get_is_login() == true) {
				string proj_name;
				string proj_addr;
				
				cin >> proj_name >> proj_addr;

				try {
					client->add_proj(proj_name, proj_addr);
					cout << "Project Created !" << endl;
				}
				catch (ReiterativeProjectNameException) { cout << "This name is existed !" << endl; }
			}
			else
				cout << "You must First Login!" << endl;
		}
/////////////////////////////////////////
		if (input == "hire") {
			if (client->get_is_login() == true) {
				string proj_name;
				string programmer;
				cin >> proj_name >> programmer;
				bool is_exist = false;
				vector<Project> projs = client->get_projects();
				for (int i=0 ; i<projs.size() ; i++)
					if (projs[i].get_proj_name() == proj_name) {
						is_exist = true;
						if (projs[i].get_proj_admin().get_username() == client->get_login()->get_username()) {
							try {
								projs[i].hire(client, programmer);
								cout << "Programmer Hired!" << endl;
							}
							catch (InvalidUsernameHireException) { cout << "Invalid Username!" << endl; }
							catch (ReiterativeProgrammerException) { cout << "Reiterative Programme!" << endl; }
						}
						else
							cout << "Only project admins can hire!" << endl;
					}
				if  (is_exist == false)
					cout << "Invalid Project Name!" << endl;	
			}
			else
				cout << "You must First Login!" << endl;
		}
/////////////////////////////////////////
		if (input == "fire") {
			if (client->get_is_login() == true) {
				string proj_name;
				string programmer;
				cin >> proj_name >> programmer;
				bool is_exist = false;
				vector<Project> projs = client->get_projects();
				for (int i=0 ; i<projs.size() ; i++)
					if (projs[i].get_proj_name() == proj_name) {
						is_exist = true;
						if (projs[i].get_proj_admin().get_username() == client->get_login()->get_username()) {
							try {
								projs[i].fire(client, programmer);
								cout << "Programmer Fired!" << endl;
							}
							catch (InvalidUsernameFireException) { cout << "Invalid Username!" << endl; }
							catch (BadFireException) { cout << "The programmer that you want to add to project, is project admin!" << endl; }
						}
						else
							cout << "Only project admins can fire!" << endl;
					}
				if  (is_exist == false)
					cout << "Invalid Project Name!" << endl;	
			}
			else
				cout << "You must First Login!" << endl;
		}
//////////////////////////////////////////
		if (input == "show") {
			if (client->get_is_login() == true) {
				string proj_name;
				string unknown;
				if (unknown == "-v" || unknown == "-a" || unknown == "-d") {
					string par2;
					string par3;

					cin >> par2;
					if (par2 == unknown) {
						cout << "Reiterative parametr!" << endl;
						break;
					}

					if (par2 == "-v" || par2 == "-a" || par2 == "-d") {
						cin >> par3;
						if (par3 == par2 || par3 == unknown) {
							cout << "Reiterative parametr!" << endl;
							break;
						}
						if (par3 == "-v" && par3 == "-a" && par3 == "-d") {
							cout << "Invalid Parametr!" << endl;
							break;
						}	
					}
					client->show(proj_name, unknown);
					client->show(proj_name, par2);
					client->show(proj_name, par3);	
				}
					
				else if (client->is_file(unknown) == true)
					client->show_file(proj_name, unknown);

				else if (client->is_file(unknown) == false)
					client->show_folder(proj_name, unknown);
			}
			else
				cout << "You must First Login!" << endl;
		}

/////////////////////////////////////////
		if (input == "exit") {
			client->vect_to_file();
			exit = true;
		}
	} // while exit

	return 0;
}
