/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */

    MosaicCanvas * canvasPtr = new MosaicCanvas(theSource.getRows(),
                                    theSource.getColumns());

    vector<Point<3>> vec;
    map<Point<3>, TileImage*> tile_map;

	for (TileImage& tile : theTiles) {
		LUVAPixel avg = tile.getAverageColor();
		Point<3> xyz_avg = convertToXYZ(avg);
		vec.push_back(xyz_avg);
		tile_map[xyz_avg] = &tile;
	}
    KDTree<3> avg_color_tree = KDTree<3>(vec);
    for (int y = 0; y < theSource.getRows(); y++) {
		for (int x = 0; x < theSource.getColumns(); x++) {
			LUVAPixel color = theSource.getRegionColor(y, x);
			Point<3> xyzColor = convertToXYZ(color);
			Point<3> nearestColor = avg_color_tree.findNearestNeighbor(xyzColor);
			canvasPtr->setTile(y, x, tile_map.at(nearestColor));
		}
	}

    return canvasPtr;
}

