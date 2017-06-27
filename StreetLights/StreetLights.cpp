//Defines the entry point for the console application.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
This function reads a line of int values into a vector function and returns that
vector.
*/
vector<int> readlineofints(int count) {
    // Input values
    vector<int> linevalues(count);
    for (int j = 0; j < count; j++) {
        int val;
        cin >> val;
        linevalues[j] = val;
    }
    return linevalues; // Return line values as a vector
}

//Code from https://stackoverflow.com/questions/21978557/sort-multidimensional-vector-by-1st-column though it's been changed somewhat
//Note; the changes make it a second column sort in descending order
//Comparison for vector<vector<int>>
struct FirstColumnOnlyCmp {
    bool operator()(const std::vector<int>& lhs,
        const std::vector<int>& rhs) const {
        return lhs[1] > rhs[1];
    }
};

//Comparison for vector<vector<double>>
struct FirstColumnOnlyCmpDouble {
    bool operator()(const std::vector<double>& lhs,
        const std::vector<double>& rhs) const {
        return lhs[1] > rhs[1];
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);

    // get test case count
    int t;
    std::cin >> t;

    // loop over all the test cases
    for (int i = 1; i <= t; i++) {
        // Read in params
        vector<int> params = readlineofints(3);
        int l = params[0];
        int n = params[1];
        int d = params[2];

        vector<bool> lightable(l); //Initialize a lightable vector to track possibility

        vector<int> light_locations;
        // Iterate over inputs
        for (int j = 0; j < n; j++) {
            light_locations = readlineofints(n);
            //For each light
            for (auto light : light_locations) {
                //Calculate cone range
                int start = max(0, light - d);
                int end = min(l, light + d);
                //Iterate over cone range turning on lightable flags
                for (int k = start; k < end; k++) {
                    lightable[k] = true;
                }
            }
        }

        bool possible = true;
        //Iterate over all the possible spaces
        for (auto space : lightable) {
            //If any space is not lightable, mark the whole problem as impossible and break
            if (space == false) { 
                possible = false;
                break;
            }
        }


        //Calculate the value/length ratio, tracking item number
        vector<vector<double>> ratio;
        vector<vector<int>> sorted_score;
        for (int i = 0; i < length.size(); i++) {
            vector<double> ratio_row;
            vector<int> sorted_score_row;
            ratio_row.push_back(i); //Add item number
            sorted_score_row.push_back(i); //Add item number
            ratio_row.push_back(double(score[i]) / double(length[i])); //Add score
            sorted_score_row.push_back(score[i]); //Add score
            ratio.push_back(ratio_row);
            sorted_score.push_back(sorted_score_row);
        }

        //Sort by descending order of the score and ratio
        sort(sorted_score.begin(), sorted_score.end(), FirstColumnOnlyCmp());
        sort(ratio.begin(), ratio.end(), FirstColumnOnlyCmpDouble());

        int remaining_length = m; //Initialize remaining length
        vector<int> items_added;
        while (remaining_length > 0) {
            int item_to_add = -1;
            for (auto item : ratio) { //Iterate through the ratio list
                if (length[item[0]] <= remaining_length) { //If the length of the next best item is small enough to fit, greedy solution found
                    item_to_add = item[0]; //Mark item as one to add
                    break; //Break out of loop
                }
            }
            if (item_to_add == -1 && length[sorted_score[0][0]]<remaining_length) { //If the most valuable item is small enough and better value
                item_to_add = sorted_score[0][0]; //Use it instead
            }
            if (item_to_add != -1) { //If there's still an eligible item to add
                items_added.push_back(item_to_add); //Record item added
                remaining_length -= length[item_to_add]; //Decrement length
            }
            else { //Otherwise
                break; //Give up
            }
        }

        //Print output
        std::cout << "Case #" << i << ": ";
        for (auto item : items_added) {
            std::cout << item + 1 << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}