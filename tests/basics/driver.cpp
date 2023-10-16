#include <sstream>
#include <stdexcept>

#include <toml11/version.hpp>
#include <toml11/toml11.hpp>

#undef NDEBUG
#include <cassert>

int main ()
{
  using namespace std;
  using namespace toml11;

  // Basics.
  //
  {
    ostringstream o;
    say_hello (o, "World");
    assert (o.str () == "Hello, World!\n");
  }

  // Empty name.
  //
  try
  {
    ostringstream o;
    say_hello (o, "");
    assert (false);
  }
  catch (const invalid_argument& e)
  {
    assert (e.what () == string ("empty name"));
  }
}
