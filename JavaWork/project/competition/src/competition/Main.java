package competition;

import java.util.Scanner;
import java.io.*;

public class Main {
	public static void main(String[] args) throws IOException {
		try {
			File myFile = new File("competition/data1.txt");
			Scanner in = new Scanner(myFile);

			//extract metadata (first line)
			String temp = in.nextLine();
			String[] line1 = temp.split(" ");
			int judges = Integer.parseInt(line1[0]);
			int contestants = Integer.parseInt(line1[1]);

			//-----------------------------------------------------

			//create arrays for the scores
			String[][] scoresString = new String[judges][contestants];
			int[][] scores = new int[judges][contestants];

			//create arrays for the scores
			String[] coefficientsString = new String[contestants];
			double[] coefficients = new double[contestants];

			//create arrays for the arithmetics
			double[] scoresSum = new double[contestants];
			double[] finalScores = new double[contestants];

			//-----------------------------------------------------

			//get each line and then separate the elements
			for (int i = 0; i < judges; i++)
				scoresString[i] = in.nextLine().split("\t");

			//convert the data to int
			for (int i = 0; i < judges; i++)
				for (int j = 0; j < contestants; j++) {
					scores[i][j] = Integer.parseInt(scoresString[i][j]);
				}

			//------------------------------------------------------

			//separate the elements in the line
			//replace ',' with '.' (floating point)
			coefficientsString = in.nextLine().replace(",", ".").split("\t");

			//convert the data to double
			for (int i = 0; i < coefficientsString.length; i++)
				coefficients[i] = Double.parseDouble(coefficientsString[i]);

			//------------------------------------------------------

			//calculate final scores for each contestant
			for (int i = 0; i < scores[0].length; i++) {
				double sum = 0;
				for (int j = 0; j < scores.length; j++)
					sum += scores[j][i];
				scoresSum[i] = sum; //sum of all elements on the line
				finalScores[i] = scoresSum[i] * coefficients[i]; //apply coefficient
			}

			//------------------------------------------------------

			FileWriter fw = new FileWriter("klasirane.txt");
			PrintWriter pw = new PrintWriter(fw);

			//print to the file
			for (int i = 0; i < finalScores.length; i++)
				pw.printf("%.2f\t", finalScores[i]);
			pw.println();

			//FOR INTELLIJ
			fw = new FileWriter("competition/klasirane.txt");
			pw = new PrintWriter(fw);
			for (int i = 0; i < finalScores.length; i++)
				pw.printf("%.2f\t", finalScores[i]);
			pw.println();

			//close handles
			pw.close();
			fw.close();
			in.close();
		}
		catch(java.io.FileNotFoundException e) {
			e.printStackTrace();
			System.out.println("If you are using Eclipse, change the path to: \"data1.txt\"");
		}
		catch(Exception e) {
			System.out.println(e.getMessage());
			e.printStackTrace();
		}
	}
}
