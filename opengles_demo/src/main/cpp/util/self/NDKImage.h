//
// Created by baishengye on 2023-11-09.
//

#ifndef AUDIOVEDIOLEANING_NDKIMAGE_H
#define AUDIOVEDIOLEANING_NDKIMAGE_H


#ifndef U8_t
#define U8_t unsigned char
#endif


class NDKImage {

public:
    NDKImage();
    ~NDKImage();

    int         GetWidth() const;
    int         GetHeight() const;
    int         GetType() const ;
    U8_t*       GetData() const;

    void        ReadFromFile(U8_t* fileName);
    void        ReadFromBuffer(U8_t* dataBuff,int length);

private:
    int         m_width;
    int         m_height;
    int         m_type;
    U8_t*       m_pImgData;
};

#endif //AUDIOVEDIOLEANING_NDKIMAGE_H
