 //Iterative, bottom-up, dynamic programming version
 // ALlen Roush, CIS 315 

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <limits.h>
#include <stdio.h>

using namespace std;

#define MAX_INT INT_MAX
 
// A utility function to print the solution (would normally put function declaration in a header) 
int printSolution(int p[], int n, string wordArray[]);



void printNeatly(int l[], int M, int n, string wordArray[])
{

    int extraSpaces[n+1][n+1]; //stores # of extra spaces for words i to j 
    int lineCost[n+1][n+1]; // penalty cost for a single line 
    int cost[n+1]; // total cost of optimal solution 
    int p[n+1]; // used for printing the solution 
    
    int i, j;

    for (i = 1; i <= n; i++)
    {
        extraSpaces[i][i] = M - l[i-1];
        
        for (j = i+1; j <= n; j++)
        {
            extraSpaces[i][j] = extraSpaces[i][j-1] - l[j-1] - 1;
        }
    }
 
    
      //Calculate line cost corresponding to the calculated extra spaces for words i to j

    for (i = 1; i <= n; i++) 
    {
        for (j = i; j <= n; j++) 
        {
            if (extraSpaces[i][j] < 0)
            {
                lineCost[i][j] = MAX_INT;
            }
            else if (j == n && extraSpaces[i][j] >= 0)
            {
                lineCost[i][j] = 0;
            }
            else
            {
                lineCost[i][j] = extraSpaces[i][j]*extraSpaces[i][j]*extraSpaces[i][j];
            }
        }
    }
 
     
     // Calculate minimum cost (penalty) 

    cost[0] = 0;
    for (j = 1; j <= n; ++j) 
    {
        cost[j] = MAX_INT; // initialize cost to infinity
        for (i = 1; i <= j; ++i)
        {
            if (cost[i-1] != MAX_INT && lineCost[i][j] != MAX_INT && (cost[i-1] + lineCost[i][j] < cost[j]))
            {
                cost[j] = cost[i-1] + lineCost[i][j];
                p[j] = i;
            }
        }
    }
    
    cout << "penalty: " << cost[n] << endl;    // print the penalty ( to stdout) 
    
    // print the lines
    printSolution(p, n, wordArray);
}


/* 
 * prints the solution from the answer calculated in printNeatly
 */
int printSolution(int p[], int n, string wordArray[])
{
    int k;
    
    if (p[n] == 1)
    {
        k = 1;
    }
    else
    {
        k = printSolution(p, p[n]-1, wordArray) + 1; // recursively call the printSolution function 
    }
    
    int w; // keep track of which words in the paragraph we are on    
    for(w = p[n] - 1; w < n; ++w)
    {
        cout << wordArray[w] << ' ';
    }
    cout << '\n';
    return k;
}


int main() // does the std input and invokes the other methods 
{

    string lineString; 
    queue<string> inputQueue; // Queue of strings for the entirety of all the lines of input
    
    // get the input
    while (getline(cin, lineString)) 
    {
        inputQueue.push(lineString); 
    }
    
    istringstream is(inputQueue.front()); 
    int P; 
    is >> P; 
    inputQueue.pop(); // pop off that value from the input queue since we are done with it.
    
    int i;
    for (i = 0; i < P; ++i)
    {
        istringstream streamString(inputQueue.front()); // stream from the front of the queue storing the lines of input
        int M; // the maximun number of characters per line M
        streamString >> M; 
        inputQueue.pop();

        string words; 
        words = inputQueue.front(); 
        inputQueue.pop();

        
        // process the words in the words string and look for spaces
        int j;
        int spaceCounter = 0;
        for (j = 0; j < words.length(); ++j)
        {
            if (isspace(words.at(j)))
            {
                ++spaceCounter;
                while (isspace(words.at(++j)))
                {
                    if (words.at(j) == '\0')
                    {
                        --spaceCounter; // don't count this as a space since ispace will do so without this code 
                    }
                }
            }
        }
        
        int word_count = spaceCounter + 1;
        
        int l[word_count]; 
        
        // count the word lengths in the string words
        istringstream ss(words);
        string s;
        int wordNumber = 0; // keep track of which words in the paragraph we are on
        while(ss >> s) 
        {
            l[wordNumber] = s.length();
            ++wordNumber;
        }
        
        // Now store the words in an array of strings using istringstream
        istringstream strstream(words);
        string str;
        string wordArray[words.length()];
        
        wordNumber = 0; // set back to zero to reset the word count of which word we are on
        
        while(strstream >> str)
        {
            wordArray[wordNumber] = str;
            ++wordNumber;
        }
        
        int n = word_count;
        
        printNeatly(l, M, n, wordArray);
        
        cout << " " << endl;
        
    } 
    
    return 0;
}



