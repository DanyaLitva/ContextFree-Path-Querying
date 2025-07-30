//UNN
//Litvyakov D. D.
//

#include "template.h"
#include <gtest.h>


TEST(graph, test_graph_num1)
{
    size_t count_vertex = 10;
    size_t nonterms_count = 4;
    size_t terms_count = 4;
    vector <vector <vector<size_t> > >bin_rules(nonterms_count, vector<vector<size_t>>(nonterms_count, vector<size_t>()));
    vector<vector<bool>> term_rules(nonterms_count, vector<bool>(terms_count + 1));
    vector<vector<vector<bool>>> term_matrix(count_vertex, vector<vector<bool>>(count_vertex, vector<bool>(terms_count + 1)));
    vector<vector<vector<vector<vector<size_t>>>>> matrix(nonterms_count, vector<vector<vector<vector<size_t>>>>());


    //продукции
    bin_rules = {
        {
            {3,2}//N0
},
    {
        {1,0}//N1
},
    {
        {3,0}, //N2
},
    {
        {0,1},{1,2}//N3
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
        //      0           1           2           3           4           5           6           7           8           9
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //0
          {{0,0,0,0,0},{0,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //1
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,1,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //2
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,1,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //3
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,1,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //4
          {{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //5
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{1,0,0,0,0},{0,0,0,1,0},{0,0,0,0,0}}, //6
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,1,0,0},{0,0,0,0,0}}, //7
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //8
          {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,1,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}}, //9

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
                        matrix[_nonterms_count].push_back(res_matrix);
                    }
                }
            }
        }
    }


    vector<size_t> path;
    size_t start = 1;
    size_t finish = 0;

    bool found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex); 
            if (found) break;
        }
    }
    EXPECT_TRUE(found);
    path.clear();

    start = 1;
    finish = 5;

    found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }
    EXPECT_TRUE(found);
    path.clear();

    start = 5;
    finish = 6;

    found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }
    EXPECT_FALSE(found);
    path.clear();

    start = 0;
    finish = 1;

    found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }
    EXPECT_FALSE(found);
    path.clear();

}


TEST(graph, test_graph_num2)
{
    size_t count_vertex = 5;
    size_t nonterms_count = 4;
    size_t terms_count = 3;
    vector <vector <vector<size_t> > >bin_rules(nonterms_count, vector<vector<size_t>>(nonterms_count, vector<size_t>()));
    vector<vector<bool>> term_rules(nonterms_count, vector<bool>(terms_count + 1));
    vector<vector<vector<bool>>> term_matrix(count_vertex, vector<vector<bool>>(count_vertex, vector<bool>(terms_count + 1)));
    vector<vector<vector<vector<vector<size_t>>>>> matrix(nonterms_count, vector<vector<vector<vector<size_t>>>>());


    //продукции
    bin_rules = {
        {
            {2,1}//N0
},
    {
        {0,3}//N1
},
    {
        {}, //N2
},
    {
        {}//N3
}
    };

    //терминалы
    term_rules = {
        // дополнительный элемент - пустое слово 
        {0,0,1,0,0}, //N0 -> c
        {0,0,0,0,0}, //N1 -> 
        {1,0,0,0,0}, //N2 -> a
        {0,1,0,0,0}  //N3 -> b
    };

    term_matrix = {
        //     0         1         2         3         4     
          {{0,0,0,0},{1,0,0,0},{0,0,0,0},{0,0,1,0},{0,0,0,0}}, //0
          {{0,0,0,0},{0,0,0,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}}, //1
          {{1,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, //2
          {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,1,0,0}}, //3
          {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,1,0,0},{0,0,0,0}} //4
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
                        matrix[_nonterms_count].push_back(res_matrix);
                    }
                }
            }
        }
    }

    vector<size_t> path;
    size_t start = 1;
    size_t finish = 4;

    bool found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }

    EXPECT_TRUE(found);

    path.clear();

    start = 4;
    finish = 1;

    found = false;
    for (size_t nt = 0; nt < nonterms_count; ++nt) {
        if (!matrix[nt].back()[start][finish].empty()) {
            found = extract_path(path, nt, start, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex);
            if (found) break;
        }
    }
    EXPECT_FALSE(found);

    path.clear();
}