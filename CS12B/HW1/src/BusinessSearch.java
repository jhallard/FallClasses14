/*
	Author - John Allard, ID: 1437547
	Class  - CS12B, HW #1
	Date   - Oct 21st, 2014

	File   - BusinessSearch.java
	Info   - This file defines the main class for the Business Search program. This class will take in a file that 
	contains a database of business name and number information, it will parse this file for the proper information,
	store each record extracted from the file into a specific record object, then populate an array with all the record
	objects built from the database file. Once the array is populated, it needs to be sorted according to the name 
	associated with each record in the array. Once the array is sorted, the user can query for phone number information
	by submitting the name of a business. 
*/

import static java.lang.System.*; 
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileReader;


class BusinessSearch {

 
 /**************************/
 /*****  Public Fields *****/
 /**************************/
 public int numRecords;




 /**************************/
 /***** Private Fields *****/
 /**************************/
 private BusinessRecord[] records;




 /**************************/
 /***** Public Methods *****/
 /**-************************/

   /* Constructor */
   // Takes in a file name and populates the records array in a sorted fashion
   public BusinessSearch(String fn) {
 	  numRecords = 0;
    
      // Load the records from the file, populate the array in an unsorted fashion.
      if(!loadFromFile(fn))
      	System.out.println("Failed to load from file.");

      // Sort the damned array
      records = sortRecords(records);

   }

   // @Function - Search
   // @Purpose  - Takes in a String which represents a business name, and it uses binary search to look through the records
   //			  array for the name that was given. If found, it will return the phone number associated with that name. If it can't
   //			  locate the query, it will inform the user as such.
   public String search(String name){

     // make sure the name at least contains some characters
   	 if(name == null || name == "") {
   		return "";
     } 

     // Use private member binary search function to look for querey. 
     int index = binarySearch(name, 0, numRecords-1);

     // if the index is negative, we didn't find the querey.
     if(index < 0)
     	return "";

     else
     	return records[index].number;
 }


 public static void main(String[] args) {

 	if(args.length <= 0){
 		System.out.println("Must input filename as argv[0]");
 		return;
 	}

 	String filename = args[0];

 	BusinessSearch bs = new BusinessSearch(filename);

 	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

 	int numqueries = 0;
 	int numfound = 0;
 	try{
	// Infinite loop where we ask the user for the input and give them output.
	while(true){
		System.out.println("Please Enter a Business Name\n");
		String input = in.readLine();

		if(input.compareTo("") == 0){
			System.out.println(numqueries+" total queries, "+ (numqueries-numfound) + " not found.\n");
		}
		else{
			String number = bs.search(input);

			if(number.compareTo("") == 0) {
				System.out.println(input + " NOT FOUND\n");
			}
			else {
				System.out.println(number+"\n");
			}
	    }   
	}
 	}
 	catch(IOException ex) {
 		ex.printStackTrace();
 	}


 }





 /**************************/
 /***** Private Methods ****/
 /**************************/

 private Boolean loadFromFile(String fn) {
 	String line = "";
    String[] lines = new String[500];
    int numLines = 0;


    try{
    // TODO : Need to Perform Data Validation on fn //
 	BufferedReader input = new BufferedReader(new FileReader(fn));
    
    // Read all the lines from the file, figure out how many records there are //
 	while((line = input.readLine()) != null) {
 		lines[numLines++] = line;
 	}
    
    // Instatiate the records array now that we know what size it should be
    records = new BusinessRecord[numLines];
    numRecords = numLines;

    // Populate the array with records
 	for(int i = 0; i < numLines; i++) {
 		String[] subfields = lines[i].split(",");
 		
 		if(subfields.length != 2 || subfields[0] == null || subfields[1] == null) {
 			System.out.println("Invalid Field");
 			break;
 		}

 		BusinessRecord br = new BusinessRecord(subfields[0], subfields[1]);
		records[i] = br;
 	}
 	} catch(IOException ex){
 		System.out.println(ex.toString());
 		System.out.println("Could not locate file");
 		return false;
 	}	

 	return true;
 }




