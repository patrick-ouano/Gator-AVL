#include <iostream>
#include "AVL.h"
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main(){
	AVLTree tree;
	int numCommands;
	cin >> numCommands;
	string line;
	getline(cin, line);

	for (int i = 0; i < numCommands; i++) {
		// read one line of input from cin
		getline(cin, line);

		// creates an input stream from that line
		istringstream in(line);

		// reads the first word from input stream
		string command;
		in >> command;

		if (command == "insert") {
			// reads up to quotation mark
			string next;
			getline(in, next, '"');

			// reads name
			string name;
			getline(in, name, '"');

			// reads ufid by skipping the white space and the quote
			string ufid;
			getline(in, ufid, '"');

			tree.insert(name, ufid);
		}
		else if (command == "remove") {
			string ufid;
			in >> ufid;
			tree.remove(ufid);
		}
		else if (command == "removeInOrderN") {
			int n;
			in >> n;
			tree.removeInOrderN(n);
		}
		else if (command == "search") {
			// reads up to quotation mark
			string next;
			getline(in, next, '"');

			if (in.peek() == '"') {
				string name;
				in.get();
				getline(in, name, '"');
				tree.searchName(name);
			}
			else {
				string ufid;
				in >> ufid;
				tree.searchID(ufid);
			}

		}
		else if (command == "printInOrder") {
			tree.printInOrder();
		}
		else if (command == "printPreOrder") {
			tree.printPreOrder();
		}
		else if (command == "printPostOrder") {
			tree.printPostOrder();
		}
		else if (command == "printLevelCount") {
			tree.printLevelCount();
		}
		else {
			cout << "unsuccessful" << endl;
		}
	}

	return 0;
}
