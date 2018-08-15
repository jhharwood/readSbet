#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <ctime>
#include <cstdio>
#include <iostream>
#include <iomanip>

//#define FILE_NAME "sbet_RTX_NAD83_180808_1742_a.out"
#define OUT_FILE "sbet_RTX_NAD83_180808_1742_a.txt"

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
            std::cout << std::fixed << std::setprecision(17) << "Time:   " << records.time << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Latitude:  " << radian_to_degrees(records.lat) << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Longitude: " << radian_to_degrees(records.lon) << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Altitude: " << records.alt << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Roll: " << records.roll << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Pitch: " << records.pitch << "\n";
            std::cout << std::fixed << std::setprecision(17) << "Heading: " << records.heading << "\n";
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

// Start Main
int main(int argc, const char* argv[])
//int main()
{
    // Check the number of parameters
    if (argc < 2)
    {
        // Tell the user how to run the program
        std::cerr << "Usage: readSbet [sbet name]\n"
                  << "Sbet name should be path to the sbet *.out file\n"
                  << "Example Usage: readSbet.exe D:/path/to/myfile.out\n"
                  << std::endl;
        return 1;
    }

    std::clock_t start;
    int duration;

    start = std::clock();

    // Read/Write Files
    //const char *input = "D:/myIn.tif"
    const char *input = argv[1];
    std::cout << "This is your file " << input << std::endl;

    SbetRecord record;

    // Open the input file;
    std::ifstream file (input, std::ios::in | std::ios::binary);
    if(!file.is_open())
    {
        std::cout << "Error in file opening..." << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Opening file: " << input << std::endl;
    }


    std::ofstream out (OUT_FILE, std::ios::out | std::ios::app);
    while (!file.eof())
    {
        file.read((char *)&record, sizeof(record));
        // Print record information
        //record.displayRecords();
        //std::cout << "\n";

        //out.write((char*)&record,sizeof(record));
        //out << record.time << "," << record.lat << "," << record.lon << record.alt << "\n";

        out << std::fixed << std::setprecision(17) << record.getTime() << "," << record.radian_to_degrees(record.getLat()) << ","   \
        << record.radian_to_degrees(record.getLon()) << "," << record.getAlt() << "," <<  record.getRoll() << "," << record.getPitch() << "," \
        << record.getHeading() << std::endl;

    }

    duration = ( std::clock() - start ) / (int) CLOCKS_PER_SEC;
    std::cout << "Processing time is: " << duration  << " seconds." << std::endl;

    file.close();
    out.close();

    return 0;
}
