#ifndef RANDOM_DOT_H
#define RANDOM_DOT_H

#include <ctime>
#include <cstdlib>
#include <stdexcept>
#include <vector>
#include <stdexcept>

using namespace std;

struct RandUtil {

    RandUtil();

    // returns a random integer between a and b (inclusive)
    int randint(int a, int b);

    // returns a random (real) number between a and b (inclusive)
    double randnum(double a, double b);

    // returns a random element from v (by copy)
    template <typename T>
    T randomElement(const vector<T>& v) {
        if (v.empty()) {
            throw invalid_argument("v cannot be empty");
        }
        return v.at(randint(0, v.size() - 1));
    }

    // returns a random element from v (by reference)
    template <typename T>
    T& randomElementRef(vector<T>& v) {
        if (v.empty()) {
            throw invalid_argument("v cannot be empty");
        }
        return v.at(randint(0, v.size() - 1));
    }

    // sample n candidates (with replacement) using the given selection probabilities
    template <typename T>
    vector<T> sample(const vector<T>& candidates, const vector<double>& probabilities, int n = 1) {

        double sumOfProbs = 0;
        for (double prob : probabilities) {
            sumOfProbs += prob;
        }

        vector<double> probabilitiesCumulative = {probabilities.front()};
        for (int i = 1; i < probabilities.size(); i++) {
            probabilitiesCumulative.push_back(probabilities.at(i) + probabilitiesCumulative.back());
        }

        vector<T> results;

        for (int i = 0; i < n; i++) {
            double randProbability = this->randnum(0, sumOfProbs);
            for (int j = 0; j < probabilitiesCumulative.size(); j++) {
                if (randProbability <= probabilitiesCumulative.at(j)) {
                    results.push_back(candidates.at(j));
                    break;
                }
            }
        }

        return results;

    }

};

#endif