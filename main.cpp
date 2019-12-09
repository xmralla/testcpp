

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class room
{
public:
    vector<pair<int, int>> points;
    bool has_point(pair<int, int>& point)
    {
        for (auto & p: points)
        {
            if(p == point)
            {
                return true;
            }
        }
        return false;
    }
};

class office
{
public:
    vector<room> rooms;
    room* find_office(pair<int, int>& point)
    {
        for(auto &r : rooms)
        {
            if(r.has_point(point))
            {
                return &r;
            }
        }
        return nullptr;
    }
    void add_room(pair<int, int>& p)
    {
        room o;
        o.points.push_back(p);
        rooms.push_back(o);
    }
};


typedef vector<vector<int>> grid_vector;


void print_grid(grid_vector& grid)
{
    size_t row_num = grid.size();
    if(row_num != 0)
    {
        size_t col_num = grid[0].size();

        for (size_t i =0; i < row_num; ++i)
        {
            for (size_t j = 0; j < col_num; ++j)
            {
                cout << static_cast<int>(grid[i][j]) << " ";
            }
            cout  << endl;
        }
    }
}

class Solution {
    office offices;
public:
    int numOffices(grid_vector& grid)
    {
        // Put code here
        offices.rooms.clear();
        int office_num = -1;
        size_t row_num = grid.size();
        if(row_num == 0)
        {
            return office_num;
        }
        size_t col_num = grid[0].size();

        for (size_t i =0; i < row_num; ++i)
        {
            for (size_t j = 0; j < col_num; ++j)
            {
                if (grid[i][j] == 1)
                {
                    pair<int, int> p(i, j);
                    room* left_room = nullptr;
                    if (j == 0)
                    {
                        if(i == 0)
                        {
                            offices.add_room(p);
                        }
                    }
                    else
                    {
                        if(grid[i][j-1] == 1)
                        {
                            pair<int,int> p(i, j-1);
                            left_room = offices.find_office(p);
                            if(left_room != nullptr)
                            {
                                left_room->points.push_back(pair<int,int> (i, j));
                            }
                            else
                            {
                                offices.add_room(p);
                            }
                        }
                        else
                        {
                            if(i == 0)
                            {
                                offices.add_room(p);
                            }
                        }
                    }
                    if ( i > 0)
                    {
                        if(grid[i-1][j] == 1)
                        {
                            pair<int,int> p(i-1, j);
                            auto upper_room = offices.find_office(p);
                            if(upper_room != nullptr)
                            {
                                if(left_room == nullptr)
                                {
                                    upper_room->points.push_back(pair<int,int> (i, j));
                                }
                                else
                                {
                                    // merge rooms if it is not the same room
                                    if(upper_room != left_room)
                                    {
                                        room new_room;
                                        new_room.points.insert(new_room.points.begin(),
                                                               upper_room->points.begin(),
                                                               upper_room->points.end());
                                        new_room.points.insert(new_room.points.end(),
                                                               left_room->points.begin(),
                                                               left_room->points.end());

                                        streamsize upper_index = upper_room - &offices.rooms[0];
                                        streamsize left_index  = left_room  - &offices.rooms[0];

                                        offices.rooms.erase(offices.rooms.begin() + upper_index);
                                        offices.rooms.erase(offices.rooms.begin() + left_index);
                                        offices.rooms.push_back(new_room);
                                    }
                                }
                            }
                            else
                            {
                                offices.add_room(p);
                            }
                        }
                        else
                        {
                            if(left_room == nullptr)
                            {
                                offices.add_room(p);
                            }
                        }
                    }
                }
            }
        }
        return static_cast<int>(offices.rooms.size());
    }
    int bigestTable(grid_vector& grid)
    {
        // Put code here
        int max_rect_size = -1;
        size_t row_num = grid.size();
        if(row_num == 0)
        {
            return max_rect_size;
        }
        const size_t col_num = grid[0].size();
        vector<char> line(col_num);

        for (auto& r : offices.rooms)
        {
            for(auto& p: r.points)
            {
                int a =0;
            }
        }
        return max_rect_size;
    }
};


bool test_report( string title, string pass, int n, int expected, bool& done)
{
    done = true;
    if(n != expected)
    {
        cerr << title << ": ERROR: expected " << expected << ", got " << n << endl;
        done = false;
    }
    else
    {
        cout << title << pass << n << endl;
    }
    return done;
}

