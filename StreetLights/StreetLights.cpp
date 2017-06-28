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

//! Begin Main Function (Note: Bold/Green comments act as section headings)
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

        //! Get inputs
        vector<int> light_locations = readlineofints(n);

        //Initialize indices
        int light_index = 0;
        int lights_on = 0;
        bool possible = true;

        //Sort lights
        sort(light_locations.begin(), light_locations.end());


        //Check to see if there are lights and if start can be illuminated
        if (light_locations.size()==0 || light_locations[0] - d > 0) {
            possible = false;
        }


        //! Go through street
        //Everything behind street_location is lit.
        for (int street_location = 0; street_location <= l; street_location = light_locations[light_index] + d) { //Set the street location to the next dark spot)           

            //If we know it's impossible, break
            if (!possible) { break; }

            //Set k to the current light
            int k = light_index;
            //Increment k until the light would no longer illuminate the current street location
            while (k<light_locations.size() && light_locations[k] - d <= street_location) {
                k++;
            }

            //Update indices
            light_index = k - 1; //Set the light to the last one that could illuminate the current street location
            lights_on++; //Increment lights on (since we're turning on the k-1 light)

            //If this was the last light 
            if (k >= light_locations.size()) {
                //If it lights to the end, break
                if (light_locations[light_index] + d >= l) {
                    break;
                } //If not, mark false and break
                else {
                    possible = false;
                    break;
                }
            }
            //If this wasn't the last light but the last light already lights to the end
            if (light_locations[light_index] + d>=l) {
                break;
            }
            //If the gap between this light and the next is nonzero, mark false and break
            if (light_locations[k] - d > light_locations[light_index] + d) {
                possible = false;
                break;
            }
        }

        //! Print output
        std::cout << "Case #" << i << ": ";
        if (possible) {
            std::cout << lights_on;
        }
        else {
            std::cout << "impossible";
        }
        std::cout << std::endl;
    }
    return 0;
}