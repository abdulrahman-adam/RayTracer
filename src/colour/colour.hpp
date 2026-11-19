#pragma once

// A colour made of red, green and blue components.
class Colour {
public:
    // Creates a colour from its red, green and blue components.
    Colour(double r, double g, double b);

    // Read-only access to the components.
    double r() const;
    double g() const;
    double b() const;

private:
    double _r;
    double _g;
    double _b;
};