bool test_numOffices()
{
    bool done = true;
    Solution solution;
    grid_vector vect = {{1,1,1,1,0},
                   {1,1,0,1,0},
                   {1,1,0,0,0},
                   {0,0,0,0,0}};

    auto n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0100", ": found offices: ",n,1,done);
    n = solution.bigestTable(vect);

    vect = {{1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0101", ": found offices: ", n,1,done);

    vect = {{0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0},
            {0,1,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0102", ": found offices: ", n,1,done);

    vect = {{0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0},
            {0,0,1,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0103", ": found offices: ", n,1,done);

    vect = {{0,0,0,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0104", ": found offices: ", n,1,done);

    vect = {{0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {0,0,0,0,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0105", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0106", ": found offices: ", n,1,done);

    vect = {{0,0,0,0,0},
            {1,1,1,1,1},
            {0,0,0,0,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0107", ": found offices: ", n,1,done);

    vect = {{0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,1},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0108", ": found offices: ", n,1,done);

    vect = {{0,0,0,0,0},
            {0,0,0,0,0},
            {0,0,0,0,0},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0109", ": found offices: ", n,1,done);


    vect = {{1,1,1,1,1},
            {0,0,0,0,1},
            {0,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0110", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0111", ": found offices: ", n,1,done);

    vect = {{1,0,0,0,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0112", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0113", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0114", ": found offices: ", n,1,done);

    vect = {{1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0115", ": found offices: ", n,1,done);

    vect = {{1,0,0,0,1},
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0116", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0117", ": found offices: ", n,1,done);

    vect = {{1,1,0,1,0},
            {1,1,0,1,0},
            {1,1,1,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0118", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,0},
            {1,1,0,1,0},
            {1,1,1,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0119", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,0},
            {1,1,0,0,0},
            {1,1,1,1,0},
            {0,0,1,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0120", ": found offices: ", n,1,done);

    vect = {{1,1,0,1,1},
            {1,1,0,1,0},
            {1,1,1,1,1},
            {0,1,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0121", ": found offices: ", n,1,done);

    vect = {{0,1,0,1,1},
            {1,1,1,1,0},
            {1,1,1,1,1},
            {0,1,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0122", ": found offices: ", n,1,done);

    vect = {{1,0,0,0,0},
            {1,0,0,0,0},
            {1,0,0,0,0},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0123", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,1,0,1},
            {1,0,1,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0124", ": found offices: ", n,1,done);


    vect = {{1,1,1,1,1},
            {1,0,1,0,1},
            {1,1,1,1,1},
            {1,0,1,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0125", ": found offices: ", n,1,done);

    vect = {{1,1,1,1,1},
            {1,0,1,0,1},
            {1,1,0,1,1},
            {1,0,1,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0126", ": found offices: ", n,1,done);

    vect = {{1,1,0,1,0},
            {1,1,0,1,0},
            {1,1,0,1,0},
            {0,0,0,0,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0200", ": found offices: ", n,2,done);

    vect = {{1,1,1,1,1},
            {1,0,1,0,1},
            {0,0,0,0,0},
            {1,0,1,0,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0201", ": found offices: ", n,2,done);

    vect = {{1,1,1,1,1},
            {1,1,1,1,1},
            {0,0,0,0,0},
            {1,1,1,1,1},
            {1,1,1,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0202", ": found offices: ", n,2,done);

    vect = {{1,1,0,1,1},
            {1,1,0,1,1},
            {1,0,0,0,1},
            {1,1,0,1,1},
            {1,1,0,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0203", ": found offices: ", n,2,done);

    vect = {{1,0,0,0,0},
            {0,1,0,0,0},
            {0,0,1,0,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0400", ": found offices: ", n,4,done);

    vect = {{1,1,0,0,1},
            {1,1,0,0,1},
            {0,0,1,1,0},
            {1,0,1,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0401", ": found offices: ", n,4,done);

    vect = {{1,1,1,1,1},
            {0,0,0,1,0},
            {0,1,0,1,1},
            {1,0,1,0,1},
            {1,0,0,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0402", ": found offices: ", n,4,done);


    vect = {{1,0,0,0,1},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {0,0,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0600", ": found offices: ", n,6,done);

    vect = {{0,1,1,0,1},
            {1,1,0,1,0},
            {0,1,0,1,0},
            {0,0,1,0,0},
            {1,1,0,1,0}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0601", ": found offices: ", n,6,done);

    vect = {{1,1,0,0,1},
            {0,1,1,1,0},
            {0,1,0,1,0},
            {1,0,1,0,1},
            {0,1,0,1,1}};
    n = solution.numOffices(vect);
    print_grid(vect);
    test_report("numOffices-0602", ": found offices: ", n,6,done);


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

