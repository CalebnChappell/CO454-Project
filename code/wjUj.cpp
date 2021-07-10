#include "DP.cpp"
#include <array>


int main() {
    std::array<int, 3> p_init = { 2, 3, 1 };
    std::vector<int> p(p_init.begin(), p_init.end());

    std::array<int, 3> d_init = { 3, 4, 4 };
    std::vector<int> d(d_init.begin(), d_init.end());

    std::array<int, 3> w_init = { 2, 1, 3 };
    std::vector<int> w(w_init.begin(), w_init.end());

    int n = w.size();

    DP dP = DP(w, d, p);
    
    int A = dP.IterationVariable();

    for (int j = 0; j < n; j++) {
        for (int a = 0; a <= A; a++) {
            dP.P_j(j, a);
        }
    }
    
    for (int j = 0; j < n; j++) {
        for (int a = 0; a <= A; a++) {
            std::cout << dP.TableValue(j, a) << ", ";
        }
        std::cout << '\n';
    }
    std::cout << "________FINISHED_______" << '\n';

    std::cout << dP.Opt();
};