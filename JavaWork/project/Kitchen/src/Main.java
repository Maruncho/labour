
public class Main {

	void doAction(Appliance app) {
		app.action();
	}
	
	public static void main(String[] args) {
		try {
			
			Appliance[] apps = {
				new Fridge("Frodger",1.1,1.2,1.82,38.2),
				new Dishwasher("Walsher",0.8,1,0.45,3.4),
				new WashingMachine("UwUashy",1,1,1,10)
			};
			
			for(Appliance x : apps) {
				System.out.println(x.toString());
			}
			
			
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println(e.getMessage());
		}

	}

}
