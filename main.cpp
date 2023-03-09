
//           NetId: kka21001                                                            Name: Karl Azangue


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void rowFunction (char array[], string sudokuName);     //Prototype of the function which goes through every row in the array of the sudoku passed to this functions and then outputs whether the row is valid, or invalid. Following this format: <array name> row <number> has multiple <duplicate number>s

void columnFunction (char array[], string sudokuName);   //Prototype of the function which goes through every column in the array of the sudoku passed to this functions and then outputs whether the row is valid, or invalid. Following this format: <array name> column <number> has multiple <duplicate number>s

void blockFunction (char array[], string sudokuName);     //Prototype of the function which goes through every grid in the array of the sudoku passed to this functions and then outputs whether the grid is valid, or invalid. Following this format: <array name>  <grid name> has multiple <duplicate number>s

//In this function, the program is going to reade a suddoku and stores its content in a character array using a switch statement, once done it is then going to pass that array to the functions, 'rowfunction', 'column function', and 'blockfunction' where the program will check wether it has valid column, row and grid. Before reading the array, the program will first sudoku the sudoku's name and store in a string called 'sodokuName' before passing it to the functions aswell. This function will also check whether a the sudoku is solved or not and outpute a statemetn accordingly.
int main()
{
    string fileName, sudokuName, reader = "";
    int count =0, space = 0;
    char *sudokuArray = new char[81];
    
    char *pointer = sudokuArray;
 
    cout <<"Enter the file name: ";  //Prompts the user to output the name of the file before storing it in the string variable named "fileName"
    getline(cin,fileName);
    
    fstream file(fileName, ios::in);   //The program open the file for reading thus enabling it to reade/move through the file
    
        if(!file.is_open())  //Checks whether the file was opened properly and outputs an error statements otherwise
        {
            cout << "File could not be opened. ";
        }

        while(getline(file, reader))  //This while loop is going to reader the program line by line until it reaches the end of the file
        {
            
            switch (count)   //In the switch statements, if the case is 0 the program will reade the sudoku name and store it in the string named "sudokuName", if the case is -1 the program breaks to the next case. Other wise the program reade through the file and store its content in a character array and once it chease case 9, the program will pass the array and the sodukuname to the function for row, columns, and grid before reseting array and count/the case back to zero/empty.
            {
                    
                case -1:
                    break;
                case 0:   //If the count is 0, the program stores the name of the sudoku in the string named 'sodokuname'
                    sudokuName = reader;
                    break;
                    
                default :
                    for(unsigned long i = 0; i < reader.length(); i++)  //The program goes through every character of the line which is currently being read and stores its content in the character array named 'sudokuArray'
                    {
                        *(sudokuArray + ((9*count-9)+i)) = reader[i];

                        if(reader[i] == ' ') //As the program goes through every character of the line being read, this is going to increment space, whenever it find '_' thus enabling the program to finc out wether the soduku is solved.
                        {
                            space++;
                        }
                    }
                    
                    if(count == 9)
                    {
                        rowFunction ( sudokuArray, sudokuName); //passes the current character array containing the soduku and the name of the sudoku to the function 'rowFunction' where the program is going to check wether each individual row is valid.
                        
                        columnFunction ( sudokuArray, sudokuName);  //passes the current character array containing the soduku and the name of the sudoku to the function 'columnFunction' where the program is going to check wether each individual column is valid.
                        
                        blockFunction ( sudokuArray, sudokuName); //passes the current character array containing the soduku and the name of the sudoku to the function 'blockFunction' where the program is going to check wether each individual grid is valid.

                        if(space > 0)  //If 'space' is greater than 1, a statmetn will be outputted accordingly stating that the program is not solved otherwise the program will output a statement stating that it is solved.
                        {
                            cout << "Sudoku " << sudokuName << " is not solved" << endl;
                        }
                        else
                        {
                            cout << sudokuName << "    solved"<< endl;
                        }
                        cout << endl;
                        
                        sudokuArray = pointer;  //This pointer in the array back to 1, thus enabling the next soduku array to overide the currrent array stored in it.
                        
                        count = -2;  //sets count to -2 so it can move pass 2 line before reaching the next sudoku name
                        space = 0;  //resets space to 0 for the next sodoku array
                    }
                    break;
            }
            count++; //increments count in order to determing the line being read
        }
        file.close();
    delete []sudokuArray;
}


