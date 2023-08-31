#include <iostream>
#include <vector>
using namespace std;

class SET {
public:
	vector<int> set;
	int size;

	SET() {
		size = 0;
	}

	int Insert(int data) {
		int left = 0, right = size - 1;
		while (left <= right) {
			if(right-left <= 1) {
				if(set[left] == data || set[right] == data) return size;
				else if(set[left] < data && set[right] > data) {
					set.insert(set.begin()+right, data);
					return ++size;
				}
				else if(set[left] > data) {
					set.insert(set.begin()+left, data);
					return ++size;
				}
				else {
					set.insert(set.begin()+right+1, data);
					return ++size;
				}
			}
			int mid = (left + right) / 2;
			if (set[mid] == data) return size;
			else if (set[mid] < data) left = mid + 1;
			else right = mid - 1;
		}
		if(size == 0) {
			set.push_back(data);
			return ++size;
		} else {
			return size;
		}
	}

	int Delete(int data) {
		int left = 0, right = size - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (set[mid] == data) {
				set.erase(set.begin()+mid);
				return --size;
			}
			else if (set[mid] < data) left = mid + 1;
			else right = mid - 1;
		}
		return size;
	}

	bool BelongsTo(int data) {
		int left = 0, right = size - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (set[mid] == data) {
				return true;
			}
			else if (set[mid] < data) left = mid + 1;
			else right = mid - 1;
		}
		return false;
	}

	int Union(SET s) { 
		int i1 = 0, i2 = 0;
		vector<int> temp;
		while(i1<size && i2<s.size) {
			if(set[i1] == s.set[i2]) {
				temp.push_back(set[i1]);
				i1++;
				i2++;
			} else if(set[i1] < s.set[i2]) {
				temp.push_back(set[i1]);
				i1++;
			} else {
				temp.push_back(s.set[i2]);
				i2++;
			}
		}
		while(i1 < size) {
			temp.push_back(set[i1]);
			i1++;
		}
		while(i2 < s.size) {
			temp.push_back(s.set[i2]);
        	i2++;
		}

		set = move(temp);
		size = set.size();
		return size;
	}

	int Intersection(SET s) {
		int i1 = 0, i2 = 0;
		vector<int> temp;
		while(i1<size && i2<s.size) {
			if(set[i1] == s.set[i2]) {
				temp.push_back(set[i1]);
				i1++;
				i2++;
			} else if(set[i1] < s.set[i2]) {
				i1++;
			} else {
				i2++;
			}
		}

		set = move(temp);
		size = set.size();
		return size;
	}

	/*int Size() {
		return size;
	}*/

	int Difference(SET s) {
		int i1 = 0, i2 = 0;
		vector<int> temp;
		while(i1<size && i2<s.size) {
			if(set[i1] == s.set[i2]) {
				i1++;
				i2++;
			} else if(set[i1] < s.set[i2]) {
				temp.push_back(set[i1]);
				i1++;
			} else {
				i2++;
			}
		}
		while(i1 < size) {
			temp.push_back(set[i1]);
			i1++;
		}

		set = move(temp);
		size = set.size();
		return size;
	}

	int SymmetricDifference(SET s) {
		int i1 = 0, i2 = 0;
		vector<int> temp;
		while(i1<size && i2<s.size) {
			if(set[i1] == s.set[i2]) {
				i1++;
				i2++;
			} else if(set[i1] < s.set[i2]) {
				temp.push_back(set[i1]);
				i1++;
			} else {
				temp.push_back(s.set[i2]);
				i2++;
			}
		}
		while(i1 < size) {
			temp.push_back(set[i1]);
			i1++;
		}
		while(i2 < s.size) {
			temp.push_back(s.set[i2]);
        	i2++;
		}
		set = move(temp);
		size = set.size();
		return size;
	}

	void Print() {
		for(int i = 0; i<size; i++) {
			if(i!=0) {
				cout << ",";
			}
			cout << set[i];
		}
	}
};

bool fastscan(int &number)
{
    bool neg = false;
    register int c;
    number = 0;
    c = getchar();
    if(c == EOF) {
    	return false;
    }
    if (c=='-')
    {
        neg = true;
        c = getchar();
    }
    while(c>='0' && c<='9') {
        number = number * 10 + c - '0';
        c = getchar();
    }
    if (neg) {
    	number *= -1;
    }
    return true;
}

int main() {
	int cmd, a, b;
	vector<SET> sets;
	while(cin>>cmd) {
		if(cmd == 6 || cmd == 9) {
			cin>>a;
			if(cmd == 6) {
				if(a == sets.size()) {
					sets.push_back(SET());
				}
				cout << sets[a].size;
			}
			else {
				if(a < sets.size()) {
					sets[a].Print();
				}
			}
		} else {
			cin>>a;
			cin>>b;
			if(cmd <= 3) {
				if(cmd == 1) {
					if(a == sets.size()) {
						sets.push_back(SET());
					}
					cout << sets[a].Insert(b);
				} else {
					if(a >= sets.size()) {
						cout << -1;
					} else if (cmd == 2) {
						cout << sets[a].Delete(b);
					} else {
						cout << sets[a].BelongsTo(b);
					}
				}
			} else {
				if(a<b) {
					if(a == sets.size()) {
						sets.push_back(SET());
					}
					if(b == sets.size()) {
						sets.push_back(SET());
					}
				} else {
					if(b == sets.size()) {
						sets.push_back(SET());
					}
					if(a == sets.size()) {
						sets.push_back(SET());
					}
				}
				
				if(cmd == 4)
					cout << sets[a].Union(sets[b]);
				else if(cmd == 5)
					cout << sets[a].Intersection(sets[b]);
				else if(cmd == 7)
					cout << sets[a].Difference(sets[b]);
				else		
					cout << sets[a].SymmetricDifference(sets[b]);
			}
		}
		cout << '\n';
	}
	return 0;
}