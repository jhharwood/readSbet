#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;
//#define FILE_NAME "sbet_RTX_NAD83_180808_1742_a.out"
#define OUT_FILE "sbet_out.txt"


// Define a structure to read in the sbet
// Define a sbet record class
class SbetRecord
{
    private:
        struct records
        {
            double time;
            double lat;
            double lon;
            double alt;
            double ewspeed;
            double nsspeed;
            double vertspeed;
            double roll;
            double pitch;
            double heading;
            double wander;
            double ewacc;
            double nsacc;
            double vertacc;
            double xacc;
            double yacc;
            double zacc;
        }records;

    public:

        // Convert degrees to radians
        double radian_to_degrees(double rad)
        {
            return rad * 180.0/M_PI;
        }

        void displayRecords()
        {
            cout << fixed << setprecision(17) << "Time:   " << records.time << "\n";
            cout << fixed << setprecision(17) << "Latitude:  " << radian_to_degrees(records.lat) << "\n";
            cout << fixed << setprecision(17) << "Longitude: " << radian_to_degrees(records.lon) << "\n";
            cout << fixed << setprecision(17) << "Altitude: " << records.alt << "\n";
            cout << fixed << setprecision(17) << "Roll: " << records.roll << "\n";
            cout << fixed << setprecision(17) << "Pitch: " << records.pitch << "\n";
            cout << fixed << setprecision(17) << "Heading: " << records.heading << "\n";
        }

        double getTime()
        {
            return records.time;
        }

        double getLat()
        {
            return records.lat;
        }

        double getLon()
        {
            return records.lon;
        }

        double getAlt()
        {
            return records.alt;
        }

        double getRoll()
        {
            return records.roll;
        }

        double getPitch()
        {
            return records.pitch;
        }

        double getHeading()
        {
            return records.heading;
        }

};

string getFileName(const string &s)
    {
        char sep = '/';

    #ifdef _WIN32
        sep = '\\';
    #endif

        size_t i = s.rfind(sep, s.length());
        if (i != string::npos)
        {
          return(s.substr(i+1, s.length() - i));
        }

        return("");
    }

// Start Main
int main(int argc, const char* argv[])
//int main()
{
    // Check the number of parameters
    if (argc < 2)
    {
        // Tell the user how to run the program
        cerr << "Usage: readSbet [sbet name]\n"
                  << "Sbet name should be path to the sbet *.out file\n"
                  << "Example Usage: readSbet.exe D:/path/to/sbet*.out\n"
                  << endl;
        return 1;
    }

    // Define time processing variables
    clock_t start;
    int duration;

    // Start the timer to get the processing time.
    start = clock();

    // Read/Write Files


    // get the sbet from the command execution
    const char *sbet = argv[1];
    //string path = argv[1];
    //char filename;
    cout << "This is your sbet file " << sbet << endl;

    SbetRecord record;

    // Open the sbet and exif file;
    ifstream fileSbet (sbet, ios::in | ios::binary);

    if(!fileSbet.is_open() && !fileSbet)
    {
        cout << "Error in file opening..." << endl;
        return 0;
    }
    else
    {
        cout << "Opening file: " << sbet << endl;
    }

    // Define Sbet out variable
    string sbetName;
    //sbetName = getFileName(path);
    //ofstream outTxt;
    cout << "This the sbet " << sbet << endl;

    ofstream outTxt (OUT_FILE, ios::out | ios::app);
    while (!fileSbet.eof())
    {
        fileSbet.read((char *)&record, sizeof(record));
        // Print record information
        //record.displayRecords();

        outTxt << fixed << setprecision(17) << record.getTime() << "," << record.radian_to_degrees(record.getLat()) << ","   \
        << record.radian_to_degrees(record.getLon()) << "," << record.getAlt() << "," <<  record.getRoll() << "," << record.getPitch() << "," \
        << record.getHeading() << endl;

    }

    // Tell user file has been read and is closing
    cout << "Closing file: " << sbet << endl;

    // Output time to read and process file
    duration = ( clock() - start ) / (int) CLOCKS_PER_SEC;
    cout << "Processing time is: " << duration  << " seconds." << endl;

    fileSbet.close();
    outTxt.close();

    return 0;
}
