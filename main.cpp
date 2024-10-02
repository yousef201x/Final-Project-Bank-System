#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;

    double mana{}, minMana{};
    int change;

    for (int i = 0; i < n; i++) {
        cin >> change;

        mana += change;

        if (mana < 0) {
            minMana += -mana;
            mana = 0;
        }
    }

    cout << minMana;
}