//In this function the program is going to go through the array mathematically in order to determing wether each individual row in the array is valid (contains a duplicate) or not and outputs a statement accordingly.
void rowFunction (char array[], string sudokuName)
{
    char *pointer = array;     //This sets a pointer to the array thus enabling it to move move through the array without using offset notations
    
    for ( int i = 1; i <= 9; i++) //This for loop checks the amount of rows being read and loops through each individual row
    {
        int seen[9] = {0};  //This creates an array named 'seen' and fill it with 0's. This is used to test whether an number has a duplicate or not. Whenever a number is encountered its index in this array increments by 1 and if an index is found to be greater than 1, then the program will outputs a statment stating so. Resets the enture array to 0's once in the next row.
        
        bool rowValid = true;  //boolean value used to check wether the entire row is valid
        
       for(int j = 1; j <=9; j++)  //This for loop is used to reader through each character in each individaul row
       {

           if(*pointer == ' ')  //The program skips the current digit/value its at if it is a space
           {
               pointer++;
               continue;
           }
           
           if(seen[*pointer - '1'] == 1)  //This is used to check whether a digit/value appeared more than onces in the array 'seen' If true the program outputs an invalid statement stating the current value is a duplicate, else the program increment the index of the value in the array and moves on to next value
           {
               seen[*pointer - '1'] += 1; //Increments values index of the current value in the array seen even when is greater than 1
               rowValid = false; //Sets 'rowvalid' to false thus enbling program to know the entire row invalid
               cout << sudokuName << "    invalid        row " << i << " has multiple " << *pointer << "s" << endl; //outputs invalid statement
           }
           else
           {
               seen[*pointer - '1'] += 1; //increment index of current value by 1 in the array seen, since it hasnt being seen before
           }
           
           pointer++; //moves through each individual character in the row

       }
        if(rowValid == true)  //Outputs a statement stating the current row is invalid since because a duplicate was found.
        {
            cout << sudokuName << " row is valid" << endl;
        }
        pointer++;
    }
}


//In this function the program is going to go through the array mathematically in order to determing wether each individual column in the array is valid (contains a duplicate) or not and outputs a statement accordingly.
void columnFunction (char array[], string sudokuName)
{
    char *pointer = array; //This sets a pointer to the array thus enabling it to move move through the array without using offset notations
    
    for (int i = 1; i <= 9; i++) //This for loop checks the amount of columns being read and loops through each individual column
    {
        int seen[9] = {0}; //This creates an array named 'seen' and fill it with 0's. This is used to test whether an number has a duplicate or not. Whenever a number is encountered its index in this array increments by 1 and if an index is found to be greater than 1, then the program will outputs a statment stating so. Resets the enture array to 0's once in the next column.
        
        bool rowValid = true;   //boolean value used to check wether the entire row is valid
        
       for(int j = 1; j <=9; j++) //This for loop is used to reader through each character in each individaul column
       {

           if(*pointer == ' ') //The program skips the current digit/value its at if it is a space
           {
               pointer += 9;
               continue;
           }
           
           if(seen[*pointer - '1'] == 1 )  //This is used to check whether a digit/value appeared more than onces in the array 'seen' If true the program outputs an invalid statement stating the current value is a duplicate, else the program increment the index of the value in the array and moves on to next value
           {
               seen[*pointer - '1'] += 1;   //Increments values index of the current value in the array seen even when is greater than 1.
               
               rowValid = false;  //Sets 'rowvalid' to false thus enbling program to know the entire row invalid
               cout << sudokuName << " invalid column\t" << i << " has multiple " << *pointer << "s" << endl;   //outputs invalid statement
           }
           else
           {
               seen[*pointer - '1'] += 1;  //Increment index of current value by 1 in the array seen, since it hasnt being seen before
           }
           pointer+=9; //This enables the program to move 9 times ahead in other to reach the next value in the column

       }
        pointer = pointer - (9*9) + 1; //This statements enable the program to move back to the next column after it is done reading the once it is currently at.
        
        if(rowValid == true)  //Outputs a statement stating the current row is invalid since because a duplicate was found.
        {
            cout << sudokuName << " column is valid" << endl;
        }
    }
}

