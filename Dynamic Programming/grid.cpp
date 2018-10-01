/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   : Sarah Cheung
	Email  : cheungsa@usc.edu
	USC ID : 9412097012
*/
#include <iostream>
#include <vector>
#include <string>
#include <climits>
//	Feel free to include any other C++ standard library if necessary.

using namespace std;
//	You can add any custom classes / helper functions here.

struct Tile {
	void setTile(int d, int p, int pd, int v) {
		isD 	= d;
		isP		= p;
		isPD 	= pd;
		val 	= v;
	}
	int isD, isP, isPD, val;
};


/*
	Based off the hint in Piazza, OPT(d, p, pd, val) returns the minimum
	amount of life Brian needs in order to complete his task. It accepts
	ints for cases where Brian is under the influence of only D, only P,
	both P and D, or neither P and D (he either gains or loses health in
	this case).
*/
int solve(int N, vector<vector<string> > G) {
/*
	Please complete this function.
	N: Number of rows / columns of the grid.
	G: A 2d vector (N*N) indicating the grid.
		G[0][0] is the top left corner
		G[N-1][N-1] is the bottom right corner
	Return: the minimum life Brain needs to complete his task.
*/
	// Declare 2D array with +1 padding for edge cases
	Tile arr[N+1][N+1];

	// Initialize values with INT_MAX
	for (int i = 0; i <= N; ++i) {
		for (int j = 0; j <= N; ++ j) {
			// Initialize with INT_MAX
			arr[i][j].setTile(INT_MAX, INT_MAX, INT_MAX, INT_MAX);
		}
	}

	// Ensure Brian is alive with at least 1 HP at the end
	arr[N-1][N].setTile(1,1,1,1);
	arr[N][N-1].setTile(1,1,1,1);

	// Set indices with min possible values, starting from the end
	for (int i = N-1; i >= 0; --i) {
		for (int j = N-1; j >= 0; --j) {
			Tile down = arr[i][j+1];
			Tile right = arr[i+1][j];
			if (G[i][j] == "D") {
				arr[i][j].setTile(
					min(down.isD, right.isD),
					min(down.isPD, right.isPD),
					min(down.isPD, right.isPD),
					min(down.isD, right.isD)
				);
			}
			else if (G[i][j] == "P") {
				arr[i][j].setTile(
					min(down.isPD, right.isPD),
					min(down.isP, right.isP),
					min(down.isPD, right.isPD),
					min(down.isP, right.isP)
				);
			}
			else {
				int healthChange = stoi(G[i][j]);

				// Assign the max possible health for Brian to have
				arr[i][j].val = max(min(down.val, right.val) - healthChange, 1);
				if (healthChange >= 0) {
					// Brian is healed
					arr[i][j].setTile(
						max(min(down.isP, right.isP) - healthChange, 1),
						max(min(down.val, right.val) - (healthChange * 2), 1),
						max(min(down.isP, right.isP) - (healthChange * 2), 1),
						arr[i][j].val
					);
				}
				else {
					// Brian is damaged by a guard
					arr[i][j].setTile(
						max(min(down.isD, right.isD) - healthChange, 1),
						max(min(down.val, right.val), 1),
						max(min(down.isD, right.isD), 1),
						arr[i][j].val
					);
				}
			}
		}
	}


	// Return optimal value, located in the starting tile
	return arr[0][0].val;

}

//	The main function reads the input and outputs your answer.
//	Please do not modify it. (Assume the input is well-formed;
//	You don't need to do any error-check)
int main(int argc, char **argv) {
	int N;
	vector<vector<string> > G;
	cin >> N;
	G.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			string tmp;
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
	cout << solve(N, G) << endl;
	return 0;
}