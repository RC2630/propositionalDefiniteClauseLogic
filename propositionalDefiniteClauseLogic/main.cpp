#include "general/file.h"
#include "general/vectorUtility.h"
#include "general/stringUtility.h"
#include "general/abstractFunctions.h"

using vecUtil::operator<<;

const string INPUT_FILE = "file/input.txt";
const string OUTPUT_FILE = "file/output.txt";

struct Clause {

    string left;
    vector<string> right;

    Clause(const string& line) {

        if (!strUtil::contains(line, "<-")) {
            this->left = line;
            return;
        }

        vector<string> leftAndRight = strUtil::split(line, " <- ");
        this->left = leftAndRight.front();
        this->right = strUtil::split(leftAndRight.back(), " ^ ");

    }

    string toString() const {
        
        if (this->right.empty()) {
            return this->left;
        }

        string rightAtomsTogether = strUtil::join(this->right, " ^ ");
        return this->left + " <- " + rightAtomsTogether;

    }

};

vector<string> getDerivablesUsingBottomUp(const vector<Clause>& clauses) {
    
    vector<string> results;
    bool nothingAddedThisIteration = false;
    vector<string> log;

    while (!nothingAddedThisIteration) {
        
        nothingAddedThisIteration = true;

        for (const Clause& clause : clauses) {

            bool rightAllDerivable = absFunc::andmap_f<string>(clause.right, [&results] (const string& atom) {
                return vecUtil::contains(results, atom);
            });

            bool leftNotYetDerived = !vecUtil::contains(results, clause.left);

            if (rightAllDerivable && leftNotYetDerived) {

                nothingAddedThisIteration = false;
                results.push_back(clause.left);

                string derivables = strUtil::join(results, ", ");
                log.push_back("using clause \"" + clause.toString() + "\", updated derivables to [" + derivables + "]");

            }

        }

    }

    file::clearFile(OUTPUT_FILE);
    file::outputVecTo(log, OUTPUT_FILE);

    return results;

}

int main() {
    
    vector<string> input;
    file::inputStrVecFrom(input, INPUT_FILE);
    vector<Clause> clauses = absFunc::map<string, Clause>(input, [] (const string& line) {
        return Clause(line);
    });

    vector<string> derivables = getDerivablesUsingBottomUp(clauses);
    cout << "\nHere are all atoms that can be derived:\n" << derivables << "\n";

}