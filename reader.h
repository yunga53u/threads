#include <iostream>
#include <fstream>
//#include <mutex>

using namespace std;

class Reader
{
    public:
        Reader();
        ~Reader();

        void make_sum(const char * const buf);
        void make_sub(const char * const buf);
        void make_xor(const char * const buf);
        //void make_sum(string& buf);
        //void make_sub(string& buf);
        //void make_xor(string& buf);

        //string read_file();
        char * read_file();
        void get_file_id();
        
        void open_file();
        void close_file();

        void work();
    private:
        ifstream infile;
        string in_file_name;
        size_t infile_size;
        unsigned int infile_id;
        ofstream outfile_sum;
        string out_file_name_sum;
        ofstream outfile_sub;
        string out_file_name_sub;
        ofstream outfile_xor;
        string out_file_name_xor;
};
