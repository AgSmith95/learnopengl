
template <typename T>
struct Point2 {
    T array[2];
    // overloading operator[], because:
    // error: ISO C++ prohibits anonymous structs [-Werror=pedantic]
    T& operator[] (int i) { return array[i]; }
    T& x() { return array[0]; }
    T& y() { return array[1]; }
};

// if no pedantic this would work:
//struct Point2 {
//    union {
//        struct {
//            int x;
//            int y;
//        };
//        int array[2];
//    };
//};

template <typename T>
struct Point3 {
    T array[3];
    T& operator[] (int i) { return array[i]; }
    T& x() { return array[0]; }
    T& y() { return array[1]; }
    T& z() { return array[2]; }
};

template <typename T>
struct Point4 {
    T array[4];
    T& operator[] (int i) { return array[i]; }
    T& x() { return array[0]; }
    T& y() { return array[1]; }
    T& z() { return array[2]; }
    T& w() { return array[3]; }
};

using P2f  = Point2<float>;
using P2i  = Point2<int>;
using P2ui = Point2<unsigned int>;

using P3f  = Point3<float>;
using P3i  = Point3<int>;
using P3ui = Point3<unsigned int>;

using P4f  = Point3<float>;
using P4i  = Point3<int>;
using P4ui = Point3<unsigned int>;
