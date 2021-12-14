package star;

import java.util.Arrays;
import java.util.Comparator;
import java.util.Map;
import java.util.Scanner;
import java.io.File;
import java.util.AbstractMap;
import java.util.ArrayList;

public class Main {

	static Star[] getStarData(Scanner in) throws NumberFormatException, Exception {
		ArrayList<Star> starsTemp = new ArrayList<Star>();
		while(in.hasNext()) {
			String line1 = in.nextLine();
			String line2 = in.nextLine();
			String line3 = in.nextLine();
			
			String[] dataStr = line2.split(" ");
			
			Star star = new Star(
				line1, 
				Double.parseDouble(dataStr[0]),
				Integer.parseInt(dataStr[1]),
				Double.parseDouble(dataStr[2]),
				line3
			);
			starsTemp.add(star);
		}
		Star[] temp = new Star[starsTemp.size()];
		return starsTemp.toArray(temp);
	}
	
	static class SortByDistance implements Comparator<Star> {
		public int compare(Star s1, Star s2) {
			if(s1.getDistance() < s2.getDistance()) return -1;
			if(s1.getDistance() > s2.getDistance()) return 1;
			return 0;
		}
	}
	
	static class SortByConstellation implements Comparator<Star> {
		public int compare(Star s1, Star s2) {
			
	
				return s1.getConstellation().compareTo(s2.getConstellation());
		}
	}
	
	static class SortByConstellationThenRMass implements Comparator<Star> {
		public int compare(Star s1, Star s2) {
			
			if(s1.getConstellation().compareTo(s2.getConstellation()) != 0)
				return s1.getConstellation().compareTo(s2.getConstellation());
			
			//s1 < s2 == s2 > s1
			return Double.compare(s2.getMass(),s1.getMass());
		}
	}
	
	static ArrayList<Map.Entry<String, Double>> ConstellationsAverageMass(Star[] stars) {
		Arrays.sort(stars, new SortByConstellation());
		
		ArrayList<Double> masses = new ArrayList<Double>();
		ArrayList<String> names = new ArrayList<String>();
		
		String currentC = null; //will be initialized properly later
		int counter = 0; // how many elements for each constellation
		for(Star s : stars) {
			if(masses.size()==0) { //initialize
				masses.add(s.getMass());
				counter = 1;
				names.add(currentC = s.getConstellation());
				continue;
			}
			
			int last = masses.size()-1; // ALIAS for last element in masses[]
			
			if(s.getConstellation().compareTo(currentC)!=0) {
				//do the average calculation
				masses.set(last,
					masses.get(last)/counter);
				
				names.add(currentC = s.getConstellation());
				masses.add(s.getMass());
				counter = 1;
				last = masses.size()-1; //update
			}
			//masses[last]+=s.getMass();
			masses.set(last,
				masses.get(last)+s.getMass());
			counter++;
		}
		//do for the last constellation
		masses.set(masses.size()-1,
				masses.get(masses.size()-1)/counter);
		
		
		var resultsList = new ArrayList<Map.Entry<String, Double>>();
		for(int i = 0; i < names.size(); i++)
			resultsList.add(new AbstractMap.SimpleEntry(names.get(i),masses.get(i)));
		return resultsList;
	}
	
	public static void main(String[] args) {
		try {
			Scanner sc = new Scanner(new File("star/src/star/mystar.txt"));
			Star[] stars = getStarData(sc);
			
			Arrays.sort(stars, new SortByDistance());
			System.out.println("\nDistance Ascending:\n");
			for(Star s : stars)
				System.out.println(s.toString());
			
			Arrays.sort(stars, new SortByConstellationThenRMass());
			System.out.println("\nConstellation Ascending THEN Mass Descending:\n");		
			for(Star s : stars)
				System.out.println(s.toString());
			
			System.out.println("\nAverage Mass of each Constellation:\n");
			for(var x : ConstellationsAverageMass(stars))
				System.out.println(x.getKey()+"'s average mass: "+x.getValue().toString()+"сл.м.");
			
		}
		catch(java.io.FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("If you are using Eclipse, change the path to: \"src/star/mystar.txt\"");
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
		
		
		
	}	
}
	
