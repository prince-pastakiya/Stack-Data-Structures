#include <iostream> // Include the input/output stream library
#include <vector>   // Include the vector library

using namespace std; // Use the std namespace to avoid having to write std:: before every standard library object

class NStacks // Define a class called NStacks
{
private:           // Declare private members
    int *storage;  // Pointer to an array that will store all stacks
    int *myBottom; // Pointer to an array that will track the bottom of each stack
    int *myTop;    // Pointer to an array that will track the top of each stack
    int stackSize; // Size of each individual stack
    int numStacks; // Number of stacks
    int totalSize; // Total size of the storage array (numStacks * stackSize)

public:                                                                                          // Declare public members
    NStacks(int stacks, int size) : numStacks(stacks), stackSize(size), totalSize(stacks * size) // Constructor
    {
        storage = new int[totalSize];  // Allocate memory for storage array
        myBottom = new int[numStacks]; // Allocate memory for myBottom array
        myTop = new int[numStacks];    // Allocate memory for myTop array
        // Initialize bottoms and tops of all stacks
        for (int i = 0; i < numStacks; i++)
        {
            myBottom[i] = i * stackSize;  // Set the bottom of each stack
            myTop[i] = i * stackSize - 1; // Set the top of each stack
        }
    }

    ~NStacks() // Destructor
    {
        delete[] storage;  // Deallocate memory of storage array
        delete[] myBottom; // Deallocate memory of myBottom array
        delete[] myTop;    // Deallocate memory of myTop array
    }
    bool isFull(int stackNum) // Function to check if a stack is full
    {
        return myTop[stackNum - 1] == ((stackNum * stackSize) - 1); // Return true if the stack is full, false otherwise
    }
    bool isEmpty(int stackNum) // Function to check if a stack is empty
    {
        return myTop[stackNum - 1] == (stackNum - 1) * stackSize - 1; // Return true if the stack is empty, false otherwise
    }

    void push(int stackNum, int value) // Function to push a value onto a stack
    {
        if (isFull(stackNum)) // If the stack is full
        {
            // Find an empty space and move stacks if necessary
            int nextStack = (stackNum % numStacks) + 1;
            int currentIndex = myTop[nextStack - 1] + 1;
            while (storage[currentIndex] != 0)
            {
                currentIndex = (currentIndex + 1) % totalSize;
            }
            // Move stacks to create space for the current stack
            while (nextStack != stackNum)
            {
                int nextBottom = (myBottom[nextStack - 1] + 1) % totalSize;
                int nextTop = (myTop[nextStack - 1] + 1) % totalSize;
                while (nextBottom != nextTop)
                {
                    int nextIndex = (nextBottom - 1 + totalSize) % totalSize;
                    storage[nextTop] = storage[nextIndex];
                    nextTop = nextIndex;
                    nextBottom = (nextBottom - 1 + totalSize) % totalSize;
                }
                myBottom[nextStack - 1] = (myBottom[nextStack - 1] + 1) % totalSize;
                myTop[nextStack - 1] = (myTop[nextStack - 1] + 1) % totalSize;
                nextStack = (nextStack % numStacks) + 1;
            }
            // Update top of the current stack
            myTop[stackNum - 1] = (myTop[stackNum - 1] + 1) % totalSize;
        }
        // Push the value onto the current stack
        int currentIndex = myTop[stackNum - 1];
        storage[currentIndex] = value;
        myTop[stackNum - 1] = (myTop[stackNum - 1] + 1) % totalSize;
    }

    int pop(int stackNum) // Function to pop a value from a stack
    {
        if (isEmpty(stackNum)) // If the stack is empty
        {
            cout << "Stack " << stackNum << " is empty." << endl; // Print an error message
            return -1;                                            // Return -1 to indicate an error
        }
        int currentIndex = myTop[stackNum - 1];                                  // Get the index of the top of the stack
        int value = storage[currentIndex];                                       // Get the value at the top of the stack
        storage[currentIndex] = 0;                                               // Clear the value at the top of the stack
        myTop[stackNum - 1] = (myTop[stackNum - 1] - 1 + totalSize) % totalSize; // Update the top of the stack
        return value;                                                            // Return the popped value
    }

    void printStack(int stackNum) // Function to print the contents of a stack
    {
        cout << "Stack " << stackNum << " members: "; // Print the stack number
        int index = myBottom[stackNum - 1];           // Get the index of the bottom of the stack
        while (index != myTop[stackNum - 1])          // While the index is not the top of the stack
        {
            cout << storage[index] << " ";   // Print the value at the current index
            index = (index + 1) % totalSize; // Update the index
        }
        cout << storage[index] << endl; // Print the value at the top of the stack
    }
};

int main() // Main function
{
    cout << "Stack Data structures follows LIFO (Last In First Out)." << endl;
    cout << "Push function add an element at end of the list." << endl;
    cout << "Pop function will remove the last element of the list." << endl;
    cout << "" << endl;

    int numStacks = 3;                    // Number of stacks
    int stackSize = 5;                    // Size of each stack
    NStacks stacks(numStacks, stackSize); // Create an instance of NStacks
    // Push values onto the stacks
    stacks.push(1, 10);
    stacks.push(1, 20);
    stacks.push(1, 30);
    stacks.push(1, 40);
    stacks.push(1, 50);

    stacks.push(2, 70);
    stacks.push(2, 80);
    stacks.push(2, 90);
    stacks.push(2, 100);
    stacks.push(2, 190);

    stacks.push(3, 110);
    stacks.push(3, 120);
    stacks.push(3, 130);
    stacks.push(3, 140);
    stacks.push(3, 200);
    stacks.push(3, 60);

    // Print the contents of the stacks
    stacks.printStack(1);
    stacks.printStack(2);
    stacks.printStack(3);

    cout << "" << endl; // Pop values from the stacks and print them
    cout << "Pop from stack 1: " << stacks.pop(1) << endl;
    cout << "Pop from stack 2: " << stacks.pop(2) << endl;
    cout << "Pop from stack 3: " << stacks.pop(3) << endl;

    cout << "" << endl; // Print the contents of the stacks after popping
    stacks.printStack(1);
    stacks.printStack(2);
    stacks.printStack(3);

    system("pause>0"); // Pause the console
}