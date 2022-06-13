package zacGonzalez.mysql.first;

//	Import Statements
import java.sql.Connection;

import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Date;
import java.util.Scanner;

public class MySQLAccess {

	// Initialize Variables
	private static Connection connect = null;
	private static Statement statement = null;
	private static ResultSet resultSet = null;
	
	private static void writeResultSet(ResultSet resultSet) throws SQLException {
		
		// ResultSet is Before the First Data Set
		while (resultSet.next()) {
			
			// Declare Columns Based on SQL Database
			String ArticleTitle = resultSet.getString("ArticleTitle");
			String ArticleID = resultSet.getString("ArticleID");
			String Department = resultSet.getString("Department");
			Date CloseDate = resultSet.getDate("CloseDate");
			String WinningBid = resultSet.getString("WinningBid");
			String InventoryID = resultSet.getString("InventoryID");
			String VehicleID = resultSet.getString("VehicleID");
			String ReceiptNumber = resultSet.getString("ReceiptNumber");
			String Fund = resultSet.getString("Fund");
			
			// Define How Each Item Will Be Printed
			System.out.println("Article Title: " + ArticleTitle);
			System.out.println("Article ID: " + ArticleID);
			System.out.println("Department: " + Department);
			System.out.println("Close Date: " + CloseDate);
			System.out.println("WinningBid: $" + WinningBid);
			System.out.println("Inventory ID: " + InventoryID);
			System.out.println("Vehicle ID: " + VehicleID);
			System.out.println("Receipt Number: " + ReceiptNumber);
			System.out.println("Fund: " + Fund);
			
		}
	}
	
	// Main Method Contains While Loop
	 public static void main(String[] args) throws Exception {
		 	while (true) {
		 		Database();
		 	}
	 }
	 
	 public static void Database () throws Exception {
			try {
				
				// This Loads the MySQL Driver
				Class.forName("com.mysql.cj.jdbc.Driver");
				
				// Setup Connection With the Database
				connect = DriverManager.getConnection("jdbc:mysql://localhost/sales?"
						+ "user=root&password=Password");
				
				// Statements Allow to Issue SQL Queries to the Database
				statement = connect.createStatement();
		 @SuppressWarnings("resource")
		 
		// System.in is a Standard Input Stream  
		Scanner sc = new Scanner(System.in);
		 
		 System.out.println("Hello, Welcome to the 2016 Monthly Sales Database Application! ");
		 System.out.println("Menu ");
		 System.out.println("1: View All Database Entries.");
		 System.out.println("2: Search Database");
		 System.out.println("3: Remove Entry from Database");
		 System.out.println("4: Exit Program");
		 System.out.println("Please Enter Your Choice: ");
		 
		 int Choice  = sc.nextInt();
		 
		 // Switch Case for User Selected Choice
		 switch (Choice) {
		 
		 // Lists All Entries
		 case 1: System.out.println("Here Are All Entries Printed: ");
		 System.out.println("");
		 
			// Get the Result of the SQL Query
			resultSet = statement.executeQuery("select * from sales.2016sales");
			writeResultSet(resultSet);
		return;
		 
		 
		// Allows User to Select How They Want to Search the Database
		 case 2: sc.nextLine();
			 System.out.println("How Would You Like to do Your Search? (1. Department, 2. Date, or 3. Vehicles)");
		 		int searchChoice = sc.nextInt();
		 		
		 		// Switch Case for User Selected Search Choice
		 		switch (searchChoice) {
		 		
		 		// Allows User to Search via Department
		 		case 1:  sc.nextLine();
		 		System.out.println("What Department Would You Like To Search For? (Must be in ALL CAPS)");
		 		String departmentSelection = sc.nextLine();
		 		System.out.println("Here is the results from that Department: ");
		 		 System.out.println("");
		 		 
				// Get the Result of the SQL Query
				resultSet = statement.executeQuery("select * from sales.2016sales where Department = '" + departmentSelection + "'");
				writeResultSet(resultSet);
				break;
				
				// Allows User to Search Via Date
		 		case 2: sc.nextLine();
		 		System.out.println("What Date Would You Like To Search For? (Must be in YYYY-MM-DD Format)");
		 		String dateSelection = sc.nextLine();
		 		System.out.println("Here is the results from that Date: ");
		 		 System.out.println("");
		 		 
		 		// Get the Results of the SQL Query
		 		resultSet = statement.executeQuery("select * from sales.2016sales where CloseDate = '" + dateSelection + "'");
		 		writeResultSet(resultSet);
		 		break;
		 		
		 		// Displays to User Entries Involving Vehicles
		 		case 3: sc.nextLine();
		 		System.out.println("Here is all Bids Involving Vehicles:");
		 		 System.out.println("");
		 		 
		 		// Get the Results of the SQL Query
		 		resultSet = statement.executeQuery("select * from sales.2016sales where VehicleID != ''");
		 		writeResultSet(resultSet);
		 		break;
		 		
		 		// If There is an Incorrect Selection
		 		default: System.out.println("Incorrect Selection, Please Try Again!");
		 		return;
		 		}
			 	
		 return;
		 
		 // Allows User to Delete Item From Database
		 case 3: sc.nextLine();
		 
			 	System.out.println("What Specific Item Would You Like to Remove?");
		 		String itemSelection = sc.nextLine();
		 		
		 		// Create String to Include SQL Query, Then Execute That Query
				String del = "delete from sales.2016sales where ArticleTitle = '" + itemSelection + "'";
				PreparedStatement prepState = connect.prepareStatement(del);
				
				prepState.execute();
				
				System.out.println("");
				
				// Any Item Will be Displayed Regardless if it Truly is in the Database or Not
				System.out.println(itemSelection + " Has Been Removed From the Database");
		 return;
		 
		 // Exit Statement
		 case 4: System.out.println("Thank you!");
		 System.exit(0);
		 break;
		 
		 // If There is an Incorrect Selection
		 default: System.out.println("Incorrect Choice! Please Try Again! ");
		 return;
		 }
			}
			catch (Exception e) {
				throw e;
			} finally {
				close();
			}
	 }
	 
	 
		// resultSet Needs to be Closed
		private static void close() {
			try {
				if (resultSet != null) {
					resultSet.close();
				}
				
				if (statement != null) {
					statement.close();
				}
				
				if (connect != null) {
					connect.close();
				}
			} catch(Exception e) {
			
			}
		
	 }
	 }

	 

