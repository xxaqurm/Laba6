/* Вариант 2 */
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>

using namespace std;
typedef long long ll;

ll calculateTiles(ll n, ll m, ll k) {
    /* Находит количество плиток, которое нужно для дорожки ширины k */
    return n * m - (n - 2 * k) * (m - 2 * k);
}

int main() {
    cin.exceptions(ios::failbit);

    ll n, m, t;
    while (true) {
        try {
            cout << "Введите свои n, m, t: ";
            cin >> n >> m >> t;
            break;
        } catch (const ios::failure& e) {
            cout << "Ошибка (" << e.what() << "): Введите целые числа." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    ll maxWidth = 0;
    ll left = 1;
    ll right = min(n, m) / 2;

    while (left <= right) {  // Бин поиск для определения максимально возможной ширины пути
        ll mid = left + (right - left) / 2;
        ll tilesNeeded = calculateTiles(n, m, mid);
        
        if (tilesNeeded <= t) {
            maxWidth = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    cout << maxWidth << endl;
    
    return 0;
}
