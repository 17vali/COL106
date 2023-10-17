/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"

struct arr {
    int* arr;
    int size;
};

struct two_arr {
    int* arr1;
    int* arr2;
    int size1;
    int size2;
};

arr strip_zeroes(arr a) {
    int i = a.size-1;
    while(i > 0 && a.arr[i] == 0) i--;
    int* res = new int[i+1];
    for(int j = 0; j <= i; j++) {
        res[j] = a.arr[j];
    }
    return {res, i+1};
}

int compare(int* a, int* b, int asize, int bsize) {
    arr l = strip_zeroes({a, asize});
    arr m = strip_zeroes({b, bsize});
    int* x = l.arr;
    int* y = m.arr;
    int xsize = l.size;
    int ysize = m.size;
    int ans = 0;
    if(xsize > ysize) ans = 1;
    else if(xsize < ysize) ans = -1;
    else {
        for(int i = xsize-1; i >= 0; i--) {
            if(x[i] > y[i]) {
                ans = 1;
                break;
            }
            if(x[i] < y[i]) {
                ans = -1;
                break;
            }
        }
    }
    delete[] x;
    delete[] y;
    return ans;
}

arr add_arrays(int* a, int* b, int asize, int bsize) {
    if (asize < bsize) {
        int* temp = a;
        a = b;
        b = temp;
    }

    int i = max(asize, bsize);
    int j = min(asize, bsize);
    int l = -1, r = -1;
    int sum = 0;
    int* res = new int[i];
    if (j == 1) {
        l++;
        sum = (a[l] + b[0]);
        res[l] = sum%10;
    } else {
        while (r < j-1) {
            l++;
            r++;
            sum = (a[l] + b[r] + sum/10);
            res[l] = sum%10;
        }
    }
    bool c = (sum/10 != 0);
    while (l < i-1 && c) {
        l++;
        c = (!(res[l] = (a[l] + 1)%10));
    }

    while (l < i-1) {
        l++;
        res[l] = a[l];
    }

    if (c) {
        int* big = new int[i + 1];
        for(int j = 0; j < i; j++) {
            big[j] = res[j];
        }
        big[i] = 1;
        delete[] res;
        return {big, i+1};
    }
    return {res, i};
}

arr sub_arrays(int* a, int* b, int asize, int bsize) {
    int l = -1, r = -1;
    int diff = 0;
    int* res = new int[asize];

    while (r < bsize-1) {
        l++;
        r++;
        diff = a[l] - b[r] - (diff < 0);
        res[l] = diff + 10*(diff < 0);
    }

    bool borr = (diff < 0);
    while (l < asize-1 && borr) {
        l++;
        borr = ((res[l] = (a[l] - 1) + 10*(a[l] == 0)) == 9); /*******/

    }

    while (l < asize-1) {
        l++;
        res[l] = a[l];
    }

    return {res, asize};
}

arr mul_arrays(int* a, int*b, int asize, int bsize) {
    int* res = new int[asize+bsize];

    long c = 0;
    for (int r=0; r < bsize; r++) {
        long prod = b[r]*a[0] + c;
        res[r] = prod % 10;
        c= prod / 10 ;
    }
    res[bsize] = c;

    for (int l = 1; l<asize; l++) {
        c = 0;
        for (int r = 0; r < bsize; r++) {
            long prod = b[r]*a[l] + res[r+l] + c;
            res[r+l] = prod % 10;
            c = prod / 10;
        }
        res[bsize + l] = c;
    }
    return {res, asize+bsize};
}

two_arr div_arrays(int* a, int* b, int asize, int bsize) {
    int* res = new int[asize-bsize+1];
    int* temp = new int[bsize+1];
    for(int i = 0; i < bsize; i++) {
        temp[i] = a[asize-bsize+i];
    }
    temp[bsize] = 0;
    int i = asize-bsize;
    while(i >= 0) {
        int q = 0;
        while(compare(temp, b, bsize+1, bsize) >= 0) {
            arr st = sub_arrays(temp, b, bsize+1, bsize);
            delete[] temp;
            temp = st.arr;
            q++;
        }
        res[i] = q;
        for(int j = bsize; j > 0; j--) {
            temp[j] = temp[j-1];
        }
        if(i>0) temp[0] = a[i-1];
        i--;
    }
    int* rem = new int[bsize];
    for(int i = 0; i < bsize; i++) {
        rem[i] = temp[i+1];
    }

    delete[] temp;
    return {res, rem, asize-bsize+1, bsize};
}

UnlimitedInt::UnlimitedInt() {
    size = 0;
    sign = 1;
    capacity = 0;
    unlimited_int = nullptr;
}

UnlimitedInt::UnlimitedInt(string s) {
    if (s == "0") {
        sign = 0;
    } else if (s[0] == '-') {
        sign = -1;
        s = s.substr(1);
    } else if (s[0] == '+') {
        sign = 1;
        s = s.substr(1);
    } else {
        sign = 1;
    }
    size = s.length();
    capacity = size;
    unlimited_int = new int[size];
    for (int i = 0; i < size; i++) {
        unlimited_int[i] = s[size - i - 1] - '0';
    }
}

