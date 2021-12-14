package date;

public class Main {

	public static void main(String[] args) {
		try {

			//12.24.2004
			Date date = new Date(24,12,2004);

			//days between 12.24.2004 and 11.5.2004
			System.out.println(date.daysBetween(new Date(5,11,2021)));

			//365 days equals 1 year in 2021-2022
			for(int i = 1; i <= 365; i++) {
				System.out.println(date.toString());
				date = date.nextDate();
			}
			System.out.println(date.toString());
			
		} catch (Exception e) {
			System.out.println("exception: "+e.getMessage());
		}
		
		
	}

}
