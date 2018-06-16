#ifndef __USER_H__
#define __USER_H__

#include <iostream>
#include <string>
#include "exceptions.h"

using namespace std;


class User {
public:
	User(string r, string u, string p);

	string get_username() { return username; }
	string get_password() { return password; }
	string get_role() { return role; }
protected:
	string username;
	string password;
	string role;
};



#endif
