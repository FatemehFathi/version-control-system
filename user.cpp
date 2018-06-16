#include "user.h"


User::User(string r, string u, string p) {
	if (r == "admin")
		role = r;

	else if (r == "user")
		role = r;

	else
		throw InvalidRoleInputException();

	username = u;
	password = p;
}


