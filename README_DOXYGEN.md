# Doxygen Documentation for Catalogo Videogiochi

## Overview
This project uses Doxygen to generate documentation for the code. Doxygen has been configured and installed for use with CLion.

## Viewing Documentation
The documentation has been generated in the `doc/html` directory. To view it:

1. Open the file `doc/html/index.html` in a web browser
2. Browse through the different sections to see documentation for files, classes, and functions

## Using Doxygen with CLion

### Setting Up Doxygen in CLion
1. Open CLion
2. Go to CLion Preferences (⌘,)
3. Navigate to Tools > Doxygen
4. Set the path to the Doxygen executable: `/Applications/Doxygen.app/Contents/Resources/doxygen`
5. Click Apply

### Generating Documentation from CLion
1. To generate documentation, create an External Tool:
   - Go to CLion Preferences > Tools > External Tools
   - Click the + button to add a new tool
   - Name: Generate Doxygen Documentation
   - Program: `/Applications/Doxygen.app/Contents/Resources/doxygen`
   - Arguments: `Doxyfile`
   - Working directory: `$ProjectFileDir$`

2. To run it:
   - Select Tools > External Tools > Generate Doxygen Documentation

### Writing Doxygen Comments
To add documentation to your code, use the following syntax:

```c
/**
 * @brief Brief description of the function
 * 
 * @param parameter1 Description of parameter1
 * @param parameter2 Description of parameter2
 * @return Description of the return value
 */
int myFunction(int parameter1, char *parameter2);
```

## More Information
For more information on using Doxygen, see the [Doxygen Manual](https://www.doxygen.nl/manual/).

