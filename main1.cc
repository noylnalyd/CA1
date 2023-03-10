/*This is a skeleton code file for use with the Finite Element Method for Problems in Physics.
It uses the deal.II FEM library, dealii.org*/

//Include files
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "FEM1.h"
#include "writeSolutions.h"

using namespace dealii;

//The main program, using the FEM class
int main (){
  try{
    deallog.depth_console (0);

    for(int i=1; i<=3; i++){
      for(int j=1; j<=4; j++){
        //Specify the basis function order: 1, 2, or 3
        unsigned int order = i;

        //Specify the subproblem: 1, 2, 3, or 4
        unsigned int problem = j;

        FEM<1> problemObject(order,problem);
        
        //Define the number of elements as an input to "generate_mesh"
        problemObject.generate_mesh(10); //e.g. a 10 element mesh
        problemObject.setup_system();
        problemObject.assemble_system();
        problemObject.solve();
        std::cout << problemObject.l2norm_of_error() << std::endl;
        
        //write output file in vtk format for visualization
        problemObject.output_results();
        
        //write solutions to h5 file
        char tag[21];
        sprintf(tag, "CA1_Order%d_Problem%d",order,problem);
        writeSolutionsToFileCA1(problemObject.D, problemObject.l2norm_of_error(), tag);
      }
    }
  }
  catch (std::exception &exc){
    std::cerr << std::endl << std::endl
	      << "----------------------------------------------------"
	      << std::endl;
    std::cerr << "Exception on processing: " << std::endl
	      << exc.what() << std::endl
	      << "Aborting!" << std::endl
	      << "----------------------------------------------------"
	      << std::endl;

    return 1;
  }
  catch (...){
    std::cerr << std::endl << std::endl
	      << "----------------------------------------------------"
	      << std::endl;
    std::cerr << "Unknown exception!" << std::endl
	      << "Aborting!" << std::endl
	      << "----------------------------------------------------"
	      << std::endl;
    return 1;
  }

  return 0;
}
