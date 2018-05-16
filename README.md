# Search Engine

Program is oriented towards information retrieval and recreating the mechanisms behind early web browsing.
Using extensive data analysis and tf-idf to get the most relevant document from search query.

[Source files](src) and [test files](test_cases) can be found within the repository.

## Usage

Source files are in the src/ directory.  This contains the .h and .cpp files.

To compile into a executable, Search.  Run ``` make ``` in the src/ directory.
Must have 5 arguments, i.e., 

```$ ./Search query_file library_file lowest_reading_level max_reading_level```

Output:
Document that is most relevant to the query_file

## Running the tests

Small and Large test cases are found in the test_cases/ directory.

Automated run script will execute multiple times to ensure validity and gather timing information on documents.

In either test_cases/small/ or test_cases/large/ run the script to compile and execute program.

 ```
 $ cd test_cases/small/
 $ chmod +x run
 $ ./run
 Running Search ...
  [      49]  [01]  tamingshrew
  [      49]  [02]  tamingshrew
  [      36]  [03]  tamingshrew
  [      46]  [04]  tamingshrew
  [      42]  [05]  tamingshrew
  [      40]  [06]  tamingshrew
  [      49]  [07]  tamingshrew
  [      48]  [08]  tamingshrew
  [      44]  [09]  tamingshrew
  [      39]  [10]  tamingshrew
Average Time: 44 milliseconds
 ```
Left column is the average time in milliseconds for each iteration and the output file on the far right.
## Authors

* **Jason Stock** - *Initial work*

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
