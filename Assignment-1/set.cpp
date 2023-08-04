#include <iostream>
#include <vector>
using namespace std;

class Set {
public:
	vector<int> set;
	int size;

	Set() {
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

	int Union(Set s) { 
		int i1 = 0, i2 = 0;
		while(i1<size && i2<s.size) {
			if(set.at(i1) == s.set.at(i2)) {
				i1++;
				i2++;
			} else if(set.at(i1) < s.set.at(i2)) {
				i1++;
			} else {
				set.insert(set.begin()+i1, s.set.at(i2));
				size++;
				i1++;
				i2++;
			}
		}
		while(i2 < s.size) {
			set.push_back(s.set.at(i2));
			size++;
        	i2++;
		}

		return size;
	}

	int Intersection(Set s) {
		int i1 = 0, i2 = 0;
		while(i1<size && i2<s.size) {
			if(set.at(i1) == s.set.at(i2)) {
				i1++;
				i2++;
			} else if(set.at(i1) < s.set.at(i2)) {
				set.erase(set.begin()+i1);
				size--;
			} else {
				i2++;
			}
		}
		set.erase(set.begin()+i1, set.end());
		size=i1;

		return size;
	}

	int Size() {
		return size;
	}

	int Difference(Set s) {
		int i1 = 0, i2 = 0;
		while(i1<size && i2<s.size) {
			if(set.at(i1) == s.set.at(i2)) {
				set.erase(set.begin()+i1);
				i2++;
				size--;
			} else if(set.at(i1) < s.set.at(i2)) {
				i1++;
			} else {
				i2++;
			}
		}
		return size;
	}

	int SymmetricDifference(Set s) {
		int i1 = 0, i2 = 0;
		while(i1<size && i2<s.size) {
			if(set.at(i1) == s.set.at(i2)) {
				set.erase(set.begin()+i1);
				i2++;
				size--;
			} else if(set.at(i1) < s.set.at(i2)) {
				i1++;
			} else {
				set.insert(set.begin()+i1, s.set.at(i2));
				size++;
				i1++;
				i2++;
			}
		}
		return size;
	}

	void Print() {
		for(int i = 0; i<size; i++) {
			if(i!=0) {
				cout << ",";
			}
			cout << set.at(i);
		}
	}
};

int search(vector<int> a, int data) {
	for(int i = 0; i<a.size(); i++) {
		if(a.at(i) == data) {
			return i;
		}
	}
	return -1;
}

int main() {
	int cmd, a, b;
	vector<int> indexes;
	vector<Set> sets;
	while(cin >> cmd) {
		if(cmd == 6 || cmd == 9) {
			cin >> a;
			int c = search(indexes, a);
			if(c == -1) {
				indexes.push_back(a);
				sets.push_back(Set());
				c = indexes.size()-1;
			}
			if(cmd == 6)
				cout << sets.at(c).Size();
			else
				sets.at(c).Print();
		} else {
			cin >> a >> b;
			if(cmd <= 3) {
				int c = search(indexes, a);
				if(cmd == 1) {
					if(c == -1) {
						indexes.push_back(a);
						sets.push_back(Set());
						c = indexes.size()-1;
					}
					cout << sets.at(c).Insert(b);
				} else if(cmd == 2) {
					if(c == -1) {
						cout << c;
					} else {
						cout << sets.at(c).Delete(b);
					}
				} else {
					if(c == -1) {
						cout << c;
					} else {
						cout << sets.at(c).BelongsTo(b);
					}
				}
			} else {
				int c = search(indexes, a);
				int d = search(indexes, b);
				if(c == -1) {
					indexes.push_back(a);
					sets.push_back(Set());
					c = indexes.size()-1;
				}
				if(d == -1) {
					indexes.push_back(b);
					sets.push_back(Set());
					d = indexes.size()-1;
				}
				if(cmd == 4)
					cout << sets.at(c).Union(sets.at(d));
				else if(cmd == 5)
					cout << sets.at(c).Intersection(sets.at(d));
				else if(cmd == 7)
					cout << sets.at(c).Difference(sets.at(d));
				else
					cout << sets.at(c).SymmetricDifference(sets.at(d));
			}
		}
		cout << endl;
	}
}