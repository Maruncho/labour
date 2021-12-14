
public class WashingMachine extends Appliance {

	WashingMachine(String n, double wi, double b, double h, double we) throws Exception {
		super(n, wi, b, h, we);
	}

	@Override
	public String action() {
		return "Washes clothes";
	}
}
