
 //A dynamic programming solution to the printing-neatly problem
    //Recursive, top-down solution 
    // Allen Roush 

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <limits.h>
#include <stdio.h>

#define MAX_INT INT_MAX

using namespace std;

//function declarations cus I didn't want to deal with objects for this assignment 

void printCost(vector<vector<int> > &lineCost, string wordArray[], int j, int M);


/* A function to print the solution lines */
void printSolution(vector<vector<int> > &lineCost, string wordArray[], int j);



 // Recursive function that returns least minimum amount of extra white space required to fit words i to j into width M
int printNeatlyRec(string wordArray[], int i, int j, int M, vector<vector<int> > &extraSpaces, vector<vector<int> > &lineCost, int n);

 



 // Recursive function that returns minimal amount of extra white space required to fit words[i through j] into width M. 
int printNeatlyRec(string wordArray[], int i, int j, int M, vector<vector<int> > &extraSpaces, vector<vector<int> > &lineCost, int n)
{
    int lineLength = 0;
    
    int index;
    for (index = i; index <= j - 1; ++index) 
    {
        string temp;
        temp = wordArray[index];
        lineLength += temp.length();
    }
    lineLength += (-i + j);

    // base case
    if (lineLength <= M || i >= (j - 1))
    {
        if (j == n) // Don't count the last line
        {
            return 0;
        }
        return (M - lineLength)*(M - lineLength)*(M - lineLength);
    }
    
    
    // Find the optimal line break position using recursion and memoization
    int best = MAX_INT;

    int bestIndex = 0;
    
    int k, error;
    
    for (k = i + 1; k <= j - 1; ++k) 
    {
        if (extraSpaces[i][k] > 0)
        {
            error = extraSpaces[i][k];
        }
        else
        {
            error = printNeatlyRec(wordArray, i, k, M, extraSpaces, lineCost, n);
        }
        
        
        if (extraSpaces[k][j] > 0)
        {
            error += extraSpaces[k][j];
        }
        else 
        {
            int tempError;
            tempError = printNeatlyRec(wordArray, k, j, M, extraSpaces, lineCost, n);
            error += tempError;
        }
    
        
        if (error < best)
        {
            best = error;
            bestIndex = k;
        }
    }
    
    int totalError = printNeatlyRec(wordArray, i, bestIndex, M, extraSpaces, lineCost, n) + printNeatlyRec(wordArray, bestIndex, j, M, extraSpaces, lineCost, n);
    
    // Memoize
    extraSpaces[i][j] = totalError;
    
    // Store solution
    lineCost[i][j] = bestIndex;
    
    return totalError;
}


 //Recursive function to print the solution from the computed answer in printNeatly stored in the int array p
void printCost(vector<vector<int> > &lineCost, string wordArray[], int j, int M)
{
    int penalty = 0;
    int i = 0;
    int k = lineCost[i][j];
    
    while (k != 0)
    {
        int lineLen = 0;
        int curLineWordCount = 0;
        int wrd;
        for (wrd = i; wrd < k; ++wrd) // where k is the number of words in that line
        {
            string word = wordArray[wrd];
            
            lineLen += word.length();
            
            ++curLineWordCount; // keep track of which word we are on 
        }
      
        penalty += ((M - (lineLen + curLineWordCount - 1))*(M - (lineLen + curLineWordCount - 1))*(M - (lineLen + curLineWordCount - 1)));
        
        i = k;
        k = lineCost[i][j];
    }    
    cout << "penalty: " << penalty << endl;
}


/* 
 * Recursive function to print the solution from the computed answer in printNeatlyRec and printNeatly
 */
void printSolution(vector<vector<int> > &lineCost, string wordArray[], int j)
{
    int i = 0;
    int k = lineCost[i][j];
    
    while (k != 0)
    {
        int wrd;
        for (wrd = i; wrd < k; ++wrd)
        {
            cout << wordArray[wrd] << ' ';
        }
        
        i = k;
        k = lineCost[i][j];
        cout << '\n';
    }
    
    // for the case when the paragraph all fits on one line
    if (k == 0)
    {
        int w;
        for (w = i; w < j; ++w)
        {
            cout << wordArray[w] << ' ';
        }
    }
}


//Function to neatly execute everything 
void printNeatly(int l[], int M, int n, string wordArray[])
{    
    vector <int> temp (n+1, 0);
    
    // extraSpaces[i][j] will have number of extra spaces if words from i to j are put in a single line
    vector<vector<int> > extraSpaces (n+1, temp);
    
    // lineCost[i][j] will have cost of a line (line cost) which has words from i to j
    vector<vector<int> > lineCost (n+1, temp);
       
    printNeatlyRec(wordArray, 0, n, M, extraSpaces, lineCost, n);
    
    printCost(lineCost, wordArray, n, M);
    printSolution(lineCost, wordArray, n);
    
    cout << '\n';
}



/* Driver to get the input and run the functions */ 
int main()
{
    string lineString; 
    queue<string> inputQueue; 
    
    while (getline(cin, lineString)) 
    {
        inputQueue.push(lineString);
    }

    istringstream is(inputQueue.front()); 
    int P; 
    is >> P; 
    inputQueue.pop(); 

    int i;
    for (i = 0; i < P; ++i)
    {
        istringstream streamString(inputQueue.front()); 
        int M; // the maximun number of characters per line M
        streamString >> M; 
        inputQueue.pop();
        
        string words; 
        words = inputQueue.front(); 
        inputQueue.pop(); 

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
                        --spaceCounter;
                    }
                }
            }
        }
        
        int n = spaceCounter + 1; // n is the word count
        

        int l[n]; // This is an array of ints for each of the words in the paragraph
        

        istringstream ss(words);
        string s;
        int wordNumber = 0; // keep track of which words in the paragraph we are on
        while(ss >> s) 
        {
            l[wordNumber] = s.length();
            ++wordNumber;
        }

        istringstream strstream(words);
        string str;
        string wordArray[words.length()];
        
        wordNumber = 0; 
        while(strstream >> str)
        {
            wordArray[wordNumber] = str;
            ++wordNumber;
        }
        
        // now feed this MAX_INTormation into the function for printing neat
        printNeatly(l, M, n, wordArray);
        
        cout << " " << endl;
        
    } 
    
    return 0;
}



