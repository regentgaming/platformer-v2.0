class Vector2D {
            private:
                double x;
                double y;
            public:
                //this is the thing
                Vector2D(double x_p, double y_p) : x(x_p), y(y_p) {}
                Vector2D() = default;
                /**
                 * @brief Returns the x value
                 * @return the x value
                 */
                double getX() {return x;}
                /**
                 * @brief Returns the y value
                 * @return the y value
                 */
                double getY() {return y;}

                Vector2D operator+(Vector2D const& other) {
                    Vector2D ret = Vector2D(x + other.x, y + other.y);
                }

                bool operator==(Vector2D const& other) {
                    return (x==other.x) && (y==other.y);
                }
};

class BoundingBox {
    private:
        Vector2D UL;
        Vector2D LR;
    public:
        BoundingBox(double x, double y, double height, double width) {
            UL = Vector2D(x,y);
            LR = Vector2D(x+width,y+height);
        }

        BoundingBox() = default;

        bool isIntersecting(BoundingBox& other) {
            return (LR.getX() > other.UL.getX() && other.LR.getX() > UL.getX()) && (LR.getY() > other.UL.getY() && other.LR.getY() > UL.getY());
        }
};
