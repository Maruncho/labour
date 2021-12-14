import java.text.DecimalFormat;

public abstract class Appliance {
	String name;
	double width;
	double breadth;
	double height;
	double weight;
	
	Appliance(String n, double wi, double b, double h, double we) throws Exception {
		name(n);
		width(wi);
		breadth(b);
		height(h);
		weight(we);
	}
	
	public String name() {
		return name;
	}
	public void name(String n) throws Exception {
		if(n.isEmpty())
			throw new Exception("Invalid name");
		name = n;
	}
	
	public double width() {
		return width;
	}
	public void width(double w) throws Exception {
		if(w<0)
			throw new Exception("Invalid width");
		width = w;
	}
	
	public double height() {
		return height;
	}
	public void height(double h) throws Exception {
		if(h<0)
			throw new Exception("Invalid height");
		height = h;
	}
	
	public double breadth() {
		return breadth;
	}
	public void breadth(double b) throws Exception {
		if(b<0)
			throw new Exception("Invalid breadth");
		breadth = b;
	}
	
	public double weight() {
		return weight;
	}
	public void weight(double w) throws Exception {
		if(w<0)
			throw new Exception("Invalid weight");
		weight = w;
	}
	
	public double volume() {
		return width*height*breadth;
	}
	
	public abstract String action();
	
	public String toString() {
		DecimalFormat df = new DecimalFormat("0.00");
		return "Name: "+name+"\t"+
				"Width: "+width+"m\t"+
				"Height: "+height+"m\t"+
				"Breadth: "+breadth+"m\t"+
				"Volume: "+df.format(volume())+"m^3\t"+
				"Weight: "+weight()+"kg\t"+
				"Action: "+action();
	}
}
