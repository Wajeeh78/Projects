#include <iostream>

struct Resolution {
  unsigned int x;
  unsigned int y;
};

enum Type {
  Png,
  Jpeg,
};

// Represents a genric file of any type
class File {
public:
  std::string path; // The path to file

  bool exists(); // Return true if file exits else false
  void open(); // Opens the file. Crashes if fails
  void save(); // Saves the file. Crashes if fails
};

// Represensts a image file
class Image : public File {
public:
  Resolution resolution; // The resolution of the image in pixel density
  Type type; // The type of the image

  Image(std::string path); // Initialize the image object

private:
  void get_resolution(); // Gets the resolution of the image
  void get_type(); // Gets the type of the image
};

// Variant to represent different types of filter
enum Filter {
  Greyscale,
  Pastel,
  Vintage,
};

// Variant to represent the three direction of rotation
enum Direction {
  Right90,
  Left90,
  Flip180,
};

// Variant to represent the common aspect ratio for cropping
enum Ratio {
  Facebook,
  Instagram,
  X, };

// The editor that modifies the image as needed
class Editor {
public:
  Image image; // The image to be modified

  void filter(Filter f); // Applies the given filter to image
  void rotate(Direction d); // Applies the given rotation direction to image
  void crop(Ratio ratio); // Applies the given aspect ratio to the image
};

// The interface that interacts with the user for input/output operations
class User {
public:
  std::string prompt(std::string msg); // Prompts the user with given msg. Returns the response as string
  void print(std::string msg); // Prints the given msg to stdout
};

int main() { return 0; }
