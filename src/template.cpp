//UNN
//Litvyakov D. D.
//


#include "template.h"

int check() { return 1; }

vector<vector<vector<size_t>>> matrix_mul(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex) {
    vector<vector<vector<size_t>>> res(vertex, vector<vector<size_t>>(vertex, vector<size_t>()));
    for (size_t i = 0; i < vertex; ++i) {
        for (size_t k = 0; k < vertex; ++k) {
            if (left[i][k].empty()) continue;
            for (size_t j = 0; j < vertex; ++j) {
                if (right[k][j].empty()) continue;
                res[i][j].push_back(k);
            }
        }
    }
    return res;
}

vector<vector<vector<size_t>>> matrix_add(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex) {
    vector<vector<vector<size_t>>> res(
        vertex,
        vector<vector<size_t>>(
            vertex,
            vector<size_t>()
        )
    );

    for (size_t i = 0; i < vertex; ++i) {
        for (size_t j = 0; j < vertex; ++j) {
            sort(left[i][j].begin(), left[i][j].end());
            sort(right[i][j].begin(), right[i][j].end());


            size_t idx_left = 0;
            size_t idx_right = 0;

            while (idx_left < left[i][j].size() && idx_right < right[i][j].size()) {
                if (left[i][j][idx_left] < right[i][j][idx_right]) {
                    res[i][j].push_back(left[i][j][idx_left]);
                    ++idx_left;
                }
                else if (right[i][j][idx_right] < left[i][j][idx_left]) {
                    res[i][j].push_back(right[i][j][idx_right]);
                    ++idx_right;
                }
                else {
                    res[i][j].push_back(left[i][j][idx_left]);
                    ++idx_left;
                    ++idx_right;
                }
            }

            while (idx_left < left[i][j].size()) {
                res[i][j].push_back(left[i][j][idx_left]);
                ++idx_left;
            }

            while (idx_right < right[i][j].size()) {
                res[i][j].push_back(right[i][j][idx_right]);
                ++idx_right;
            }
        }
    }
    return res;
}

bool matrix_eq(vector<vector<vector<size_t>>> left, vector<vector<vector<size_t>>> right, size_t vertex) {
    for (size_t i = 0; i < vertex; ++i) {
        for (size_t j = 0; j < vertex; ++j) {
            if (left[i][j].size() != right[i][j].size()) return false;
            for (size_t k = 0; k < left[i][j].size(); ++k) {
                if (left[i][j][k] != right[i][j][k]) return false;
            }
        }
    }
    return true;
}

void print_last_matrix(vector < vector<vector<vector<vector<size_t>>>>>& matrix) {
    size_t nonterms_count = matrix.size();

    for (size_t nt = 0; nt < nonterms_count; ++nt) {

        const auto& last_matrix = matrix[nt].back();
        cout << "N" << nt << "(" << matrix[nt].size() << "):\n";

        for (size_t i = 0; i < last_matrix.size(); ++i) {
            for (size_t j = 0; j < last_matrix[i].size(); ++j) {
                cout << "[";
                for (size_t k = 0; k < last_matrix[i][j].size(); ++k) {
                    cout << last_matrix[i][j][k];
                    if (k < last_matrix[i][j].size() - 1) cout << ",";
                }
                cout << "]";
                if (j < last_matrix[i].size() - 1) cout << " ";
            }
            cout << "\n";
        }
        cout << "----------------------------------------\n";
    }
}

bool extract_path(vector<size_t>& path, size_t nt, size_t start, size_t finish, vector<vector<vector<vector<vector<size_t>>>>>& matrix, vector<vector<vector<size_t>>>& bin_rules, vector<vector<vector<bool>>>& term_matrix, vector<vector<bool>>& term_rules, size_t count_vertex)
{
    if (start == finish) {
        path.push_back(start);
        return true;
    }

    for (size_t i = 0; i < term_matrix[start][finish].size(); ++i) {
        if (term_matrix[start][finish][i] && term_rules[nt][i]) {
            path.push_back(start);
            path.push_back(finish);
            return true;
        }
    }

    for (size_t rule_idx = 0; rule_idx < bin_rules[nt].size(); ++rule_idx) {
        size_t B = bin_rules[nt][rule_idx][0];
        size_t C = bin_rules[nt][rule_idx][1];

        for (size_t k = 0; k < count_vertex; ++k) {
            if (!matrix[B].back()[start][k].empty() &&
                !matrix[C].back()[k][finish].empty()) {

                vector<size_t> sub_path1;
                vector<size_t> sub_path2;

                if (extract_path(sub_path1, B, start, k, matrix, bin_rules, term_matrix, term_rules, count_vertex) &&
                    extract_path(sub_path2, C, k, finish, matrix, bin_rules, term_matrix, term_rules, count_vertex)) {

                    path.insert(path.end(), sub_path1.begin(), sub_path1.end());
                    path.insert(path.end(), sub_path2.begin() + 1, sub_path2.end());
                    return true;
                }
            }
        }
    }
    return false;
}