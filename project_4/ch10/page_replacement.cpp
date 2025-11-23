#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> generateReferenceString(int length) {
    vector<int> refString;
    for (int i = 0; i < length; ++i) {
        refString.push_back(rand() % 10);
    }
    return refString;
}

int runFIFO(int frameCount, const vector<int>& refString) {
    vector<int> frames;
    int faults = 0;
    
    for (int page : refString) {
        if (find(frames.begin(), frames.end(), page) != frames.end()) {
            continue;
        }

        faults++;
        if (frames.size() < frameCount) {
            frames.push_back(page);
        } else {
            frames.erase(frames.begin());
            frames.push_back(page);
        }
    }
    return faults;
}

int runLRU(int frameCount, const vector<int>& refString) {
    vector<int> frames;
    int faults = 0;

    for (int page : refString) {
        auto it = find(frames.begin(), frames.end(), page);
        
        if (it != frames.end()) {
            // HIT: Remove it from current position and push to back (Most Recently Used)
            frames.erase(it);
            frames.push_back(page);
        } else {
            // MISS
            faults++;
            if (frames.size() < frameCount) {
                frames.push_back(page);
            } else {
                // Frames full: Remove the front (Least Recently Used)
                frames.erase(frames.begin());
                frames.push_back(page);
            }
        }
    }
    return faults;
}

int runOPT(int frameCount, const vector<int>& refString) {
    vector<int> frames;
    int faults = 0;

    for (size_t i = 0; i < refString.size(); ++i) {
        int page = refString[i];

        if (find(frames.begin(), frames.end(), page) != frames.end()) {
            continue;
        }

        faults++;
        if (frames.size() < frameCount) {
            frames.push_back(page);
        } else {
            int furthestIndex = -1;
            int victimIndex = -1;

            for (int f = 0; f < frames.size(); ++f) {
                int currentFramePage = frames[f];
                int nextUse = -1;

                for (size_t k = i + 1; k < refString.size(); ++k) {
                    if (refString[k] == currentFramePage) {
                        nextUse = k;
                        break;
                    }
                }

                if (nextUse == -1) {
                    victimIndex = f;
                    break; 
                }

                if (nextUse > furthestIndex) {
                    furthestIndex = nextUse;
                    victimIndex = f;
                }
            }
            
            // Replace victim
            if (victimIndex != -1) {
                frames[victimIndex] = page;
            }
        }
    }
    return faults;
}

int main() {
    srand(time(0));

    int numFrames, strLen;

    cout << "--- Page Replacement Algorithm Simulation ---" << endl;
    cout << "Enter number of page frames: ";
    if (!(cin >> numFrames)) return 1;
    
    cout << "Enter length of random page-reference string: ";
    if (!(cin >> strLen)) return 1;

    vector<int> refString = generateReferenceString(strLen);

    cout << "\nGenerated Reference String: ";
    for (int p : refString) cout << p << " ";
    cout << "\n" << string(50, '-') << endl;

    int fifoFaults = runFIFO(numFrames, refString);
    int lruFaults = runLRU(numFrames, refString);
    int optFaults = runOPT(numFrames, refString);

    cout << left << setw(15) << "Algorithm" << " | " << "Page Faults" << endl;
    cout << string(30, '-') << endl;
    cout << left << setw(15) << "FIFO" << " | " << fifoFaults << endl;
    cout << left << setw(15) << "LRU" << " | " << lruFaults << endl;
    cout << left << setw(15) << "OPT" << " | " << optFaults << endl;
    cout << string(30, '-') << endl;

    return 0;
}
