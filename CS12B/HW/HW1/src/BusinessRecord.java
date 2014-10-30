/*
	Author - John Allard, ID: 1437547
	Class  - CS12B, HW #1
	Date   - Oct 21st, 2014
	
	File   - BusinessRecord.java
	Info   - This file defines a helper class for the Business Search program. This class will serve as an abstract
	representation of a business, it will contain the name of the business and the phone number at which this business can 
	be reached. It will also contain helper methods that allow one BusinessRecord to be compared against another for equality,
	and for alphabetic ordering based on the name associated with the record.  This class will be used by the BusinessSearch
	class to populate an array of business information. 
*/


import static java.lang.System.*; 

class BusinessRecord {

  public String name;
  public String number;

  /* Default Constructor */
  BusinessRecord() {
   name = "";
   number = "";
  }

  BusinessRecord(String name, String number) {
  	this.name = name;
  	this.number = number;
  }

  Boolean lessThan(BusinessRecord br) {
  	if(name.compareTo(br.name) <= 0)
  		return true;
  	else
  		return false;
  }
  
}