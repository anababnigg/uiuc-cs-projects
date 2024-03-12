#include <StickerSheet.h>

StickerSheet::StickerSheet(const Image& picture) {
    baseimage = picture;
}

int StickerSheet::addSticker(Image& sticker, int x, int y) { 
    int layer = num_stickers;   
    if (!stickers.empty() && stickers.size() != num_stickers) {
        for (unsigned int i = 0; i < stickers.size(); i++) {
            if (stickers[i] == nullptr) {
                stickers[i] = &sticker;
                sticker_coords[i] = {x,y};
                layer = i;
                break;
            }
        }
    } else {
        stickers.push_back(&sticker);
        sticker_coords.push_back({x,y});
    }
    num_stickers++;
    return layer;
}

int StickerSheet::setStickerAtLayer(Image& sticker, unsigned layer, int x, int y) {
    //std::cout << stickers.size() << " : " << layer << std::endl;
    if (layer < stickers.size()) {
        if (stickers[layer] == nullptr) {num_stickers++;
        }
        stickers[layer] = &sticker;
        sticker_coords[layer] = {x,y};
        return layer;
    } else {
        addSticker(sticker, x, y);
        return num_stickers - 1;
    }
}


bool StickerSheet::translate(unsigned index, int x, int y) {
    if (index >= stickers.size() || stickers[index] == nullptr) {return false;}
    sticker_coords[index] = {x,y};
    return true;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index < stickers.size()) {
    stickers[index] = nullptr;
    num_stickers--;
    }
}

Image* StickerSheet::getSticker(unsigned index) {
    if (index < stickers.size()) {return stickers[index];}
    return nullptr;
}

int StickerSheet::layers() const {
    return stickers.size();
}

Image StickerSheet::render() const{
    Image rendered(baseimage);
    unsigned x_max = baseimage.width();
    unsigned y_max = baseimage.height();
    for (unsigned i = 0; i < stickers.size(); i++){
        if (stickers[i] != nullptr) {
        unsigned x_max = std::max(x_max, sticker_coords[i].first + stickers[i]->width());
        unsigned y_max = std::max(y_max, sticker_coords[i].second + stickers[i]->height());
        }
    }
    rendered.resize(x_max,y_max);
    for (unsigned i = 0; i < stickers.size(); i++) {
        if (stickers[i] != nullptr) {
            Image sticker = *stickers[i];
            unsigned image_width = sticker_coords[i].first + sticker.width();
            unsigned image_height = sticker_coords[i].second + sticker.height();
            for (unsigned x = sticker_coords[i].first; x < image_width; x++) {
                for (unsigned y = sticker_coords[i].second; y < image_height; y++) {
                    cs225::HSLAPixel &sticker_pixel = sticker.getPixel(x-sticker_coords[i].first,y-sticker_coords[i].second);
                    cs225::HSLAPixel &rendered_pixel = rendered.getPixel(x,y);
                    if (sticker_pixel.a != 0) {rendered_pixel = sticker_pixel;}
                }
            }
        }
    }
    return rendered;
}