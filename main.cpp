

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numOffices(vector<vector<char>>& grid)
    {
        // Put code here
        int offices = -1;
        size_t row_num = grid.size();
        if(row_num == 0)
        {
            return offices;
        }
        size_t col_num = grid[0].size();

        vector<set<size_t>> floors;
        for (size_t i =0; i < row_num; ++i)
        {
            set<size_t> floor;
            int count = 0;
            for (size_t j = 0; j < col_num; ++j)
            {
                if (grid[i][j] == 1)
                {
                    floor.insert(j);
                    if(j == 0)
                    {
                        ++count;
                    }
                    else if (grid[i][j-1] == 0)
                    {
                        ++count;
                    }
                }
            }

            if(offices == -1)
            {
                offices  = count;
            }
            else
            {
                bool push = false;
                for (auto w : floor)
                {
                    bool found = false;
                    for(auto k : floors.back())
                    {
                        if (k == w)
                        {
                            found = true;
                            break;
                        }
                    }
                    if(! found)
                    {
                        push = true;
                    }
                }
                if(push)
                {
                    int count = 0;
                    size_t prev = 0;
                    bool check_next = false;
                    for(auto a : floor)
                    {
                        bool found = false;
                        for(auto b : floors.back())
                        {
                            if (b == a)
                            {
                                found = true;
                                break;
                            }
                        }
                        if (! found)
                        {
                            if(a == 0)
                            {
                            ++count;
                            }
                            else if (a-1 != prev)
                            {
                                ++count;
                                check_next = true;
                            }
                        }
                        else if (a - 1 == prev && check_next)
                        {
                            --count;
                            check_next = false;
                        }

                        prev = a;
                    }
                    offices += count;
                }
            }
            floors.push_back(floor);
        }
        return offices;
    }
    int bigestTable(vector<vector<char>>& grid)
    {
        // Put code here
        int offices = -1;
        size_t row_num = grid.size();
        if(row_num == 0)
        {
            return offices;
        }
        size_t col_num = grid[0].size();

        vector<vector<size_t>> floors;
        for (size_t i =0; i < row_num; ++i)
        {
            vector<size_t> floor;
            for (size_t j = 0; j < col_num; ++j)
            {
                if (grid[i][j] == 1)
                {
                    floor.push_back(j);
                }
            }
            floors.push_back(floor);
        }
        return offices;
    }
};


bool test_report( string title, int n, int expected, bool& done)
{
    if(n != expected)
    {
        cerr << title << ": ERROR: expected " << expected << ", got " << n << endl;
        done = false;
    }
    else
    {
        cout << title << ": found offices: " << n << endl;
    }
}

bool test_numOffices()
{
    bool done = true;
    Solution solution;
    vector<vector<char>> vect = {{1,1,1,1,0},
                                 {1,1,0,1,0},
                                 {1,1,0,0,0},
                                 {0,0,0,0,0}};

    auto n = solution.numOffices(vect);
    test_report("numOffices-0100", n,1,done);

    vect = {{1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0101", n,1,done);

    vect = {{0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0102", n,1,done);

    vect = {{0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0103", n,1,done);

    vect = {{0,0,0,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0104", n,1,done);

    vect = {{0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0105", n,1,done);

    vect = {{1,1,1,1,1},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0106", n,1,done);

    vect = {{0,0,0,0,0},
            {1,1,1,1,1},
            {0,0,0,0,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0107", n,1,done);

    vect = {{0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,1},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0108", n,1,done);

    vect = {{0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0109", n,1,done);


    vect = {{1,1,1,1,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0110", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0111", n,1,done);

    vect = {{1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0112", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0113", n,1,done);

    vect = {{1,1,1,1,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0114", n,1,done);

    vect = {{1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0115", n,1,done);

    vect = {{1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0116", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    test_report("numOffices-0117", n,1,done);

    vect = {{1,1,0,1,0},
            {1,1,0,1,0},
            {1,1,1,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0118", n,1,done);

    vect = {{1,1,1,1,0},
            {1,1,0,1,0},
            {1,1,1,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0119", n,1,done);

    vect = {{1,1,1,1,0},
            {1,1,0,0,0},
            {1,1,1,1,0},
            {0,0,1,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0120", n,1,done);

    vect = {{1,1,0,1,1},
            {1,1,0,1,0},
            {1,1,1,1,1},
            {0,1,0,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-1021", n,1,done);

    vect = {{0,1,0,1,1},
            {1,1,1,1,0},
            {1,1,1,1,1},
            {0,1,0,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0122", n,1,done);

    vect = {{1,1,0,1,0},
            {1,1,0,1,0},
            {1,1,0,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0200", n,2,done);

    vect = {{1,0,0,0,0},
            {0,1,0,0,0},
            {0,0,1,0,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0400", n,4,done);

    vect = {{1,0,0,0,1},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    test_report("numOffices-0600", n,6,done);


    return done;
}
int main()
{
    if (test_numOffices())
    {
        return 0;
    }
    return  -1;
}

/*
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int minimumConcat(string initial, string goal) {
        // Code Here
        auto len = initial.length();
        for(size_t i = 0; i < len; ++i)
        {
            for(size_t i = 0; i < len; ++i)
            {

            }
        }

        return 0;
    }
};

int main()
{
    // Parsing input here
    string initial, goal;

    initial = "abc";
    goal = "acdbc";

    Solution solution;
    cout << solution.minimumConcat(initial, goal);

    return 0;
}*/

