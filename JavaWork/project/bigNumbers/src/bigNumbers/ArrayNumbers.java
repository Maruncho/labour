package bigNumbers;

public class ArrayNumbers {

	public static int[] add_zeros(int[] var, int wantedLength) {
		int diff = wantedLength-var.length;
		int[] result = new int[wantedLength];
		for(int i = 0; i < diff; i++)
			result[i]=0;
		for(int i = diff; i < wantedLength; i++)
			result[i]=var[i-diff];
		return result;
	}

	public static int[] remove_zeros(int[] var) {
		//count the zeroes in front
		int counter = 0;
		for(int i = 0; i < var.length; i++) {
			if(var[i]==0) {
				counter++;
			}
			else
				break;
		}
		//remove the zeroes in front
		int newLength = var.length-counter;
		
		if(newLength==0) //if it's all zeroes
			return new int[] {0};
		
		int[] result = new int[newLength];
		for(int i = 0; i < newLength; i++)
			result[i]=var[i+counter];
		return result;
	}
	
	public static int[] to_int_array(String numRaw) {
		int[] num = new int[numRaw.length()];
		for(int i = 0; i < num.length; i++)
			num[i] = numRaw.charAt(i)-48; //ASCII table conversion
		return num;
	}
	
	public static int convert_to_int(int[] var) {  
		int result = 0;
		for(int i = 0; i < var.length; i++)
			result += var[i] * Math.pow(10,var.length-1-i);
		return result;
	}
	
	public static int compare(int[] num1, int[] num2) {
		
		if(num1.length > num2.length)
			return 1;
		if(num1.length < num2.length)
			return -1;
		
		//check individual digits
		for(int i = 0; i < num1.length; i++) {
			if(num1[i] > num2[i])
				return 1;
			if(num1[i] < num2[i])
				return -1;
		}
		
		//no differences
		return 0;
	}
	
	public static int[] add(int[] first, int[] second) {
		
		//to add them, they need to have equal length
		switch(compare(first, second)){
		case 1:
			second = add_zeros(second,first.length);
			break;
		case -1:
			first = add_zeros(first,second.length);
			break;
		case 0: // equal lengths
		}
		
		int[] result = new int[first.length+1];
		for(int i = 0; i < result.length; i++)
			result[i]=0;
		
		for(int i = first.length; i > 0; i--) {
			result[i]+=first[i-1]+second[i-1];
			if(result[i]>9) {
				result[i-1]+=1;
				result[i]-=10;
			}
		}
		result = remove_zeros(result);
		return result;
	}
	
	public static int[] subtract(int[] first, int[] second) {
		
		//to add them, they need to have equal length
		switch(compare(first, second)){
		case 1:
			second = add_zeros(second,first.length);
			break;
		case -1:
			first = add_zeros(first,second.length);
			break;
		case 0: // equal lengths
		}
				
		int[] result = new int[first.length];
		for(int i = 0; i < result.length; i++)
			result[i]=0;
		
		for(int i = first.length-1; i >= 0; i--) {
			result[i]+=first[i]-second[i];
			if(result[i]<0) {
				result[i-1]-=1;
				result[i]+=10;
			}
		}
		if(result[0]==-1)
			result[0]=0;
		result = remove_zeros(result);
		return result;
	}
	
	public static int[] multiply(int[] first, int[] second) {
		int[] res = first;
		for(int i = 1; i < convert_to_int(second); i++) {
			res = add(res,first);
			first = add_zeros(first,res.length);
		}
		return res;
	}
	
	public static void print(int[] arr) {
		for(int i = 0; i < arr.length; i++)
			System.out.print(arr[i]);
	}
	
}
