/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"
#include <vector>
#include <utility>


 class StickerSheet {
     public:
     StickerSheet (const Image & picture, unsigned max);
     ~StickerSheet ();
     StickerSheet (const StickerSheet &other);
     const StickerSheet & operator= (const StickerSheet &other);
     void changeMaxStickers (unsigned max);
     int addSticker (Image &sticker, unsigned x, unsigned y);
     bool translate (unsigned index, unsigned x, unsigned y);
     void  removeSticker (unsigned index);
     Image * getSticker (unsigned index) const;
     Image render () const;
     void draw(Image sticker, unsigned xCord, unsigned yCord) const;



    //Try:
     private:
     /* Helper functions: */
        void _copy(const StickerSheet & other);
        void _destroy();
    /* Base picture */
        Image  picture_;
    /* Sticker Array */
        Image *stickers_;
        int stickers_size;
        int stickers_ct;
    /*Stickers Cords Array*/
        unsigned *xCords;
        unsigned *yCords;
    /* pairs of stickers corrdinates using vector */
        //std::vector< std::pair<int,int> > stickers_cords;

};
