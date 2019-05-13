/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

/* Note: std::map   links index and object, here it takes a point and return an index*/
/* Steps: first get average color of all the tile images, map to LUVAPixel;
          then for each pixel of the mosaic canvas, set tile image */
MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

     map<Point<3>, int> tilesMap;
     vector<Point<3>> modTiles;
     //modTiles.resize((theTiles.size()));

     for (unsigned i = 0; i < theTiles.size(); i++) {
       LUVAPixel pix = theTiles[i].getAverageColor();
       //double arr [4] = { pix.l*1.00000, pix.u*1.00000, pix.v*1.00000, pix.a*1.00000};
       //Point<4> p (arr);
       Point<3> point = convertToXYZ(pix);
       modTiles.push_back(point);
       tilesMap[point] = i;
     }

     KDTree<3> tree(modTiles);
     int rows = theSource.getRows();
     int columns = theSource.getColumns();
     MosaicCanvas * canvas = new MosaicCanvas(rows, columns);

     for (int x = 0; x < rows; x++) {
       for (int y = 0; y < columns; y++) {
         LUVAPixel pix = theSource.getRegionColor(x, y);
         //double arr[4] = {pix.l*1.00000, pix.u*1.00000, pix.v*1.00000, pix.a*1.00000};
         //Point<3> query (arr);
         Point<3> nn = tree.findNearestNeighbor(convertToXYZ(pix));
         auto it = tilesMap.find(nn);
         if (it != tilesMap.end()) {canvas -> setTile(x,y, &theTiles[tilesMap[nn]]);}
       }
     }

    return canvas;
}


