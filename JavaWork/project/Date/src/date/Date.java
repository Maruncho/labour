package date;

public class Date {
	private byte day;
	private byte month;
	private short year;
	
	public Date() {
		day = 1;
		month = 1;
		year = 2000;
	}
	
	public Date(int d, int m, int y) throws Exception {
		if( setDay(d)==false ) throw new Exception("Invalid date :<");
		if( setMonth(m)==false ) throw new Exception("Invalid date :<");
		if( setYear(y)==false ) throw new Exception("Invalid date :<");
	}
	
	//check
	public boolean isCorrect() { //probably useless
		return setDay(day) && setMonth(month) && setYear(year);
	}
	
	private boolean leapYear(int y) {
		if(y%4==0)
			return true;
		return false;
	}
	
	public boolean isLeapYear() {
		return leapYear(year);
	}
	
	//get
	public byte getDay() {
		return day;
	}
	
	public byte getMonth() {
		return month;
	}
	
	public short getYear() {
		return year;
	}
	
	//set
	
	public boolean setDay(int d) {
		if(d<1||d>31)
			return false;
		
		switch(month) {
		
		case 4:case 6:case 9:case 11:
			if(d>30)
				return false;
			break;
			
		case 2:
			if(d>29)
				return false;
			if(!isLeapYear() && d>28)
				return false;
		}
		
		day = (byte) d; //an oversight in the project
		return true;
	}
	
	public boolean setMonth(int m) {
		if(m<1||m>12)
			return false;
		
		switch(m) {
		
		case 4:case 6:case 9:case 11:
			if(day>30)
				return false;
			break;
			
		case 2:
			if(day>29)
				return false;
			if(!isLeapYear() && day>28)
				return false;
		}
		
		month = (byte) m; //an oversight in the project requirements
		return true;
	}
	
	public boolean setYear(int y) {
		if(y<1||y>9999)
			return false;
		
		if(!leapYear(y) && month==2 && day==29) 
			return false;
		//hundred lines :O
		year = (short) y; //an oversight in the project requirements
		return true;
	}
	
	//----
	
	public Date nextDate() {
		
		boolean nextMonth = false; //for later
		
		byte oday = day;	  //
		byte omonth = month; //"other" Date variables
		short oyear = year;	//
		oday++;
		
		//handle days
		switch(omonth) {
		case 4:case 6:case 9:case 11:
			if(oday>30)
				nextMonth = true;
			break;
			
		case 2:
			if(!isLeapYear() && oday>28)
				nextMonth = true;
			if(oday>29)
				nextMonth = true;
			break;
			
		default:
			if(oday>31)
				nextMonth = true;
		}
		
		//handle the month and year
		if(nextMonth) {
			oday = 1;
			omonth++;
			if(omonth>12) {
				omonth = 1;
				oyear++;
			}
				
		}
		//it will never throw, but oh well
		try {
			return new Date((int)oday,(int)omonth,(int)oyear);
		} catch (Exception e) {
			e.printStackTrace();
		}
		//will never reach, but oh well
		return new Date();
	}
	
	public int compareTo(Date d) {
		// this < d --> -1
		// this == d --> 0
		// this > d --> 1
		//year
		if(year < d.year)
			return -1;
		else if(year > d.year) 
			return 1;
		else //check month
		
		//month
		if(month < d.month)
			return -1;
		else if(month > d.month) 
			return 1;
		else //check day
			
		//day
		if(day < d.day)
			return -1;
		else if(day > d.day) 
			return 1;
		else return 0;
	}
	
	public int daysBetween(Date d) {
		if(compareTo(d)==0) return 1; //inclusive
		
		Date big = this;
		Date small = d;	
		if(big.compareTo(small)==-1) {
			big = d;
			small = this;
		}
		
		int days = 1; //including the starter day
		//brute force >:D
		while(big.compareTo(small)!=0) {
			small=small.nextDate();
			days++;
		}
		return days;
	}
	
	public String toString() {
		if(!isCorrect()) return "Incorrect";
		
		//Format requires zeros:
		//Correct: 01.01.0012
		//Wrong: 1.1.12
		
		String dayZero = "";
		if(day<10)
			dayZero = "0";
		
		String monthZero = "";
		if(month<10)
			monthZero = "0";
		
		String yearZeroes = "";
		if(year<1000)
			yearZeroes += "0";
		if(year<100)
			yearZeroes += "0";
		if(year<10)
			yearZeroes += "0";
		
		return dayZero+String.valueOf(day)+"."+
		monthZero+String.valueOf(month)+"."+
		yearZeroes+String.valueOf(year);
	}
}
