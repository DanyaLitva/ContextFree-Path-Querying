//UNN
//Litvyakov D. D.
//

// NOLINTBEGIN
#include "template.h"
// NOLINTEND

using namespace std;

const int MAX_DEPTH = 20;
const bool Detailed_output = 0;

int main()
{
    size_t count_vertex = 6;
    size_t nonterms_count = 4;
    size_t terms_count = 4;
    vector <vector <vector<size_t> > >bin_rules(nonterms_count, vector<vector<size_t>>(nonterms_count, vector<size_t>()));
    vector<vector<bool>> term_rules(nonterms_count, vector<bool>(terms_count + 1));
    vector<vector<vector<bool>>> term_matrix(count_vertex, vector<vector<bool>>(count_vertex, vector<bool>(terms_count + 1)));
    vector<vector<vector<vector<vector<size_t>>>>> matrix(nonterms_count, vector<vector<vector<vector<size_t>>>>());
    vector<size_t> from_starting;

    //S -> N0|N1|N2|N3
    from_starting = { 0, 1, 2, 3 };

    //продукции
    bin_rules = {
        {
            {}//N0
},
    {
        {}//N1
},
    {
        {0,1},{2,3} //N2
},
    {
        {}//N3
}
    };

    //терминалы
    term_rules = {
        // дополнительный элемент - пустое слово 
        {1,0,0,0,0}, //N0 -> a
        {0,1,0,0,0}, //N1 -> b
        {0,0,1,0,0}, //N2 -> c
        {0,0,0,1,0}  //N3 -> d
    };

    term_matrix = {
        //      0           1           2           3           4           5         
          {{0,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0}}, //0
          {{0,0,0,0,0},{0,0,0,0,0},{0,1,0,0,0},{0,1,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //1
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,1,0}}, //2
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,1,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,1,0}}, //3
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,1,0,0,0}}, //4
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}} //5
    };

    for (size_t i = 0; i < nonterms_count; ++i) {
        matrix[i].push_back(vector<vector<vector<size_t>>>(count_vertex, vector<vector<size_t>>(count_vertex)));
    }

    for (size_t i = 0; i < count_vertex; ++i) {
        for (size_t j = 0; j < count_vertex; ++j) {
            for (size_t k = 0; k < terms_count; ++k) {
                if (term_matrix[i][j][k] != 0) {
                    for (size_t nonterm_it = 0; nonterm_it < nonterms_count; nonterm_it++) {
                        if (term_rules[nonterm_it][k] != 0) matrix[nonterm_it][0][i][j].push_back(i);
                    }
                }
            }
        }
    }

    if (Detailed_output) print_last_matrix(matrix);

    for (size_t i = 0; i < nonterms_count; ++i) {
        matrix[i].push_back(matrix[i].front());
    }

    bool flag = 1;
    while (flag) {
        flag = 0;
        for (size_t _nonterms_count = 0; _nonterms_count < nonterms_count; ++_nonterms_count) {
            for (size_t it_rule = 0; it_rule < bin_rules[_nonterms_count].size(); ++it_rule) {
                vector<vector<vector<size_t>>> res_matrix;
                if ((bin_rules[_nonterms_count][it_rule].size() != 0)) {
                    res_matrix = matrix_mul(matrix[(bin_rules[_nonterms_count][it_rule][0])].back(), matrix[(bin_rules[_nonterms_count][it_rule][1])].back(), count_vertex);

                    res_matrix = matrix_add(matrix[_nonterms_count].back(), res_matrix, count_vertex);

                    if (!matrix_eq(matrix[_nonterms_count].back(), res_matrix, count_vertex)) {
                        flag = 1;
                        matrix[_nonterms_count].back() = res_matrix;
                    }
                }
            }
        }
    }

    if (Detailed_output) {
        cout << endl << endl;
        cout << "After the closure:" << endl << endl;
        print_last_matrix(matrix);
        cout << endl;
    }

    vector<size_t> path;
    size_t start = 0;
    size_t finish = 0;

    cout << "Start and Finish vertex: ";
    cin >> start >> finish;
    cout << endl;

    bool found = false;
    for (size_t nt : from_starting) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }

    cout << "Path: ";
    if (path.size() == 0) cout << "no path" << endl;
    else {
        for (size_t sz = 0; sz < path.size(); sz++) {
            cout << path[sz];
            if ((sz != path.size() - 1)) cout << " -> ";
        }

        cout << endl;
        cout << endl << "Terminals: ";
        for (size_t i = 0; i < path.size() - 1; ++i) {
            size_t from = path[i];
            size_t to = path[i + 1];

            for (size_t term = 0; term < terms_count; ++term) {
                if (term_matrix[from][to][term]) {
                    cout << char('a' + term);
                    break;
                }
            }
        }

        cout << endl;
    }


    cout << endl;
    vector<vector<size_t>> all_paths;
    int max_edges = MAX_DEPTH;

    for (size_t nt : from_starting) {
        if (!matrix[nt].back()[start][finish].empty()) {
            vector<vector<size_t>> nt_paths = extract_all_paths_w_depth(nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex, max_edges);
            all_paths.insert(all_paths.end(), nt_paths.begin(), nt_paths.end());
        }
    }

    if (all_paths.empty()) {
        cout << "No paths found." << endl;
    }
    else {
        cout << "Found " << all_paths.size() << " paths:" << endl;
        for (const auto& path : all_paths) {
            cout << endl;
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }

            cout << endl << "Terminals: ";
            for (size_t i = 0; i < path.size() - 1; ++i) {
                size_t from = path[i];
                size_t to = path[i + 1];

                for (size_t term = 0; term < terms_count; ++term) {
                    if (term_matrix[from][to][term]) {
                        cout << char('a' + term);
                        break;
                    }
                }
            }
            cout << endl;

        }
    }
}
