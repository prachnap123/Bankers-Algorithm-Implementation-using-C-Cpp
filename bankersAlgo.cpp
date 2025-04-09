#include <iostream>
using namespace std;

int maxRequirement[10][10], allocation[10][10], need[10][10];
int avail[10];
int np, nr;

void readMatrix(int matrix[10][10]) {
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            cin >> matrix[i][j];
}

void displayMatrix(int matrix[10][10]) {
    for (int i = 0; i < np; i++) {
        cout << "\n P" << i << "\t";
        for (int j = 0; j < nr; j++) {
            cout << " " << matrix[i][j];
        }
    }
}

void calculateNeed() {
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = maxRequirement[i][j] - allocation[i][j];
}

void banker() {
    int finish[10] = {0}, safeSeq[10], k = 0, flag;

    for (int i = 0; i < np; i++) {
        flag = 0;
        if (finish[i] == 0) {
            for (int j = 0; j < nr; j++) {
                if (need[i][j] > avail[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                finish[i] = 1;
                safeSeq[k++] = i;
                for (int j = 0; j < nr; j++)
                    avail[j] += allocation[i][j];
                i = -1;  // Restart the loop to check from the first process again
            }
        }
    }

    flag = 0;
    for (int i = 0; i < np; i++) {
        if (finish[i] == 0) {
            cout << "\nThe system is in deadlock!";
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        cout << "\n The system is in a safe state! \n Safe sequence is ==> ";
        for (int i = 0; i < np; i++)
            cout << " P" << safeSeq[i];
    }
}

int main() {
    cout << "\nEnter the number of processes: ";
    cin >> np;
    cout << "\nEnter the number of resources: ";
    cin >> nr;

    cout << "\nEnter the initial allocation matrix:\n";
    readMatrix(allocation);

    cout << "\nEnter the max requirement matrix:\n";
    readMatrix(maxRequirement);

    cout << "\nEnter the available resources:\n";
    for (int j = 0; j < nr; j++)
        cin >> avail[j];

    cout << "\n****** Entered Data is ******\n";
    cout << "\nInitial allocation:\n";
    displayMatrix(allocation);

    cout << "\n\nMaximum Requirement:\n";
    displayMatrix(maxRequirement);

    cout << "\n\nAvailable resources:\n ";
    for (int j = 0; j < nr; j++)
        cout << " " << avail[j];

    calculateNeed();
    cout << "\n\nNeed is:\n";
    displayMatrix(need);

    banker();

    cout << "\n\n\n";
    return 0;
}
