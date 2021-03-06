package bigNumbers;

import java.util.Scanner;

public class Main {
	
	public static void main(String[] args) {
		
		//Get input
		Scanner in = new Scanner(System.in);
		System.out.println("Въведете 2 естесвени числа на отделни редове:");
		
		//Convert
		int[] num1 = ArrayNumbers.to_int_array(in.nextLine());		
		int[] num2 = ArrayNumbers.to_int_array(in.nextLine());
		
		//Compare the two numbers
		boolean num1Bigger = false; //used for later
		boolean num2Bigger = false;	//used for later
		switch(ArrayNumbers.compare(num1, num2)){
		case 1:
			System.out.println("The first is bigger");
			num1Bigger = true;
			break;
		case -1:
			System.out.println("The second is bigger");
			num2Bigger = true;
			break;
		case 0:
			System.out.println("The numbers are equal");
		}
		
		//Operations
		System.out.print("Sum:");
		ArrayNumbers.print(ArrayNumbers.add(num1,num2));
		 
		
		System.out.println();
		
		
		System.out.print("Difference:");
			//find who's bigger (Negative values are not supported)
		if(num1Bigger)
			ArrayNumbers.print(ArrayNumbers.subtract(num1,num2));
		else if(num2Bigger)
			ArrayNumbers.print(ArrayNumbers.subtract(num2,num1));
		else//whatever
			ArrayNumbers.print(ArrayNumbers.subtract(num1,num2)); 
		
			
		System.out.println();
		
		
		System.out.print("Product:");
		ArrayNumbers.print(ArrayNumbers.multiply(num1,num2));
		
		
		//-----------------------------------
		in.close();
		
	}
}
