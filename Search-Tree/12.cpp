nclude <iostream>
#include <cstdio>
#include <climits>
#include <vector>

#define pb push_back

typedef long long ll;

using namespace std;

ll maxlength = 0, minsum = LLONG_MAX, verval = LLONG_MAX;
ll lftval, rghtval;
vector<ll> answer;

struct vertex{
    vertex* leftson = nullptr;
    vertex* rightson = nullptr;
    vertex* anc = nullptr;
    ll value, height = 0, r0 = LLONG_MAX / 2, r1 = LLONG_MAX / 2, l0 = LLONG_MAX / 2, l1 = LLONG_MAX / 2;
    bool emp = false, leftH = false, leaf = false;

    vertex(ll value){
        this -> value = value;
    }

    void add(ll value){
        if (value < this->value){
            if (leftson == nullptr){
                leftson = new vertex(value);
                leftson -> anc = this;
            } else {
                leftson -> add(value);
            }
        } else if (value > this->value){
            if (rightson == nullptr){
                rightson = new vertex(value);
                rightson -> anc = this;
            } else {
                rightson -> add(value);
            }
        } else {
            return;
        }
    }

    vertex* find(ll val){
        if (val < value){
            return leftson -> find(val);
        } else if (val > value){
            return rightson -> find(val);
        } else {
            return this;
        }
    }

    void findMax(){
        ll l = 0, r = 0, a;
        if (leftson != nullptr){
            leftson -> findMax();
            l = leftson -> height;
        }
        if (rightson != nullptr){
            rightson -> findMax();
            r = rightson -> height;
        }
        a = l + r;
        if (leftson != nullptr && rightson != nullptr){
            ++a;
        }
        if ((leftson == nullptr || rightson == nullptr) && (leftson != nullptr || rightson != nullptr)){
            ++a;
        }
        ll versum = min(r0 + l1, r1 + l0);
        if (a > maxlength){
            maxlength = a;
            verval = value;
            minsum = versum;
        } else if (a == maxlength && versum < minsum){
            minsum = versum;
            verval = value;
        } else if (a == maxlength && versum == minsum && value < verval){
            verval = value;
        }
    }

    ll findVal(){
        answer.clear();
        if (value != lftval){
            leftson -> findVal(true);
        }
        if (value != rghtval){
            answer.pb(value);
            rightson -> findVal(false);
        } else {
            answer.pb(value);
        }
        return answer[answer.size() / 2];
    }

    void findVal(bool left){
        if (left && value == lftval){
            answer.pb(value);
            return;
        } else if (!left && value == rghtval){
            answer.pb(value);
            return;
        }
        if (leftH){
            leftson -> findVal(left);
            answer.pb(value);
        } else {
            answer.pb(value);
            rightson -> findVal(left);
        }
    }

    void del(){
        if (leftson != nullptr && leftson -> height == 0){
            delete leftson;
        } else if (leftson != nullptr){
            leftson -> del();
            delete leftson;
        }
        if (rightson != nullptr && rightson -> height == 0){
            delete rightson;
        } else if (rightson != nullptr){
            rightson -> del();
            delete rightson;
        }
    }

    void init(){
        ll l = -1, r = -1;
        if (leftson == nullptr && rightson == nullptr){
            l0 = value;
            r0 = value;
            height = 0;
            leaf = true;
            return;
        }
        if (leftson != nullptr){
            leftson -> init();
            if (leftson -> leaf){
                l1 = value;
                l0 = leftson -> value;
            } else {
                if (leftson -> leftH){
                    l0 = leftson -> l0;
                    l1 = leftson -> l1;
                } else {
                    l0 = leftson -> r0;
                    l1 = leftson -> r1;
                }
            }
            l = leftson -> height;
        } else {
            if (leftson == nullptr && rightson == nullptr){
                l0 = value;
            } else {
                l1 = value;
            }
        }
        if (rightson != nullptr){
            rightson -> init();
            if (rightson -> leaf){
                r1 = value;
                r0 = rightson -> value;
            } else {
                if (rightson -> leftH){
                    r0 = rightson -> l0;
                    r1 = rightson -> l1;
                } else {
                    r0 = rightson -> r0;
                    r1 = rightson -> r1;
                }
            }
            r = rightson -> height;
        } else {
            if (leftson == nullptr && rightson == nullptr){
                r0 = value;
            } else {
                r1 = value;
            }
        }
        height = max(l, r) + 1;
        if (l >= r){
            leftH = true;
        } else {
            leftH = false;
        }
    }

    void traversal(){
        if (this == nullptr || emp == true) {
            return;
        }
        cout << value << endl;
        if (leftson != nullptr){
            leftson -> traversal();
        }
        if (rightson != nullptr){
            rightson -> traversal();
        }
    }

    vertex* left(){
        if (leftson == nullptr){
            return this;
        } else {
            return leftson -> left();
        }
    }

    void erase(ll value, bool left = true){
        if (value < this -> value){
            leftson -> erase(value, true);
        } else if (value > this -> value){
            rightson -> erase(value, false);
        } else {
            vertex* ver = this;
            if (leftson == nullptr && rightson == nullptr){
                emp = true;
            } else if (leftson == nullptr){
                ver -> value = rightson -> value;
                ver -> leftson = rightson -> leftson;
                ver -> rightson = rightson -> rightson;
            } else if (rightson == nullptr){
                ver -> value = leftson -> value;
                ver -> rightson = leftson -> rightson;
                ver -> leftson = leftson -> leftson;
            } else {
                vertex* vert = rightson -> left();
                vertex* ver1 = vert -> anc;
                if (ver1 == this){
                    ver -> value = ver -> rightson -> value;
                    ver -> rightson = ver -> rightson -> rightson;
                } else {
                    ver1 -> leftson = vert -> rightson;
                    vert -> leftson = this -> leftson;
                    vert -> rightson = this -> rightson;
                    if (left && anc != nullptr) {
                        anc -> leftson = vert;
                    } else if (anc != nullptr) {
                        anc -> rightson = vert;
                    } else {
                        this -> value = vert -> value;
                        rightson = vert -> rightson;
                        leftson = vert -> leftson;
                    }
                }
            }
        }
    }
    void print(){
        cout << value << " " << height << " " << l0 << " " << l1 << " " << r0 << " " << r1 << endl;
        if (leftson != nullptr){
            leftson -> print();
        }
        if (rightson != nullptr){
            rightson -> print();
        }
    }
};

int main(){
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    freopen("tst.in","r",stdin);
    freopen("tst.out","w",stdout);
    ll a;
    vertex* root = nullptr;
    while (cin >> a){
        if (root == nullptr){
            root = new vertex(a);
        } else {
            root -> add(a);
        }
    }
    root -> init();
    root -> findMax();
    if (maxlength % 2 == 1 || maxlength == 0){
        root -> traversal();
        return 0;
    } else {
        vertex* ver = root -> find(verval);
        ll val1 = ver -> r0 + ver -> l1, val2 = ver -> r1 + ver -> l0;
        if (val1 < val2){
            lftval = ver -> l1;
            rghtval = ver -> r0;
            root -> erase(ver -> findVal());
        } else if (val2 < val1){
            lftval = ver -> l0;
            rghtval = ver -> r1;
            root -> erase(ver -> findVal());
        } else {
            ll value1, value2;
            lftval = ver -> l1;
            rghtval = ver -> r0;
            value1 = ver -> findVal();
            lftval = ver -> l0;
            rghtval = ver -> r1;
            value2 = ver -> findVal();
            if (value1 == value2){
                root -> erase(ver -> findVal());
            }
        }
        root -> traversal();
    }
    return 0;
}
