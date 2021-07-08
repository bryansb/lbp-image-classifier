#ifndef BASE_INCLUDED
#define BASE_INCLUDED
    #include "./base.hpp"
#endif

#ifndef OPENCV_HEADERS_INCLUDED
#define OPENCV_HEADERS_INCLUDED
    #include "./opencv_headers.hpp"
#endif


#define compab_mask_inc(ptr, shift) \
    { \
        value |= ( (unsigned int) (cntr - *ptr) & 0x80000000 ) \
        >> (31 - shift); ptr++; \
    }


class LBPDescriptor{
    private:
        int* LBP8(const int*, int, int);

    public:
        LBPDescriptor();
        vector<int> lbp(Mat);
};

