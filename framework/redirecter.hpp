#include <ostream>
// http://stackoverflow.com/questions/4017034/c-where-does-the-ofstream-class-save-the-files-to
// http://wordaligned.org/articles/cpp-streambufs
/* ==============================================
    Stream redirecter. Usage:

    std::ofstream log("tests.log");
    redirecter redirect(log, std::cout); 

    It redirect the std::cout to a logfile. saved in the current working dir.

 */
class redirecter
{
public:
    // Constructing an instance of this class causes
    // anything written to the source stream to be redirected
    // to the destination stream.
    redirecter(std::ostream & dst, std::ostream & src)
        : src(src)
        , srcbuf(src.rdbuf())
    {
        src.rdbuf(dst.rdbuf());
    }
    
    // The destructor restores the original source stream buffer
    ~redirecter()
    {
        src.rdbuf(srcbuf);
    }
private:
    std::ostream & src;
    std::streambuf * const srcbuf;
};