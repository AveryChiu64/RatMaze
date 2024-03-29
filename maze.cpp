#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <queue>

using namespace std;

bool check(string move,int startX,int startY, char maze[8][12]){
	int afterX=startX,afterY=startY;
	for(int i=0;i<move.length();i++){
		if(move[i]=='U')
		afterY--;
		else if(move[i]=='D')
		afterY++;
		else if(move[i]=='L')
		afterX--;
		else
		afterX++;
	}
	//make sure it is in the bounds of the maze 
	return afterX >= 0 && afterX < 12 && afterY >= 0 && afterY < 8 &&
	maze[afterY][afterX]!='B' && maze[afterY][afterX]!='#';
}
bool foundEnd(string move,int startX,int startY, char maze[8][12],char end){
	int afterX=startX,afterY=startY;
	for(int i=0;i<move.length();i++){
		if(move[i]=='U')
		afterY--;
		else if(move[i]=='D')
		afterY++;
		else if(move[i]=='L')
		afterX--;
		else
		afterX++;
	}
	return maze[afterY][afterX]==end;
}//check if we have reached the end of the maze

void printEnd(string move,int startX,int startY, char maze[8][12],char end){
	int afterX=startX,afterY=startY;
	for(int i=0;i<move.length();i++){
		if(move[i]=='U')
		afterY--;
		else if(move[i]=='D')
		afterY++;
		else if(move[i]=='L')
		afterX--;
		else
		afterX++;
		
		maze[afterY][afterX]='#';//where P represents the pathway to exit
	}
	
	for(int i=0;i<8;i++){
		for(int j=0;j<12;j++) {
			cout << maze[i][j] <<" ";
		}
		cout << endl;
	}
	
}//end of printEnd function

bool searchUntilEnd(int counter, queue<string> &paths, int startX, 
int startY, char maze[8][12],char end) {
	//counts the number of checks and stops one it is past 300
	counter++;
	//finds the previous string of pathways eg LLLL
	string moveCheck="";
	moveCheck=paths.front();
	paths.pop();
	//possible pathways
	//u is up
	//d is down
	//l is left
	//r is right 
	char dir[4]= {'U','D','L','R'};
	//goes through each direction in the loop and puts it into queue
	for(int checks=0;checks<4;checks++){
		//checks what the next move would look like
		//as a string (eg LL) 
		string move=moveCheck+dir[checks];
		//checks if it is valid before pushing it into the queue
		if(check(move,startX,startY, maze))
		paths.push(move);
		//returns the pathway if the end is found 
		if(foundEnd(move,startX,startY, maze, end)) {
			printEnd(move,startX,startY,maze,end);
		//NOW SET THE SHORTEST PATH HERE BY CALLING THE OTHER CLASS 
		//TO STORE THE SHORTEST PATH
		//OUTPUT THIS PATH
		return true;
	}
		if(counter>500)
		return false;
		
		}
		return	searchUntilEnd(counter, paths, startX, startY, maze, end);
		//will return false if nothing can be found
		
	}

int main() {
	
	//Variables
	char maze[8][12];
	int xStart=0, yStart=0, countSteps=0, xCheese=0,yCheese=0,counter=0;
	bool foundCheese=0, foundExit=0;
	
	//greets the user
	cout <<"Welcome to the maze program" << endl;
	cout <<"Please enter a file" << endl;
	cout <<"The program will reveal the shortest path" << endl;
	cout <<"the rat can take to get to the cheese and exit" << endl;
	cout <<"(if possible), the path will be represented by # symbols" << endl;
	//take in file
	ifstream fin("maze.txt");
	//check file open
	if(!fin) 
		return -1;
	//take in a 2D array maze and print it 
	for(int i=0;i<8;i++){
		for(int j=0;j<12;j++) {
			fin >> maze[i][j];
			cout << maze[i][j] <<" ";
			if(maze[i][j]=='R') { //find starting x and y coords
			xStart=j;
			yStart=i;
		}
			if(maze[i][j]=='C') {
				xCheese=j;
				yCheese=i;
			}
		}
		cout << endl;
}
cout <<"Here is the maze you entered" << endl;
cout<< "The rat is R" << endl;
cout<< "The cheese is S" << endl;
cout << "The exit is X" << endl;
cout << endl;
queue<string> paths;
paths.push("");
	if(searchUntilEnd(counter,paths, xStart, yStart, maze, 'C')) {
	cout <<"Path found for cheese" << endl << endl << endl;
	//reset everything to find cheese
	counter=0;
	queue<string> paths2;
	paths2.push("");
	if(searchUntilEnd(counter,paths2, xCheese, yCheese, maze, 'X')) 
	cout <<"Shortest path found from start to cheese to exit" << endl;

}
	else if(searchUntilEnd(counter,paths, xStart, yStart, maze, 'X')) {
	cout <<"Shortest path found from start to exit, but not cheese" << endl;
}
	else
	cout <<"There is no path to the path or cheese" << endl;
	
	system("PAUSE");
	return 0;
}//end of main