 // @Method -- sortRecords
 // @Info   -- Performs a Merge Sort on the names assocaited with each record in the records array.
 private BusinessRecord[] sortRecords(BusinessRecord[] records) {

    // My merge sort method is not in place so we will be populating a new records array with the sorted data. 
    BusinessRecord[] sortedRecords = new BusinessRecord[records.length];

    // initiate the left and right record sub-arrays
    BusinessRecord[] leftrecs = null; BusinessRecord[] rightrecs = null;
    int middle = records.length/2;

    // Check the base case, a list of length 1 is sorted;
    if(records.length == 1) {
    	return records;
    }
  
    // Now we have to see if the length is even or odd to ensure we get out bounds correct.
    if(records.length % 2 != 0) {
    	rightrecs = new BusinessRecord[(records.length/2)+1];
    	leftrecs = new BusinessRecord[records.length/2];
    }
    else {
    	rightrecs = new BusinessRecord[records.length/2];
    	leftrecs = new BusinessRecord[records.length/2];
    }


    
    // Populate the left and right halves of the arrays //
    for(int i = 0, j = 0; i < records.length; i++) {

    	if(i < middle)
    		leftrecs[i] = records[i];
    	else
    		rightrecs[j++] = records[i];
    }

    // Recursion!!!! //
    leftrecs = sortRecords(leftrecs);
    rightrecs = sortRecords(rightrecs);
 

    // Merge the two sublists together!
    sortedRecords = mergeRecords(leftrecs, rightrecs);

    return sortedRecords;
 }



  // @Function - mergeRecords
  // @Purpose  - Takes in two lists of BusinessRecord objects, merges them into one list in sorted order,
  //             and returns this list the the sortRecords function. To do the merge it compares the lowest 
  //			 elements from each list and puts the lowest one in the master record list, then repeats.
  private BusinessRecord[] mergeRecords(BusinessRecord[] leftRecords, BusinessRecord[] rightRecords) {

  	int leftInd = 0;
  	int rightInd = 0;
  	int mergeInd = 0;

  	if(leftRecords == null)
  		return rightRecords;
  	if(rightRecords == null)
  		return leftRecords;

  	// This will hold our merged list of records
  	BusinessRecord[] mergedRecords = new BusinessRecord[leftRecords.length+rightRecords.length];

  	// While there are still elements left to be merged
  	while(leftInd < leftRecords.length || rightInd < rightRecords.length) {

  		// If we have run out of left records to merge, insert the right records. //
  		if(leftInd == leftRecords.length) {
  			while(mergeInd < mergedRecords.length){
  				mergedRecords[mergeInd] = rightRecords[rightInd];
  				mergeInd++;
  				rightInd++;
  			}
  			
  		}
  		// If we have run out of right records to merge , insert the left records
  		else if(rightInd == rightRecords.length){ 
  			while(mergeInd < mergedRecords.length){
  				mergedRecords[mergeInd] = leftRecords[leftInd];
  				mergeInd++;
  				leftInd++;
  			}
  		}
  		else {
  			// if the left one comes before the right one alphabetically
  			if( !(leftRecords[leftInd].lessThan(rightRecords[rightInd])) ){
  				mergedRecords[mergeInd] = rightRecords[rightInd];
  				mergeInd++; rightInd++;
  			}
  			else {
  				mergedRecords[mergeInd] = leftRecords[leftInd];
  				mergeInd++; leftInd++;
  			}
  		}
  		
  	}

  	return mergedRecords;
  } // end MergeRecords Method



  // @Function - BinarySearch
  // @Purpose  - Takes a querey and searches through the records for that querey, returns the index of the querey if it exists
  // 			 and returns -1 if it cannot find the entry.
  private int binarySearch(String name, int ind1, int ind2) {
  		

  	// if there is only one element and it is not the right answer, return false
  	if(ind1 == ind2 && records[ind1].name.compareTo(name) != 0)
  		return -1;

  	// if there are only two elements I have to do this one annoying case. 
  	if(ind2-ind1 == 1){
  		if(records[ind1].name.compareTo(name) == 0)
  			return ind1;
  		else if(records[ind2].name.compareTo(name) == 0)
  			return ind2;
  		else
  			return -1;
  	}

  	int mid = (ind2+ind1)/2;
  	int compare = name.compareTo(records[mid].name);
  
  	// If it is in the left half of the array 
  	if(compare < 0)
  		return binarySearch(name, ind1, mid);
  
  	// Else it is in the right half of the array
  	else if(compare > 0) {
  		return binarySearch(name, mid, ind2);
  	}

  return mid;
} // end bianrySearch function

  		
} // end BusinessSearch class



 