//UNN
//Litvyakov D. D.
//

#pragma once
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>

int check();

using namespace std;

vector<vector<vector<size_t>>> matrix_mul(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex);

vector<vector<vector<size_t>>> matrix_add(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex);

bool matrix_eq(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex);

void print_last_matrix(vector < vector<vector<vector<vector<size_t>>>>>& matrix);

bool extract_path(vector<size_t>& path, size_t nt, size_t start, size_t finish, vector<vector<vector<vector<vector<size_t>>>>>& matrix, vector<vector<vector<size_t>>>& bin_rules, vector<vector<vector<bool>>>& term_matrix, vector<vector<bool>>& term_rules, size_t count_vertex);

vector<vector<size_t>> extract_all_paths(size_t nt, size_t start, size_t finish, vector<vector<vector<vector<vector<size_t>>>>>& matrix, vector<vector<vector<size_t>>>& bin_rules, vector<vector<vector<bool>>>& term_matrix, vector<vector<bool>>& term_rules, size_t count_vertex);

vector<vector<size_t>> extract_all_paths_w_depth(size_t nt, size_t start, size_t finish, vector<vector<vector<vector<vector<size_t>>>>>& matrix, vector<vector<vector<size_t>>>& bin_rules, vector<vector<vector<bool>>>& term_matrix, vector<vector<bool>>& term_rules, size_t count_vertex, int max_edges);