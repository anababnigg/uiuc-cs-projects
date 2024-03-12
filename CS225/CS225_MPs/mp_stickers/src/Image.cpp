#include <Image.h>


void Image::lighten() {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).l + 0.1 <= 1) {this->getPixel(w, h).l += 0.1;}
            else{this->getPixel(w, h).l = 1;}
        }
    }
}

void Image::lighten(double amount) {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).l + amount > 1) {this->getPixel(w, h).l = 1;}
            else if(this->getPixel(w, h).l + amount < 0) {this->getPixel(w, h).l = 0;}
            else{this->getPixel(w, h).l += amount;}
        }
    }
}


void Image::darken() {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).l - 0.1 >= 0) {this->getPixel(w, h).l -= 0.1;}
            else{this->getPixel(w, h).l = 0;}
        }
    }
}

void Image::darken(double amount) {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).l - amount > 1) {this->getPixel(w, h).l = 1;}
            else if(this->getPixel(w, h).l - amount < 0) {this->getPixel(w, h).l = 0;}
            else{this->getPixel(w, h).l -= amount;}
        }
    }
}

void Image::saturate() {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).s + 0.1 <= 1) {this->getPixel(w, h).s += 0.1;}
            else{this->getPixel(w, h).s = 1;}
        }
    }
}

void Image::saturate(double amount) {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).s + amount > 1) {this->getPixel(w, h).s = 1;}
            else if(this->getPixel(w, h).s + amount < 0) {this->getPixel(w, h).s = 0;}
            else{this->getPixel(w, h).s += amount;}
        }
    }
}

void Image::desaturate() {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).s - 0.1 >= 0) {this->getPixel(w, h).s -= 0.1;}
            else{this->getPixel(w, h).s = 0;}
        }
    }
}

void Image::desaturate(double amount) {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).s - amount > 1) {this->getPixel(w, h).s = 1;}
            else if(this->getPixel(w, h).s - amount < 0) {this->getPixel(w, h).s = 0;}
            else{this->getPixel(w, h).s -= amount;}
        }
    }
}

void Image::grayscale() {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            this->getPixel(w, h).s = 0;
        }
    }
}

//are the exclusion [0, 360] cases correct? hues are a circle so unsure how to do
// wait its literally a circle theres no negatives
// FIX
void Image::rotateColor(double degrees) {
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            if(this->getPixel(w, h).h + degrees > 360) {
                this->getPixel(w, h).h = (this->getPixel(w, h).h + degrees - 360);
            }
            else if(this->getPixel(w, h).h + degrees < 0) {
                this->getPixel(w, h).h = (360 + this->getPixel(w, h).h + degrees);
            }
            else{
                this->getPixel(w, h).h += degrees;
            }
        }
    }
}

void Image::illinify() {
    unsigned int ill_orange = 11;
    unsigned int ill_blue = 216;
    for (unsigned int h = 0; h < height(); h++) {
        for (unsigned int w = 0; w < width(); w++) {
            //find closest (going orange first)
            if(std::abs(this->getPixel(w, h).h - ill_orange) < std::abs(this->getPixel(w, h).h - ill_blue)) {
                this->getPixel(w, h).h = ill_orange;
            } else {
                this->getPixel(w, h).h = ill_blue;
            }
        }
    }
}

void Image::scale(double factor) {
    Image scaled(factor * width(), factor * height());
    for (unsigned int h = 0; h < scaled.height(); h++) {
        for (unsigned int w = 0; w < scaled.width(); w++) {
            scaled.getPixel(w, h) = this->getPixel(unsigned(w / factor), unsigned(h / factor));
        }
    }
    *this = scaled;
}

void Image::scale(unsigned w, unsigned h) {
    unsigned int width = this->width();
    unsigned int height = this->height();

    double scale_h = (w * 1.0) / (double) height;
    double scale_w = (h * 1.0) / (double) width;

    if(scale_w < scale_h) {scale(scale_w);} 
    else {scale(scale_h);}
}