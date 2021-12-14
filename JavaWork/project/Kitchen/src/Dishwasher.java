
public class Dishwasher extends Appliance {

	Dishwasher(String n, double wi, double b, double h, double we) throws Exception {
		super(n, wi, b, h, we);
	}

	@Override
	public String action() {
		return "Does dishes";
	}

}