//In this function the program is going to go through the array mathematically in order to determing wether each individual grid in the array is valid (contains a duplicate) or not and outputs a statement accordingly.
void blockFunction (char array[], string sudokuName)
{
    string gridname = ""; //This string serves as the name of the grid the program is currently at.
    
    char *pointer = array;  //This sets a pointer to the array thus enabling it to move move through the array without using offset notations
            
    for ( int i = 1; i <= 9; i++) //This for loop checks the amount of grid being read, and loops through each individual grid
    {
        int seen[9] = {0}; //This creates an array named 'seen' and fill it with 0's. This is used to test whether an number has a duplicate or not. Whenever a number is encountered its index in this array increments by 1 and if an index is found to be greater than 1, then the program will outputs a statment stating so. Resets the enture array to 0's once in the next column.
        
        bool rowValid = true; //boolean value used to check wether the entire row is valid

        for ( int k = 1; k <= 3; k++)  //This for loop is used to set the grid rows
        {
           for(int j = 1; j <=3; j++)  //This for loop is used to read through each character in each row at the current grid
           {

               switch(i)  //This switch statemetn resets the name of the grid 'gridname' base off the grid it is at.
               {
                   case 1:
                       gridname = "upper left";
                       break;
                   case 2:
                       gridname = "upper middle";
                       break;
                   case 3:
                       gridname = "upper right";
                       break;
                   case 4:
                       gridname = "left";
                       break;
                   case 5:
                       gridname = "middle";
                       break;
                   case 6:
                       gridname = "right";
                       break;
                   case 7:
                       gridname = "lower left";
                       break;
                   case 8:
                       gridname = "lower middle";
                       break;
                   case 9:
                       gridname = "lower right";
                       break;
               }

               if(*pointer == ' ') //The program skips the current digit/value its at if it is a space
               {
                   pointer++;
                   continue;
               }
               
               if(seen[*pointer - '1'] == 1)   //This is used to check whether a digit/value appeared more than onces in the array 'seen' If true the program outputs an invalid statement stating the current value is a duplicate, else the program increment the index of the value in the array and moves on to next value
               {
                   seen[*pointer - '1'] += 1;  //Increments values index of the current value in the array seen even when is greater than 1.
                   
                   rowValid = false;  // //Sets 'rowvalid' to false thus enbling program to know the entire row invalid
                   
                   cout << sudokuName << "    invalid    " << gridname << " has multiple " << *pointer << "s" << endl;  //outputs invalid statement
               }
               else
               {
                   seen[*pointer - '1'] += 1;   //Increment index of current value by 1 in the array seen, since it hasnt being seen before
               }
               pointer++; //moves through each individual character in the grid's row

           }
                
            pointer+=6; //Moves the character ahead 6 times onces it is done reader a row
        }
        
        if(rowValid == true)
        {
            cout << sudokuName << "     valid" << endl;
        }
 
        if(i % 3 == 0)   //This statement checks whether the program reaches the 3, 6 and 9th grid. If so it will move back 6 times in order to get to the next block (4, or 7), else it is going to be move back 24 blocks in orther to get the next block. Its important to note that after going through each grid, the pointer is 6 times 7 times ahead and its for this reason the program has to move back 6 times instead of move aheads once, and moving back 24 instead of 18.
        {
            pointer-=6; //moves back 6 blocks
        }
        else
        {
            pointer -= 24; //moves back 24 blocks
        }
    }
}




    











































