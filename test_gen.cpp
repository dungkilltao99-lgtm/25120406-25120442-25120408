#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <filesystem>

using namespace std;

void my_reverse(string &s) {
    int l = 0, r = s.length() - 1;
    while (l < r) {
        char temp = s[l];
        s[l] = s[r];
        s[r] = temp;
        l++; r--;
    }
}

void my_swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

unsigned long long my_seed = 987654321;
int my_rand() {
    my_seed = (my_seed * 1103515245 + 12345) % 2147483648;
    return my_seed % 26;
}

string toBase26(int val, int length) {
    string res = "";
    for (int i = 0; i < length; i++) {
        res += (char)('a' + (val % 26));
        val /= 26;
    }
    my_reverse(res);
    return res;
}

void createTest(string filename, const vector<int>& data) {
    ofstream out(filename);
    out << data.size() << "\n";
    for (int i = 0; i < data.size(); i++) {
        out << data[i] << "\n";
    }
    out.close();
    cout << "[OK] Da tao thanh cong: " << filename << "\n";
}

void createTest(string filename, const vector<string>& data) {
    ofstream out(filename);
    out << data.size() << "\n";
    for (int i = 0; i < data.size(); i++) {
        out << data[i] << "\n";
    }
    out.close();
    cout << "[OK] Da tao thanh cong: " << filename << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return 1;
    }

    string type = argv[1];
    int target_id = stoi(argv[2]);

    if (type == "int") {
        filesystem::create_directory("int");
        int MAX_N = 100000;
        vector<int> a;
        mt19937 rng(8888);

        a.assign(MAX_N, 0);
        for (int i = 0; i < MAX_N; i++) {
            a[i] = i;
        }
        for (int i = 2; i < MAX_N; i++) {
            swap(a[i], a[i / 2]);
        }
        for (int i = 0; i < MAX_N; i++) {
            if (a[i] % 2 == 0) a[i] = a[i] * 10000;
            else a[i] = -a[i] * 10000;
        }
        if (target_id == 1) createTest("int/test001.in", a);

        a.clear();
        int edge_cases[5] = {0, -1, 1, 2147483647, -2147483648LL};
        uniform_int_distribution<int> dist_edges(0, 4);
        for (int i = 0; i < MAX_N; i++) {
            a.push_back(edge_cases[dist_edges(rng)]);
        }
        if (target_id == 2) createTest("int/test002.in", a);

        a.clear();
        uniform_int_distribution<long long> dist_full(-2147483648LL, 2147483647LL);
        for (int i = 0; i < MAX_N; i++) {
            a.push_back((int)dist_full(rng));
        }
        if (target_id == 3) createTest("int/test003.in", a);

        a.clear();
        uniform_int_distribution<long long> dist_large(1000000000LL, 2147483647LL);
        for (int i = 0; i < MAX_N; i++) {
            int val = (int)dist_large(rng);
            a.push_back(-val);
        }
        if (target_id == 4) createTest("int/test004.in", a);

        a.clear();
        int pattern1 = 0xAAAAAAAA;
        int pattern2 = 0x55555555;
        for (int i = 0; i < MAX_N; i++) {
            if (i % 2 == 0) {
                a.push_back(pattern1 ^ (rng() % 100));
            } else {
                a.push_back(pattern2 ^ (rng() % 100));
            }
        }
        if (target_id == 5) createTest("int/test005.in", a);
    }
    else if (type == "strlexi") {
        filesystem::create_directory("strlexi");
        int MAX_N = 100000;
        vector<string> a;

        a.assign(MAX_N, "");
        string prefix1(95, 'a');
        int val1 = 0;
        for (int i = 0; i <= MAX_N / 2; i++) {
            a[i] = prefix1 + toBase26(val1++, 5);
            if (MAX_N - 1 - i > i) {
                a[MAX_N - 1 - i] = prefix1 + toBase26(val1++, 5);
            }
        }
        if (target_id == 1) createTest("strlexi/test001.in", a);

        a.clear();
        string base(99, 'z');
        string pattern[] = {base + "a", base + "z", base + "b", base + "y"};
        for (int i = 0; i < MAX_N; i++) {
            a.push_back(pattern[i % 4]);
        }
        if (target_id == 2) createTest("strlexi/test002.in", a);

        a.clear();
        int chunk_size = 32;
        for (int i = 0; i < MAX_N; i += chunk_size) {
            string chunk_prefix = toBase26(i, 5) + string(94, 'm');
            for (int j = 0; j < chunk_size && i + j < MAX_N; ++j) {
                a.push_back(chunk_prefix + (char)('z' - j));
            }
        }
        if (target_id == 3) createTest("strlexi/test003.in", a);

        a.clear();
        for (int i = 0; i < MAX_N; i++) {
            string s = "";
            for (int j = 0; j < 100; j++) {
                s += char('a' + my_rand());
            }
            a.push_back(s);
        }
        if (target_id == 4) createTest("strlexi/test004.in", a);

        a.clear();
        string prefix5(95, 'x');
        for (int i = MAX_N - 1; i >= 0; i--) {
            a.push_back(prefix5 + toBase26(i, 5));
        }
        if (target_id == 5) createTest("strlexi/test005.in", a);
    }
    else if (type == "strlenlexi") {
        filesystem::create_directory("strlenlexi");
        int MAX_N = 10000;
        vector<string> a;

        a.clear();
        string clone_str(100, 'x');
        for (int i = 0; i < MAX_N; i++) {
            a.push_back(clone_str);
        }
        if (target_id == 1) createTest("strlenlexi/test001.in", a);

        a.clear();
        a.resize(MAX_N);
        vector<int> perm(MAX_N);
        for (int i = 0; i < MAX_N; i++) perm[i] = i;
        for (int i = 2; i < MAX_N; i++) my_swap(perm[i], perm[i / 2]);

        string prefix(95, 'a');
        for (int i = 0; i < MAX_N; i++) {
            a[i] = prefix + toBase26(perm[i], 5);
        }
        if (target_id == 2) createTest("strlenlexi/test002.in", a);

        a.clear();
        for (int len = 100; len >= 10; len--) {
            int count = MAX_N / 91;
            char c = 'a' + ((100 - len) % 26);
            string s(len, c);
            for(int k = 0; k < count; k++) {
                a.push_back(s);
            }
        }
        while (a.size() < MAX_N) {
            a.push_back(string(10, 'z'));
        }
        if (target_id == 3) createTest("strlenlexi/test003.in", a);

        a.clear();
        int chunk_size = 32;
        for (int i = 0; i < MAX_N; i += chunk_size) {
            string chunk_prefix = toBase26(i, 5) + string(94, 'm');
            for (int j = 0; j < chunk_size && i + j < MAX_N; ++j) {
                a.push_back(chunk_prefix + (char)('z' - j));
            }
        }
        if (target_id == 4) createTest("strlenlexi/test004.in", a);

        a.clear();
        string long_str(100, 'z');
        string short_str(10, 'a');
        for (int i = 0; i < MAX_N / 2; i++) {
            a.push_back(long_str);
            a.push_back(short_str);
        }
        if (target_id == 5) createTest("strlenlexi/test005.in", a);
    }

    return 0;
}