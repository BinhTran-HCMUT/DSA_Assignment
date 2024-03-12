#include "ConcatStringList.h"

void tc1() {
    ConcatStringList s1("Hello,_world");
    // test length
    cout << "s1's length: " << s1.length() << endl;
    // test get
    cout << "char at index 2: " << s1.get(2) << endl;
    try {
        cout << "char at index 22: " << s1.get(22) << endl;
    }
    catch (out_of_range & ofr) {
        cout << "Exception out_of_range: " << ofr.what() << endl;
    }
    // test indexOf
    cout << "in s1, index of 'o': " << s1.indexOf('o') << endl;
    cout << "in s1, index of 'a': " << s1.indexOf('a') << endl;
    // test toString
    cout << "s1 toString: " << s1.toString() << endl;
}

void tc2() {
    ConcatStringList s1("Hello,");
    ConcatStringList s2("_this_is");
    ConcatStringList s3("_an_assignment");

    // test concat
    ConcatStringList s4 = s1.concat(s2);
    cout << "s4: " << s4.toString() << endl;

    ConcatStringList s5 = s1.concat(s2).concat(s3);
    cout << "s5: " << s5.toString() << endl;

    // test subString
    ConcatStringList s6 = s5.subString(5, 15);
    cout << "s6: " << s6.toString() << endl;
    
    // test reverse
    ConcatStringList s7 = s5.reverse();
    cout << "s7: " << s7.toString() << endl;
}

void tc3() {
    ConcatStringList * s1 = new ConcatStringList("Hello");
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList(s1->concat(*s2));

    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s1---" << endl;
    delete s1;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s3---" << endl;
    delete s3;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;

    cout << "---After deleting s2---" << endl;
    delete s2;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
}

void tc4() {
    ConcatStringList s1("Hello,_world");
    cout << (s1.subString(0, 12).subString(0, 11).subString(0, 10)).toString() << endl;
}

void special_tc(){
    ConcatStringList * s1 = new ConcatStringList("Hello");                            // SPECIAL TEST CASE
    ConcatStringList * s2 = new ConcatStringList("_world");
    ConcatStringList * s3 = new ConcatStringList("LOL");
    ConcatStringList * s4 = new ConcatStringList("HOHO");
    ConcatStringList * s5 = new ConcatStringList(s1->concat(*s2));
    ConcatStringList * s6 = new ConcatStringList(s5->reverse());
    ConcatStringList * s7 = new ConcatStringList(s6->concat(*s3));
    ConcatStringList * s8 = new ConcatStringList(s7->subString(1,14));
    ConcatStringList * s9 = new ConcatStringList(s8->concat(*s4));
    cout << endl;
    cout <<"--------SPECIAL--------" << endl;
    cout <<"s1: "<<s1->toString()<<endl;
    cout <<"s2: "<<s2->toString()<<endl;
    cout <<"s3: "<<s3->toString()<<endl;
    cout <<"s4: "<<s4->toString()<<endl;
    cout <<"s5: "<<s5->toString()<<endl;
    cout <<"s6: "<<s6->toString()<<endl;
    cout <<"s7: "<<s7->toString()<<endl;
    cout <<"s8: "<<s8->toString()<<endl;
    cout <<"s9: "<<s9->toString()<<endl;
    cout << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s1;
    cout << "--------After deleting s1--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s2;
    cout << "--------After deleting s2--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s4;
    cout << "--------After deleting s4--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s5;
    cout << "--------After deleting s5--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s6;
    cout << "--------After deleting s6--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s3;
    cout << "--------After deleting s3--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;    
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s7;
    cout << "--------After deleting s7--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s9;
    cout << "--------After deleting s9--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
    delete s8;
    cout << "--------After deleting s8--------" << endl;
    cout << ConcatStringList::refList.refCountsString() << endl;
    cout << ConcatStringList::delStrList.totalRefCountsString() << endl;
    cout <<"size of DelStrList: " <<ConcatStringList::delStrList.size() << endl;
    cout << endl;
}

int main() {
    tc1();
    tc2();
    tc3();
    tc4();
    special_tc();
    return 0;
}