/*
 
 
 #include <iostream>
 #include <fstream>
 #include <string>

 using namespace std;

 void rowFunction (char array[], string sudokuName);
 void columnFunction (char array[], string sudokuName);
 void blockFunction (char array[], string sudokuName);

 int main()
 {
     string fileName, sudokuName, reader = "";
     int count =0, space = 0;
     char *sudokuArray = new char[81];
     
     char *pointer = sudokuArray;
  
     cout <<"Enter the file name: ";
     cin >> fileName;
     
     fstream file(fileName, ios::in);
     
         if(!file.is_open())
         {
             cout << "FIle could not be opened. ";
         }

         while(getline(file, reader))
         {
             switch (count)
             {
                 case 0:
                     sudokuName = reader;
                     break;
                     
                 default :
                     for(unsigned long i = 0; i < reader.length(); i++)
                     {
                         *(sudokuArray + ((9*count-9)+i)) = reader[i];

                         if(reader[i] == ' ') //pointer+=i || sudokuArray+=i == ' ')
                         {
                             space++;
                         }
                     }
                     
                     if(count == 9)
                     {
                         rowFunction ( sudokuArray, sudokuName);
                         columnFunction ( sudokuArray, sudokuName);
                         blockFunction ( sudokuArray, sudokuName);

                         if(space > 0)
                         {
                             cout << "Sudoku " << sudokuName << " is not solved" << endl;
                         }
                         else
                         {
                             cout << sudokuName << "    solved"<< endl;
                         }
                         cout << endl;
                         
                         sudokuArray = pointer;
                         
                         count = -2;
                         space = 0;
                     }
                     break;
             }
             count++;
         }
         file.close();
 }


 void rowFunction (char array[], string sudokuName)
 {
     char *pointer = array;
     
     for ( int i = 1; i <= 9; i++)
     {
         int seen[9] = {0};
         bool rowValid = true;
         
        for(int j = 1; j <=9; j++)
        {
            pointer++;

            if(*pointer == ' '){
                continue;
            }
            
            if(seen[*pointer - '1'] == 1)
            {
                seen[*pointer - '1'] += 1;
                rowValid = false;
                cout << sudokuName << " invalid row\t" << i << " has multiple " << *pointer << "s" << endl;
            }
            else
            {
                seen[*pointer - '1'] += 1;
            }
        }
         if(rowValid == true){
             cout << sudokuName << " is valid" << endl;
         }
     }
 }


 void columnFunction (char array[], string sudokuName)
 {
     */ /*pointer */ /*= array;
     for (int i = 1; i <= 9; i++)
     {
        for(int j = i; j <= 9; j++)
        {
            if( i != j)
            {
                if (array[i] == array[j]) //pointer+=i == pointer+=j )
                {
                    cout << sudokuName << " invalid column\t" << i << " has multiple " << array[i] */ /*pointer+=i*/ /* << "s" << endl;
                }
                else
                {
                    cout << sudokuName << " is valid" << endl;
                }
             }
        }
     }
 }


 void blockFunction (char array[], string sudokuName)
 {
     string gridname = "";
    // *pointer = array;
     for ( int i = 1; i <= 9; i++)
     {
         for ( int k = 1; k <= 3; i++)
         {
             for(int j = 0; j < 3; j++)
             {
                 if (array[k] == array[j]) //pointer+=i == pointer+=j )
                 {
                     // digit = Pointer ++
                     switch(i)
                     {
                         case 1:
                             gridname = "Upper left";
                             break;
                         case 2:
                             gridname = "Upper middle";
                             break;
                         case 3:
                             gridname = "Upper right";
                             break;
                         case 4:
                             gridname = "Left";
                             break;
                         case 5:
                             gridname = "middle";
                             break;
                         case 6:
                             gridname = "right";
                             break;
                         case 7:
                             gridname = "lower left";
                             break;
                         case 8:
                             gridname = "lower middle";
                             break;
                         case 9:
                             gridname = "lower right";
                             break;
                     }
                     
                     cout << sudokuName << " invalid  grid\t" << gridname << " has multiple " << i << "s" << endl;
                 }
                 else
                 {
                     cout << sudokuName << "    valid" << endl;
                 }
                     
             }
         }
            
     }
 }

*/









