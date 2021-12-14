
public class Fridge extends Appliance {

	Fridge(String n, double wi, double b, double h, double we) throws Exception {
		super(n, wi, b, h, we);
	}

	@Override
	public String action() {
		return "Refrigerates";
	}
}
