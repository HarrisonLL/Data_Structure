
#include "Image.h"
#include "StickerSheet.h"
#include "cs225/HSLAPixel.h"
#include <vector>
#include <utility>



StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    picture_ = picture; //base picture
    stickers_size = max;
    stickers_ct = 0;
    stickers_ = new Image[stickers_size]; // stickers array
    //stickers_cords.resize(max); // resize the sticker_cords
    xCords = new unsigned[stickers_size];
    yCords = new unsigned[stickers_size];
}


StickerSheet::~StickerSheet() {
    _destroy();
}

StickerSheet::StickerSheet(const StickerSheet & other) {
    _copy(other);
}


const StickerSheet & StickerSheet::operator= (const StickerSheet & other) {
    if (& other != this) {
        _destroy();
        _copy(other);
      }

    return *this;
}


void StickerSheet::changeMaxStickers(unsigned max) {

    if ((int)max < stickers_size) {
      stickers_size = (int)max;
      for (int i = max; i < stickers_ct; i++) {
       stickers_[i] = Image();
      }

    //  Image *temp = new Image[(int)max];
    //  for (int i = 0; i < (int)max; i++) {
    //     temp[i] = stickers_[i];
    //  }
    //  delete[] stickers_;
    //  stickers_ = temp;

/*  Not need: 
     //unsigned *temp1 = new unsigned[(int)max];
     // for (int i = 0; i < (int)max; i++) {
     //    temp1[i] = xCords[i];
     // }
     // delete[] xCords;
     // xCords = temp1;

     // unsigned *temp2 = new unsigned[(int)max];
     // for (int i = 0; i < (int)max; i++) {
     //    temp2[i] = yCords[i];
     // }
     // delete[] yCords;
     // yCords = temp2;

     // stickers_ct = max;
*/
    }

    if (stickers_size < (int)max) {
      stickers_size = (int)max;
      Image * temp_ = new Image[max];
      for (int i = 0; i < stickers_ct; i++) {
        temp_[i] = stickers_[i];
      }
      delete[] stickers_;
      stickers_ = temp_;
      
      unsigned * temp1_ = new unsigned[max];
      for (int i = 0; i < stickers_ct; i++) {
        temp1_[i] = xCords[i];
      }
      delete[] xCords;
      xCords = temp1_;

      unsigned * temp2_ = new unsigned[max];
      for (int i = 0; i < stickers_ct; i++) {
        temp2_[i] = yCords[i];
      }
      delete[] yCords;
      yCords = temp2_;

    }

}



int StickerSheet::addSticker(Image & sticker, unsigned x, unsigned y) {


   if (stickers_ct >= stickers_size) {

        return -1;

    }

        // if count < size, add the element into the array
    stickers_[stickers_ct++] = sticker;
    xCords[stickers_ct - 1] = x;
    yCords[stickers_ct - 1] = y;
    return (stickers_ct-1);

}



// index starts at 0
bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if ((int)index >= stickers_ct) { return false; }

    xCords[index]= x;
    yCords[index]= y;
    return true;
}


void StickerSheet::removeSticker(unsigned index) {
    
      if ((int) index + 1 == stickers_ct) {
        stickers_[index] = Image();
        stickers_ct--;
      }

      if((int)index < stickers_ct) {

        for (int i = index; i < stickers_ct-1; i++) {
          stickers_[i] = stickers_[i + 1];
        }
        
    
        for (int i = index; i < stickers_ct; i++) {
          xCords[i] = xCords[i + 1];
        }

        for (int i = index; i < stickers_ct; i++) {
          yCords[i] = yCords[i + 1];
        }


        stickers_ct -= 1;

      }
}



Image * StickerSheet::getSticker(unsigned index) const {
    if ((int)index >= stickers_ct) { return NULL;}
    Image * sticker = new Image();
    sticker = &stickers_[index];
    return sticker;
}

Image StickerSheet::render() const {


    Image *Out = new Image();
    Out -> resize(picture_.width(), picture_.height());

    for (unsigned x = 0; x < picture_.width(); x++) {
        for (unsigned y = 0; y < picture_.height(); y++) {
          Out -> getPixel(x,y) = picture_.getPixel(x,y);
        }
      }

    for (int i = 0; i < stickers_ct; i++) {
        Image sticker = stickers_[i];
        unsigned xCord = xCords[i];
        unsigned yCord = yCords[i];
        if ((xCord + sticker.width())> Out -> width()) {
          Out -> resize((xCord + sticker.width()), Out -> height());
          }
        if ((yCord + sticker.height())> Out -> height()) {
            Out -> resize(Out -> width(), (yCord + sticker.height()));
          }
        for (unsigned x = 0; x < sticker.width(); x++) {
            for (unsigned y = 0; y < sticker.height(); y++) {
              HSLAPixel & pixel0 = sticker.getPixel(x,y);
              if (pixel0.a > 0) {
                  Out -> getPixel(xCord + x, yCord + y) = pixel0;
              }
            }
        }

    }

    return *Out;

}


void StickerSheet::_copy(const StickerSheet & other) {
    stickers_size = other.stickers_size;
    stickers_ct = other.stickers_ct;
    picture_ = other.picture_;
    stickers_ = new Image[other.stickers_size];
    for (int i = 0; i < other.stickers_ct; i++) {
        stickers_[i] = other.stickers_[i];
    }
    xCords = new unsigned[other.stickers_size];
    for (int i = 0; i < other.stickers_ct; i++) {
        xCords[i] = other.xCords[i];
    }
    yCords = new unsigned[other.stickers_size];
    for (int i = 0; i < other.stickers_ct; i++) {
        yCords[i] = other.yCords[i];
    }

}


void StickerSheet::_destroy() {
    delete[] stickers_;
    stickers_ = NULL;
    delete[] xCords;
    xCords = NULL;
    delete[] yCords;
    yCords = NULL;
}