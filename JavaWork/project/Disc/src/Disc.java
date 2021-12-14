
public class Disc {
	private String n;
	private int s;
	
	public Disc(String name, int size) throws Exception {
		name(name);
		size(size);
	}
	
	public int size() {
		return s;
	}
	public void size(int size) throws Exception {
		if(size>4096 || size<0)
			throw new Exception("Invalid size");
		s = size;
	}
	
	public String name() {
		return n;
	}
	public void name(String name) throws Exception {
		if(name.isEmpty() || name.length() > 32)
			throw new Exception("Invalid name");
		n = name;
	}
	
	public String toString() {
		return n+" : "+ String.valueOf(s)+"MB";
	}
}
