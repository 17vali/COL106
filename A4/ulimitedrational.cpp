/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

struct arr {
    int* arr;
    int size;
};

arr strip_zeroes2(arr a) {
    int i = a.size-1;
    while(i > 0 && a.arr[i] == 0) i--;
    int* res = new int[i+1];
    for(int j = 0; j <= i; j++) {
        res[j] = a.arr[j];
    }
    return {res, i+1};
}

int compare2(int* a, int* b, int asize, int bsize) {
    arr l = strip_zeroes2({a, asize});
    arr m = strip_zeroes2({b, bsize});
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

UnlimitedInt* gcd(UnlimitedInt* a, UnlimitedInt* b) {
    if(a->get_sign() == 0) return new UnlimitedInt(b->get_array(), b->get_size(), b->get_sign(), b->get_size());

    UnlimitedInt* x = new UnlimitedInt(a->get_array(), a->get_size(), a->get_sign(), a->get_size());
    UnlimitedInt* y = new UnlimitedInt(b->get_array(), b->get_size(), b->get_sign(), b->get_size());

    while(y->get_sign() != 0) {
        UnlimitedInt* t = new UnlimitedInt(x->get_array(), x->get_size(), x->get_sign(), x->get_size());
        delete x;
        x = y;
        y = UnlimitedInt::mod(t, y);
        delete t;
    }
    delete y;
    UnlimitedInt* ans = new UnlimitedInt(x->get_array(), x->get_size(), 1, x->get_size());
    delete x;
    return ans;
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt();
    q = new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if(den->get_sign() == 0) {
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    } else {
        int comp = compare2(num->get_array(), den->get_array(), num->get_size(), den->get_size());
        UnlimitedInt* g;
        if(comp == 0) {
            g = new UnlimitedInt(num->get_array(), num->get_size(), num->get_sign(), num->get_size());
        } else if(comp < 0) {
            g = gcd(den, num);
        } else {
            g = gcd(num, den);
        }
        p = UnlimitedInt::div(num, g);
        q = UnlimitedInt::div(den, g);
        delete g;
    }
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->to_string();
}

string UnlimitedRational::get_q_str() {
    return q->to_string();
}

string UnlimitedRational::get_frac_str() {
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    UnlimitedInt* l = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* r = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* p = UnlimitedInt::add(l, r);
    delete l;
    delete r;
    UnlimitedInt* q = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* res = new UnlimitedRational(p, q);
    delete p;
    delete q;
    return res;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    UnlimitedInt* l = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* r = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* p = UnlimitedInt::sub(l, r);
    delete l;
    delete r;
    UnlimitedInt* q = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* res = new UnlimitedRational(p, q);
    delete p;
    delete q;
    return res;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    UnlimitedInt* p = UnlimitedInt::mul(p1, p2);
    UnlimitedInt* q = UnlimitedInt::mul(q1, q2);
    UnlimitedRational* res = new UnlimitedRational(p, q);
    delete p;
    delete q;
    return res;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1->get_p();
    UnlimitedInt* q1 = i1->get_q();
    UnlimitedInt* p2 = i2->get_p();
    UnlimitedInt* q2 = i2->get_q();
    UnlimitedInt* p = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* q = UnlimitedInt::mul(q1, p2);
    UnlimitedRational* res = new UnlimitedRational(p, q);
    delete p;
    delete q;
    return res;
}