/*

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void rowFunction (char array[], string sudokuName);
void columnFunction (char array[], string sudokuName);
void blockFunction (char array[], string sudokuName);

int main()
{
    string fileName, sudokuName, reader = "";
    int count =0, space = 0;
    char *sudokuArray = new char[81];
    
    char *pointer = sudokuArray;
 
    cout <<"Enter the file name: ";
    cin >> fileName;
    
    fstream file(fileName, ios::in);
    
        if(!file.is_open())
        {
            cout << "File could not be opened. ";
        }

        while(getline(file, reader))
        {
            switch (count)
            {
                    
                case -1:
                    break;
                case 0:
                    sudokuName = reader;
                    break;
                    
                default :
                    for(unsigned long i = 0; i < reader.length(); i++)
                    {
                        *(sudokuArray + ((9*count-9)+i)) = reader[i];

                        if(reader[i] == ' ') //pointer+=i || sudokuArray+=i == ' ')
                        {
                            space++;
                        }
                    }
                    
                    if(count == 9)
                    {
                        rowFunction ( sudokuArray, sudokuName);
                        columnFunction ( sudokuArray, sudokuName);
                        blockFunction ( sudokuArray, sudokuName);

                        if(space > 0)
                        {
                            cout << "Sudoku " << sudokuName << " is not solved" << endl;
                        }
                        else
                        {
                            cout << sudokuName << "    solved"<< endl;
                        }
                        cout << endl;
                        
                        sudokuArray = pointer;
                        
                        count = -2;
                        space = 0;
                    }
                    break;
            }
            count++;
        }
        file.close();
}


void rowFunction (char array[], string sudokuName)
{
    char *pointer = array;
    
    for ( int i = 1; i <= 9; i++)
    {
        //int seen[9] = {0};
        int *seen = new int[9];
        seen = {0};
        
        
        bool rowValid = true;
        
       for(int j = 1; j <=9; j++)
       {

           if(*pointer == ' ')
           {
               pointer++;
               continue;
           }
           
           if(seen+=(*pointer) == 1)
           {
               seen +=(*pointer) += 1;
               rowValid = false;
               cout << sudokuName << "    invalid        row " << i << " has multiple " << *pointer << "s" << endl;
           }
           else
           {
               seen+=(*pointer) += 1;
           }
           
           pointer++;

       }
        if(rowValid == true)
        {
            cout << sudokuName << " row is valid" << endl;
        }
        pointer++;
    }
}


void columnFunction (char array[], string sudokuName)
{
    char *pointer = array;
    int index = 0;
    
    for (int i = 1; i <= 9; i++)
    {
        int seen[9] = {0};
        bool rowValid = true;
        
       for(int j = 1; j <=9; j++)
       {

           if(*pointer == ' ')
           {
               pointer += 9;
               index += 9;
               continue;
           }
           
           if(seen[*pointer - '1'] == 1 )//&& *pointer - '1' > 0)
           {
               seen[*pointer - '1'] += 1;
               rowValid = false;
               cout << sudokuName << " invalid column\t" << i << " has multiple " << *pointer << "s" << endl;           }
           else
           {
               seen[*pointer - '1'] += 1;
           }
           pointer+=9;
           index += 9;
           
        

       }
        
        pointer = pointer - (9*9) + 1;
        index = index - (9*9) + 1;
        if(rowValid == true)
        {
            cout << sudokuName << " column is valid" << endl;
        }
    }
}


void blockFunction (char array[], string sudokuName)
{
    string gridname = "";
    char *pointer = array;
        
    for ( int i = 1; i <= 9; i++)
    {
        
        int seen[9] = {0};
        bool rowValid = true;

        for ( int k = 1; k <= 3; k++)
        {
           for(int j = 1; j <=3; j++)
           {

               switch(i)
               {
                   case 1:
                       gridname = "upper left";
                       break;
                   case 2:
                       gridname = "upper middle";
                       break;
                   case 3:
                       gridname = "upper right";
                       break;
                   case 4:
                       gridname = "left";
                       break;
                   case 5:
                       gridname = "middle";
                       break;
                   case 6:
                       gridname = "right";
                       break;
                   case 7:
                       gridname = "lower left";
                       break;
                   case 8:
                       gridname = "lower middle";
                       break;
                   case 9:
                       gridname = "lower right";
                       break;
               }

               if(*pointer == ' ')
               {
                   pointer++;
                   continue;
               }
               
               if(seen[*pointer - '1'] == 1)
               {
                   seen[*pointer - '1'] += 1;
                   rowValid = false;
                   cout << sudokuName << "    invalid    " << gridname << " has multiple " << *pointer << "s" << endl;
                   
               }
               else
               {
                   seen[*pointer - '1'] += 1;
               }
               pointer++;

           }
            pointer+=6;
        }
        
        if(rowValid == true)
        {
            cout << sudokuName << "     valid" << endl;
        }
 
        if(i % 3 == 0)
        {
            pointer-=6;
        }
        else
        {
            pointer -= 24;
        }
           
    }
    
}



*/
    










































