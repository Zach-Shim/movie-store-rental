# Movie Rental Store Requirements Document

- [1. Overview](#heading)
- [2. File Parsing](#heading-1)
  * [2.1 Movie File](#sub-heading-1)
  * [2.2 Client File](#sub-heading-2)
  * [2.3 Transaction File](#sub-heading-3)
- [3. Storing Information in Databases](#heading-2)
  * [3.1 Storing Movies](#sub-heading-1)
  * [3.2 Storing Clients](#sub-heading-2)
  * [3.3 Storing Transactions](#sub-heading-3)
- [4. Processing Transactions](#heading-3)

<!-- toc -->

## 1. Overview
A local movie rental store wishes to automate their inventory tracking system. Currently there are three types of movies/videos (in DVD media) to be tracked:
- Comedy (denoted as ‘F’ for funny)
- Drama (denoted as ‘D’)
- Classics (denoted as ‘C’)

The movie rental store management system has the following requirements:
Be able to track four types of possible actions a client can take in the system: 
- Borrow (denoted as ‘B’): (stock – 1) for each item borrowed
- Return (denoted as ‘R’): (stock + 1) for each item returned
- Inventory (denoted as ‘I’): outputs the inventory of all the items in the store
- History (denoted as ‘H’): outputs all the transactions of a customer

Borrows and returns of items by customers are also to be tracked.
The program must be able to initialize the contents of the store's inventory from a file, the customer list from another file, and then process an arbitrary sequence of commands from a third file.

## 2. File Parsing

### 2.1 Movie File
A movie file will contain information about each movie that is to be stores in the store's inventory
There are three types of movies:
- For comedy movies: F, Stock, Director, Title, Year it released
- For drama movies: D, Stock, Director, Title, Year it released
- For classics movies: C, Stock, Director, Title, Major actor Release date

Example of what data would look like:
F, 10, Nora Ephron, You've Got Mail, 1998
D, 10, Steven Spielberg, Schindler's List, 1993 
C, 10, George Cukor, Holiday, Katherine Hepburn 9 1938 2 1971
C, 10, George Cukor, Holiday, Cary Grant 9 1938 
Z, 10, Hal Ashby, Harold and Maude, Ruth Gordon 
D, 10, Phillippe De Broca, King of Hearts, 1967

Important Requirements:
- File parsing assumes correct file formatting but allows information to be invalid, e.g., in this data, the 'Z'
code is an invalid entry so this line has to be discarded and users should be notified about this issue.

- There is an arbitrary amount of stock of each movie. There should be no instance where a stock is negative.

- The classical movie type has a different format than the other two. It contains Major actor which is always formatted as two strings, first name and last name, separated by a space. Then the Release date contains month and year information, and no comma (but a space) between Major actor and Release date. In addition, for classical movies, one movie (e.g., Holiday) may have multiple lines so the total stock of this movie will be the sum of all the stocks in the lines about this movie (e.g., 20 for Holiday in the above example).

Examples of how the inventory should look after transactions occur on a classical movie with same directors and title but different actors: 
Scenario 1 ---------------------------------------------------------------------------------------------------------------------------------------------------
C, 10, George Cukor, Holiday, Katherine Hepburn 9 1938
C, 10, George Cukor, Holiday, Cary Grant 9 1938
There are 20 total for Holiday initially. If customer wants to borrow Holiday with Hepburn, it will decrease the stock from Hepburn's stock, and the result is
C, 9, George Cukor, Holiday, Katherine Hepburn 9 1938
C, 10, George Cukor, Holiday, Cary Grant 9 1938 
Scenario 2 ---------------------------------------------------------------------------------------------------------------------------------------------------
C, 0, George Cukor, Holiday, Katherine Hepburn 9 1938
C, 10, George Cukor, Holiday, Cary Grant 9 1938
There are 10 total for holiday initially. If customer wants to borrow Holiday with Hepburn, it is unavailable and ask other alternative (Holiday with Grant)

### 2.2 Client File
A client txt file contains customer information, one line per customer. Customers have a 4-digit ID number that uniquely identifies them, followed by last name, first name, all separated by a space.
For example,
      1111 Mouse Mickey
      1000 Mouse Minnie
Program assumes that the data is formatted correctly, but may have invalid data such as a 5-digit ID number

### 2.3 Transaction File
A transaction txt file will contain information regarding what type of transaction a client would like to do on a specific movie.
The first field is action type (B, R, I, or H). Then the rest of fields are as follows:
- Action types I: no more fields
- Action type H: one more field customer ID. Fields are separated by a space
- Action types B and R: customer ID followed by type of media (currently only ‘D’ for
DVD) then movie type and movie data (with values of the two sorting attributes, using comma or space to separate them as in the movie data file). Fields are separated by a space.
For example,
      B 1234 D C 9 1938 Katherine Hepburn
      B 1234 D F Pirates of the Caribbean, 2003
      R 1234 D C 9 1938 Katherine Hepburn
      B 1234 D D Steven Spielberg, Schindler's List, S
      H 1234
      X 1234 Z C 9 1938 Katherine Hepburn
      B 1234 D Y 2 1971 Ruth Gordon
      B 9999 D F Pirates of the Caribbean, 2003 B 1234 D C 2 1975 Blah Blah
      
Important Requirements:
- Same as movies, the data will be formatted correctly, but may include errors.

- Program must handle invalid action code (e.g., ‘X’ in the above example), invalid video code (e.g., ‘Y’), incorrect customer ID (i.e., not found. 
For example, 9999), and invalid movie (i.e., not found. For example, classic movie in month 2 of 1975 with a "Blah Blah" title). For bad data, discard the line and notify users.

- Program must handle incorrect commands. For example, a command that makes the number of an item in the inventory goes below zero, a return command when a movie was not borrowed, etc.

## 3. Storing Information in Databases
Since we have not learned how to store information in databases yet (such as SQL), they will be stored locally in data structures

## 3.1 Storing Movies
To store movie data in the system, items should be sorted as follows:
- comedy movies (‘F’) sorted by Title, then Year it released
- dramas (‘D’) are sorted by Director, then Title
- classics (‘C’) are sorted by Release date, then Major actor
You can assume that each item is uniquely identified by its complete set of sorting attributes.

A hashtable can be implemented to store movies efficiently in intentory by mapping converting certain information about the movie into a hash key (convert a string to an int). A dynamic array will be used to store the items according to their unique number and look them up in O(1) time. Hash tables usually waste some memory, since not all the array will be filled. However, the waste is not too bad, if you store pointers to items, rather than the items themselves.

To make operations on movies easier, inhertiance will be used with class Movie as a base class and sublasses Comedy, Drama, and Classic will inherit as children of the Movie class.

## 3.2 Storing Clients
A client should be sorted by a 4-digit ID number that uniquely identifies them
For example,
      5432 Mouse Mickey       (Mickey Mouse would be stored in the system using his 4-digit ID 5342)
      7382 Mouse Minnie

Similar to Movies, a hashtable can be implemented to efficiently store clients. Since they all have unique ID's creating an array of 10000 clients and directly mapping them into their respective index is a viable option of implementaing a hashing algorithm.

## 3.3 Storing Transactions
Transactions will not be stored. Each line in a Transaction txt file will create a new Transaction object and will be deleted after it has been completed.

## 4. Processing Transactions
Important Requirements:
- Do not print output for successful ‘B’ or ‘R’ commands, but print error messages for incorrect data and/or incorrect command. Output for ‘H’ and ‘I’ commands should be neatly formatted with one line per item/transaction. ‘I’ should output all Comedy movies, then all Dramas, then all Classics. 
- Each category of movies should be ordered according to the sorting criteria discussed in 3.1 Storing Movies. 
- 'B' should subtract 1 from the stock of a movie based on the information given in the Transaction txt file. Each movie borrowed needs to be kept track of, which can be done inside a Customer. If a Client returns the (same) borrowed movie, then the stock of the movie should add 1.
- 'R' should add 1 to the stock of a movie based on the information given in the Transaction txt file.
- ‘H’ should show a list of DVD transactions of a customer in chronological order (latest to earliest) and specify whether the movie was
borrowed or returned.
- 'I' should display the stock and information of all movies in the video rental stores inventory
- Each line of data is new Transaction object. Once the transaction has been performed, the object is deleted and the next line is processed.
