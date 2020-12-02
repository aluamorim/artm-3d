/**
* 
*  This file is part of the "3D Acoust RTM" (ARTM-3D).
*
*  ARTM-3D is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  ARTM-3D is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with ARTM-3D.  If not, see <https://www.gnu.org/licenses/>6.
*
*  @author: Anderson Amorim
*/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <RTM.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc<2){
        cout << "> You forgot the input.json file!" << endl;
        return -1;
    }
    try{
        string inputFile(argv[1]);

        RTMParam rtmParam(inputFile);
        /** Loading input parameters from JSON file */
        rtmParam.loadRTMParam();

        /* fpga kernel path passed as input*/
        if (argc==3){
            string xclbinFile(argv[2]);
            rtmParam.fpga_xclbin = xclbinFile;
        }

        // creates RTMProcess instance
        RTMAcousticProcess rtmProcess(rtmParam);
        rtmProcess.rtm();
    }catch(RTMException &e){
        cout << "> Error:\n" << e.what() << endl;
        cout << "> Aborting!" << endl;
        exit(EXIT_FAILURE);
    }catch(RTMParamException &e){
        cout << "> Error:\n" << e.what() << endl;
        cout << "> Aborting!" << endl;
        exit(EXIT_FAILURE);
    }
    catch(...){
       cout << endl;
       cout << "> Error: Rougue Exception Flying Around. Aborting!" << endl;
       exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}
