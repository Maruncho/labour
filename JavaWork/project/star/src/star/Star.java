package star;

public class Star {
	private String id;
	private double distance;
	private int classification;
	private double mass;
	private String constellation;
	
	Star(String id, double d, int c, double m, String con) throws Exception {
		setId(id);
		setDistance(d);
		setClassification(c);
		setMass(m);
		setConstellation(con);
	}
	
	static final String[] classNames = 
		{"UNDEFINED",
				"хипергигант",
				"свръхгигант",
				"ярък гигант",
				"гигант",
				"субгигант",
				"джудже",
				"субджудже",
				"червено джудже",
				"кафяво джудже"
		};
	
	public String getId() {
		return id;
	}
	public void setId(String s) throws Exception {
		if(s.length()>20 || s.isBlank())
			throw new Exception("Invalid id length");
		id = s;
	}
	
	public double getDistance() {
		return distance;
	}
	public void setDistance(double d) throws Exception {
		if(d<0)
			throw new Exception("Invalid distance");
		distance = d;
	}
	
	public int getClassification() {
		return classification;
	}
	public void setClassification(int i) throws Exception {
		if(i<1 || i>9)
			throw new Exception("invalid class number");
		classification = i;
	}
	
	public double getMass() {
		return mass;
	}
	public void setMass(double m) throws Exception {
		if(m<0)
			throw new Exception("Invalid mass");
		mass = m;
	}
	
	public String getConstellation() {
		return constellation;
	}
	public void setConstellation(String c) throws Exception {
		if(c.length()>30 || c.isBlank())
			throw new Exception("Invalid constellation id length");
		constellation = c;
	}
	
	public String toString() {
		return id+"\t"+
				String.valueOf(distance)+"св.г."+"\t"+
				classNames[classification]+"\t"+
				String.valueOf(mass)+"сл.м."+"\t"+
				constellation;
	}
}