UnlimitedInt::UnlimitedInt(int i) {
    if (i == 0) {
        sign = 0;
        size = 1;
    } else if (i < 0) {
        sign = -1;
        i = -i;
        size = 0;
    } else {
        sign = 1;
        size = 0;
    }
    int temp = i;
    while (temp > 0) {
        temp /= 10;
        size++;
    }
    capacity = size;
    unlimited_int = new int[size];
    for (int j = 0; j < size; j++) {
        unlimited_int[j] = i % 10;
        i /= 10;
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    unlimited_int = new int[sz];
    for (int i = 0; i < sz; i++) {
        unlimited_int[i] = ulimited_int[i];
    }
    capacity = cap;
    sign = sgn;
    size = sz;
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

int UnlimitedInt::get_capacity() {
    return capacity;
}

string UnlimitedInt::to_string() {
    string s = "";
    if (sign == -1) {
        s += "-";
    }
    for (int i = size - 1; i >= 0; i--) {
        s += (char) (unlimited_int[i] + '0');
    }
    return s;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->sign == 0) return new UnlimitedInt(i2->unlimited_int, i2->capacity, i2->sign, i2->size);
    if (i2->sign == 0) return new UnlimitedInt(i1->unlimited_int, i1->capacity, i1->sign, i1->size);

    if(i1->sign == i2->sign) {
        arr res = add_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
        UnlimitedInt* ans = new UnlimitedInt(res.arr, res.size, i1->sign, res.size);
        delete[] res.arr;
        return ans;
    }

    int comp = compare(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    if(comp == 0) return new UnlimitedInt(0);

    arr res;
    if(comp > 0) {
        res = sub_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    } else {
        res = sub_arrays(i2->unlimited_int, i1->unlimited_int, i2->size, i1->size);
    }
    arr st = strip_zeroes(res);
    delete[] res.arr;
    UnlimitedInt* ans = new UnlimitedInt(st.arr, st.size, (comp > 0) ? i1->sign : i2->sign, st.size);
    delete[] st.arr;
    return ans;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->sign == 0) return new UnlimitedInt(i2->unlimited_int, i2->capacity, -i2->sign, i2->size);
    if (i2->sign == 0) return new UnlimitedInt(i1->unlimited_int, i1->capacity, i1->sign, i1->size);

    if(i1->sign != i2->sign) {
        arr res = add_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
        UnlimitedInt* ans = new UnlimitedInt(res.arr, res.size, i1->sign, res.size);
        delete[] res.arr;
        return ans;
    }

    int comp = compare(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    if(comp == 0) return new UnlimitedInt(0);

    arr res;
    if(comp > 0) {
        res = sub_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    } else {
        res = sub_arrays(i2->unlimited_int, i1->unlimited_int, i2->size, i1->size);
    }
    arr st = strip_zeroes(res);
    delete[] res.arr;
    UnlimitedInt* ans = new UnlimitedInt(st.arr, st.size, (comp > 0) ? i1->sign : -i2->sign, st.size);
    delete[] st.arr;
    return ans;
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->sign==0 || i2->sign==0) return new UnlimitedInt(0);

    arr res = mul_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    arr st = strip_zeroes(res);
    delete[] res.arr;
    UnlimitedInt* ans = new UnlimitedInt(st.arr, st.size, (i1->sign == i2->sign) ? 1 : -1, st.size);
    delete[] st.arr;
    return ans;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->sign==0) return new UnlimitedInt(0);

    if(compare(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size) < 0) {
        if(i1->sign==i2->sign) return new UnlimitedInt(0);
        else return new UnlimitedInt(-1);
    }

    two_arr res = div_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    arr q = strip_zeroes({res.arr1, res.size1});
    arr rem = strip_zeroes({res.arr2, res.size2});
    delete[] res.arr1;
    delete[] res.arr2;
    if((i1->sign!=i2->sign && rem.arr[rem.size-1] != 0)) {
        arr st = add_arrays(q.arr, new int[1]{1}, q.size, 1);
        delete[] q.arr;
        q = st;
    }
    delete[] rem.arr;
    UnlimitedInt* ans= new UnlimitedInt(q.arr, q.size, (i1->sign == i2->sign) ? 1 : -1, q.size);
    delete[] q.arr;
    return ans;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->sign==0) return new UnlimitedInt(0);

    two_arr res = div_arrays(i1->unlimited_int, i2->unlimited_int, i1->size, i2->size);
    arr rem = strip_zeroes({res.arr2, res.size2});
    delete[] res.arr1;
    delete[] res.arr2;

    if(rem.arr[rem.size-1] == 0) {
        delete[] rem.arr;
        return new UnlimitedInt(0);
    }
    if(i1->sign!=i2->sign) {
        arr st = sub_arrays(i2->unlimited_int, rem.arr, i2->size, rem.size);
        delete[] rem.arr;
        rem = st;
    }
    UnlimitedInt* ans = new UnlimitedInt(rem.arr, rem.size, (i2->sign > 0)? 1:-1, rem.size);
    delete[] rem.arr;
    return ans;
}
